#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct line {
    float x1, y1, x2, y2;
    line(float xa, float ya, float xb, float yb): x1(xa), y1(ya), x2(xb), y2(yb) {};
};

bool check_line_intersection(line* line1, line* line2, float* intersectionx, float* intersectiony) {
    float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
    
    s10_x = line1->x2 - line1->x1;
    s10_y = line1->y2 - line1->y1;
    s32_x = line2->x2 - line2->x1;
    s32_y = line2->y2 - line2->y1;
    
    denom = s10_x * s32_y - s32_x * s10_y;
    if (denom == 0)
        return false;
    
    s02_x = line1->x1 - line2->x1;
    s02_y = line1->y1 - line2->y1;
    s_numer = s10_x * s02_y - s10_y * s02_x;
    t_numer = s32_x * s02_y - s32_y * s02_x;
    
    if ((s_numer < 0) == (denom > 0))
        return false;
    if ((s_numer > denom) == (denom > 0))
        return false;
    if ((t_numer < 0) == (denom > 0))
        return false;
    if((t_numer > denom) == (denom > 0))
        return false;
    
    t = t_numer / denom;
    *intersectionx = line1->x1 + (t * s10_x);
    *intersectiony = line1->y1 + (t * s10_y);
    
    return true;
}

bool notsame(int ix, int iy, line* l1) {
    if((ix==l1->x1 && iy==l1->y1) || ix==l1->x2 && iy==l1->y2) return false;
    return true;
}

bool check_simple_polygon(vector<line*> polygon) {
    for(int i=0; i<polygon.size(); i++) {
        auto line1 = polygon[i];
        for(int j=0; j<polygon.size(); j++) {
            auto line2 = polygon[j];
            float ix, iy;
            if(check_line_intersection(line1, line2, &ix, &iy) 
                && notsame(ix, iy, line1) && notsame(ix, iy, line2)) {
                return false;
            }
        }
    }
    return true;
}

bool check_polygon_intersection(vector<line*> polygoni, vector<line*> polygonj) {
    for(int i=0; i<polygoni.size(); i++) {
        for(int j=0; j<polygonj.size(); j++) {
            float ix, iy;
            if(check_line_intersection(polygoni[i], polygonj[j], &ix, &iy)) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char const *argv[]) {
    int N;
    cin>> N;
    // vector<vector<pair<int, int>>> polygons(N, vector<pair<int, int>>());
    vector<vector<line*>> polygons(N, vector<line*>());
    for(int i=0; i<N; i++) {
        float x1, y1, x2, y2;
        int m;
        cin>> m;
        vector<pair<float, float>> points;
        for(int j=0; j<m; j++) {
            cin>> x1>> y1;
            points.push_back({x1, y1});
        }
        for(int j=0; j<points.size()-1; j++) {
            auto line1 = new line(points[j].first, points[j].second, points[j+1].first, points[j+1].second);
            polygons[i].push_back(line1);
        }
        int j = points.size()-1;
        auto line1 = new line(points[j].first, points[j].second, points[0].first, points[0].second);
        polygons[i].push_back(line1);
    }
    // count number of simple polygons
    int simplePolygonCount = 0;
    for(auto polygon: polygons) {
        if(check_simple_polygon(polygon)) {
            simplePolygonCount++;
        }
    }
    cout<< simplePolygonCount<< " ";

    // count number of polygons intersecting
    set<pair<int, int>> pairs;
    for(int i=0; i<polygons.size(); i++) {
        for(int j=i+1; j<polygons.size(); j++) {
            auto polyi = polygons[i];
            auto polyj = polygons[j];
            if(check_polygon_intersection(polyi, polyj)) {
                pairs.insert({i, j});
                pairs.insert({j, i});
            }
        }
    }
    cout<< pairs.size()/2<< endl;
    return 0;
}