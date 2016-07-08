/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1392 - Multi Round Matches

        Category: Mathematics

        Keys: Inequality, Bounding, Algebraic Manipulation

*/

#include <bits/stdc++.h>

using namespace std;

int Test, Case = 0;
long long R, T, N;

long long Sum (long long l, long long r) {
    if (l > r) return 0;
    long long a = (r * (r + 1)) >> 1;
    long long b = (l * (l - 1)) >> 1;
    return a - b;
}

int main (int argc, char const *argv[]) {
    scanf("%d", &Test); while (Test--) {
        scanf("%lld %lld %lld", &R, &T, &N);
        printf("Case %d: ", ++Case);

        if (T < R or T > N * R) {
            printf("0\n");
            continue;
        }

        long long low = (N * R - T + N - 2)/(N - 1);
        long long high = (T - R)/(N - 1);

        long long X = N * Sum(1, min(R - 1, high)) + max(0LL, R - high - 1) * (T - R) + Sum(high + 1, R - 1);
        long long Y = Sum(1, min(low - 1, R - 1)) - max(0LL, R - low) * (N * R - T) + N * Sum(low, R - 1);
        long long Answer = X - Y + R - 1;

        printf("%lld\n", Answer);
    }
    return 0;
}

