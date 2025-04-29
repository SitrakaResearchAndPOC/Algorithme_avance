
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ulong;

ulong mul_mod(ulong a, ulong b, const ulong mod) {
    ulong res = 0, c;
    for (b %= mod; a; a & 1 ? (b >= mod - res ? res -= mod : 0, res += b) : 0, a >>= 1, (c = b) >= mod - b ? c -= mod : 0, b += c);
    return res % mod;
}

ulong pow_mod(ulong n, ulong exp, const ulong mod) {
    ulong res = 1;
    for (n %= mod; exp; exp & 1 ? res = mul_mod(res, n, mod) : 0, n = mul_mod(n, n, mod), exp >>= 1);
    return res;
}

int is_prime(ulong n) {
// AJOUTER POUR PLUSIEURS BASES
//    static const ulong bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};  // Base étendue
      static const ulong bases[] = {2};  // Base étendue

    static const int n_bases = sizeof(bases) / sizeof(bases[0]);

    if (n < 2) return 0;
    for (int i = 0; i < n_bases; ++i)
        if (n % bases[i] == 0)
            return n == bases[i];

    if (n < bases[n_bases - 1] * bases[n_bases - 1])
        return 1;

    int r = 0;
    ulong d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    for (int i = 0; i < n_bases; ++i) {
        ulong a = bases[i];
        ulong x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;

        int is_composite = 1;
        for (int j = 0; j < r - 1; ++j) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                is_composite = 0;
                break;
            }
        }
        if (is_composite) return 0;
    }

    return 1;
}

int main(void) {
    ulong prime_numbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int size_primes = sizeof(prime_numbers) / sizeof(prime_numbers[0]);

    ulong carmichael_numbers[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041};
    int size_carmichael = sizeof(carmichael_numbers) / sizeof(carmichael_numbers[0]);

    printf("Tests de nombres premiers :\n");
    for (int i = 0; i < size_primes; i++) {
        ulong n = prime_numbers[i];
        printf("%llu : ", n);
        if (is_prime(n)) {
            printf("Premier (résultat correct)\n");
        } else {
            printf("Composé (faux négatif impossible)\n");
        }
    }

    printf("\nTests de nombres de Carmichael (faux positifs possibles) :\n");
    for (int i = 0; i < size_carmichael; i++) {
        ulong n = carmichael_numbers[i];
        printf("%llu : ", n);
        if (is_prime(n)) {
            printf("Probablement premier (faux positif)\n");
        } else {
            printf("Composé (résultat correct)\n");
        }
    }

    return 0;
}
