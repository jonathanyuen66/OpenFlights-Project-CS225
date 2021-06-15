//Graphs Class

#include "airport_graph.h"
#include <math.h> 
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;


//default constructor
Graph::Graph(){

}


//constructor with airport.dat and routes.dat
//it calls the two helper functions
Graph::Graph(std::string & airportFile, std::string & routesFile){
    insertAllVertices(airportFile);
    insertAllEdge(routesFile);
}


//construct the vertices 
//such that each airport object is connected with its ID
void Graph::insertVertex(int v, Airport ap)
{
    vertices[v] = ap;
}


//takes airport.dat and insert each airport into the class line by line
void Graph::insertAllVertices(std::string & fileName)
{
    std::fstream file;
    //open the file
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currLine;
        //iterate through each line of the file
        while(getline(file, currLine)){ 
            //if a line has insufficient information, 
            //discard the line by returning default vector
            int comma = 0;
            for(unsigned i = 0; i < currLine.size(); ++i){
                char current = currLine[i];
                if(current == ',')
                    comma++;
            }
            if(comma == 13){
                //create and insert an airport object from current line in file
                Airport ap(currLine);
                insertVertex(ap.getAirportID(), ap);
            }
        }
        file.close(); 
    }
}


//helper function that converts a line of flight data to a vector
//this is a simplified version of the airport parsing counterpart
std::vector<std::string> Graph::_createEdge(string & line){
    //constructing a vector of strings of the flight information seperated by comma
    //there is no quotation marks in any line, so the function does not consider it
    //if input line does not contain all 8 columns, return a empty vector
    std::string currString = "";
    std::vector<std::string> flightVector;

    //if a line has insufficient information, 
    //discard the line by returning default vector
    int comma = 0;
    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];
        if(current == '\\')
            return flightVector;
        if(current == ',')
            comma++;
    }
    if(comma != 8)
        return flightVector;
    
    // Iterate through all characters in the line
    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];
        //if a comma is detected, push the current string to the vector
        if(current == ',') {
            flightVector.push_back(currString);
            currString = "";
        }
        //otherwise if it's just a regular char, append it to the current string
        else
            currString += current;
    }

    return flightVector;
}


//helper function that creates an edge from a vector generated from above function
Flight Graph::createEdge(std::vector<std::string> flightVector){
    int source = stoi(flightVector[3], nullptr);
    int dest = stoi(flightVector[5], nullptr);
    auto it = vertices.find(source);
    auto it2 = vertices.find(dest);
    //before caculating weight, gotta check if source and destination airports are both inserted
    //to avoid inserting an element into the map by using [] operator
    if(it != vertices.end() && it2 != vertices.end()){
        //if an edge to the same destination is not found in the list of adjacent airports
        //the find function returns the key of the desired element or the end iterator if the element is not found
        //only inserts when the flight does not exist in the adjacency list of the airport
        double weight = calcWeight(source, dest);
        return Flight(source, dest, weight);
    }
    //if either airport is not inserted, return default constructed flight
    return Flight();
}


//inserts a single edge, calls the above two helper functions
//checks if the flight already exists before inserting
void Graph::insertEdge(Flight f){       
    int source = f.getSourceId();
    int dest = f.getDestId();

    //if an edge to the same destination is not found in the list of adjacent airports
    //the find function returns the key of the desired element or the end iterator if the element is not found
    //only inserts when the flight does not exist in the adjacency list of the airport
    if (vertices[source].destAPs.find(dest) == vertices[source].destAPs.end())   
        (vertices[source].destAPs)[dest] = f;
}


//similar to insert all vertices
//iterates through routes.dat and insert flight for each line 
void Graph::insertAllEdge(std::string & fileName){
    std::fstream file;
    //open the file
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currLine;
                    
        //iterate through each line of the file
        while(getline(file, currLine)){ 
            std::vector<std::string> currVect = _createEdge(currLine);
            
            if(currVect != std::vector<std::string>()){
                Flight f = createEdge(currVect);
                Flight defaultF = Flight();
                if(!(f == defaultF))
                    insertEdge(f);
            }
        }
        file.close(); 
    }
}


//returns the unordered_map of airports
//for testing: iterate though the unordered_map to see all inserted airports
unordered_map<int, Airport> Graph::getVertices(){
    return vertices;
}


//returns the flights coming out of the given airport
//for testing: iterate though the unordered_map to see inserted flights
unordered_map<int, Flight> Graph::adjVertWithWeight(int airportID) {
    auto it = vertices.find(airportID);
    if(it != vertices.end()){
        Airport& ap = vertices[airportID];
        return ap.destAPs;
    }
    return unordered_map<int, Flight> ();
}

string Graph::getAPName(int ID){
    auto it = vertices.find(ID);
    if(it != vertices.end()){
        return vertices[ID].getAirportName();
    }
    return string();
}


//Calculating distance between two coordinates
//returns distance in KM
//adapted from: https://www.geeksforgeeks.org/program-distance-two-points-earth/
double Graph::calcWeight(int fromID, int toID){
    //convert the latitude and longitude to radian
    double lat1 = radianConvert(vertices[fromID].getAirportLatitude());
    double lon1 = radianConvert(vertices[fromID].getAirportLongitude());
    double lat2 = radianConvert(vertices[toID].getAirportLatitude());
    double lon2 = radianConvert(vertices[toID].getAirportLongitude());

    //calculate the difference
    double lonDiff = lon2 - lon1;
    double latDiff = lat2 - lat1;
    
    //using Haversine Formula, R is radious of earth in KM
    long double ans = pow(sin(latDiff / 2), 2) +cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans));
    double R = 6371;
    ans *= R;
    return ans; 
}


//helper function to calcWeight
double Graph::radianConvert(double degree)
{
    // M_PI is the constant of pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
 

//traversal graph to populate adj matrix for pagerank
void Graph::adjMatrix(PageRank *pr_obj){

    //determine and set the dimention
    int size = vertices.size();
    pr_obj->A.resize(size,vector<double>(size));
    pr_obj->name_list.resize(size);
    pr_obj->num = size;


    //initialize obj matrix
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            pr_obj->A[i][j] = 0.0;
        }        
    }

    //populate the namelist of pagerank obj
    int x = 0;
    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        if(it->second.getAirportID() == 0){
            continue;
        }
        pr_obj->name_list[x] = (it->second.getAirportID());
        x++;     
    }
    

    //check every flight of every airport
    //put the weight into the adj matrix according to the order of the namelist
    x = 0;
    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        if(x == size) break;
        if(it->second.getAirportID() == 0){
            continue;
        }

        //check the flights of the current vertices/airport
        for(auto flight = it->second.destAPs.begin(); flight != it->second.destAPs.end(); ++flight){
            int y = 0;
            //find out the proper place for the weight of the current flight according to the namelist
            for (auto temp = pr_obj->name_list.begin(); temp != pr_obj->name_list.end(); ++temp) {
                if (*temp == flight->second.getDestId()) break;
                y++;
            } 
            if(y == size) break;
            pr_obj->A[y][x] = flight->second.getWeight();
        }
        x++;
    }
}

