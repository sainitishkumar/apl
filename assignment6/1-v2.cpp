#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// // search for insert position of val in the arr
int binarySearch(vector<long long int> arr, int val) {
    int low = 0, high = arr.size()-1;
    while (low <= high) {
        int mid = (high+low)/2;
        (arr[mid] < val) ? low = mid+1 : high = mid-1;
    }
    return low;
}

int linearSearch(vector<int> arr, int val) {
    int pos = 0;
    while(pos < arr.size()) {
        if(arr[pos] > val) break;
        pos++;
    }
    return pos;
}

int recurse(vector<long long int> arr, vector<int> freq, int low, int high, int a, int b) {
    if(low>high) {
        return 0;
    }
    if(low==high) {
        int lowpos = binarySearch(arr, low);
        if(arr[lowpos]!=low) return a;
        else {
            return b*freq[lowpos];
        }
    }
    int mid = (low+high)/2;
    int lowPos = binarySearch(arr, low);
    int highPos = binarySearch(arr, high);
    if(arr[highPos] == high) {
        highPos += (freq[highPos]-1);
    }
    int nz = highPos-lowPos;
    int val;
    if(nz == 0) {
        val = a;
        return val;
    } else {
        val = nz*b*(high-low+1);
    }
    int val1 = recurse(arr, freq, low, mid, a, b);
    int val2 = recurse(arr, freq, mid+1, high, a, b);

    return min(val, val1+val2);
}

// removes duplicates from array and stores its frequency
void removeDuplicates(vector<long long int> arr, vector<int> &frequency) {
    int curr = arr[0];
    int freq = 1;
    for(int i=1; i<arr.size(); i++) {
        if(curr!=arr[i]) {
            frequency.push_back(freq);
            freq = 1;
            curr = arr[i];
        } else {
            freq++;
        }
    }
    frequency.push_back(freq);
}

int main() {
    int t, n, k, a, b;
    cin>> t;
    while(t--) {
        cin>> n>> k>> a>> b;
        vector<long long int> arr;
        for(int i=0; i<k; i++) {
            long long int temp;
            cin>> temp;
            arr.push_back(temp-1);
        }
        sort(arr.begin(), arr.end());
        vector<int> frequency;
        removeDuplicates(arr, frequency);
        cout<< recurse(arr, frequency, 0, pow(2, n)-1, a, b)<<endl;
    }
    return 0;
}