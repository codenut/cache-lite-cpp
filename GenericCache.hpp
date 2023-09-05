template <typename K, typename V>
class GenericCache
{
    public:
        virtual void set(K key, V value) = 0;
        virtual V get(K key) = 0;
        virtual void remove(K key) = 0;
        virtual void clear() = 0;
};
