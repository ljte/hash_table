#include "time.h"
#include "stdio.h"
#include "stdlib.h"


int is_prime(int num) {
    if (num == 0 || num == 1) {
        return 0;
    }
    for (int i = 2; i < num; i ++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int get_prime_larger_than_(int limit) {
    srand(time(NULL));
    int n = rand() + limit;
    return n;
}