#include "Airport.h"
#include <iostream>

using namespace std;

Airport::Airport() {
	elevation_ft = 0;
	latitude = 0;
	longitude = 0;
}

void Airport::print() const {
    {
        cout << "----------------------------------\n";
        cout << "ID: " << ident << endl;
        cout << "Name: " << name << endl;
        cout << "Continent: " << continent << endl;
        cout << "Type: " << type << endl;
        cout << "Elevation (ft): " << elevation_ft << endl;
        cout << "Coordinates: " << latitude << ", " << longitude << endl;
    }
}