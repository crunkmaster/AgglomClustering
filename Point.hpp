#include <vector>

using namespace std;

#ifndef _POINT
#define _POINT

class Point {
private:
    vector<double> _coordinates;
public:
    vector<double> coor() const;
    Point& operator=(const Point& rhs);
    Point(vector<double> components);
    void print(void) const;
    int size(void) const;
    bool operator==(const Point &rhs) const;
};

double euc_distance(Point p, Point q);

#endif
