#pragma once
#include "airport_graph.h"
#include "Flight.h"
#include "Airport.h"
#include "Djikstras.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Landmark{
    public:
        Landmark(Graph& g, string StartAirport, string Landmark, string DestAirport);
        Landmark(Graph& g, string StartAirport, string Landmark1, string Landmark2, string DestAirport);
        vector<string> getPath();
        double getDist();

    private:
        vector<string> path;
        double dist;
};