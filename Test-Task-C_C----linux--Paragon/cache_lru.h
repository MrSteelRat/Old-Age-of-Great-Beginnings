#ifndef CACHE_LRU_H
#define CACHE_LRU_H

/**
 * Cache_lru - main structure representing the cache
 */
typedef struct cache_lru Cache_lru;

/**
 * cache_lru_create() - Create and initilize the LRU cache with
 * positive @capacity.
 * @capacity: Maximum number of stored items.
 * Return:    Pointer to cache instanse.
 */
Cache_lru *cache_lru_create(int capacity);

/**
 * cache_lru_destroy() - Cache delete function.
 * @cache: Double pointer to Cache_lru created by cache_lru_create().
 */
void cache_lru_destroy(Cache_lru **cache);

/**
 * cache_lru_put() - Update the @value of the @key if the @key exist.
 * Otherwise, add the key-value pair to the cache.
 * If the number of keys exceds the capacity from this operation,
 * evict the less recently used key.
 * @cache: Pointer to Cache_lru created by cache_lru_create().
 * @value: Value.
 * @key:   Key (non-negative).
 */
void cache_lru_put(Cache_lru *cache, int key, int value);

/**
 * cache_lru_put() - Return the value of the @key if the @key exist,
 * otherwice return -1.
 * @cache: Pointer to Cache_lru created by cache_lru_create().
 * @key:   Key (non-negative).
 */
int cache_lru_get(Cache_lru *cache, int key);

#endif /* CACHE_LRU_H */
