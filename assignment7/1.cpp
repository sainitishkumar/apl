#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int k, n;
    cin>> k>> n;
    vector<int> weights;
    for(int i=0; i<n; i++) {
        int temp;
        cin>> temp;
        weights.push_back(temp);
    }
    sort(weights.begin(), weights.end());
    reverse(weights.begin(), weights.end());
    
    int containerCounter = 0, weightsCounter = 0;
    int scrapWeight = 0, containerCapacity = 0;
    
    while(containerCounter < k && weightsCounter < (int)weights.size()) {
        if(containerCapacity + weights[weightsCounter] > 1000) {
            containerCapacity = 0;
            containerCounter++;
        } else {
            containerCapacity += weights[weightsCounter];
            weightsCounter++;
        }
    }
    while(weightsCounter < (int)weights.size()) {
        scrapWeight += weights[weightsCounter];
        weightsCounter++;
    }
    cout<< scrapWeight<< endl;
    return 0;
}