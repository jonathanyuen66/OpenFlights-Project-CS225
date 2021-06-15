#pragma once
#include "airport_graph.h"
#include "Flight.h"
#include "Airport.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Djikstras {
    public:
        //
        Djikstras (Graph g, string StartAirport, string DestAirport);
        //getters
        double getShortestDistance() const;
        vector<string> getPathVertices() const;
        vector<pair<int, double>> getAdjacent(string Source);
        //helper function that checks whether the vertex exist
        bool vertexExists(string node);

    private:
        map<string, double> distances;
        unordered_map<string, string> previous_nodes;
        priority_queue<pair<double, string>, vector<pair<double, string>>,greater<pair<double, string>> > Q;
        unordered_map <string, bool> visited; 
        double path;
        unordered_map<string, unordered_map<int, Flight> > adjacency_list;
        vector<string> path_vertices;
};