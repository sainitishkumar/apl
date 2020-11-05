#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool isMaximal(vector<vector<int>> &M, vector<pair<int, int>> &gifts, int W, int n) {
    // // get the minimum item which is not used
    int i=n, w=W;
    int INTMAX = 999999999;

    while(i>0 && w>0) {
        int wi = gifts[i-1].first;
        int hi = gifts[i-1].second;
        
        if(M[i][w] == INTMAX) return false;
        else if(w-wi<0) return false;
        else if(M[i][w] == M[i-1][w-wi] + wi*hi) {
            i = i - 1;
            w = w - wi;
        } else if(M[i][w] == M[i-1][w]) {
            break;
        } else {
            return false;
        }
    }

    if(W + gifts[i-1].first > (M[0].size()-1)) {
        return true;
    }
    return false;
}

int main() {
    int n, W, H, totalWeight;
    int INTMAX = 999999999;

    cin>> n>> W>> H;
    vector<pair<int, int>> gifts;

    for(int i=0; i<n; i++) {
        int w, h;
        cin>> w>> h;
        gifts.push_back({w, h});
        totalWeight+=(w*h);
    }

    sort(gifts.begin(), gifts.end(), [](const pair<int, int>& l, const pair<int, int>& r){
        if(l.first==r.first) return l.second > r.second;
        return l.first > r.first;
    });

    vector<vector<int>> M;
    for(int i=0; i<=n; i++) {
        vector<int> temp;
        for(int w=0; w<=W; w++) {
            (w == 0)? temp.push_back(0): temp.push_back(INTMAX);
        }
        M.push_back(temp);
    }

    for(int w=1; w<=W; w++) {
        for(int i=1; i<=n; i++) {
            int hi = gifts[i-1].second, wi = gifts[i-1].first;
            int temp = (w-wi < 0)? INTMAX: M[i-1][w-wi];
            M[i][w] = min(temp+hi*wi, M[i-1][w]);
        }
    }

    // now calculate all the maximal packing weights
    vector<int> maximalPacks;
    
    int minGiftwidth = gifts[gifts.size()-1].first;
    for(int i=1; i<=n; i++) {
        for(int w=W; w>W-minGiftwidth; w--) {
            if(M[i][w]!=INTMAX) maximalPacks.push_back(M[i][w]);
        }
    }

    // last row i = n
    for(int w=1; w<=W-minGiftwidth; w++) {
        if(M[n][w] != INTMAX && isMaximal(M, gifts, w, n)) {
            maximalPacks.push_back(M[n][w]);
        }
    }

    if(maximalPacks.empty()) cout<< 0<< endl;
    else {
        auto minimum = min_element(maximalPacks.begin(), maximalPacks.end());
        cout<< totalWeight - *minimum<< endl;
    }
    return 0;
}