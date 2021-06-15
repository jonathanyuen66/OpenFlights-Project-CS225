#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

#include "Airport.h"
#include "PageRank.h"
#include "airport_graph.h"
#include "Djikstras.h"
#include "BFS.h"
#include "Landmark.h"

using namespace std;


int main() {
    cout << ""<< endl;
    cout << "CS225 Final Project: OpenFlights" << endl;
    cout << "Team member: zihengc2, haoyu9, yuen9, rmday2" << endl;
    
    while(true) {
        string airportFile;
        string routesFile;
        string StartingAirport;
        string DestinationAirport;
        
        bool validDataset = false;
        
        while(validDataset == false){
            cout << "Enter \"default\" to construct graph using datasets from OpenFlights.org \nor enter name of airports dataset" << endl;
            string airportIn;
            cin >> airportIn;
            if(airportIn != "default"){
                airportFile = airportIn;
                cout << "Enter name of routes dataset" << endl;
                string routesIn;
                cin >> routesIn;
                string routesFile = routesIn;
                Graph airportGraph(airportFile, routesFile);
                
                if(airportGraph.getVertices().size() == 0){
                    cout << "Empty graph constructed. Please input again:" << endl;
                }else
                    validDataset = true;
            }
            else{
                validDataset = true;
                airportFile = "airports.dat";
                routesFile = "routes.dat";
            }
        }

        Graph airportGraph(airportFile, routesFile);
        unordered_map<int, Airport> verticesInGraph = airportGraph.getVertices();

        
        cout << "Enter a number to select an operation:" << endl;
        cout << "(0) Using BFS, traverse all of the graph from a given airport " << endl;
        cout << "(1) Using BFS, traverse a given number of moves of the graph from a given airport" << endl;
        cout << "(2) Using BFS, traverse the graph until a destination airport from a given airport" << endl;
        cout << "(3) Calculate the shortest path between two airports" << endl;
        cout << "(4) Calculate the shortest path between two airports passing one landmark" << endl;
        cout << "(5) Calculate the shortest path between two airports passing two landmark" << endl;
        cout << "(6) PageRank" << endl;

        int mode; 
        cin >> mode;
         
        bool validSource = false;

        switch (mode)
        {
            case 0:{
                validSource = false;
                while(validSource == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        validSource = true;
                        BFS myBFS(airportFile, routesFile);
                        vector<string> result_all = myBFS.BFS_all(sourceAP);
                        string sourceAPName = it->second.getAirportName();
                        cout << "Printing out traversal from " << sourceAPName << ": " << endl;
                        for(unsigned i = 0; i < result_all.size(); i++){
                            cout << result_all[i] << " --> ";
                            if(i%4 == 0 && i != 0)
                                cout << "" << endl;
                        }
                        break;
                    }else{
                        cout << "Source airport ID not found in graph." << endl;
                    }
                }
                break;
            }


            case 1:{
                validSource = false;
                while(validSource == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        validSource = true;
                        cout << "Enter moves to traverse:" << endl;
                        int moves;
                        cin >> moves;
                        BFS myBFS(airportFile, routesFile);
                        vector<string> result_moves = myBFS.BFS_moves(sourceAP, moves);
                        string sourceAPName = it->second.getAirportName();
                        cout << "Printing out first " << moves << " moves from " << sourceAPName << ": " << endl;
                        for(unsigned i = 0; i < result_moves.size(); i++){
                            cout << result_moves[i];
                            if(i != result_moves.size()-1)
                                cout << " --> ";
                            if(i%4 == 0 && i != 0)
                                cout << "" <<endl;
                        }
                        break;
                    }else{
                        cout << "Source airport ID not found in graph." << endl;
                    }
                }
                break;
            }


            case 2:{
                bool validAP = false;
                while(validAP == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        string sourceAPName = it->second.getAirportName();
                        cout << "Enter a destination airport ID:" << endl;
                        int destAP; 
                        cin >> destAP;
                        auto it2 = verticesInGraph.find(destAP);
                        if(it2 != verticesInGraph.end()){
                            validAP = true;
                            BFS myBFS(airportFile, routesFile);
                            vector<string> result_dest = myBFS.BFS_dest(sourceAP, destAP);
                            string destAPName = it2->second.getAirportName();
                            cout << "Printing out traversal from " << sourceAPName << " to " << destAPName<< ": " << endl;
                            for(unsigned i = 0; i < result_dest.size(); i++){
                                cout << result_dest[i];
                                if(i != result_dest.size()-1)
                                    cout<< " --> ";
                                if(i%4 == 0 && i != 0)
                                    cout << "" << endl;
                            }
                        }
                    }else{
                        cout << "Invalid airport input" << endl;
                    }
                } 
                break;
            }


            case 3:{
                string start; 

                cout << "Enter the name of source airport name, \nor enter 'default' to use 'Newark Liberty International Airport' as start and 'Gold Coast Airport' as end:\n";
                
                cin.ignore();
                getline(std::cin, start);

                if(start == "default"){
                    Djikstras shortestpath = Djikstras(airportGraph, "Newark Liberty International Airport", "Gold Coast Airport");
                    vector<string> path = shortestpath.getPathVertices();
                    double distance = shortestpath.getShortestDistance();

                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if(i != path.size()-1)
                            cout<< " --> ";
                        if(i%4 == 0 && i != 0)
                            cout << "" << endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                } else {
                    cout << "Enter the end location:\n";
                    string end; 
                    getline(std::cin, end);
                    Djikstras shortestpath = Djikstras(airportGraph, start, end);
                    vector<string> path = shortestpath.getPathVertices();
                    double distance = shortestpath.getShortestDistance();
                    if(distance == 0.0){
                        cout<< "One or more airport not found!"<<endl;
                        break;
                    }
                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if(i != path.size()-1)
                            cout<< " --> ";
                        if(i%4 == 0 && i != 0)
                            cout << "" << endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                }
                break;
            }


            case 4:{
                string start; 
                string end; 
                string ld;
                string lld;
                cout << "Enter the start location, \nor enter 'example' to use 'Newark Liberty";
                cout << "International Airport' as start, 'Gold Coast Airport' as end, ";
                cout << "and 'Chicago O'Hare International Airport'";
                cout << "as the selected landmark:\n";
                cin.ignore();
                getline(std::cin, start);

                if(start == "example"){
                    Landmark l1 = Landmark(airportGraph, "Newark Liberty International Airport", "Chicago O'Hare International Airport", 
                                                        "Gold Coast Airport");
                    
                    vector<string> path = l1.getPath();
                    double distance = l1.getDist();

                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout<< path[i] <<endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                } else {
                    cout << "Enter the end location:\n";
                    getline(std::cin, end);
                    cout << "Enter the first landmark:\n";
                    getline(std::cin, ld);
                    Landmark l1 = Landmark(airportGraph, start, ld, end);
                    
                    vector<string> path = l1.getPath();
                    double distance = l1.getDist();

                    if(distance == 0.0){
                        cout<< "One or more airport not found!"<<endl;
                        break;
                    }
                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout<< path[i] <<endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;   
                }
                break;
            }



            case 5:{
                string airportFile = "airports.dat";
                string routesFile = "routes.dat";
                string StartingAirport;
                string DestinationAirport;
                Graph airportGraph(airportFile, routesFile);
                

                string start; 
                string end; 
                string ld;
                string lld;
                cout << "Enter the start location, \nor enter 'example' to use 'Newark Liberty";
                cout << "International Airport' as start, 'Gold Coast Airport' as end," << endl;
                cout << "and 'Chicago O'Hare International Airport', 'Beijing Capital International Airport'";
                cout << "as the selected landmark:\n";
                cin.ignore();
                getline(std::cin, start);

                if(start == "example"){
                    Landmark l1 = Landmark(airportGraph, "Newark Liberty International Airport", "Chicago O'Hare International Airport", 
                                                        "Gold Coast Airport", "Beijing Capital International Airport");
                    
                    vector<string> path = l1.getPath();
                    double distance = l1.getDist();

                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout<< path[i] <<endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                } else {
                    cout << "Enter the end location:\n";
                    getline(std::cin, end);
                    cout << "Enter the first landmark:\n";
                    getline(std::cin, ld);
                    cout << "Enter the second landmark:\n";
                    getline(std::cin, lld);
                    Landmark l1 = Landmark(airportGraph, start, ld, end, lld);
                    
                    vector<string> path = l1.getPath();
                    double distance = l1.getDist();

                    cout<<"Airports Visited: \n"<<endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout<< path[i] <<endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;   
                }

                break;
            }

            case 6:{
                string airportFile = "airports.dat";
                string routesFile = "routes.dat";
                Graph airportGraph(airportFile, routesFile);
                unordered_map<int, Airport> airportMap = airportGraph.getVertices();
                if(true){
                    PageRank *test = new PageRank();                      //create pagerank obj
                    airportGraph.adjMatrix(test);                         //generate initial adjmatrix from graph
                    test->makeA(test->num, 0.85);                         //finalize adjmatrix
                    vector<double> initial = test->initial_vector();      //generate initial vector 
                    vector<double> re = test->rank(initial, 100, false);           //perform pagerank alg, 100 iteration                        
                    cout << "\nenter the number of the most important airport to be printed: \n";
                    int top;
                    cin >> top; 
                    vector<int> id_rank = test->top_airport(top);           //pickout the top top important airport        
                }
                break;
            }
        }
        cout << "" << endl;
        cout << "" << endl;
        cout << "Computation finished. Now restarting the program. "<< endl;
        cout << "" << endl;
    }
    return 0;
}
