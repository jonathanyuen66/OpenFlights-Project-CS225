#include "Flight.h"
#include <limits.h>

//Default constructor
Flight::Flight(){
    sourceAP = -1;
    destinationAP = -1; 
    weight = INT_MAX;
};


//constructor without given weight
//treat weight as infinity
Flight::Flight(int s, int d){
    sourceAP = s;
    destinationAP = d; 
    weight = INT_MAX;
};

//constructor with all private variables
Flight::Flight(int s, int d, double w){
    sourceAP = s;
    destinationAP = d; 
    weight = w;
};

//getters
int Flight::getSourceId() {
    return sourceAP;
}


int Flight::getDestId() {
    return destinationAP;
}


double Flight::getWeight() {
    return weight;
}

//setters
void Flight::setWeight(double w) {
    weight = w;
}

void Flight::setSource(double s) {
    sourceAP = s;
}

void Flight::setDestination(double d) {
    destinationAP = d; 
}

// returns true if the weight comparison holds
bool Flight::operator<(const Flight& other) const {
    return weight < other.weight;
}

//return true if two flights are from and to the same airports
bool Flight::operator==(Flight& other) const {
    if (sourceAP != other.sourceAP)
        return false;
    if (destinationAP != other.destinationAP)
        return false;
    return true;
}