#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <random>
#include <queue>

using namespace std;

bool bfs(vector<vector<int>> &graph, int vtx, int i) {
    int pow2i = pow(2, i);
    int count = 1;

    queue<int> q;
    unordered_set<int> visited;

    q.push(vtx);
    while(!q.empty()) {
        if(count == pow2i) break;

        auto currVtx = q.front();
        q.pop();
        
        if(visited.find(currVtx) == visited.end()) {
            visited.insert(currVtx);
            auto neighbors = graph[currVtx];
            for(auto neighbor: neighbors) {
                if(visited.find(neighbor) == visited.end()) {
                    q.push(neighbor);
                    count++;
                }
            }
        }
    }
    if(q.empty() && count<pow2i) return false;
    else if(count == pow2i) return true;

    return true;
}

int main() {
    int n, m;
    double c, epsilon, d_avg;
    vector<vector<int>> graph;

    cin>> n>> m;
    graph.assign(n, vector<int>());
    c = (double)n/(double)m;
    d_avg = 2/c;
    epsilon = 0.01;
    
    for(int i=0; i<m; i++) {
        int u, v;
        cin>> u>> v;
        graph[u].push_back(v);
    }
    
    double l = log2(1/epsilon*d_avg)+1;
    bool connected = true;
    
    for(auto i=8; i<=l; i++) {
        int ti = floor(l/(pow(2, i-1)*epsilon*d_avg));
        // vector<int> randomVertices;
        // for(int i=0; i<ti; i++) randomVertices.push_back(rand()%n);
        float count = 0;
        while(count<ti) {
            int vtx = rand()%n;
            bool val = bfs(graph, vtx, i);
            if(!val) {
                connected = false;
                cout<< "NO\n";
                return 0;
            }
            count+=1;
        }
    }
    connected ? cout<< "YES\n" : cout<< "NO\n";
    return 0;
}