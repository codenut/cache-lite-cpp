#include <gtest/gtest.h>
#include "PerpetualCache.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(PerpetualCache, test_set_get_present)
{
    PerpetualCache<string, int> cache;

    cache.set("key", 2);
    EXPECT_EQ(2, cache.get("key"));
}

TEST(PerpetualCache, test_set_get_absent)
{
    PerpetualCache<string, int> cache;

    try {
        cache.remove("key");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(PerpetualCache, test_remove_present)
{
    PerpetualCache<string, int> cache;

    cache.set("key", 2);
    cache.remove("key");

    try {
        cache.get("key");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(PerpetualCache, test_remove_absent)
{
    PerpetualCache<string, int> cache;

    cache.set("key", 2);
    cache.remove("absent");

    EXPECT_EQ(2, cache.get("key"));
}

TEST(PerpetualCache, test_clear)
{
    PerpetualCache<string, int> cache;

    cache.set("key", 2);
    EXPECT_EQ(2, cache.get("key"));
    cache.clear();

    try {
        cache.get("key");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(PerpetualCache, test_pointer_key)
{
    PerpetualCache<string, int> cache;

    string key = "key";
    string *keyPtr = &key;

    cache.set(*keyPtr, 2);
    EXPECT_EQ(2, cache.get(*keyPtr));

    key = "abc";
    try {
        // cache key is still "key" as unordered maps
        // creates a copy as a key
        cache.get(*keyPtr);
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(PerpetualCache, test_pointer_value)
{
    PerpetualCache<string, int> cache;

    string key = "key";
    string *keyPtr = &key;

    int val = 1;
    int *valPtr = &val;

    cache.set(*keyPtr, *valPtr);
    EXPECT_EQ(1, cache.get(*keyPtr));

    val = 3;
    // still 1 because unordered maps stored a copy of the value
    EXPECT_EQ(1, cache.get(*keyPtr));
}

TEST(PerpetualCache, test_pointer_type)
{
    PerpetualCache<string *, int *> cache;

    string key = "key";
    string *keyPtr = &key;

    int val = 1;
    int *valPtr = &val;

    cache.set(keyPtr, valPtr);
    EXPECT_EQ(1, *cache.get(keyPtr));

    val = 3;
    EXPECT_EQ(3, *cache.get(keyPtr));

    key = "abc";
    EXPECT_EQ(3, *cache.get(keyPtr));
}
