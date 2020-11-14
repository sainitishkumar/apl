#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    int val;
    node* first_child;
    node* second_child;
    node* third_child;
    node(int v) {
        val = v;
        first_child = second_child = third_child = NULL;
    }
};

int main() {
    vector<vector<int>> tree;
    vector<node* > leaves;
    int n;
    
    cin>> n;
    tree.assign(n+1, vector<int>());

    for(int i=0; i<pow(3, n); i++) {
        int temp;
        cin>> temp;
        auto n = new node(temp);
        leaves.push_back(n);
    }

    while(leaves.size()>1) {
        vector<node* > temp;
        for(int j=0; j<leaves.size(); j+=3) {
            int majority;
            if(leaves[j]->val+leaves[j+1]->val+leaves[j+2]->val >= 2) {
                majority = 1;
            } else {
                majority = 0;
            }
            auto newnode = new node(majority);
            newnode->first_child  = leaves[j];
            newnode->second_child = leaves[j+1];
            newnode->third_child  = leaves[j+2];
            temp.push_back(newnode);
        }
        leaves.clear();
        copy(temp.begin(), temp.end(), back_inserter(leaves));
    }
    // for(int i=1; i<n+1; i++) {
    //     auto tempvec = tree[i-1];
    //     for(int j=0; j<tempvec.size(); j+=3) {
    //         if(tempvec[j]+tempvec[j+1]+tempvec[j+2] >= 2) {
    //             tree[i].push_back(1);
    //         } else {
    //             tree[i].push_back(0);
    //         }
    //     }
    // }
    // reverse(tree.begin(), tree.end());
    cout<< leaves[0]->val<< endl;
    auto curr = leaves[0]->first_child;
    int sum = leaves[0]->val;
    int child = 1;
    while(curr!=NULL) {
        sum+=curr->val;
        if(child==0) {
            curr = curr->first_child;
            child = 1;
        } else if(child==1) {
            curr = curr->second_child;
            child = 2;
        } else if(child==2) {
            curr = curr->third_child;
            child = 0;
        }
    }
    cout<< sum<< endl;
    return 0;
}