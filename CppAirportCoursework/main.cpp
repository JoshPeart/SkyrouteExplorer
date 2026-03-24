#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Airport {
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
	float coordinates;
};


// ------ FUNCTION DECLERATIONS ------

void loadAirports(vector<Airport>& airports);

// ------ MAIN ------

int main() 
{
	vector<Airport> airports;

	int choice = 0;

	cout << "====== Nottingham SkyRoute Explorer ======\n";
	cout << "1. Search airports by country\n";
	cout << "2. Search airports by name\n";
	cout << "3. Search by IATA code\n";
	cout << "4. Count airports by type\n";
	cout << "5. Add a new airport\n";
	cout << "6. Save changes\n";
	cout << "7. Advanced options(radius search, nearest airport, high / low elevation, etc.)\n";
	cout << "8. Exit\n";
	cout << "===============================================================\n";
	cout << "Enter choice: ";

	cin >> choice;

    
}

// ------ LOAD CSV ------

void loadAirports(vector<Airport>& airports) {
    ifstream file("airports.csv");
    string line;

    if (!file.is_open()) {
        cout << "Error: airports.csv could not be opened.\n";
        return;
    }

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        Airport a;
        string temp;

        try {
            getline(ss, temp, ','); a.ident = stoi(temp);
            getline(ss, a.type, ',');
            getline(ss, a.name, ',');
            getline(ss, temp, ','); a.elevation_ft = stoi(temp);
            getline(ss, temp, ','); a.continent = stod(temp);
            getline(ss, a.iso_country, ',');
            getline(ss, a.iso_region, ',');
            getline(ss, temp, ','); a.municipality = stoi(temp);
            getline(ss, temp, ','); a.icao_code = stoi(temp);
            getline(ss, temp, ','); a.iata_code = stoi(temp);

            airports.push_back(a);
        }
        catch (...) {
            // Skip bad rows but do not crash
            cout << "Warning: skipped an invalid row in CSV.\n";
        }
    }