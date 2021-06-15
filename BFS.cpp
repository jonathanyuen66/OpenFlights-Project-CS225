#include "BFS.h"
#include <climits>

//implementation constructor that calls a graph constructor
BFS::BFS(const string &airportFile, const string &routeFile){
    string a = airportFile;
    string r = routeFile;
    airport_graph = Graph(a, r);
}


//returns a vector of strings of the traversed airports in BFS order
//this function returns all of the traversal of the disjoint set 
//that contains the source airport
vector<string> BFS::BFS_all(int sourceAP){
    vector<string> result;
    //declare a vector that covers all of the airports
    //and initialize all airports to not visited
    vector<bool> visited(14111, false);
    
    //BFS initialization
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;
    
    //BFS using a queue
    while (!queue.empty()) {
        //set currentAP to front of the queue
        currentAP = queue.front();
        //process currentAP by pushing its name to the vector
        result.push_back(airport_graph.getAPName(currentAP));
        //iterate thorugh all adjacent airports of the currentAP
        
        for (auto it : airport_graph.adjVertWithWeight(currentAP)){
            //if the ID of the adjacent airport is not visited
            if (visited[it.first] == false) { 
                //enqueue neighbor airport and set it to visited
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }
    return result;
}


//returns a vector of strings of the traversed airports in BFS order
//this function returns the traversal up to the given moves
vector<string> BFS::BFS_moves(int sourceAP, int moves){
    //unsigned temp_moves = (unsigned)moves;
    vector<string> result;
    //declare a vector that covers all of the airports
    //and initialize all airports to not visited
    vector<bool> visited(14111, false);
    
    //BFS initialization
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;
    
    //BFS using a queue
    while (!queue.empty()) {
        //stop traversing if number of moves is reached
        if(result.size() == (unsigned)moves + 1)
            return result;
        //set currentAP to front of the queue
        currentAP = queue.front();
        //process currentAP by pushing its name to the vector
        result.push_back(airport_graph.getAPName(currentAP));
        //iterate thorugh all adjacent airports of the currentAP
        for (auto it : airport_graph.adjVertWithWeight(currentAP)){
            //if the ID of the adjacent airport is not visited
            if (visited[it.first] == false) { 
                //enqueue neighbor airport and set it to visited
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }

    return result;
}


//returns a vector of strings of the traversed airports in BFS order
//this function returns the traversal up to the destination airport
//if there is no traversal between the two, returns an empty vector
vector<string> BFS::BFS_dest(int sourceAP, int destAP){
    vector<string> result;
    //declare a vector that covers all of the airports
    //and initialize all airports to not visited
    vector<bool> visited(14111, false);
    
    //BFS initialization
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;
    
    //BFS using a queue
    while (!queue.empty()) {
        //set currentAP to front of the queue
        currentAP = queue.front();
        if(currentAP == destAP){
            result.push_back(airport_graph.getAPName(currentAP));
            break;
        }
        //process currentAP by pushing its name to the vector
        result.push_back(airport_graph.getAPName(currentAP));
        //iterate thorugh all adjacent airports of the currentAP
        for (auto it : airport_graph.adjVertWithWeight(currentAP)){
            //if the ID of the adjacent airport is not visited
            if (visited[it.first] == false) { 
                //enqueue neighbor airport and set it to visited
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }
    //if destAP is not reached, return empty vector
    if(currentAP != destAP)
        return vector<string> ();
    return result;
}