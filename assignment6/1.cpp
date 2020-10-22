#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// // search for insert position of val in the arr
long long int binarySearchLeft(vector<long long int> &arr, long long int val) {
    long long int low = 0, high = arr.size()-1;
    while (low <= high) {
        long long int mid = (high+low)/2;
        (arr[mid] < val) ? low = mid+1 : high = mid-1;
    }
    return low;
}

long long int binarySearchRight(vector<long long int> &arr, long long int val) {
    long long int low = 0, high = arr.size()-1;
    while (low <= high) {
        long long int mid = (high+low)/2;
        (arr[mid] > val) ? high = mid-1 : low = mid+1;
    }
    return high;
}

long long int recurse(vector<long long int> &arr, long long int low, long long int high, long long int a, long long int b) {
    if(low>high) {
        return 0;
    }
    if(low==high) {
        long long int lowpos = binarySearchLeft(arr, low);
        long long int highpos = binarySearchRight(arr, low);
        if(arr[lowpos]!=low) return a;
        else {
            long long int count=highpos-lowpos+1;
            return b*count;
        }
    }
    long long int mid = (low+high)/2;
    long long int lowPos = binarySearchLeft(arr, low);
    long long int highPos = binarySearchRight(arr, high);

    long long int nz = highPos-lowPos+1;
    long long int val;
    if(nz == 0) {
        return a;
    } else {
        val = nz*b*(high-low+1);
    }
    long long int val1 = recurse(arr, low, mid, a, b);
    long long int val2 = recurse(arr, mid+1, high, a, b);

    return min(val, val1+val2);
}

int main() {
    long long int t, n, k, a, b;
    cin>> t;
    while(t--) {
        cin>> n>> k>> a>> b;
        vector<long long int> arr;
        for(long long int i=0; i<k; i++) {
            long long int temp;
            cin>> temp;
            arr.push_back(temp-1);
        }
        sort(arr.begin(), arr.end());
        cout<< recurse(arr, 0, pow(2, n)-1, a, b)<<endl;
    }
    return 0;
}