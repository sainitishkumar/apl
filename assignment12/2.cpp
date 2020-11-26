#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

struct line {
    float x1, y1, x2, y2;
    line(float xa, float ya, float xb, float yb): x1(xa), y1(ya), x2(xb), y2(yb) {};
};

struct EventsNode {
    int x, y, id; // id is polygon number
    bool isStartNode;
    EventsNode *horizontalNeighbor, *verticalNeighbor;
    
    EventsNode(int x1, int y1, int id1, bool start) {
        x = x1;
        y = y1;
        id = id1;
        isStartNode = start;
        horizontalNeighbor = NULL;
        verticalNeighbor = NULL;
    }
    void print(string msg = "Event") {
        cout<< msg<< " "<< x<< " "<< y<< " "<< id<< endl;
    }
};

struct EventsCompare {
    bool operator()(EventsNode *n1, EventsNode *n2) {
        if(n1->x==n2->x) {
            return n1->y > n2->y;
        }
        return n1->x > n2->x;
    }
};

struct SweepNodesCompare {
    bool operator()(EventsNode *n1, EventsNode *n2) {
        return n1->y < n2->y;
    }
};

int main(int argc, char const *argv[]) {
    int N;
    cin>> N;
    priority_queue<EventsNode*, vector<EventsNode*>, EventsCompare> EventsQueue;
    // map<pair<int, int>, EventsNode*> VerticalLines;

    for(int i=0; i<N; i++) {
        float x1, y1;
        int m;
        cin>> m;
        EventsNode *first, *node1, *temp, *curr;
        for(int j=0; j<m; j++) {
            cin>> x1>> y1;
            if(j==0) {
                first = new EventsNode(x1, y1, i, NULL);
                curr = first;
                // polygons[i].push_back(node1);
                EventsQueue.push(curr);
            } else {
                node1 = curr;
                temp = new EventsNode(x1, y1, i, NULL);
                
                if(node1->x == temp->x) {
                    node1->verticalNeighbor = temp;
                    temp->verticalNeighbor = node1;
                } else {
                    if(node1->x < temp->x) {
                        node1->isStartNode = true;
                        temp->isStartNode = false;
                        node1->horizontalNeighbor = temp;
                        temp->horizontalNeighbor = node1;
                    } else {
                        node1->isStartNode = false;
                        temp->isStartNode = true;
                        node1->horizontalNeighbor = temp;
                        temp->horizontalNeighbor = node1;
                    }
                }
                curr = temp;
                EventsQueue.push(curr);
            }
        }
        node1 = curr;
        temp = first;
        if(node1->x == temp->x) {
            node1->verticalNeighbor = temp;
            temp->verticalNeighbor = node1;
        } else {
            if(node1->x < temp->x) {
                node1->isStartNode = true;
                temp->isStartNode = false;
                node1->horizontalNeighbor = temp;
                temp->horizontalNeighbor = node1;
            } else {
                node1->isStartNode = false;
                temp->isStartNode = true;
                node1->horizontalNeighbor = temp;
                temp->horizontalNeighbor = node1;
            }
        }
    }
    
    set<EventsNode*, SweepNodesCompare> SweepLine;
    set<int> simpleCount;
    set<pair<int, int>> PolyIntersections;

    while(!EventsQueue.empty()) {
        auto event = EventsQueue.top();
        EventsQueue.pop();
        // EventsQueue.pop();
        SweepLine.insert(event);
        if(!event->isStartNode) {
            SweepLine.erase(event->horizontalNeighbor);
        }
        auto event2 = EventsQueue.top();
        EventsQueue.pop();
        SweepLine.insert(event2);
        if(!event2->isStartNode) {
            SweepLine.erase(event2->horizontalNeighbor);
        }
        if(event->y < event2->y) {
            // event->print("Event1");
            // event2->print("Event2");
            auto iter1 = SweepLine.lower_bound(event);
            auto iter2 = SweepLine.lower_bound(event2);
            for(auto iter=iter1; iter!=iter2; iter++) {
                // (*iter)->print("Iter");
                if((*iter)!=event && (*iter)!=event2) {
                    if((*iter)->id != event->id) {
                        PolyIntersections.insert({(*iter)->id, event->id});
                        PolyIntersections.insert({event->id, (*iter)->id});
                    } else {
                        simpleCount.insert(event->id);
                    }
                }
            }
        }
        if(!event->isStartNode) {
            SweepLine.erase(event);
        }
        if(!event2->isStartNode) {
            SweepLine.erase(event2);
        }
    }
    cout<< N - simpleCount.size()<< " "<< PolyIntersections.size()/2<< endl;
    return 0;
}