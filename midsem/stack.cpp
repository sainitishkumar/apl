#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Node {
    private:
        int data;
        Node *next;
        Node *prev;
    public:
        Node();
        Node(int d);
        int getData();

        void setNext(Node* n);
        Node* getNext();
        
        void setPrev(Node* n);
        Node* getPrev();
        
        void changeData(int val);
};

Node::Node(int x) {
    data = x;
    next = prev = NULL;
}

int Node::getData() { return this->data;}

void Node::setNext(Node* n) { this->next = n;}
Node* Node::getNext() { return this->next;}

void Node::setPrev(Node* n) { this->prev = n;}
Node* Node::getPrev() { return this->prev;}

void Node::changeData(int val) { this->data = val;}


class LinkedList {
    private:
        Node* head;
        Node* tail;
    public:
    int size;
    LinkedList();
    LinkedList(int n);
    void insert(int x);
    void remove();
    int getTail();
};

LinkedList::LinkedList() {
    size = 0;
    head = NULL;
    tail = NULL;
}

LinkedList::LinkedList(int n) {
    size = 0;
    head = new Node(n);
    tail = head;
    size++;
}

void LinkedList::insert(int x) {
    auto curr = new Node(x);
    if(head == NULL) {
        head = curr;
        tail = head;
    } else {
        curr->setPrev(tail);
        tail->setNext(curr);
        tail = curr;
    }
    size++;
}

void LinkedList::remove() {
    size--;
    if(size==0) {
        head = NULL;
        tail = NULL;
    } else {
        tail = tail->getPrev();
        tail->setNext(NULL);
    }
}

int LinkedList::getTail() {
    return tail->getData();
}

class Stack
{
    private:
        int sum = 0;
        int size = 0;
        LinkedList list_obj;
        LinkedList minstack;
    public:
    void push(int d){
        list_obj.insert(d);
        sum+=d;
        size+=1;
        if(minstack.size == 0) {
            minstack.insert(d);
        } else {
            int mintop = minstack.getTail();
            if(d < mintop) minstack.insert(d);
            else minstack.insert(mintop);
        }
    }
    void pop(){
        if(size>0) {
            int top = list_obj.getTail();
            sum-=top;
            size--;
            list_obj.remove();
            minstack.remove();
        }
    }
    void getTop(){
        //Implement your code here
        if(size > 0) cout<< list_obj.getTail()<< endl;
        else cout<<"stack empty\n";
    }
    void getMin(){
        //Implement your code here
        if(size > 0) cout<< minstack.getTail()<< endl;
        else cout<<"stack empty\n";
    }
    void getSum(){
        //Implement your code here
        cout<< sum<< endl;
    }
};

int main() {
    int n;
    cin>> n;
    Stack S;
    while(n--) {
        int q, data;
        cin>> q;
        switch(q) {
            case 0:
                cin>> data;
                S.push(data);
                break;
            case 1:
                S.pop();
                break;
            case 2:
                S.getTop();
                break;
            case 3:
                S.getMin();
                break;
            case 4:
                S.getSum();
                break;
        }
    }
    return 0;
}