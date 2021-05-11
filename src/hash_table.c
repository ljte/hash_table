#include "hash_table.h"
#include <string.h>
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "prime.h"

static Ht_Item *New_Ht_Item(const char *key,
                            const char *val) {
    Ht_Item *item = (Ht_Item *)malloc(sizeof(Ht_Item));
    item->key = strndup(key, strlen(key));
    item->value = strndup(val, strlen(val));
    return item;
}

static Hash_Table *HT_New(const int base_size) {
    Hash_Table *ht = (Hash_Table *)malloc(sizeof(Hash_Table));
    ht->base_size = base_size;

    ht->cap = next_prime(base_size);

    ht->len = 0;
    ht->items = calloc(ht->cap, sizeof(Ht_Item *));
    return ht;
}

Hash_Table *HashTable_New() {
    return HT_New(HT_BASE_SIZE);
}

static int HashTable_Load(const Hash_Table *ht) {
    return (int) (ht->len * 100 / ht->cap);
}

static void HT_Item_Print(Ht_Item *item) {
    fprintf(stdout, "%s => %s\n", item->key, item->value);
}

void HashTable_Print(Hash_Table *ht) {
    for (int i = 0; i < ht->cap; i++) {
        Ht_Item *item = ht->items[i];
        if (item != NULL && item != &deleted_item) {
            HT_Item_Print(item);
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

#define FIRST_PRIME 129
#define SECOND_PRIME 131

int double_hash(const char *str,
                const int nbuckets,
                const int attempt) {
    const int first_hash = hash(str, FIRST_PRIME, nbuckets);
    const int second_hash = hash(str, SECOND_PRIME, nbuckets);
    return (first_hash + (attempt * (second_hash + 1))) % nbuckets;
}

static void HashTable_Resize(Hash_Table *ht, const int new_base) {
    if (new_base < HT_BASE_SIZE) return;

    Hash_Table *new_ht = HT_New(new_base);
    for (int i = 0; i < ht->cap; i++) {
        Ht_Item *item = ht->items[i];
        if (item != NULL && item != &deleted_item)
            HashTable_Insert(new_ht, item->key, item->value);
    }

    ht->base_size = new_ht->base_size;
    ht->len = new_ht->len;

    const int cap = ht->cap;
    ht->cap = new_ht->cap;
    new_ht->cap = cap;

    Ht_Item **items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = items;

    HashTable_Del(new_ht);
}

static void HashTable_ResizeUp(Hash_Table *ht) {
    const int new_base = ht->cap * 2;
    return HashTable_Resize(ht, new_base);
}

static void HashTable_ResizeDown(Hash_Table *ht) {
    const int new_base = ht->cap / 2;
    return HashTable_Resize(ht, new_base);
}

void HashTable_Insert(Hash_Table *ht,
                      const char *key,
                      const char *val) {
    if (HashTable_Load(ht) > 70)
        HashTable_ResizeUp(ht);
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
        cur_item = ht->items[hash];
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
    if (HashTable_Load(ht) < 10)
        HashTable_ResizeDown(ht);
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

void Del_Ht_Item(Ht_Item *item) {
    free(item->key);
    free(item->value);
    free(item);
    item = NULL;
}

void HashTable_Del(Hash_Table *ht) {
    for (int i = 0; i < ht->cap; i++) {
        Ht_Item *item = ht->items[i];
        if (item != NULL && item != &deleted_item)
            Del_Ht_Item(item);
    }
    free(ht->items);
    free(ht);
    ht = NULL;
}
