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
Hash_Table *New_Hash_Table();
void Del_Hash_Table(Hash_Table *);

int hash(const char *, int, int);

#endif //HASH_TABLE_H
