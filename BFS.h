#pragma once
#include "airport_graph.h"
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

class BFS {
    public:
        BFS(const string &airportFile, const string &routeFile);
        vector<string> BFS_all(int sourceAP);
        vector<string> BFS_moves(int sourceAP, int moves);
        vector<string> BFS_dest(int sourceAP, int destAP);
    
    private:
        Graph airport_graph;
};