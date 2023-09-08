#include <list>
#include <unordered_map>
#include "PerpetualCache.h"

using namespace std;

template<typename K, typename V>
class LruCache : public GenericCache<K, V>
{
public:
    explicit LruCache(int capacity);

    void set(const K &key, const V &value);

    V &get(const K &key);

    void remove(const K &key);

    void clear();

private:
    void touch(const K &key);

    void invalidate();

    PerpetualCache<K, pair<V, typename list<K>::iterator>> cache;
    list<K> key_list;

    int capacity{};
    int size = 0;
};

template<typename K, typename V>
LruCache<K, V>::LruCache(const int capacity)
{
    this->capacity = capacity;
}

template<typename K, typename V>
void LruCache<K, V>::set(const K &key, const V &value)
{
    try {
        this->get(key);
    } catch (invalid_argument const &err) {
        key_list.push_back(key);
        this->size += 1;
    }

    cache.set(key, std::make_pair(value, prev(this->key_list.end())));
    invalidate();
}

template<typename K, typename V>
V &LruCache<K, V>::get(const K &key)
{
    this->touch(key);
    return cache.get(key).first;
}

template<typename K, typename V>
void LruCache<K, V>::remove(const K &key)
{
    this->key_list.erase(this->cache.get(key).second);
    cache.remove(key);

    this->size -= 1;
    assert(this->size == this->key_list.size());
}

template<typename K, typename V>
void LruCache<K, V>::clear()
{
    this->cache.clear();
    this->size = 0;
}

template<typename K, typename V>
void LruCache<K, V>::touch(const K &key)
{
    this->key_list.erase(this->cache.get(key).second);
    this->key_list.push_back(key);
    this->cache.get(key).second = prev(this->key_list.end());
}

template<typename K, typename V>
void LruCache<K, V>::invalidate()
{
    if (this->size > this->capacity) {
        auto invalidated_key = key_list.front();
        this->remove(invalidated_key);
    }
}