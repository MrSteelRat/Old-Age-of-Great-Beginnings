#include "cache_lru.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "linux-utils/list.h"
#include "linux-utils/rbtree.h"

// Cache node structure
struct cache_node {
  int key;
  int value;
  struct rb_node rb_node;     // Red-black tree node
  struct list_head lru_list;  // Doubly linked list node
};

// LRU Cache structure
struct cache_lru {
  int capacity;
  int size;
  struct rb_root rb_root;     // Root of the red-black tree
  struct list_head lru_head;  // Head of the LRU list
};

// Helper function for searching a key in the RB tree
static struct cache_node* cache_lru_find(struct cache_lru* cache, int key) {
  struct rb_node* node = cache->rb_root.rb_node;
  while (node) {
    struct cache_node* data = rb_entry(node, struct cache_node, rb_node);
    if (key < data->key)
      node = node->rb_left;
    else if (key > data->key)
      node = node->rb_right;
    else
      return data;
  }
  return NULL;
}

// Add a new node to the RB tree
static void cache_lru_add_rb(
  struct cache_lru* cache, struct cache_node* new_node) {
  struct rb_node **link = &cache->rb_root.rb_node, *parent = NULL;
  while (*link) {
    struct cache_node* data = rb_entry(*link, struct cache_node, rb_node);
    parent = *link;
    if (new_node->key < data->key)
      link = &(*link)->rb_left;
    else
      link = &(*link)->rb_right;
  }
  rb_link_node(&new_node->rb_node, parent, link);
  rb_insert_color(&new_node->rb_node, &cache->rb_root);
}

// Remove a node from the RB tree
static void cache_lru_remove_rb(
  struct cache_lru* cache, struct cache_node* node) {
  rb_erase(&node->rb_node, &cache->rb_root);
}

// Create a new LRU cache
struct cache_lru* cache_lru_create(int capacity) {
  struct cache_lru* cache = malloc(sizeof(struct cache_lru));
  cache->capacity = capacity;
  cache->size = 0;
  cache->rb_root = RB_ROOT;
  INIT_LIST_HEAD(&cache->lru_head);
  return cache;
}

// Destroy the LRU cache
void cache_lru_destroy(struct cache_lru** cache) {
  struct cache_node* node;
  struct list_head *pos, *tmp;
  list_for_each_safe(pos, tmp, &(*cache)->lru_head) {
    node = list_entry(pos, struct cache_node, lru_list);
    list_del(pos);
    cache_lru_remove_rb(*cache, node);
    free(node);
  }
  free(*cache);
  *cache = NULL;
}

// Put a key-value pair in the cache
void cache_lru_put(struct cache_lru* cache, int key, int value) {
  struct cache_node* node = cache_lru_find(cache, key);
  if (node) {
    // Update value and move to front of LRU list
    node->value = value;
    list_del(&node->lru_list);
    list_add(&node->lru_list, &cache->lru_head);
  } else {
    // If the cache is full, evict the least recently used item
    if (cache->size >= cache->capacity) {
      struct list_head* lru_tail = cache->lru_head.prev;
      node = list_entry(lru_tail, struct cache_node, lru_list);
      list_del(lru_tail);
      cache_lru_remove_rb(cache, node);
      free(node);
      cache->size--;
    }
    // Add new node to the cache
    node = malloc(sizeof(struct cache_node));
    node->key = key;
    node->value = value;
    cache_lru_add_rb(cache, node);
    list_add(&node->lru_list, &cache->lru_head);
    cache->size++;
  }
}

// Get a value by key from the cache
int cache_lru_get(struct cache_lru* cache, int key) {
  struct cache_node* node = cache_lru_find(cache, key);

  if (node) {
    // Move to front of LRU list
    list_del(&node->lru_list);
    list_add(&node->lru_list, &cache->lru_head);
    return node->value;
  } else {
    return -1;  // Key not found
  }
}
