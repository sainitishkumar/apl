#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// helper functions
bool isPrime(int number) {
    if(number == 2) return true;
    if(number < 2 || number%2 == 0) return false;
    for(int i=3; i<=sqrt(number); i+=2) {
        if(number % i == 0)
            return false;
    }
    return true;
}

class BstNode {
    private:
        int data;
        BstNode *left;
        BstNode *right;
    public:
        BstNode(int x);
        int getData();

        void setLeft(BstNode* n);
        BstNode* getLeft();
        
        void setRight(BstNode* n);
        BstNode* getRight();
        
        void changeData(int val);
};

BstNode::BstNode(int x) {
    data = x;
    left = right = NULL;
}

int BstNode::getData() { return this->data;}

void BstNode::setLeft(BstNode* n) { this->left = n;}
BstNode* BstNode::getLeft() { return this->left;}

void BstNode::setRight(BstNode* n) { this->right = n;}
BstNode* BstNode::getRight() { return this->right;}

void BstNode::changeData(int val) { this->data = val;}

class BinaryTree {
    private:
        vector<BstNode *> arrayTree;
        int size;
    public:

        void setSize(int size);
        void insertNode(int nodeVal);
        
        void commandA();
        void commandB(int b);
        void commandC(int c);

        void print();
};

// BinaryTree::BinaryTree() {}

void BinaryTree::setSize(int size) {
    this->size = size;
}

void BinaryTree::insertNode(int nodeVal) {
    auto node = new BstNode(nodeVal);
    if(arrayTree.size() > 0) {
        auto parentNode = this->arrayTree[(arrayTree.size()-1)/2];
        ((arrayTree.size()) % 2 == 0) ? parentNode->setRight(node) : parentNode->setLeft(node);
    }
    this->arrayTree.push_back(node);
}

void BinaryTree::commandA() {
    // print sum of nodes with prime value grand parent
    int sum = 0;
    for(int i=0; i<arrayTree.size(); i++) {
        auto node = arrayTree[i];
        if(isPrime(node->getData())) {
            // get the grand children
            auto grandChildren = {4*i+3, 4*i+4, 4*i+5, 4*i+6};
            for(auto gc: grandChildren) {
                if(gc < arrayTree.size()) { sum+=arrayTree[gc]->getData();}
            }
        }
    }
    cout<< sum<< endl;
}

void BinaryTree::commandB(int b) {
    // b = level in tree
    // if level is palindrome, print sum of the nodes
    // else print the sum of the first and last nodes of the level
    
    // starting index of the level = 2^b - 1
    vector<int> vec;
    for(int i = pow(2, b) - 1, count = 0; count < pow(2, b); i++, count++) {
        if(i >= arrayTree.size()){ break;}
        vec.push_back(arrayTree[i]->getData());
    }
    // now check if vec is palindrome or not
    if(vec.size() == 1) {
        cout<< vec[0]<< endl;
    } else {
        int sum = 0;
        int i = 0, j = vec.size() - 1;
        bool flag = true;
        while(i <= j) {
            (i == j) ? sum += vec[i] : sum += 2*vec[i];
            if(vec[i] != vec[j]) {
                flag = false;
                break;
            }
            i++; j--;
        }
        if(!flag) sum = vec[0]+vec[vec.size()-1];

        cout<< sum<< endl;
    }
}

int recurse(BstNode* node, bool flag) {
    if(node == NULL) return 0;
    if(flag) return recurse(node->getLeft(), false) + node->getData();
    else     return recurse(node->getRight(), true) + node->getData();
}

void BinaryTree::commandC(int c) {
    // node at index of c
    auto node = arrayTree[c];
    // going left, flag = true
    // going right, flag = false
    cout<< max(recurse(node, false), recurse(node, true))<< endl;
}

void BinaryTree::print() {
    // lvl order
    queue<BstNode* > q;
    q.push(arrayTree[0]);
    while(!q.empty()) {
        queue<BstNode* > q2;
        while(!q.empty()) {
            auto node = q.front();
            q.pop();
            cout<< node->getData()<< " ";
            if(node->getLeft()) q2.push(node->getLeft());
            if(node->getRight()) q2.push(node->getRight());
        }
        cout<< endl;
        q = q2;
    }
    cout<< endl;
}

int main() {
    int N, m;
    char command;

    auto btree = new BinaryTree();

    cin>> N;
    while(N--) {
        cin>> command;
        if(command == 'i') {
            cin>> m;
            while(m--) {
                int nodeval;
                cin>> nodeval;
                btree->insertNode(nodeval);
            }
        } else if(command == 'a') {
            btree->commandA();
        } else if(command == 'b') {
            int b_val;
            cin>> b_val;
            btree->commandB(b_val);
        } else if(command == 'c') {
            int c_val;
            cin>> c_val;
            btree->commandC(c_val);
        }
    }
    // btree->print();
    return 0;
}