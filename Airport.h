#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Flight.h"

using namespace std;

class Airport {
    public:
        //constructors
        Airport();
        Airport(string &line);
        Airport(vector<string> airportVector);    
        Airport(int id, string name, string city, string country, double latitude, double longitude);
        
        //getters
        int getAirportID();
        string getAirportName();
        string getAirportCity();
        string getAirportCountry();
        double getAirportLatitude();
        double getAirportLongitude();

        //each airport how has an unordered map that records
        //the ID of each adjacent airport and the corresponding flight
        //it can be used as an adjacency list
        unordered_map<int, Flight> destAPs;

    private:
        int airport_id;
        string airport_name;
        string airport_city;
        string airport_country;
        double airport_latitude;
        double airport_longitude;
        
};
