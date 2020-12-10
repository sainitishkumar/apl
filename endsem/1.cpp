#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using namespace std;

void dfs(int v, vector<vector<int>> &g, vector<bool> &vis, vector<bool> &vis2, int &counter) {
    if(vis2[v] == true) {
        return;
    } else {
        if(vis[v]) {
            counter++;
            return;
        } else {
            vis[v] = true;
            for(auto neigh: g[v]) {
                dfs(neigh, g, vis, vis2, counter);
            }
            vis[v] = false;
            vis2[v] = true;
        }
    }
}

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
        if(graph[v1].size()==3) degree3.push_back(v1);
        if(graph[v2].size()==3) degree3.push_back(v2);
    }
    int vtx = degree3[0];
    // cout<< vtx<< endl;
    vector<bool> visited(n, false);
    vector<bool> visited2(n, false);
    vector<int> parent(n, 1250001);
    // do bfs from this vtx
    queue<int> bfsq;
    int curr = vtx, prev = vtx;
    bfsq.push(vtx);
    set<pair<int, int>> cycles;
    map<int, int> counter;
    for(auto i:degree3) {
        counter[i]=0;
    }
    int c;
    for(auto v: degree3) {
        dfs(v, graph, visited, visited2, c);
    }
    cout<< c<< endl;
    return 0;
}
