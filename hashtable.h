#pragma once

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef uint64_t(hash) (const char*, size_t);
typedef struct _hashtable hashtable;
typedef void cleanupfunction(void*);

hashtable* hash_table_create(uint64_t size, hash* hf,cleanupfunction* cleanup);
void hash_table_destroy(hashtable* ht);
void hash_table_print(hashtable* ht);
bool hash_table_insert(hashtable* ht, const char* key, void* obj);
void* hash_table_lookup(hashtable* ht, const char* key);
void* hash_table_delete(hashtable* ht, const char* key);

