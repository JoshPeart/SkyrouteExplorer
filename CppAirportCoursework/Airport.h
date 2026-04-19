#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
using namespace std;

class Airport {
public:
	string ident;
	string type;
	string name;
	int elevation_ft;
	string continent;
	string iso_country;
	string iso_region;
	string municipality;
	string icao_code;
	string iata_code;
	string gps_code;
	string local_code;
	double latitude;
	double longitude;

	Airport();
	void print() const;
};

#endif

