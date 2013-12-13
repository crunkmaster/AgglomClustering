#include <map>
#include <list>
#include "Cluster.hpp"

using namespace std;

#ifndef _CLUSTERCONTAINER
#define _CLUSTERCONTAINER

typedef pair<size_t, size_t> IDPair;

class ClusterContainer {
private:
    list<Cluster> _clusters;
    map<IDPair, double> _dist_table;
public:
    ClusterContainer(void);
    ClusterContainer(const list<Cluster> &clusters);
    void calcDistances(void);
    list<Cluster> clusters(void) const;
    void removeCluster(const Cluster &target);
    size_t size(void) const;
    void merge(size_t first_id, size_t second_id);
    void insert(const Cluster &cl);
    IDPair getClosest(void);
    void printDistTable(void) const;
    Cluster clusterById(size_t id);
};

struct CmpDstPair {
    inline bool operator()(const pair<IDPair, double> &l, 
		    const pair<IDPair, double> &r) const;
};

#endif
