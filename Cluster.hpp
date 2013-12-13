#include <vector>
#include <tuple>
#include "Point.hpp"

using namespace std;

#ifndef _CLUSTER
#define _CLUSTER

class Cluster {
private:
    static size_t _count;
    size_t _id;
    vector<Point> _points;
public:
    Cluster(void); //default constructor
    Cluster(Point a);
    Cluster(vector<Point> points);
    size_t id(void) const;
    void setId(size_t id);
    void print(void) const;
    double distance_from(const Cluster &other) const;
    void add(const Cluster& rhs);
    Cluster operator+(const Cluster &rhs); // finds intersection of two clusters
    friend void swap(Cluster &first, Cluster &second);
    Cluster& operator=(Cluster rhs);
    bool operator==(const Cluster &rhs) const;
};

#endif
