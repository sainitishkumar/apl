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
    vector<int> newarr;
    while(t>0) {
        // cin>> n>> m>> x;
        scanf("%d %d %d", &n, &m, &x);
        newarr.assign(n+2, 0);
        
        /*
            get the left and right indices of the range of sprinkler for all m sprinklers
            then add one to left index of the arr, subtract one from the right+1 index of the array
            when we perform the prefix sum operation on the resultant array,
            we can find the areas where sprinklers can't reach
        */
        
        int pos = 0;
        for(int i=0; i<m; i++) {
            // cin>> pos;
            scanf("%d", &pos);
            
            int leftIndex = (pos - x <= 0) ? 1 : pos - x;
            int rightIndex = (pos + x > n) ? n : pos + x;
            
            newarr[leftIndex] += 1;
            newarr[rightIndex+1] -= 1;
        }
        
        int count = 0;
        
        // counting with prefix sum to reproduce the final array
        // count+=1 where the arr val is 0
        if(newarr[1] == 0) count+=1;
        for(int i=2; i<=n; i++) {
            newarr[i] += newarr[i-1];
            if(newarr[i] == 0) count+=1;
        }
        // cout<< count<< endl;
        printf("%d\n", count);
        t--;
    }
}