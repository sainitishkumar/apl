#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class rectangle {
public:
    int x1, y1;
    int x2, y2;
    int height;
    int width;
    rectangle(int a, int b, int c, int d): x1(a), y1(b), x2(c), y2(d) {
        height = y2 - y1;
        width  = x2 - x1;
    }
    bool checkIntersection(rectangle *rec);
};

bool rectangle::checkIntersection(rectangle *rec) {
    bool flag = true;
    int count = 0;
    if(this->x1 < rec->x2 && this->y1 < rec->y2) {
        count++;
    }
    // if(rec->x2 < this->x1 && rec->y2 < this->y1) {
    //     count++;
    // }
    // if(rec->x1 < this->x2 && rec->y1 < this->y2) {
    //     count++;
    // }
    if(rec->x1 < this->x2 && rec->y1 < this->y2) {
        count++;
    }
    return (count == 2);
}

int main() {
    int t, n;
    scanf("%d", &t);

    vector<rectangle* > List;
    vector<int> checkList;

    while(t>0) {
        scanf("%d", &n);
        List.assign(n, NULL);
        checkList.assign(n, 0);

        int x1, y1, x2, y2;
        for(int i=0; i<n; i++) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            rectangle *temp = new rectangle(x1, y1, x2, y2);
            List[i] = temp;
        }
        
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(i != j) {
                    if(List[i]->checkIntersection(List[j])) {
                        checkList[i] = 1;
                        break;
                    }
                }
            }
        }

        int count = 0;
        for(int i=0; i<n; i++) {
            // cout<< checkList[i]<< " ";
            if(checkList[i] == 1) count++;
        }
        // cout<< endl;
        printf("%d\n", count);
        t--;
    }
    return 0;
}
