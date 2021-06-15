#include "Landmark.h"

using namespace std;

//Landmark algorithm with 1 landmark
Landmark::Landmark(Graph& g, string StartAirport, string Landmark, string DestAirport){
    //calculate the shortest path from source to landmark and landmark to dest
    Djikstras d1(g, StartAirport, Landmark);
    Djikstras d2(g, Landmark, DestAirport);
    //update dist and path
    if(d1.getShortestDistance() == 0.0 || d2.getShortestDistance() == 0.0){
        dist = 0.0;
        path.clear();
    }else{
        dist = d1.getShortestDistance() + d2.getShortestDistance();
        path.resize(d1.getPathVertices().size() + d2.getPathVertices().size() - 1);
        for(unsigned i = 0; i < d1.getPathVertices().size(); i++){
            path[i] = d1.getPathVertices()[i];
        }
        for(unsigned i = 0; i < d2.getPathVertices().size(); i++){
            path[i+ d1.getPathVertices().size() - 1] = d2.getPathVertices()[i];
        }
    }
}


//Landmark algorithm with 2 landmarks
//start and end airports fixed
//with n landmarks, need to run Djikstras n^2+n times, cost increases significantly
Landmark::Landmark(Graph& g, string StartAirport, string Landmark1, string Landmark2, string DestAirport){
    //first path: 0-1-2-3 with 1 and 2 being landmarks
    Djikstras d0_1(g,  StartAirport,  Landmark1);
    Djikstras d1_2(g, Landmark1, Landmark2);
    Djikstras d2_3(g, Landmark2, DestAirport);
    
    //second path: 0-2-1-3 with 1 and 2 being landmarks
    Djikstras d0_2(g, StartAirport, Landmark2);
    Djikstras d2_1(g, Landmark2, Landmark1);
    Djikstras d1_3(g, Landmark1, DestAirport);
    
    double temp0 = d0_1.getShortestDistance() + d1_2.getShortestDistance() + d2_3.getShortestDistance();
    double temp1 = d0_2.getShortestDistance() + d2_1.getShortestDistance() + d1_3.getShortestDistance();
    
    if(temp0 == 0.0 || temp1 == 0.0){
        dist = 0.0;
        path.clear();
    }else{
        //compute distances and update accordingly
        if(temp0 < temp1){
            dist = temp0;
            path.resize(d0_1.getPathVertices().size() + d1_2.getPathVertices().size() + d2_3.getPathVertices().size() - 2);
            for(unsigned i = 0; i < d0_1.getPathVertices().size(); i++){
                path[i] = d0_1.getPathVertices()[i];
            }
            for(unsigned i = 0; i < d1_2.getPathVertices().size(); i++){
                path[i+ d0_1.getPathVertices().size() - 1] = d1_2.getPathVertices()[i];
            }
            for(unsigned i = 0; i < d2_3.getPathVertices().size(); i++){
                path[i+ d0_1.getPathVertices().size() + d1_2.getPathVertices().size()- 2] = d2_3.getPathVertices()[i];
            }
        }else{
            dist = temp1;
            path.resize(d0_2.getPathVertices().size() + d2_1.getPathVertices().size() + d1_3.getPathVertices().size() - 2);
            for(unsigned i = 0; i < d0_2.getPathVertices().size(); i++){
                path[i] = d0_2.getPathVertices()[i];
            }
            for(unsigned i = 0; i < d2_1.getPathVertices().size(); i++){
                path[i+ d0_2.getPathVertices().size() - 1] = d2_1.getPathVertices()[i];
            }
            for(unsigned i = 0; i < d1_3.getPathVertices().size(); i++){
                path[i+ d0_2.getPathVertices().size() + d2_1.getPathVertices().size()- 2] = d1_3.getPathVertices()[i];
            }
        }
    }
}


vector<string> Landmark::getPath(){
    return path;
}


double Landmark::getDist(){
    return dist;
}
