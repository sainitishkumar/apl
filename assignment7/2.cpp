#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

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
    if(k==1) {
        int scrap = 0, gifts=0, i=0;
        while(i<weights.size()) {
            if(gifts+weights[i] <=1000) gifts+=weights[i];
            else scrap+=weights[i];
            i++;
        }
        cout<<scrap<<endl;
        return 0;
    }
    multimap<int, int> containers;
    for(int i=0; i<k; i++) containers.insert({0, 1});

    int weightsCounter = 0, scrapWeight = 0;
    while(weightsCounter<(int)weights.size()) {
        // for(auto i:containers) cout<< i.first<< " ";
        // cout<< endl;
        int giftWeight = weights[weightsCounter];
        // cout<< giftWeight<< endl;
        // gather elements in S
        int leftBound = ((800 - giftWeight)>0) ? 800-giftWeight : 0;
        int rightBound = 1000 - giftWeight;

        auto leftS = containers.lower_bound(leftBound);
        auto rightS = containers.lower_bound(rightBound);
        if(leftS==containers.end() && rightS==containers.end()) {
            // find T
            auto leftT = containers.lower_bound(0);
            auto rightT = containers.lower_bound(800-giftWeight);

            if(leftT==containers.end() && rightT==containers.end()) {
                scrapWeight+=giftWeight;
            } else if(rightT==containers.end()) {
                if(leftT->first > (800-giftWeight)) {
                    scrapWeight += giftWeight;
                } else {
                    auto rightmost = prev(containers.end());
                    int temp = rightmost->first;
                    containers.erase(rightmost);
                    containers.insert({temp+giftWeight, 1});
                }
            } else if(leftT==containers.end()) {
                if(rightT->first > (800-giftWeight)) {
                    rightT--;
                }
                int temp = rightT->first;
                containers.erase(rightT);
                containers.insert({temp+giftWeight, 1});
            } else {
                if(rightT->first > (800-giftWeight)) {
                    rightT--;
                }
                int temp = rightT->first;
                containers.erase(rightT);
                containers.insert({temp+giftWeight, 1});
            }
        } else {
            if((leftS->first + giftWeight) < 800 || (leftS->first + giftWeight) > 1000) {
                auto leftT = containers.lower_bound(0);
                auto rightT = containers.lower_bound(800-giftWeight);

                if(leftT==containers.end() && rightT==containers.end()) {
                    scrapWeight+=giftWeight;
                } else if(rightT==containers.end()) {
                    if(leftT->first > (800-giftWeight)) {
                        scrapWeight += giftWeight;
                    } else {
                        auto rightmost = prev(containers.end());
                        int temp = rightmost->first;
                        containers.erase(rightmost);
                        containers.insert({temp+giftWeight, 1});
                    }
                } else if(leftT==containers.end()) {
                    if(rightT->first > (800-giftWeight)) {
                        rightT--;
                    }
                    int temp = rightT->first;
                    containers.erase(rightT);
                    containers.insert({temp+giftWeight, 1});
                } else {
                    if(rightT->first > (800-giftWeight)) {
                        rightT--;
                    }
                    int temp = rightT->first;
                    containers.erase(rightT);
                    containers.insert({temp+giftWeight, 1});
                }
            } else {
                int temp = leftS->first;
                containers.erase(leftS);
            }
        }
        weightsCounter++;
    }
    for(auto remaining:containers) {
        scrapWeight+=remaining.first;
    }
    cout<< scrapWeight<< endl;
    // priority_queue<int> containers; // max heap
    // for(int i=0; i<k; i++) containers.push(0);

    // int weightsCounter = 0;
    // int scrapWeight = 0;
    // while(weightsCounter < (int)weights.size() && !containers.empty()) {
    //     // gather all elements which would fit in S
    //     int giftWeight = weights[weightsCounter];
    //     priority_queue<int, vector<int>, greater<int>> S;
    //     priority_queue<int> T, q2;
        
    //     while(!containers.empty()) {
    //         auto temp = containers.top(); containers.pop();
    //         if((temp+giftWeight) >= 800 && (temp+giftWeight)<=1000) {
    //             S.push(temp);
    //         } else if(temp+giftWeight < 800) {
    //             T.push(temp);
    //             break;
    //         } else {
    //             q2.push(temp);
    //         }
    //     }
        
    //     if(!S.empty()) {
    //         int minInS = S.top(); S.pop();
    //         minInS += giftWeight;
    //     } else if(!T.empty()) {
    //         int maxInT = T.top(); T.pop();
    //         T.push(maxInT+giftWeight);
    //     } else {
    //         scrapWeight += giftWeight;
    //     }

    //     while(!S.empty()) {
    //         int temp = S.top(); S.pop();
    //         containers.push(temp);
    //     }
        
    //     while(!T.empty()) {
    //         int temp = T.top(); T.pop();
    //         containers.push(temp);
    //     }

    //     while(!q2.empty()) {
    //         int temp = q2.top(); q2.pop();
    //         containers.push(temp);
    //     }
    //     weightsCounter++;
    // }
    // while(!containers.empty()) {
    //     int temp = containers.top(); containers.pop();
    //     scrapWeight += temp;
    // }
    // while(weightsCounter < (int)weights.size()) {
    //     scrapWeight += weights[weightsCounter];
    //     weightsCounter++;
    // }
    // cout<< scrapWeight<< endl;
    return 0;
}