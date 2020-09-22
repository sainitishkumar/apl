#include <iostream>

using namespace std;

// Node class
class DllNode {
    private:
        int data;
        DllNode *next;
        DllNode *prev;
    public:
        DllNode(int x);
        int getData();

        void setNext(DllNode* n);
        DllNode* getNext();
        
        void setPrev(DllNode* n);
        DllNode* getPrev();
        
        void changeData(int val);
};

DllNode::DllNode(int x) {
    data = x;
    next = prev = NULL;
}

int DllNode::getData() { return this->data;}

void DllNode::setNext(DllNode* n) { this->next = n;}
DllNode* DllNode::getNext() { return this->next;}

void DllNode::setPrev(DllNode* n) { this->prev = n;}
DllNode* DllNode::getPrev() { return this->prev;}

void DllNode::changeData(int val) { this->data = val;}

// LL class
class Dll {
    int size;
    DllNode *head, *tail;
    public:
        Dll(string num);
        ~Dll();
        int getSize();

        void insertFront(int num);
        void insertBack(int num);

        void add(int c, int i);
        void mul(int c, int i);

        void print();
};

Dll::Dll(string num) {
    this->size = 0;
    if(num == "") { return;}

    this->head = new DllNode(num[num.length() - 1] - '0');
    this->tail = this->head;

    this->size++;
    
    int i = num.length() - 2;
    while(i >= 0) {
        insertBack(num[i] - '0');
        i--;
    }
}

Dll::~Dll() {
    auto curr = head, next = curr;
    while(curr!=NULL) {
        next = curr->getNext();
        delete curr;
        curr = next;
    }
}

int Dll::getSize() {return this->size;}

void Dll::insertFront(int num) {
    auto curr = new DllNode(num);
    curr->setNext(head);
    head->setPrev(curr);
    head = curr;

    size++;
}

void Dll::insertBack(int num) {
    auto curr = new DllNode(num);
    curr->setPrev(tail);
    tail->setNext(curr);
    tail = curr;

    size++;
}

void Dll::add(int c, int i) {
    if(c == 0) return;
    // cout<< "size "<< this->getSize()<< endl;
    // cout<< i<< " "<< this->getSize()<< endl;
    if(i <= this->getSize() - 1) {
        auto curr = head;
        for(int count=0; count<i; count++)
            curr = curr->getNext();
        
        int nodeval = curr->getData();
        int ad = (nodeval+c)%10;
        int carry = (nodeval+c)/10;
        // cout<< ad<< " "<< carry<< endl;
        curr->changeData(ad);

        while(carry != 0) {
            curr = curr->getNext();
            if(curr == NULL) {
                this->insertBack(carry);
                return;
            } else {
                nodeval = curr->getData();
                ad = (nodeval+carry)%10;
                carry = (nodeval+carry)/10;
                curr->changeData(ad);
            }
        }
    } else {
        // if the adding number is greater than the dll
        int size = this->getSize();
        for(int count = 0; count < i - size + 1; count++) {
            this->insertBack(0);
        }
        tail->changeData(c);
    }
}

void Dll::mul(int c, int i) {
    // check if c == 0
    if(c == 0) {
        head = new DllNode(0);
        tail = head;
        size = 1;
        return;
    }
    // multiply num by c
    auto curr = head;
    int mul = 0, carry = 0;
    while(curr != NULL) {
        int nodeval = curr->getData();
        mul = (nodeval*c + carry)%10;
        carry = (nodeval*c + carry)/10;
        curr->changeData(mul);
        curr = curr->getNext();
    }
    if(carry != 0) {
        this->insertBack(carry);
    }
    // then shift right by i
    while(i>0) {
        this->insertFront(0);
        i--;
    }
}

void Dll::print() {
    auto curr = tail;
    while(curr != NULL && curr->getPrev() != NULL && curr->getData() == 0) {
        curr = curr->getPrev();
    }
    int count = 0;
    while(curr != NULL) {
        count++;
        printf("%d", curr->getData());
        curr = curr->getPrev();
    }
    if(count == 0) cout<< 0;
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int t, q;
    string num;
    cin>> t;

    while(t > 0) {
        cin>> num;
        // cout<< "@"<< num<< endl;
        num.erase(0, min(num.find_first_not_of('0'), num.size()-1));
        // cout<< "@"<< num<< endl;
        cin>> q;
        Dll *doubleLL = new Dll(num);
        while(q > 0) {
            int c, i;
            char op;

            cin>> op>> c>> i;
            
            if(op == 'a') doubleLL->add(c, i);
            if(op == 'm') doubleLL->mul(c, i);
            q--;
        }
        doubleLL->print();
        delete doubleLL;
        t--;
    }
    return 0;
}