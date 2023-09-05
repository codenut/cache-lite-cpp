#include "GenericCache.hpp"

using namespace std;

template <typename K, typename V>
class ExpirableCache: public GenericCache<K, V>
{
    public:
        void set(K key, V value); 
        V get(K key);
        void remove(K key);
        void clear();
};

template <typename K, typename V>
void ExpirableCache<K, V>::set(K key, V value) 
{
    cout << "set" << endl;
}

template <typename K, typename V>
V ExpirableCache<K, V>::get(K key) 
{

}

template <typename K, typename V>
void ExpirableCache<K, V>::remove(K key) 
{

}

template <typename K, typename V>
void ExpirableCache<K, V>::clear() 
{

}
