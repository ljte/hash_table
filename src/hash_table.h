#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "stddef.h"

typedef struct {
    char *key;
    char *value;
} Ht_Item;

static Ht_Item deleted_item = {NULL, NULL};

typedef struct {
    size_t len;
    int base_size;
    int cap;
    Ht_Item **items;
} Hash_Table;

#define HT_BASE_SIZE 50

static Ht_Item *New_Ht_Item(const char *, const char *);
static void Del_Ht_Item(Ht_Item *);
Hash_Table *HashTable_New();
static Hash_Table *HT_New(int);
void HashTable_Del(Hash_Table *);
void HashTable_Insert(Hash_Table *, const char *, const char *);
void HashTable_Print(Hash_Table *);
char *HashTable_Find(Hash_Table *, const char *);
void HashTable_DeleteItem(Hash_Table *, const char *);
static void HashTable_Resize(Hash_Table *, int);
static void HashTable_ResizeUp(Hash_Table *);
static void HashTable_ResizeDown(Hash_Table *);
static int HashTable_Load(const Hash_Table *);

int hash(const char *, int, int);
int double_hash(const char *, int, int);

#endif //HASH_TABLE_H
