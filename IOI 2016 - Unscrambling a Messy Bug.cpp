/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2016 - Unscrambling a Messy Bug
        
        Category: Divide and Conquer
        
        Keys: Constructive Algorithms
        
*/

#include <bits/stdc++.h>
#include "messy.h"

using namespace std;

void go (int n, int l, int r) {
	if (l + 1 == r) return;
	int m = l + r >> 1;
	string s = "";
	for (int i = 0; i < n; ++i) {
		s += '1';
	}
	for (int i = l; i < r; ++i) {
		s[i] = '0';
	}
	for (int i = l; i < m; ++i) {
		s[i] = '1';
		add_element(s);
		s[i] = '0';
	}
	go(n, l, m);
	go(n, m, r);
}

vector <int> v;

void kill (int n, int l, int r, string no) {
	if (l + 1 == r) {
		for (int i = 0; i < n; ++i) {
			if (no[i] == '0') {
				v[i] = l;
				break;
			}
		}
		return;
	}
	string x = no, y = "";
	for (int i = 0; i < n; ++i) {
		y += '1';
	}
	for (int i = 0; i < n; ++i) {
		if (no[i] == '0') {
			no[i] = '1';
			if (check_element(no)) {
				x[i] = '1';
				y[i] = '0';
			}
			no[i] = '0';
		}
	}
	int m = l + r >> 1;
	kill(n, l, m, y);
	kill(n, m, r, x);
}

vector <int> restore_permutation (int n, int w, int r) {
	go(n, 0, n);
	compile_set();
	v.resize(n);
	string s = "";
	for (int i = 0; i < n; ++i) {
		s += '0';
	}
	kill(n, 0, n, s);
	return v;
}

