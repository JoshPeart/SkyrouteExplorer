#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H

#include "Airport.h"
#include <vector>

class AirportManager
{
private:
	std::vector<Airport> airports;
public:

	// ------ FUNCTION DECLERATIONS ------
	void loadAirports(vector<Airport>& airports);
	void printAirport(const Airport& a);

	void searchByCountry(const vector<Airport>& airports);
	void searchByName(const vector<Airport>& airports);
	void searchByIATA(const vector<Airport>& airports);

	void countByType(const vector<Airport>& airports);
	void addAirport(vector<Airport>& airports);
	void saveAirports(const vector<Airport>& airports);
};

#endif

