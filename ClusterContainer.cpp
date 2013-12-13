#include "ClusterContainer.hpp"
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

/**
 * Functor for comparing elements in the _dist_table map in the 
 * if the distance associated with l is less than the distance associated
 * with r, it returns true, else false.
 * @param l  a const reference to a pair<IDPair, double>
 * @param r  a const reference to a pair<IDPair, double>
 * @return a bool represent whether l < r
 */
bool CmpDstPair::operator()(const pair<IDPair, double> &l,
                            const pair<IDPair, double> &r) const {
    return l.second < r.second;
}

/**
 * Returns a copy of the list of clusters associated with the ClusterContainer
 * @return list<Cluster>  that is a copy of _clusters;
 */
list<Cluster> ClusterContainer::clusters(void) const {
    return _clusters;
}

/**
 * Calculate distances between all of the Cluster's in the ClusterContainer,
 * intelligently avoiding the recalculation of distances that have already been defined,
 * or distances that don't need to be defined.
 */
void ClusterContainer::calcDistances(void) {
    for (auto cluster : _clusters)
        for (auto other : _clusters) {
            IDPair currPair = make_pair(cluster.id(), other.id());
            if (_dist_table.find(currPair) != _dist_table.end())
                continue; // don't bother calculating a new distance
            else {
                if (currPair.first >= currPair.second) {
                    // keep these undefined to avoid recalculating
                    // and to also avoid computing distances to self.
                    continue;
                }
                else {
                    // if the clusters are different, calc distance
                    // and update the table.
                    _dist_table[currPair] = cluster.distance_from(other);
                }
            }
        }
}

/**
 * Constructor, empty initializes the _clusters list in the ClusterContainer
 */
ClusterContainer::ClusterContainer(void) {
    _clusters = {}; // empty initialize clusters list
}

/**
 * Constructor, initializes the _clusters list in the ClusterContainer 
 * from the parameter
 * @param clusters a const reference to the list<Cluster> object from which
 * the _clusters list ClusterContainer should be initialized
 */
ClusterContainer::ClusterContainer(const list<Cluster> &clusters) {
    _clusters = clusters;
}

/** 
 * Returns the number of Cluster's stored in the container
 * @return size_t  representing the number of Cluster's in the _clusters list
 */
size_t ClusterContainer::size(void) const {
    return _clusters.size();
}

/**
 * Adds a Cluster to the container. 
 * @param cl  a const reference to the Cluster you intend to insert.
 */
void ClusterContainer::insert(const Cluster &cl) {
    _clusters.push_back(cl);
}

/**
 * Returns the IDPair of the two closest Cluster's 
 * @return IDPair associated with the smallest entry in the _dist_table
 */
IDPair ClusterContainer::getClosest(void) {
    pair<IDPair, double> min_elem = *min_element(begin(_dist_table),
                                                 end(_dist_table), CmpDstPair());
    return min_elem.first;
}

/**
 * Finds the Cluster in the ClusterContainer associated with an id.
 * @param id  a size_t representing the id of the cluster you are looking for.
 * @return a copy of the Cluster with that id
 */
Cluster ClusterContainer::clusterById(size_t id) {
    for (auto cluster : _clusters) {
	if (cluster.id() == id)
	    return cluster;
    }
    throw string("invalid id");
}

/**
 * Merges two Cluster's in the container by id.
 * @param first_id  a size_t containing the id of the first Cluster
 * @param second_id  a size_t containing the id of the second Cluster
*/
void ClusterContainer::merge(size_t first_id, size_t second_id) {
    // find clusters associated with id's passed
    Cluster first;
    Cluster second;

    for (auto cluster : _clusters) {
        if (cluster.id() == first_id) first = cluster;
        else if (cluster.id() == second_id) second = cluster;
    }

    auto first_it = find(begin(_clusters), end(_clusters), first);
    auto second_it = find(begin(_clusters), end(_clusters), second);
    first_it->add(second);
    _clusters.erase(second_it);

    // remove all things in the table to/from cluster with second_id;
    // because that cluster no longer exists.
    map<IDPair, double> _dist_table_cp(_dist_table);
    for (pair<IDPair, double> elem : _dist_table) {
        IDPair key = elem.first;
        if (key.first == second_id or key.second == second_id) {
            _dist_table_cp.erase(key);
        }
    }
    _dist_table.clear();
    _dist_table.insert(begin(_dist_table_cp), end(_dist_table_cp));
    // if the pair pertains to the cluster that was just added to,
    // recalculate the distances associated with that pair.
    for (auto elem : _dist_table){
        if ((elem.first.first == first_id) or (elem.first.second == first_id)) {
            IDPair currPair = make_pair(elem.first.first, elem.first.second);
            Cluster elem_first;
            Cluster elem_second;
            // find the clusters matching the ids and update the distances
            for (auto cluster : _clusters) {
                if (cluster.id() == elem.first.first) elem_first = cluster;
                if (cluster.id() == elem.first.second) elem_second = cluster;
            }
            // distance between cluster with id elem.first.first and elem.first.second
            _dist_table[currPair] = elem_first.distance_from(elem_second);
        }
    }
}

/**
 * Prints table of distances between clusters in a readable format
 */
void ClusterContainer::printDistTable(void) const {
    for (pair<IDPair, double> elem : _dist_table) {
        auto key = elem.first;
        auto val = elem.second;

        cout << "pair: " << key.first << ", " << key.second << ": "
             << "distance: " << val << endl;
    }
}
