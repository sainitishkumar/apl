#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
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

// bool oddcycle return true if found
bool oddcycle(vector<vector<int>> &graph, int vtx) {
    int K, L, n;
    n = graph.size();
    K = 50*(int)sqrt(n);
    L = 60;
    vector<vector<int>> randomWalk;
    randomWalk.assign(K, vector<int>());
    for(int i=0; i<K; i++) {
        randomWalk[i].push_back(vtx);
        int count = 1;
        int currVtx = vtx;
        while(count<L) {
            int randomNeighbor = (int)rand()%(graph[currVtx].size());
            randomWalk[i].push_back(randomNeighbor);
            currVtx = randomNeighbor;
            count++;
        }
    }
    // random walks done
    // now find if any vtx has even cycle with any other vertex

    for(int i=0; i<K; i++) {
        for(int j=i+1; j<K; j++) {
            for(int k=1; k<randomWalk[i].size(); k++) {
                int currVtx = randomWalk[i][k];
                for(int l=1; l<randomWalk[j].size(); l++) {
                    if(currVtx==randomWalk[j][l]) {
                        if((k+l)%2!=0) {
                            return true;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    int n, m;
    double c, epsilon, d_avg;
    vector<vector<int>> graph;

    cin>> n>> m;
    graph.assign(n, vector<int>());
    c = (double)n/(double)m;
    d_avg = 2/c;
    epsilon = 0.1;
    
    for(int i=0; i<m; i++) {
        int u, v;
        cin>> u>> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    double l = log2(1/epsilon*d_avg)+1;
    bool bipartite = true;
    int constant = 10;
    int T = 10*(1/epsilon);
    for(auto i=1; i<=T; i++) {
        int vtx = rand()%n;
        if(oddcycle(graph, vtx)) {
            bipartite = false;
            break;
        }
    }
    bipartite ? cout<< "YES\n" : cout<< "NO\n";
    return 0;
}