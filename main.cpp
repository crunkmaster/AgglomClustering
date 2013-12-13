#include "Cluster.hpp"
#include "Point.hpp"
#include "ClusterContainer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

vector<string> split(string str, string sep);
void print_usage(string problem);

int main(int argc, char *argv[]) {
    string buffer;
    vector<string> input_lines;
    vector<vector<string> > input_words;
    vector<double> temp_point;
    vector<Point> points;
    ClusterContainer container;

    int K;

    // make sure that the argument being passed is a valid int
    if (argc != 2) {
        print_usage(string("incorrect number of arguments"));
    }
    try {
        if (atoi(argv[1]) == atof(argv[1]))
            K = atoi(argv[1]);
        else
            throw string("not an integer!");
    }
    catch (string &exc) {
        print_usage(string("please enter an integer"));
    }

    while (!cin.eof()) {
        getline(cin, buffer);
        input_lines.push_back(buffer);
    }

    for (auto line : input_lines)
        input_words.push_back(split(line, " "));

    // now, check if each input line contains the same number of elements
    int flag = input_words[0].size();
    for (auto word : input_words) {
        try {
            if (word.size() != size_t(flag)) throw "invalid input vector";
        }
        catch (char const *except) {
            cout << except << endl;
            exit(1); // exit room gracefully.
        }

        for (auto comp : word) {
            // generate a point
            temp_point.push_back(atof(comp.c_str()));
        }
        // push generated point onto new vector of points
        points.push_back(temp_point);
        temp_point.clear();
    }

    for (auto point : points) {
        // push point as a cluster onto the cluster_container.
        container.insert(Cluster(point));
    }

    while (container.size() > size_t(K)) {
        container.calcDistances(); // populate the initial distance table
	//	container.printDistTable();
        // find the pair with the smallest distance between them
	IDPair closest = container.getClosest();

	// output the pair of clusters being merged
	cout << "Merging: "
	     << "cluster: ";
	container.clusterById(closest.first).print();
	cout << endl;
	cout << "cluster: ";
	container.clusterById(closest.second).print();
	cout << endl;

	// merge the two closest clusters
        container.merge(closest.first, closest.second);
    }

    cout << "final clusters:" << endl;
    for (auto cluster : container.clusters()) {
        cluster.print();
        cout << endl << endl;
    }

    return 0;
}

vector<string> split(string str, string sep) {
    char *cstr = const_cast<char *>(str.c_str());
    char *current;
    vector<string> arr;

    current = strtok(cstr, sep.c_str());

    while (current != NULL ) {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}

void print_usage(string problem) {
    cout << problem << endl;
    cout << "usage: cat [textfile] | ./lab6 [num_clusters] > [outfile]" << endl;
    exit(1);
}
