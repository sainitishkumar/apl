#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class point {
    public:
    int x, y;
    point(int a, int b): x(a), y(b) {}
    float distance(point *p);
    float slope(point *p);
    int area(point *p);
};

int point::area(point *p) {
    return (this->x - p->x)*(this->x - p->x) + 
            (this->y - p->y)*(this->y - p->y);
}

float point::slope(point *p) {
    return ((float)(this->y - p->y)) / ((float)(this->x - p->x));
}

float point::distance(point *p) {
    return sqrt((this->x - p->x)*(this->x - p->x) + 
                (this->y - p->y)*(this->y - p->y));
}

vector<pair<float, float>> possibleVtx(point *a, point *b) {
    // there are four possible vertices for given two points as an edge
    float d = a->distance(b);

    if(a->x == b->x) {
        int x = a->x;
        int y1 = a->y;
        int y2 = b->y;
        return {{x+d, y1}, {x+d, y2}, {x-d, y1}, {x-d, y2}};
    } else if(a->y == b->y) {
        int y = a->y;
        int x1 = a->x;
        int x2 = b->x;
        return {{x1, y+d}, {x1, y-d}, {x2, y+d}, {x1, y-d}, {x2, y-d}};
    } else {
        // line not parallel to x axis and y axis
        float m = a->slope(b);
        
        int x1 = a->x, y1 = a->y;
        int x2 = b->x, y2 = b->y;

        float shift = sqrt((d*d)/(m*m+1));

        pair<float, float> a = {x1 - m*shift, y1 + shift};
        pair<float, float> b = {x1 + m*shift, y1 - shift};
        pair<float, float> c = {x2 - m*shift, y2 + shift};
        pair<float, float> d = {x2 + m*shift, y2 - shift};
        
        return {a, b, c, d};
    }
}

int main() {
    // shift all x and y by 30000 to Q1
    int n, x, y;
    scanf("%d", &n);
    
    vector<vector<int>> table;
    for(int i=0; i<60001; i++) {
        vector<int > temp;
        table.push_back(temp);
    }

    vector<point* > vec(n, NULL);
    for(int i=0; i<n; i++) {
        scanf("%d %d", &x, &y);
        x+=30000;
        y+=30000;
        vec[i] = new point(x, y);
        table[x].push_back(y);
    }

    int maxArea = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(i==j) continue;
            // considering these two as one side of the square
            // we can find coords for possible vertices of square
            // cout<< "main - "<< vec[i]->x-30000<< " "<< vec[i]->y-30000<< " "<< vec[j]->x-30000<< " "<< vec[j]->y-30000<< endl;
            auto vecs = possibleVtx(vec[i], vec[j]);
            // first pair
            int pos_x0 = vecs[0].first, pos_y0 = vecs[0].second;
            int pos_x1 = vecs[2].first, pos_y1 = vecs[2].second;
            // second pair
            int pos_x2 = vecs[1].first, pos_y2 = vecs[1].second;
            int pos_x3 = vecs[3].first, pos_y3 = vecs[3].second;
            
            // cout<< pos_x0<< " "<< pos_x1<< " "<< pos_x2<< " "<< pos_x3<< endl;
            int area = vec[i]->area(vec[j]);
            // now check if either of the pairs exist in the table
            if(pos_x0 < 60001 && pos_x0 >= 0) {
                if(find(table[pos_x0].begin(), table[pos_x0].end(), pos_y0)!=table[pos_x0].end() &&
                    find(table[pos_x1].begin(), table[pos_x1].end(), pos_y1)!=table[pos_x1].end()) {
                        maxArea = max(maxArea, area);
                    }
            }
            if(pos_x2 < 60001 && pos_x2 >= 0) {
                if(find(table[pos_x2].begin(), table[pos_x2].end(), pos_y2)!=table[pos_x2].end() &&
                    find(table[pos_x3].begin(), table[pos_x3].end(), pos_y3)!=table[pos_x3].end()) {
                        maxArea = max(maxArea, area);
                    }
            }
        }
    }
    (maxArea == 0)? printf("NO\n") : printf("%d\n", maxArea);
    return 0;
}