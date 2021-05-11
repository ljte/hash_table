#include "src/hash_table.h"
#include "stdio.h"

int main() {
    Hash_Table *ht = HashTable_New();
    HashTable_Insert(ht, "Hello", "World");
    HashTable_Insert(ht, "Some", "Word");
    HashTable_DeleteItem(ht, "Some");
    HashTable_Insert(ht, "Kwa", "Dima");
    HashTable_Insert(ht, "Cool", "Dima");
    HashTable_Insert(ht, "Swag", "Dima");
    HashTable_Print(ht);
    fprintf(stdout, "LEN: %ld CAP: %d\n", ht->len, ht->cap);
    HashTable_Del(ht);
    return 0;
}
