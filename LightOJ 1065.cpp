/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1065 - Number Sequence

        Category - Mathematics, Linear Algebra

        Keys: Matrix Exponentiation, Big Mod

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (int)1e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007

i64 T, a, b, n, m, k, Result[3][3], Val;

void Mat_Mult (i64 A[][3], i64 B[][3], i64 Prod[][3]) {
    Prod[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % m;
    Prod[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % m;
    Prod[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % m;
    Prod[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % m;
}

void Mat_Exp (i64 X[][3], i64 Ret[][3], i64 n) {
    i64 Temp[3][3];
    Ret[0][0] = 1, Ret[0][1] = 0;
    Ret[1][0] = 0, Ret[1][1] = 1;
    while (n) {
        if (n & 1) {
            Mat_Mult(Ret, X, Temp);
            Ret[0][0] = Temp[0][0], Ret[0][1] = Temp[0][1];
            Ret[1][0] = Temp[1][0], Ret[1][1] = Temp[1][1];
        }
        Mat_Mult(X, X, Temp);
        X[0][0] = Temp[0][0], X[0][1] = Temp[0][1];
        X[1][0] = Temp[1][0], X[1][1] = Temp[1][1];
        n = n >> 1;
    } return;
}

void Kill (void) {
    scanf("%lld", &T);
    for (k = 1; k <= T; k++) {
        scanf("%lld %lld %lld %lld", &a, &b, &n, &m);
        m = pow(10, m);
        printf("Case %lld: ", k);
        if (n == 0) printf("%lld\n", a);
        else if (n == 1) printf("%lld\n", b);
        else {
            i64 Base[3][3] = {{1, 1}, {1, 0}};
            Mat_Exp(Base, Result, n);
            Val = b * Result[1][0] + a * Result[1][1];
            printf("%lld\n", Val % m);
        }
    }
}

int main () {
    Kill();
    return 0;
}
