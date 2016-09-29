/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	TopCoder - BipartiteConstruction
    	
    	Category: Mathematics
    	
    	Keys: Constructive Algorithm, Combinatorics
    	
*/

#include <bits/stdc++.h>

using namespace std;

class BipartiteConstruction {public: vector <int> construct (int K);};

const int n = 20;

vector <int> BipartiteConstruction :: construct (int K) {
    vector <int> edges;
    edges.push_back(n);
    
    for (int i = n - 1; i; --i) {
	edges.push_back(i * n + i);
	for (int j = 0; j < 3; ++j) edges.push_back(i * n + i - 1);
    }

    int node = 0; while (K) {
	int r = K % 3;
	K /= 3;
	for (int i = 0; i < r; ++i) edges.push_back(node);
	++node;
    }    

    return edges;
}

