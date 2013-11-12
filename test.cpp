#include "cluster.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

vector<string> split(string str, string sep);
void print_usage();

int main(int argc, char *argv[]) {
    string buffer;
    vector<string> input_lines;
    vector<vector<string> > input_words;
    vector<double> temp_point;
    vector<Point> points;
    vector<Cluster> clusters;

    if (argc != 2) {
        print_usage();
    }

    int K = atoi(argv[1]);

    cout << "separating into " << K << " clusters" << endl;

    while (!cin.eof()) {
        getline(cin, buffer);
        input_lines.push_back(buffer);
    }

    for (auto it = input_lines.begin(); it != input_lines.end(); ++it) {
        input_words.push_back(split(*it, " "));
    }

    // now, check if each input line contains the same number of elements
    int flag = input_words[0].size();
    for (auto it = input_words.begin(); it != input_words.end(); ++it) {
        try {
            if (it->size() != flag) throw "invalid input vector";
        }
        catch (char const *except) {
            cout << except << endl;
            exit(1); // exit room gracefully.
        }

        for (auto itt = it->begin(); itt != it->end(); ++itt) {
            // generate a point
            temp_point.push_back(atof(itt->c_str()));
        }
        // push generated point onto new vector of points
        points.push_back(temp_point);
        // clear the temp_point so we can generate a new one.
        temp_point.clear();
    }

    for (auto point = points.begin(); point != points.end(); ++point) {
        // push point as a cluster onto the cluster_container.
        clusters.push_back(Cluster(*point));
    }

    cout << "all clusters" << endl;
    int number = 0;
    for (auto cl = clusters.begin(); cl != clusters.end(); ++cl) {
        cout << number+1 << ": ";
        cl->print();
        number++;
    }

    cout << endl;

    while (clusters.size() > K) {
        pair<Cluster, Cluster> closest_clusters(clusters[0], clusters[1]);
        for (auto it = clusters.begin(); it != clusters.end(); ++it)
            for (auto itt = it + 1 ; itt != clusters.end(); ++itt) {
                auto pair_first = closest_clusters.first;
                auto pair_second = closest_clusters.second;

                double base_distance = euc_distance(it->get_centroid(),
                                                    itt->get_centroid());
                double least_distance = euc_distance(pair_first.get_centroid(),
                                                     pair_second.get_centroid());

                if (base_distance < least_distance) {
                    closest_clusters.first = *it;
                    closest_clusters.second = *itt;
                }
            }
        // merge these two clusters
        Cluster temp = (closest_clusters.first + closest_clusters.second);

        auto first = find(clusters.begin(), clusters.end(),
                          closest_clusters.first);
        auto second = find(clusters.begin(), clusters.end(),
                           closest_clusters.second);

        clusters.erase(second);
        clusters.erase(first);
        clusters.push_back(temp);
    }

    int i = 0;
    for (auto cl = clusters.begin(); cl != clusters.end(); ++cl) {
        cout << "cluster #" << i+1 << ": " << endl;
        cl->print();
        i++;
        cout << endl;
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

void print_usage() {
    cout << "you aren't using this correctly" << endl;
    exit(1);
}
