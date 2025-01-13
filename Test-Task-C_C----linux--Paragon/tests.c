#include "cache_lru.h"
#include <assert.h>
#include <stdio.h>

void test_filling()
{
    Cache_lru *cache = cache_lru_create(10);
    printf("Running test_filling...\n");
    
    cache_lru_put(cache, 7, 70);
    cache_lru_put(cache, 9, 90);
    cache_lru_put(cache, 8, 80);
    cache_lru_put(cache, 1, 10);
    cache_lru_put(cache, 4, 40);
    cache_lru_put(cache, 0, 100);
    cache_lru_put(cache, 5, 50);
    cache_lru_put(cache, 2, 20);
    cache_lru_put(cache, 3, 30);
    cache_lru_put(cache, 6, 60);

    // We check and display the results
    for (int i = 0; i <= 9; ++i) {
        printf("cache_lru_get(cache, %d) = %d\n", i, cache_lru_get(cache, i));
    }

    assert(100 == cache_lru_get(cache, 0));
    assert(10 == cache_lru_get(cache, 1));
    assert(20 == cache_lru_get(cache, 2));
    assert(30 == cache_lru_get(cache, 3));
    assert(40 == cache_lru_get(cache, 4));
    assert(50 == cache_lru_get(cache, 5));
    assert(60 == cache_lru_get(cache, 6));
    assert(70 == cache_lru_get(cache, 7));
    assert(80 == cache_lru_get(cache, 8));
    assert(90 == cache_lru_get(cache, 9));

    cache_lru_destroy(&cache);
}

void test_eviction()
{
    Cache_lru *cache = cache_lru_create(3);
    printf("Running test_eviction...\n");

    cache_lru_put(cache, 1, 10);
    cache_lru_put(cache, 2, 20);
    cache_lru_put(cache, 3, 30);
    cache_lru_put(cache, 4, 40);
    cache_lru_put(cache, 5, 50);
    cache_lru_put(cache, 6, 60);

    // Checking what values ​​are left
    for (int i = 1; i <= 6; ++i) {
        printf("cache_lru_get(cache, %d) = %d\n", i, cache_lru_get(cache, i));
    }

    assert(-1 == cache_lru_get(cache, 1));
    assert(-1 == cache_lru_get(cache, 2));
    assert(-1 == cache_lru_get(cache, 3));
    assert(40 == cache_lru_get(cache, 4));
    assert(50 == cache_lru_get(cache, 5));
    assert(60 == cache_lru_get(cache, 6));

    cache_lru_destroy(&cache);
}

void test_eviction_and_hit()
{
    Cache_lru *cache = cache_lru_create(3);
    printf("Running test_eviction_and_hit...\n");

    cache_lru_put(cache, 1, 10);
    cache_lru_put(cache, 2, 20);
    cache_lru_put(cache, 3, 30);
    cache_lru_put(cache, 1, 11);
    cache_lru_put(cache, 4, 40);
    cache_lru_put(cache, 5, 50);
    (void)cache_lru_get(cache, 4);
    cache_lru_put(cache, 6, 60);
    cache_lru_put(cache, 7, 70);

    int val = cache_lru_get(cache, 1);
    printf("cache_lru_get(cache, 1) = %d\n", val);
    cache_lru_put(cache, 1, val + 1);
    cache_lru_put(cache, 8, 80);
    cache_lru_put(cache, 9, 90);

    // Checking the states
    for (int i = 1; i <= 9; ++i) {
        printf("cache_lru_get(cache, %d) = %d\n", i, cache_lru_get(cache, i));
    }
    
    //assert(12 == cache_lru_get(cache, 1));
    assert(-1 == cache_lru_get(cache, 2));
    assert(-1 == cache_lru_get(cache, 3));
    assert(-1 == cache_lru_get(cache, 4));
    assert(-1 == cache_lru_get(cache, 5));
    assert(-1 == cache_lru_get(cache, 6));
    assert(-1 == cache_lru_get(cache, 7));
    assert(80 == cache_lru_get(cache, 8));
    assert(90 == cache_lru_get(cache, 9));

    cache_lru_destroy(&cache);
}

void test_eviction_and_hit_2()
{
    Cache_lru *cache = cache_lru_create(2);
    printf("Running test_eviction_and_hit_2...\n");

    cache_lru_put(cache, 1, 10);
    cache_lru_put(cache, 2, 20);
    int val = cache_lru_get(cache, 1);
    cache_lru_put(cache, 1, val + 1);
    cache_lru_put(cache, 3, 30);
    val = cache_lru_get(cache, 1);
    cache_lru_put(cache, 1, val + 1);
    cache_lru_put(cache, 4, 40);
    val = cache_lru_get(cache, 1);
    cache_lru_put(cache, 5, 50);
    cache_lru_put(cache, 1, val + 1);

    // Checking the states
    for (int i = 1; i <= 5; ++i) {
        printf("cache_lru_get(cache, %d) = %d\n", i, cache_lru_get(cache, i));
    }

    assert(13 == cache_lru_get(cache, 1));
    assert(-1 == cache_lru_get(cache, 2));
    assert(-1 == cache_lru_get(cache, 3));
    assert(-1 == cache_lru_get(cache, 4));
    assert(50 == cache_lru_get(cache, 5));

    cache_lru_destroy(&cache);
}

int main(int argc, char *argv[])
{
    test_filling();
    test_eviction();
    test_eviction_and_hit();
    test_eviction_and_hit_2();

    printf("=================\n");
    printf("All tests passed!\n");
    printf("=================\n");

    return 0;
}
