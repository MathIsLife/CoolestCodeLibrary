/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        NCPC 2015 - Farey Sequence (UVa 12995)
        
        Category: Mathematics
        
        Keys: Observation, Number Theory
        
*/

#include <bits/stdc++.h> 

using namespace std;

const int N = 1e6 + 10;

int t, n;
long long phiSum[N];

void generate_totient (void) {
	for (int i = 2; i < N; ++i) {
		phiSum[i] = i;
	}
	for (int i = 2; i < N; ++i) {
		if (phiSum[i] == i) {
			for (int j = i; j < N; j += i) {
				phiSum[j] /= i;
				phiSum[j] *= (i - 1);
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		if (phiSum[i] == i) --phiSum[i];
		phiSum[i] += phiSum[i - 1];
	}
}

int main (int argc, char const *argv[]) {
	generate_totient();
	while (scanf("%d", &n) and n) {
    	printf("%lld\n", phiSum[n]);
	}
	return 0;
}

