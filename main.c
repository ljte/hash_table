#include "src/hash_table.h"
#include "src/utils.h"
#include "stdio.h"

int main() {
    Hash_Table *ht = New_Hash_Table();
    Del_Hash_Table(ht);
    const char str[] = "Hello, world";
    const int prime = get_prime_larger_than_(INT8_MAX);
    printf("%d\n", prime);
    return 0;
}
