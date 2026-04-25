#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H

#include "Airport.h"
#include <vector>

// Can be improved by making attributes private and using getters/setters

class AirportManager
{
private:
	std::vector<Airport> airports;
public:

	// ------ FUNCTION DECLERATIONS ------
	void loadAirports();
	void advancedOptions();

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

	double deg2rad(double deg);
	double HaversineDistance(double lat1, double lon1, double lat2, double lon2);
	bool getAirportByIdent(string ident, Airport& result);
	void FindDistance();
};

#endif

