// CppAirportCoursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Flights {
    int field;
    string airport_id;
    string type;
    string name;
    string elevation_ft;
    string continent;
    string iso_country;
    string iso_reigon;
    string coordinates;
};

int main()
{
    ifstream file("airports.csv");

    if (!file.is_open()) {
        cout << "ERROR: Could not find airports.csv." << endl;
        return 0;
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string field;
        string airport_id;
        string type;
        string name;
        string elevation_ft;
        string continent;
        string iso_country;
        string iso_reigon;
        string coordinates;

        try {
            getline(ss, field, ','); airport_id = field;
            getline(ss, field, ','); type = field;
            getline(ss, field, ','); name = field;
            getline(ss, field, ','); elevation_ft = field;
            getline(ss, field, ','); continent = field;
            getline(ss, field, ','); iso_country = field;
            getline(ss, field, ','); iso_reigon = field;
            getline(ss, field, ','); 
            getline(ss, field, ',');
            getline(ss, field, ','); 
            getline(ss, field, ','); 
            getline(ss, field, ','); 
            getline(ss, field, ','); 
            getline(ss, field, ','); coordinates = field;


            if (iso_country == "NZ") {
                cout << "Country: " << iso_country << " Type: " << type << " Name: " << name << " Coordinates: " << coordinates << endl;
            }
        }
        catch (...) {
            // Malformed row - skip it
        }
    };

    return 0;
}


