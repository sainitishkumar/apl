#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

int position(int posx, int posy, int n, int m) {
    return m*posx+posy;
}

string remove(string k) {

    string ans = "";
    int i=0;
    while(i<k.size()-1) {
        if(k[i]!=k[i+1]) {
            ans+=k[i];
            i++;
        }
        else i+=2;
    }
    ans+=k[k.size()-1];
    return ans;
}

string removedouble(string k) {
    if(k.size()<=4) return k;
    string ans = "";
    int i=0, j=2;
    while(j+1<k.size()) {
        string temp1 = "", temp2 = "";
        temp1+=(k[i]+k[i+1]);
        temp2+=(k[j]+k[j+1]);
        if(temp1!=temp2) {
            ans+=k[i];
            ans+=k[i+1];
            i+=2;
            j+=2;
        } else {
            i+=4;
            j+=4;
        }
    }
    string temp1 = "", temp2 = "";
    // i = k.size()-4;
    // j = k.size()-2;
    // temp1+=(k[i]+k[i+1]);
    // temp2+=(k[j]+k[j+1]);
    // if(temp1!=temp2) {
    //     ans+=k[j];
    //     ans+=k[j+1];
    // }
    ans+=k.substr(i);
    return ans;
}

void print(vector<int> matrix, int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cout<< matrix[position(i, j, n, m)]<< " ";
        }
        cout<< endl;
    }
}

int main() {
    int m, n;
    string k;

    cin>> m>> n;
    vector<int> matrix;
    for(int i=0; i<m*n; i++) {
        int temp;
        cin>> temp;
        matrix.push_back(temp);
    }

    cin>> k;
    auto s = ((remove(k)));
    int i = 0;

    s = removedouble(s);

    while(i<s.size()) {
        if(s[i] == 'x') {
            // horizontal(matrix, n, m);
            // operation x
            for(int i=0; i<n; i++) {
                for(int j=0; j<=m/2-1; j++) {
                    // swap i, j with i, m-j-1
                    int t = matrix[position(i, j, n, m)];
                    matrix[position(i, j, n, m)] = matrix[position(i, m - j - 1, n, m)];
                    matrix[position(i, m - j - 1, n, m)] = t;
                }
            }
        } else if(s[i]=='y') {
            // vertical(matrix, n, m);
            // operation y
            for(int i=0; i<=n/2-1; i++) {
                for(int j=0; j<m; j++) {
                    // swap i, j with n - i - 1, j
                    int t = matrix[position(i, j, n, m)];
                    matrix[position(i, j, n, m)] = matrix[position(n - i - 1, j, n, m)];
                    matrix[position(n - i - 1, j, n, m)] = t;
                }
            }
        }
        i++;
    }
    print(matrix, n, m);
    return 0;
}