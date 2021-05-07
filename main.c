#include "src/hash_table.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main() {
    srand(time(NULL));
    Hash_Table *ht = HashTable_New();
    HashTable_Insert(ht, "Hello", "World");
    HashTable_Print(ht);
    Ht_Item *item = HashTable_Find(ht, "Hello");
    fprintf(stdout, "LEN: %ld CAP: %d\n", ht->len, ht->cap);
    if (item != NULL)
        fprintf(stdout, "ITEM: %s | %s", item->key, item->value);
    else
        printf("NULL\n")
    HashTable_Del(ht);
    return 0;
}
