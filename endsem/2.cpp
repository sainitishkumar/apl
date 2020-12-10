#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using namespace std;

int main() {
    int m, n;
    cin>> n>> m;
    vector<vector<int>> graph(n, vector<int>());
    vector<int> degree3;
    for(int i=0; i<m; i++) {
        int v1,v2;
        cin>> v1>> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
        if(graph[v1].size()==2) degree3.push_back(v1);
        if(graph[v2].size()==2) degree3.push_back(v2);
    }
    vector<bool> visited(n, false);
    vector<int> parent(n, 1250001);
    // cout<< vtx<< endl;
    
    // do bfs from this vtx
    int no_cycles=0;
    for(auto vtx: degree3) {
        queue<int> bfsq;
        int curr = vtx, prev = vtx;
        bfsq.push(vtx);
        set<pair<int, int>> cycles;
        map<int, int> counter;
        for(auto i:degree3) {
            counter[i]=0;
        }
        while(!bfsq.empty()) {
            prev = curr;
            curr = bfsq.front();
            bfsq.pop();
            visited[curr] = true;
            for(int neigh: graph[curr]) {
                if(visited[neigh]) {
                    if(parent[curr] != neigh) {
                        // cout<< neigh<< " "<< curr<< endl;
                        cycles.insert({curr, neigh});
                        // cout<< vtx<< endl;
                        if(graph[neigh].size() == 3) {
                            counter[neigh]++;
                        } else if(graph[curr].size()==3) {
                            counter[curr]++;
                        }
                    }
                } else {
                    bfsq.push(neigh);
                    visited[neigh] = true;
                    parent[neigh] = curr;
                }
            }
        }
        int count=0;
        for(auto i:counter) {
            if(i.second>=2) count=2;
        }
        if(count==2){
            no_cycles+=3;
        }
        else {
            no_cycles+=(cycles.size()/2);
        }
    }
    cout<< no_cycles<< endl;
    return 0;
}
