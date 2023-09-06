template <typename K, typename V>
class GenericCache
{
public:
    virtual void set(const K& key, const V& value) = 0;
    virtual V& get(const K& key) = 0;
    virtual void remove(const K& key) = 0;
    virtual void clear() = 0;
};
