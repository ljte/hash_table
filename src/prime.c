#include "prime.h"

int is_prime(int x) {
    if (x < 2) return 0;
    else if (x < 4) return 1;
    else if (x % 2 == 0) return 0;

    for (int i = 3; i < x; i++)
        if (x % i == 0)
            return 0;

    return 1;
}

int next_prime(int x) {
    while (!is_prime(x))
        x++;
    return x;
}
