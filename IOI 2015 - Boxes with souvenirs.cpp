/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2015 - Boxes with souvenirs
        
        Category: Ad hoc
        
        Keys: Observation, Constructive Algorithms
        
*/

#include <bits/stdc++.h>
#include "boxes.h"

using namespace std;

vector <long long> costLeft;
vector <long long> costRight;

long long delivery (int N, int K, int L, int p[]) {
  int mid = L >> 1;
  for (int i = 0; i < N; ++i) {
    if (p[i] > mid) {
      costRight.push_back(2LL * (L - p[i]));
    } else {
      costLeft.push_back(2LL * p[i]);
    }
  }
  reverse(costRight.begin(), costRight.end());
  int sizeLeft = (int) costLeft.size();
  int sizeRight = (int) costRight.size();
  for (int i = K; i < sizeLeft; ++i) {
    costLeft[i] += costLeft[i - K];
  }
  for (int i = K; i < sizeRight; ++i) {
    costRight[i] += costRight[i - K];
  }
  long long leftCost = sizeLeft ? costLeft[sizeLeft - 1] : 0;
  long long rightCost = sizeRight ? costRight[sizeRight - 1] : 0;
  long long ret = leftCost + rightCost;
  for (int i = 0; i <= K; ++i) {
    int leftTaken = i, rightTaken = K - i;
    long long left = leftTaken >= sizeLeft ? 0 : costLeft[sizeLeft - 1 - leftTaken];
    long long right = rightTaken >= sizeRight ? 0 : costRight[sizeRight - 1 - rightTaken];
    ret = min(ret, L + left + right);
  }
  return ret;
}

