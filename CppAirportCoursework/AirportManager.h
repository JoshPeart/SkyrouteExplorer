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
	void loadAirports();
	void dataSorting();

	void searchByCountry();
	void searchByName();
	void searchByIATA();

	void countByType();
	void addAirport();
	void saveAirports();

	void sortByName();
	void sortByCountry();
	void sortByType();
	void sortByLatLon();
	void sortByElevation();

	void printFirstN(int n);
};

#endif

