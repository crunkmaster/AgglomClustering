#include <vector>
#include <map>
#include "cluster.h"
#include <typeinfo>
#include <iostream>
#include <cmath>

using namespace std;

// returns distance between two given points
double euc_distance(Point p, Point q) {
    int dimension = q.size();
    double distance;
    vector<double> components;
    double sum_of_squares = 0;

    for (int i = 0; i < dimension; i++ )
        components.push_back(q.coor()[i] - p.coor()[i]);
    for (auto it = components.begin(); it != components.end(); ++it)
        sum_of_squares += pow(*it, 2); // (q-p)^2

    distance = pow(sum_of_squares, (1.0/2));
    return distance;
}


Point::Point(vector<double> components) {
    _coordinates = components;
}

vector<double> Point::coor() const {
    return _coordinates;
}

void Point::print(void) const {
    for (auto it = _coordinates.begin(); it != _coordinates.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int Point::size(void) const {
    return _coordinates.size();
}

bool Point::operator==(const Point &rhs) const {
    if (_coordinates == rhs._coordinates) return true;
    else return false;
}

Cluster::Cluster(Point a) {
    _points.push_back(a);
}

Cluster::Cluster(vector<Point> points) {
    _points = points;
}

Cluster Cluster::operator+(const Cluster &rhs) {
    // make a cluster containing everything from the rhs
    Cluster temp(rhs._points);
    // add to the cluster everything from the current cluster
    temp._points.insert(temp._points.end(), _points.begin(), _points.end());
    return temp;
}

Cluster& Cluster::operator=(const Cluster &rhs) {
    _points = rhs._points;
    return *this;
}

bool Cluster::operator==(const Cluster &rhs) const {
    if (_points == rhs._points) return true;
    else return false;
}

void Cluster::print(void) const {
    for (auto it = _points.begin(); it != _points.end(); ++it) {
        it->print();
    }
}

Point Cluster::get_centroid(void) const {
    //essentially the dimensionality of the points
    int size = _points[0].size();
    map<int, double> sums;
    map<int, double> averages;
    vector<double> centroid;

    // for each point
    for (auto it = _points.begin(); it != _points.end(); ++it) {
        for (int i = 0; i < size; i++) {
            sums[i] += (it->coor())[i];
        }
    }
    for (int i = 0; i < size; i++) {
        // for each calculated sum, get the average
        averages[i] = sums[i] / _points.size();
        // push each average component
        centroid.push_back(averages[i]);
    }
    return Point(centroid);
}

int Cluster::num_points(void) const {
    return _points.size();
}

double Cluster::distance_from(const Cluster &other) const {
    double distance = euc_distance(this->get_centroid(), other.get_centroid());
    return distance;
}

vector<Cluster> Cluster_Container::clusters(void) const {
    return _clusters;
}

Cluster_Container::Cluster_Container(const vector<Cluster> &clusters)
    : _cluster_count(0) {
    _clusters = clusters;
}

int Cluster_Container::num_clusters(void) const {
    return _cluster_count;
}

void Cluster_Container::insert(const Cluster &cl) {
    _clusters.push_back(cl);
    _cluster_count++;
}
