#include <gtest/gtest.h>
#include "PerpetualCache.hpp"

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

    try
    {
        cache.remove("key");
    }
    catch (invalid_argument const & err)
    {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}

TEST(PerpetualCache, test_remove_present)
{
    PerpetualCache<string, int> cache;

    cache.set("key", 2);
    cache.remove("key");

    try
    {
        cache.get("key");
    }
    catch (invalid_argument const & err)
    {
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

    try
    {
        cache.get("key");
    }
    catch (invalid_argument const & err)
    {
        EXPECT_EQ(err.what(), string("Unknown key!"));
    }
}