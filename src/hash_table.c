#include "hash_table.h"
#include <string.h>
#include "stdlib.h"
#include "math.h"


static Ht_Item *New_Ht_Item(const char *key, const char *val) {
    Ht_Item *item = (Ht_Item *)malloc(sizeof(Ht_Item));
    item->key = strndup(key, strlen(key));
    item->value = strndup(val, strlen(val));
    return item;
}

Hash_Table *New_Hash_Table() {
    Hash_Table *ht = (Hash_Table *)malloc(sizeof(Hash_Table));
    ht->len = 53;
    ht->cap = 0;
    ht->items = calloc(ht->len, sizeof(Ht_Item *));
    return ht;
}

void Del_Ht_Item(Ht_Item *item) {
    free(item->key);
    free(item->value);
    free(item);
}

void Del_Hash_Table(Hash_Table *ht) {
    for (int i = 0; i < ht->len; i++) {
        Ht_Item *item = ht->items[i];
        if (item != NULL)
            Del_Ht_Item(item);
    }
    free(ht->items);
    free(ht);
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