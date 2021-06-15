#include "Djikstras.h"
#include <map>
#include <climits>
#include <stack>

using namespace std;

/* 
*	vertexExists(string node)
*	Description: This function ensures that an airport exists in the adjacency list.
*	input: node -- the name of the airport as a string
*	return: boolean that indicate whether the vertex exist or not
*/
bool Djikstras::vertexExists(string node) {
    if (adjacency_list.find(node) == adjacency_list.end()) {
        return false;
    }
    return true;
}

/* 
*	getAdjacent(string source)
*	Description: This function finds all of the neighboring airports to the input airport 
    and returns a vector of the neighboring airport and its flight distance from the input airport.
*	input: source -- the name of the airport as a string
*	return: a vector of pairs of neighboring airports and their respective distances from the input airport
*/
vector<pair<int, double>> Djikstras::getAdjacent(string source) {
    auto lookup = adjacency_list.find(source);
    vector<string> result;

    if (lookup == adjacency_list.end())
        return vector<pair<int,double>>();

    else {
        vector<pair<int,double>> vertex_list;
        unordered_map<int, Flight> &map = adjacency_list.at(source);
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(make_pair(it->first, it->second.getWeight()));
        }
        return vertex_list;
    }
}

/* 
*	Djikstras(Graph g, string StartAirport, string DestAirport)
*	Description: Implementation of Djikstra's algorithm for finding the shortest path between airports.
*	input: g -- Graph of the connecting airports
*	       StartAirport -- the starting airport
*	       DestAirport -- the destination airport
*	return: N/A
*/
Djikstras::Djikstras(Graph g, string StartAirport, string DestAirport) {
    path_vertices.clear();
    vector<string> vertices;  

    unordered_map<int, Airport> airportMap = g.getVertices();

    for (auto it = airportMap.begin(); it != airportMap.end(); ++it) {
        vertices.push_back(it->second.getAirportName());
        if(it->second.getAirportName() == StartAirport) {
            distances.insert(make_pair(it->second.getAirportName(), 0.0));
            previous_nodes.insert(make_pair(it->second.getAirportName(), ""));
            visited.insert(make_pair(it->second.getAirportName(), false));
        }
        else {
            distances.insert(make_pair(it->second.getAirportName(), INT_MAX));
            previous_nodes.insert(make_pair(it->second.getAirportName(), ""));
            visited.insert(make_pair(it->second.getAirportName(), false));
        }
    }
    pair<double,string> initial = make_pair(0.0, StartAirport);
    Q.push(initial);

    for(auto it = airportMap.begin(); it != airportMap.end(); ++it) {
        adjacency_list.insert(make_pair(it->second.getAirportName(), it->second.destAPs));
    }

    while(Q.top().second != DestAirport) {
        pair<double, string> currentNode = Q.top();
        Q.pop();
        vector<pair<int , double>> neighbors = getAdjacent(currentNode.second);
        vector<pair<string, double>> neighborNames;
        for (auto each : neighbors) {
            for (auto it = airportMap.begin(); it != airportMap.end(); ++it) {
                if (each.first == it->first) {
                    neighborNames.push_back(make_pair(it->second.getAirportName(), each.second));
                }
            }
        }
        for (auto neighbor : neighborNames) {
            if (visited[neighbor.first] == false && visited[currentNode.second] == false) {
                double weight = neighbor.second;
                if(weight + distances[currentNode.second] < distances[neighbor.first]) {
                    distances[neighbor.first] = weight + distances[currentNode.second];
                    previous_nodes[neighbor.first] = currentNode.second;
                    Q.push(make_pair(distances[neighbor.first], neighbor.first)); 
                }
            }
        }
        visited[currentNode.second] = true;
    }
 
    path = distances[DestAirport];

    string key = DestAirport;
    path_vertices.push_back(DestAirport);
    while(key != StartAirport) {
        path_vertices.push_back(previous_nodes[key]);
        key = previous_nodes[key];
    }
    std::reverse(path_vertices.begin(), path_vertices.end());
}

/* 
*	getShortestDistance()
*	Description: getter function
*	return: gets the path distance from the starting airport to the destination airport
*/
double Djikstras::getShortestDistance() const {
  return path;
}

/* 
*	getPathVertices()
*	Description: getter function
*	return: gets all of the airports along the path
*/
vector<string> Djikstras::getPathVertices() const {
  return path_vertices;
}