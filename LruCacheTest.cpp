#include <gtest/gtest.h>
#include "LruCache.h"

TEST(LruCache, test_set)
{
    LruCache<string, int> cache(2);
    const string key = "key";
    cache.set(key, 1);

    EXPECT_EQ(1, cache.get(key));

    cache.set("a", 2);
    cache.set("b", 2);

    try {
        cache.get("key");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(LruCache, test_set_with_invalidation)
{
    LruCache<string, int> cache(2);

    cache.set("a", 1);
    cache.set("b", 2);
    cache.set("c", 3);

    EXPECT_EQ(3, cache.get("c"));
    EXPECT_EQ(2, cache.get("b"));

    try {
        cache.get("a");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(LruCache, test_set_with_invalidation_existing_key)
{
    LruCache<string, int> cache(2);

    cache.set("a", 1);
    cache.set("b", 2);
    cache.set("a", 11);
    cache.set("c", 3); // b should be invalidated

    EXPECT_EQ(11, cache.get("a"));
    EXPECT_EQ(3, cache.get("c"));

    try {
        cache.get("b");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }

    cache.remove("a");

    try {
        cache.get("a");
    }
    catch (invalid_argument const &err) {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}
