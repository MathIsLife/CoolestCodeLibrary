/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        NCPC 2015 - Train Station (UVa 12997)
        
        Category: Mathematics
        
        Keys: Calculus, Numerical Integration
        
*/

#include <bits/stdc++.h> 

using namespace std;

const int MAGIC = 1000;
const long double EPS = 1e-10;

int t, cs = 0;
long double x, a, b, d;

long double at (long double p) {
    long double one = hypot(p, x);
    long double two = hypot(p + d, x);
    long double ret = one * two + d * (one + two) - one * one - p * d;
    return ret/2.0;
}

int main (int argc, char const *argv[]) {
    scanf("%d", &t); while (t--) {
    	scanf("%Lf %Lf %Lf %Lf", &x, &a, &b, &d);
    	a -= d;
    	printf("Case %d: ", ++cs);
    	if (fabs(a - b) < EPS) {
    	    long double ans = at(b)/d;
    	    printf("%0.12f\n", (double) ans);
    	    continue;
    	}
    	long double jump = (a - b)/MAGIC;
    	long double ans = (at(a) + at(b))/2.0;
    	for (int k = 1; k < MAGIC; ++k) {
    	    ans += at(b + k * jump);
    	}
    	ans *= jump, ans /= d, ans /= (a - b);
    	printf("%0.12f\n", (double) ans);
    }
    return 0;
}

