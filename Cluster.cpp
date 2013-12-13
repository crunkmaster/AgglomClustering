#include <vector>
#include <map>
#include "Cluster.hpp"
#include "Point.hpp"
#include <typeinfo>
#include <iostream>
#include <cmath>

using namespace std;

// initialize _count to 0
size_t Cluster::_count = 0;

/**
 * constructor, empty initializes the _points vector
*/
Cluster::Cluster(void) {
    _points = {}; // empty points vector;
}

/**
 * Constructor, creates a Cluster from an n-dimensional Point.
 * Creates the Cluster by adding the Point to the Cluster's _points vector
 * and then assigning it an id and incrementing the number of instantiated clusters
 * @param a  the Point from which the cluster should be created.
 */

Cluster::Cluster(Point a) {
    _points.push_back(a);
    _id = _count;
    _count++;
}

/**
 * Constructor, creates a Cluster from a vector of n-dimensional Point's.
 * Creates the cluster by making the _points vector equal to the points parameter
 * @param points   the vector<Point> from which the cluster should be created.
 */
Cluster::Cluster(vector<Point> points) {
    _points = points;
    // _id = _count;
    // _count++;
}

/**
 * Appends the input Cluster to the current cluster
 * @param rhs  a const reference to the Cluster you would like to append.
 */
void Cluster::add(const Cluster& rhs) {
    this->_points.insert(end(_points), begin(rhs._points), 
			 end(rhs._points));
}

/**
 * Swaps two Cluster's by swapping their _id and _points fields.
 * using std::swap
 * @param first a reference to the first Cluster.
 * @param second a reference to the second Cluster.
 */
void swap(Cluster& first, Cluster &second) {
    using std::swap;
    
    swap(first._id, second._id);
    swap(first._points, second._points);
}

/**
 * overloaded assignment operator which makes a copy of the
 * right hand side and swaps it with the left hand side. using Cluster::swap
 *
 * @param rhs  the Cluster on the right hand side of the assignment
 * @return a reference to the Cluster after the assignment has taken place.
 */
Cluster& Cluster::operator=(Cluster rhs) {
    swap(*this, rhs);
    return *this;
}

/**
 * overloaded equality operator. 
 * 
 * @param rhs  a const reference to the Cluster on the right hand side
 * @return a bool. true if equal, false otherwise.
 */
bool Cluster::operator==(const Cluster &rhs) const {
    if (_points == rhs._points) return true;
    else return false;
}

/**
 * Nicely prints a cluster.
 */
void Cluster::print(void) const {
    cout << "[";

    for (auto it = begin(_points); it != end(_points); ++it) {
	if (it != end(_points) - 1) {
	    it->print();
	    cout << "," << endl;
	}
	else {
	    it->print();
	}
    }
    cout << "]";
}

/** 
 * Returns the id associated with a Cluster object
 * @return size_t  the _id field of the cluster
 */
size_t Cluster::id(void) const {
    return _id;
}

/**
 * sets the _id field of the cluster to the parameter id
 * @param id  a size_t representing the desired id
 */
void Cluster::setId(size_t id) {
    _id = id;
}

/**
 * Computes the distance between the current Cluster, and another Cluster
 * @param other   the const reference to the Cluster you want to find the distance to
 * @return double representing the distance from the current cluster and the parameter.
 */
double Cluster::distance_from(const Cluster &other) const {
    double sum_distances = 0;
    for (Point point : _points)
        for (Point other_point : other._points)
            sum_distances += euc_distance(point, other_point);
    
    return sum_distances / (this->_points.size() * other._points.size());
}
