#include <iostream>
#include "ExpireableCache.hpp"

using namespace std;

int main() 
{
    cout << "hello world" << endl; 

    ExpirableCache<string, int> cache;
    cache.set("key", 0);
}
