#include <vector>

using namespace std;

#ifndef _CLUSTER
#define _CLUSTER

class Point {
private:
    vector<double> _coordinates;
public:
    vector<double> coor() const;
    Point(vector<double> components);
    void print(void) const;
    int size(void) const;
    bool operator==(const Point &rhs) const;
};

class Cluster {
private:
    vector<Point> _points;
public:
    Cluster(Point a);
    Cluster(vector<Point> points);
    int num_points(void) const;
    void print(void) const;
    Point get_centroid(void) const;
    double distance_from(const Cluster &other) const;
    Cluster operator+(const Cluster &rhs); // merges two clusters.
    Cluster& operator=(const Cluster &rhs);
    bool operator==(const Cluster &rhs) const;
};

class Cluster_Container {
private:
    vector<Cluster> _clusters;
    int _cluster_count;
public:
    Cluster_Container(const vector<Cluster> &clusters);
    vector<Cluster> clusters(void) const;
    void remove_Cluster(const Cluster &target);
    int num_clusters(void) const;
    void merge_cluster(const Cluster &first, const Cluster &second);
    void insert(const Cluster &cl);
};

double euc_distance(Point p, Point q);

#endif
