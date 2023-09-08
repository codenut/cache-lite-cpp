#include <unordered_map>
#include "GenericCache.h"

// TODO: Implement LRU Cache

using namespace std;

template<typename K, typename V>
class PerpetualCache : public GenericCache<K, V>
{
public:
    void set(const K &key, const V &value);

    V &get(const K &key);

    void remove(const K &key);

    void clear();

private:
    bool exists(const K &key);

    unordered_map<K, V> cache;
};

template<typename K, typename V>
void PerpetualCache<K, V>::set(const K &key, const V &value)
{
    this->cache[key] = value;
}

template<typename K, typename V>
V &PerpetualCache<K, V>::get(const K &key)
{
    if (!this->exists(key)) {
        throw std::invalid_argument("Unknown key!");
    }
    return this->cache[key];
}

template<typename K, typename V>
void PerpetualCache<K, V>::remove(const K &key)
{
    this->cache.erase(key);
}

template<typename K, typename V>
void PerpetualCache<K, V>::clear()
{
    this->cache.clear();
}

template<typename K, typename V>
bool PerpetualCache<K, V>::exists(const K &key)
{
    return this->cache.find(key) != this->cache.end();
}
