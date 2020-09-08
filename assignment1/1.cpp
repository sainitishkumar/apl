#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int t, n, m ,x;
    cin>> t;
    vector<int> ranges;
    while(t>0) {
        cin>> n>> m>> x;
        
        ranges.assign(n+1, 0);
        // int* ranges = new int[n+1];
        // for(int i=0; i<n+1; i++) ranges[i] = 0;
        
        for(int i=0; i<m; i++) {
            int pos;
            cin>> pos;
            int leftIndex = (pos - x <= 0) ? 1 : pos - x;
            int rightIndex = (pos+x <= n) ? pos+x : n;
            ranges[leftIndex] = rightIndex;
        }
        // now count by traversing the array and check where each range ends
        // for(int i=1; i<n+1; i++) cout<< ranges[i]<< " ";
        // cout<< endl;

        int maxval = 0, count = 0;
        for(int i=1; i<n+1; i++) {
            maxval = max(maxval, ranges[i]);
            if(i > maxval) count++;
            else if(i == maxval) maxval = 0;
        }
        cout<< count<< endl;
        t--;
    }
    return 0;
}