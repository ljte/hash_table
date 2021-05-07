#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "stddef.h"
#include "stdint.h"

typedef struct {
    char *key;
    char *value;
} Ht_Item;

typedef struct {
    size_t len;
    int cap;
    Ht_Item **items;
} Hash_Table;


static Ht_Item *New_Ht_Item(const char *, const char *);
static void Del_Ht_Item(Ht_Item *);
Hash_Table *HashTable_New();
void HashTable_Del(Hash_Table *);
void HashTable_Insert(Hash_Table *, const char *, const char *);
void HashTable_Print(Hash_Table *);
Ht_Item *HashTable_Find(Hash_Table *ht, const char *key);

int hash(const char *, int, int);
int double_hash(const char *, const int, const int);

#endif //HASH_TABLE_H
