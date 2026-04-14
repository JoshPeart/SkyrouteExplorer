#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
using namespace std;

struct Airport {
	string ident;
	string type;
	string name;
	string elevation_ft;
	string continent;
	string iso_country;
	string iso_region;
	string municipality;
	string icao_code;
	string iata_code;
	string gps_code;
	string local_code;
	string latitude;
	string longitude;
};

#endif

