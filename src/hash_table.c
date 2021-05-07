#include "hash_table.h"
#include <string.h>
#include "stdlib.h"
#include "stdio.h"
#include "math.h"


static Ht_Item *New_Ht_Item(const char *key,
                            const char *val) {
    Ht_Item *item = (Ht_Item *)malloc(sizeof(Ht_Item));
    item->key = strndup(key, strlen(key));
    item->value = strndup(val, strlen(val));
    return item;
}

Hash_Table *HashTable_New() {
    Hash_Table *ht = (Hash_Table *)malloc(sizeof(Hash_Table));
    ht->cap = 53;
    ht->len = 0;
    ht->items = calloc(ht->cap, sizeof(Ht_Item *));
    return ht;
}

void Del_Ht_Item(Ht_Item *item) {
    free(item->key);
    free(item->value);
    free(item);
}

void HashTable_Del(Hash_Table *ht) {
    for (int i = 0; i < ht->cap; i++) {
        Ht_Item *item = ht->items[i];
        if (item != NULL && item != &deleted_item)
            Del_Ht_Item(item);
    }
    free(ht->items);
    free(ht);
}

void HashTable_Print(Hash_Table *ht) {
    for (int i = 0; i < ht->cap; i++) {
        Ht_Item *item = ht->items[i];
        if (item != NULL && item != &deleted_item) {
            fprintf(stdout, "%s => %s\n", item->key, item->value);
        }
    }
}

int hash(const char *str,
         const int prime,
         const int nbuckets) {
    long hash_val = 0;
    const size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        hash_val += (long) pow(prime, (double)len - i + 1) *  str[i];
        hash_val %= nbuckets;
    }
    return (int) hash_val;
}

int double_hash(const char *str,
                const int nbuckets,
                const int attempt) {
    const int first_hash = hash(str, 129, nbuckets);
    const int second_hash = hash(str, 131, nbuckets);
    return (first_hash + (attempt * (second_hash + 1))) % nbuckets;
}

void HashTable_Insert(Hash_Table *ht,
                      const char *key,
                      const char *val) {
    int i = 0;
    int hash = double_hash(key, ht->cap, i);
    Ht_Item *item= New_Ht_Item(key, val);
    Ht_Item *cur_item = ht->items[hash];
    while (cur_item != NULL) {
        if (cur_item != &deleted_item) {
            if (strcmp(cur_item->key, key) == 0) {
                Del_Ht_Item(cur_item);
                ht->items[hash] = item;
                return;
            }
        }
        hash = double_hash(key, ht->cap, ++i);
        item = ht->items[hash];
    }
    ht->items[hash] = item;
    ht->len++;
}

char *HashTable_Find(Hash_Table *ht, const char *key) {
    int i = 0;
    int hash = double_hash(key, ht->cap, i);
    Ht_Item *item = ht->items[hash];
    while (item != NULL) {
        if (item != &deleted_item) {
            if (strcmp(item->key, key) == 0)
                return item->value;
        }
        hash = double_hash(key, ht->cap, ++i);
        item = ht->items[hash];
    }
    return NULL;
}


void HashTable_DeleteItem(Hash_Table *ht, const char *key) {
    int i = 0;
    int hash = double_hash(key, ht->cap, i);
    Ht_Item *item = ht->items[hash];
    while (item != NULL) {
        if (item != &deleted_item) {
            if (strcmp(item->key, key) == 0) {
                Del_Ht_Item(item);
                ht->items[hash] = &deleted_item;
            }
        }
        hash = double_hash(key, ht->cap, ++i);
        item = ht->items[hash];
    }
    ht->len--;
}