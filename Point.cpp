#include <vector>
#include "Point.hpp"
#include <cmath>
#include <iostream>

/**
 * generate a point from a vector of components.
 * 
 * @param components  an n-dimensional vector<double> giving the components.
 */

Point::Point(vector<double> components) {
    _coordinates = components;
}

/**
 * returns the coordinates vector of a Point object
 *
 * @return  vector<double>
 */
vector<double> Point::coor() const {
    return _coordinates;
}

/**
 * prints a point nicely
 */
void Point::print(void) const {
    cout << "[";
    for (auto it = begin(_coordinates); it != end(_coordinates); ++it) {
	// if we are not printing the last coordinate
	if (it != end(_coordinates) - 1) {
	    cout << *it << " ";
	}
	else {
	    cout << *it; 
	}
    }
    cout << "]";
}

/**
 * returns the number of components in a point
 * @return int representing number of components
 */
int Point::size(void) const {
    return _coordinates.size();
}

/**
 * overloaded assignment operator, makes one point equal to another
 * by setting their _coordinates fields to be the same
 *
 * @param rhs a const Point& 
 * @return Point& to the object that was set equal to rhs
 */
Point& Point::operator=(const Point& rhs) {
    _coordinates = rhs._coordinates;
    return (*this);
}

/**
 * overloaded equality operator, compares two points and says
 * if they are equal.
 * 
 * @return bool: true if equal, false otherwise.
 */
bool Point::operator==(const Point &rhs) const {
    if (_coordinates == rhs._coordinates) return true;
    else return false;
}

/**
 * computes the standard euclidian distance between
 * two n-dimensional Point objects (where n is the same for both of them).
 * 
 * @param p an n-dimensional Point
 * @param q an n-dimensional Point
 * @return a double representing the euclidian distance between them.
 */
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
