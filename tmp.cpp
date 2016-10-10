#include <bits/stdc++.h>

using namespace std;

const int N = 305;
const int MOD = 1e9 + 7;

struct polynomial {
    int deg;
    long long coeff[N];

    // assuming deg f >= deg g
    polynomial operator / (polynomial f, polynomial g) {
        polynomial h;
        
    }
};

int t, n, q;
long long p[N];
polynomial f;

long long bigMod (long long a, long long e) {
    long long r = 1;
    e += (MOD - 1), e %= (MOD - 1), a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}



polynomial gcd (polynomial f, polynomial g) {
    if ()
}

int main (int argc, char const *argv[]) {
    scanf("%d", &t); while (t--) {
        scanf("%d %d", &n, &q);
        for (int i = 1; i <= n; ++i) scanf("%lld", p + i);
        f.deg = n, f.coeff[n] = 1;

        for (int i = n - 1; i >= 0; --i) {
            f.coeff[i] = 0;
            for (int j = n, k = n - i; k; --j, --k) {
                f.coeff[i] -= p[k] * f.coeff[j];
                f.coeff[i] %= MOD;
            }
            f.coeff[i] *= bigMod(n - i, - 1), f.coeff[i] %= MOD;
        }


    }
    return 0;
}
