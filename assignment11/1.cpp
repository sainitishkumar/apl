#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <queue>

using namespace std;

bool reachable(int s, int t, vector<vector<int>> &graph) {
    vector<int> visited(graph.size(), 0);
    queue<int> q;
    int curr = s;
    q.push(curr);

    while(!q.empty()) {
        curr = q.front();
        visited[curr] = 1;
        q.pop();
        if(curr==t) return true;
        for(int i=0; i<graph[curr].size(); i++) {
            if(graph[curr][i]==1 && visited[i]==0) {
                q.push(i);
            }
        }
    }
    return false;
}

int main() {
    int C, m, N, q;
    cin>> C>> m;
    
    vector<vector<int>> T(C, vector<int>(C, 0));

    for(int i=0; i<m; i++) {
        int c1, c2;
        cin>> c1>> c2;
        T[c1][c2]=1;
        T[c2][c1]=1;
    }
    
    cin>> N;
    vector<vector<int>> Graph(N, vector<int>(N, 0));
    map<int, vector<int>> colours;
    vector<int> colors;

    for(int i=0; i<N; i++) {
        int color;
        cin>> color;
        colors.push_back(color);
        if(colours.find(color)==colours.end()) {
            colours[color] = {i};
        } else {
            colours[color].push_back(i);
        }
    }
    
    for(int i=0; i<T.size(); i++) {
        for(int j=0; j<T[0].size(); j++) {
            if(T[i][j]==1) {
                for(int vtxi: colours[i]) {
                    for(int vtxj: colours[j]) {
                        Graph[vtxi][vtxj] = 1;
                        Graph[vtxj][vtxi] = 1;
                    }
                }
            }
        }
    }
    for(int col=0; col<colours.size(); col++) {
        auto temp = colours[col];
        for(int i=0; i<temp.size(); i++) {
            for(int j=i+1; j<temp.size(); j++) {
                Graph[temp[i]][temp[j]] = 1;
                Graph[temp[j]][temp[i]] = 1;
            }
        }
    }
    
    vector<vector<float>> exchangeRates(N, vector<float>());
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            float temp;
            cin>> temp;
            exchangeRates[i].push_back(temp);
        }
    }
    // precomputing distances
    vector<vector<float>> floyd(N, vector<float>(N, 0));
    for(int i=0; i<Graph.size(); i++) {
        for(int j=0; j<Graph[0].size(); j++) {
            if(Graph[i][j]==1) {
                floyd[i][j] = exchangeRates[i][j];
            } else {
                floyd[i][j] = (float)INT_MIN;
            }
        }
    }
    for(int k=0; k<N; k++) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                if(floyd[i][k]>(float)INT_MIN && floyd[k][j]> (float)INT_MIN) {
                    floyd[i][j] = max(floyd[i][j], floyd[i][k]*floyd[k][j]);
                }
            }
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            for(int t=0; t<N; t++) {
                if(floyd[t][t]>1 && floyd[i][t]>(float)INT_MIN && floyd[t][j]>(float)INT_MIN) {
                    floyd[i][j] = (float)INT_MIN;
                }
            }
        }
    }
    cin>> q;
    for(int i=0; i<q; i++) {
        int s, t, currency;
        cin>> s>> t>> currency;
        if(s==t) {
            printf("%.3f\n", currency);
            continue;
        }
        if(reachable(s, t, Graph)) {
            // float val = bfs(s, t, Graph, exchangeRates);
            float val = floyd[s][t];
            if(isinf(val)) {
                printf("INF\n");
            } else if(val<-2147483648.0) {
                printf("INF\n");
            } else {
                printf("%.3f\n", val*currency);
            }
        } else {
            printf("-1\n");
        }
    }
    return 0;
}