#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

class Course {
    public:
    int required_time;
    int forget_time;
    int start;
    int end;
    int id;

    // this method will return the binary representation of course id
    string binary() {
        string str = bitset<64>(id).to_string();
        return str;
    } 
    
    // this will check if course id is prime
    bool is_prime() {
        if(id <= 1) return false;
        for(int i = 2; i < sqrt(id); i++) {
            if(id%i == 0) return false;
        }
        return true;
    } 

    virtual void print() = 0;
};



class IntelligentSystemsCourse: public Course  {

    public:
    IntelligentSystemsCourse(int idv, int st, int et, int rt, int ft) {
        id = idv;
        start = st;
        end = et;
        required_time = rt;
        forget_time = ft;
    }

    void print() {
        if(id%2 == 0) cout<<"ml\n";
        else cout<<"dl\n";
    }
};

class SystemsCourse: public Course {
    public:
    SystemsCourse(int idv, int st, int et, int rt, int ft) {
        id = idv;
        start = st;
        end = et;
        required_time = rt;
        forget_time = ft;
    }

    void print() {
        string binid = binary();
        int c = 0;
        for(int i = 0; i < (int) binid.size(); i++) {
            if(binid[i] == '1') c++;
        }
        if(c%2 == 0) cout<<"programming\n";
        else cout<<"networking\n";
    }

};

class TheoreticalCSCourse: public Course {
    public:
    TheoreticalCSCourse(int idv, int st, int et, int rt, int ft) {
        start = st;
        id = idv;
        end = et;
        required_time = rt;
        forget_time = ft;
    }

    void print() {
        if(id%2 == 0) cout<<"graphs\n";
        else if(id%3 == 0) cout<<"maths\n";
        else if(is_prime()) cout<<"algos\n";
    }

};


// to store overlapping time between a course and 'free time'
class CourseIntersection {
    public:
    Course* course;
    int start;
    int end;
    int span;
    CourseIntersection(Course* c, int s, int e) {
        course = c;
        start = s;
        end = e;
        span = e - s;
    }
};


// compare function to be used in sorting
bool compare(const Course* c1, const Course* c2) {
    if(c1->start < c2->start)
        return true;
    return false;
}


int main() {

    int N, M;
    cin>>N>>M;
    
    vector<pair<int, int> > free_time;
    vector<Course*> courses;
    vector<int> required_time;
    vector<int> forget_time;
    
    
    for(int i = 0; i < N; i++) {
        int st, et;
        cin>>st>>et;
        free_time.push_back(make_pair(st, et));
    }

    
    for(int i = 0; i < M; i++) {
        int id, type, st, et, rt, ft;
        cin>>id>>type>>st>>et>>rt>>ft;
        if(type == 0) {
            IntelligentSystemsCourse* p = new IntelligentSystemsCourse(id, st, et, rt, ft);
            courses.push_back(p);
        } else if(type == 1) {
            SystemsCourse* p = new SystemsCourse(id, st, et, rt, ft);
            courses.push_back(p);
        } else if(type == 2) {
            TheoreticalCSCourse* p = new TheoreticalCSCourse(id, st, et, rt, ft);
            courses.push_back(p);
        }
        
    }

    
    // sorting both the lists
    sort(free_time.begin(), free_time.end());
    sort(courses.begin(), courses.end(), compare);
    
    // this vector will store the final answer
    vector<Course*> ans;

    int i = 0, j = 0;
    
    
    // get all the intervals in which the course is available and you have free time
    // store it in this vector
    // each intersection will store what course is being being offered
    // and the span (duration) of the intersection
    vector<CourseIntersection> civ;

    while(j < M && i < N) {

        int is = max(free_time[i].first, courses[j]->start);
        int ie = min(free_time[i].second, courses[j]->end);

        if(ie - is > 0) {
            // push intersection
            CourseIntersection tmp = CourseIntersection(courses[j], is, ie);
            civ.push_back(tmp);
            if (free_time[i].second < courses[j]->end)
                i++;
            else
                j++;
        } else if (free_time[i].second < courses[j]->end)
            i++;
        else
            j++;
    }


    int cn = civ.size();

    // for each of the intersections found in the above loop
    // for each of the course
    
    
    // both inner and outer loop depend on variable 'i'
    // their complexity, combined together is at most O(m+n) 
    i = 0;
    while(i < cn) {
        CourseIntersection curr = civ[i];
        int rt = curr.course->required_time;
        int ft = curr.course->forget_time;
        bool success = false;
        while(i < cn && curr.course->id == civ[i].course->id) {
            // if the same course is still going on check for forget time
            if(i > 0 && civ[i-1].course->id == civ[i].course->id && civ[i].start - civ[i-1].end >= ft) {
                rt = curr.course->required_time;
            }

            // decrease the required time with the intersection span
            rt -= civ[i].span;

            // mark it as completed
            if(rt <= 0) success = true;

            i++;
        }

        if(success) {
            ans.push_back(curr.course);
        }
    }


   
    cout<<ans.size()<<"\n";


    for(int i = 0; i < (int) ans.size(); i++) {
        ans[i]->print();
    }

    return 0;
}