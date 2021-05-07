#include "src/hash_table.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main() {
    srand(time(NULL));
    Hash_Table *ht = HashTable_New();
    HashTable_Insert(ht, "Hello", "World");
    HashTable_Insert(ht, "Some", "Word");
    HashTable_DeleteItem(ht, "Hello");
    HashTable_Insert(ht, "Some", "Dima");
    HashTable_Print(ht);
    fprintf(stdout, "LEN: %ld CAP: %d\n", ht->len, ht->cap);
    HashTable_Del(ht);
    return 0;
}
