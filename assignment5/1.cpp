#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

class FreeSlot {
    public:
        int start;
        int end;
        FreeSlot(int s, int e): start(s), end(e) {}
};

class Course {
    public:
    int required_time;
    int forget_time;
    int start;
    int end;
    int id;

    Course(int id, int cs, int ce, int x, int f): id(id), start(cs), end(ce), required_time(x), forget_time(f) {}

    string binary() {
    	string str = bitset<64>(id).to_string();
        return str;
    }
    
    bool is_prime() {
        if(id <= 1) return false;
        for(int i = 2; i < sqrt(id); i++) {
            if(id%i == 0) return false;
        }
        return true;
    }
    virtual void print() {}
};

class ISystems: public Course {
    public:
        int type;
        ISystems(int id, int type, int cs, int ce, int x, int f): Course(id, cs, ce, x, f),  type(type) {}
        void print() {
            if(id%2 == 0) cout<< "ml\n";
            else cout<< "dl\n";
        }
};

class Systems: public Course {
    public:
        int type;
        Systems(int id, int type, int cs, int ce, int x, int f): Course(id, cs, ce, x, f),  type(type) {}
        void print() {
            // even set bits
            string bits = binary();
            int count = 0;
            for(auto i: bits) {
                if(i=='1') count++;
            }
            if(count%2 == 0) cout<<"programming\n";
            else cout<< "networking\n";
        }
};

class TheoreticalCS: public Course {
    public:
        int type;
        TheoreticalCS(int id, int type, int cs, int ce, int x, int f): Course(id, cs, ce, x, f),  type(type) {}
        void print() {
            if(id%2==0) cout<< "graphs\n";
            else if(id%3==0) cout<< "maths\n";
            else if(is_prime()) cout<< "algos\n";
        }
};

// helper functions

pair<int, int> findOverlap(Course* course, FreeSlot* free) {
    int os, oe; // start and end of overlap
    if(course->start <= free->start) {
        os = free->start;
    } else {
        os = course->start;
    }
    if(course->end <= free->end) {
        oe = course->end;
    } else {
        oe = free->end;
    }
    return {os, oe};
}

int main() {
    int N, M;
    cin>> N>> M;
    vector<FreeSlot* > temp1(4000001, NULL), freeSlots;
    vector<Course* >   temp2(4000001, NULL), courseSlots;

    int fs, fe;

    while(N--) {
        cin>> fs>> fe;
        auto temp = new FreeSlot(fs, fe);
        // freeSlots.push_back(temp);
        temp1[fs] = temp;
    }

    for(auto iter: temp1) {
        if(iter != NULL) {
            freeSlots.push_back(iter);
        }
    }

    int id, type, cs, ce, x, f;
    while(M--) {
        cin>> id>> type>> cs>> ce>> x>> f;
        if(type == 0) {
            auto temp = new ISystems(id, type, cs, ce, x, f);
            temp2[cs] = temp;
        } else if(type == 1) {
            auto temp = new Systems(id, type, cs, ce, x, f);
            temp2[cs] = temp;
        } else {
            auto temp = new TheoreticalCS(id, type, cs, ce, x, f);
            temp2[cs] = temp;
        }
    }

    for(auto iter: temp2) {
        if(iter != NULL) {
            courseSlots.push_back(iter);
        }
    }

    // now they are sorted
    int i = 0; // pointer to free slot array
    int j = 0; // pointer to course slot array
    vector<Course* > possibleCourses; // vector to store all the possible courses

    while(i<freeSlots.size() && j<courseSlots.size()) {
        vector<FreeSlot* > tempFree;
        auto course = courseSlots[j];
        while(i<freeSlots.size() && (freeSlots[i]->start < course->end)) {
            auto free = freeSlots[i];
            if(free->end > course->start) {
                tempFree.push_back(free);
            }
            i++;
        }
        // now check in tempFree we can complete the course
        if(tempFree.size() <= 0) { j++; continue;}
        auto free = tempFree[0];
        int os, oe; // start and end of overlap
        auto overlap = findOverlap(course, free);
        os = overlap.first;
        oe = overlap.second;
        int courseComplete = (oe-os);
        // cout<< course->id<< " "<< os<< " "<< oe<< endl;
        for(int temp=1; temp<tempFree.size(); temp++) {
            auto free = tempFree[temp];
            auto prevFree = tempFree[temp-1];
            if((free->start - prevFree->end) >= course->forget_time) {
                // forgot course
                courseComplete = 0;
            }
            // find overlap btw free and course
            int os, oe; // start and end of overlap
            auto overlap = findOverlap(course, free);
            os = overlap.first;
            oe = overlap.second;
            courseComplete += (oe-os);
        }
        // cout<< "time: "<< courseComplete<< " "<< course->required_time<< endl;
        if(courseComplete >= course->required_time) {
            possibleCourses.push_back(course);
        }
        auto last = tempFree[tempFree.size()-1];
        if(last->start <= course->end && last->end >= course->end) {
            // free slot for next course
            i--;
        }
        j++;
    }
    // printing the output
    cout<< possibleCourses.size()<< endl;
    for(auto c:possibleCourses) {
        c->print();
    }
    return 0;
}