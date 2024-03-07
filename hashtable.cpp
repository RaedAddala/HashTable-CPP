#include"./hashtable.h"



typedef struct entry {
    char* key;
    void* obj;
    struct entry* next;
} entry;

struct _hashtable {
    uint64_t size;
    hash* hash;
    cleanupfunction* cleanup;
    entry** elements;
};

static size_t hash_table_index(hashtable* ht, const char* key);


/*
    Default Cleanup is free
*/
hashtable* hash_table_create(uint64_t size, hash* hf, cleanupfunction* cleanup) {
    hashtable* ht = (hashtable*)malloc(sizeof(*ht));
    ht->size = size;
    ht->hash = hf;

    if (cleanup != nullptr)
        ht->cleanup = cleanup;
    else
        ht->cleanup = free;


    ht->elements = (entry**)calloc(sizeof(entry*), ht->size);
    return ht;
}
void hash_table_destroy(hashtable* ht) {
    // free each element
    for (uint32_t i = 0; i < ht->size; i++)
    {
        while (ht->elements[i])
        {
            entry* tmp = ht->elements[i];
            ht->elements[i] = tmp->next;
            ht->cleanup(tmp->obj);
            free(tmp->key);
            free(tmp);
        }

    }

    // free the pointer to the elements
    free(ht->elements);
    // free the hash table
    free(ht);
}
void hash_table_print(hashtable* ht) {
    printf("Start HashTable\n");
    for (uint64_t i = 0; i < ht->size; ++i) {
        if (ht->elements[i] == nullptr) {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t\n", i);
            entry* tmp = ht->elements[i];
            while (tmp != nullptr) {
                printf("\"%s\" (%p) - ", tmp->key, tmp->obj);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }

}
bool hash_table_insert(hashtable* ht, const char* key, void* obj) {
    if (key == nullptr || obj == nullptr || ht == nullptr) return false;
    size_t index = hash_table_index(ht, key);

    if (hash_table_lookup(ht, key) != nullptr) return false;

    // Create a new entry
    entry* e = (entry*)malloc(sizeof(*e));
    e->obj = obj;
    e->key = strdup(key);
    e->next = ht->elements[index];
    ht->elements[index] = e;

    return true;
}
void* hash_table_lookup(hashtable* ht, const char* key) {
    if (key == nullptr || ht == nullptr) return nullptr;
    size_t index = hash_table_index(ht, key);
    entry* tmp = ht->elements[index];
    while (tmp != nullptr && strcmp(tmp->key, key) != 0)
        tmp = tmp->next;

    return tmp != nullptr ? tmp->obj : nullptr;
}
void* hash_table_delete(hashtable* ht, const char* key) {
    if (key == nullptr || ht == nullptr) return nullptr;
    size_t index = hash_table_index(ht, key);

    entry* tmp = ht->elements[index];
    entry* prev = nullptr;

    while (tmp != nullptr && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == nullptr) {
        return nullptr;
    }
    if (prev == nullptr)
    {
        ht->elements[index] = tmp->next;
    }
    else {
        prev->next = tmp->next;
    }
    void* res = tmp->obj;
    free(tmp);
    return res;
}
static size_t hash_table_index(hashtable* ht, const char* key) {
    return (size_t)(ht->hash(key, strlen(key))) % (size_t)(ht->size);
}