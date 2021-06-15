//Airport Class
#include "Airport.h"
#include <string>

using namespace std;

//default constructor: setting private variables to empty strings, double to 0.0
Airport::Airport(){
    airport_id = 0;
    airport_name = "";
    airport_city = "";
    airport_country = "";
    airport_latitude = 0.0;
    airport_longitude = 0.0;
}


//constructor with matching variables
Airport::Airport(int id, string name, string city, string country, double latitude, double longitude)
: airport_id(id), airport_name(name), airport_city(city), airport_country(country), airport_latitude(latitude), airport_longitude(longitude) {  }


//constructor with a single line from airport.dat
//the ending \n is not in the input line
Airport::Airport(string &line){
    //constructing a vector of strings of the airport information seperated by comma
    //quotes are not included
    //if input line does not contain all 13 columns, call default constructor 
    bool quoteFlag = false;
    std::string currString = "";
    std::vector<std::string> airportVector;

    // Iterate through all characters in the line
    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];

        // if quotation mark has not occured before
        if(!quoteFlag) {
            //push the current string to the vector when encounters a ","
            //and reset current string
            if(current == ',') {
                airportVector.push_back(currString);
                currString = "";
            }
            //if current char is a quotation mark, turn on the quote flag
            else if(current == '"')
                quoteFlag = true;
            //if just a regular char, append it to the current string
            else
                currString += current;
        }
        // if there is a quotation mark from before
        else{
            //if we are at the second quotation mark
            if(current == '"' && i+1 < line.size()) {
                if(line[i+1] == '"') {
                    currString += '"';
                    i++;
                }
                //don't add this quotation and turn off the flag
                else
                    quoteFlag = false;
            }
            //if just a regular char, append it to the current string
            else
                currString += current;
        }
    }
    
    //updating private variables
    airport_id = stoi(airportVector[0], nullptr);
    airport_name = airportVector[1];
    airport_city = airportVector[2];
    airport_country = airportVector[3];
    airport_latitude = stod(airportVector[6], nullptr);
    airport_longitude = stod(airportVector[7], nullptr);
}


//vector constructor
//note that the vector must be in the right order
//such that the latitude and longitude must be vector[6] and vector[7]
Airport::Airport(vector<string> airportVector){
    airport_id = stoi(airportVector[0], nullptr);
    airport_name = airportVector[1];
    airport_city = airportVector[2];
    airport_country = airportVector[3];
    airport_latitude = stod(airportVector[6], nullptr);
    airport_longitude = stod(airportVector[7], nullptr);
}


//getters
int Airport::getAirportID() {
    return airport_id;
}
string Airport::getAirportName() {
    return airport_name;
}
string Airport::getAirportCity() {
    return airport_city;
}
string Airport::getAirportCountry() {
    return airport_country;
}
double Airport::getAirportLatitude() {
    return airport_latitude;
}
double Airport::getAirportLongitude() {
    return airport_longitude;
}