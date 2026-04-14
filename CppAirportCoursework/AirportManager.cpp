#include "AirportManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// ------ LOAD CSV ------

void AirportManager::loadAirports(vector<Airport>& airports) {
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
            getline(ss, a.ident, ',');
            getline(ss, a.type, ',');
            getline(ss, a.name, ',');

            getline(ss, temp, ','); 
            a.elevation_ft = temp.empty() ? 0 : stoi(temp);

            getline(ss, a.continent, ',');
            getline(ss, a.iso_country, ',');
            getline(ss, a.iso_region, ',');
            getline(ss, a.municipality, ',');
            getline(ss, a.icao_code, ',');
            getline(ss, a.iata_code, ',');
            getline(ss, a.gps_code, ',');
            getline(ss, a.local_code, ',');

            getline(ss, temp, ',');
            a.latitude = temp.empty() ? 0.0 : stod(temp);
            getline(ss, temp, ',');
            a.longitude = temp.empty() ? 0.0 : stod(temp);

            airports.push_back(a);
        }
        catch (...) {
            // Skip bad rows but do not crash
            cout << "Warning: skipped an invalid row in CSV.\n";
        }
    }
}

// ------ PRINT -----
void AirportManager::printAirport(const Airport& a) {
    cout << "----------------------------------\n";
    cout << "ID: " << a.ident << endl;
    cout << "Name: " << a.name << endl;
    cout << "Continent: " << a.continent << endl;
    cout << "Type: " << a.type << endl;
    cout << "Elevation (ft): " << a.elevation_ft << endl;
    cout << "Coordinates: " << a.latitude << ", " << a.longitude << endl;
}

// ----- SEARCH -----
void AirportManager::searchByCountry(const vector<Airport>& airports) {
    string country;
    cout << "Enter country code (e.g. GB, US): ";
    getline(cin, country);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iso_country == country) {
            printAirport(airports[i]);
        }
    }
}

void AirportManager::searchByName(const vector<Airport>& airports) {
    string Name;
    cout << "Enter flight name: ";
    getline(cin, Name);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].name.find(Name) != string::npos) {
            printAirport(airports[i]);
        }
    }
}

void AirportManager::searchByIATA(const vector<Airport>& airports) {
    string IATA;
    cout << "Enter IATA code: ";
    getline(cin, IATA);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iata_code == IATA) {
            printAirport(airports[i]);
        }
    }
}

// ----- COUNT BY TYPE -----
void AirportManager::countByType(const vector<Airport>& airports) {
    vector<string> types;
    vector<int> counts;

    for (int i = 0; i < airports.size(); i++) {
        bool found = false;

        for (int j = 0; j < types.size(); j++) {

            if (airports[i].type == types[j]) {
                counts[j]++;
                found = true;
            }
        }

        // if type was not found in the list
        if (!found) {
            types.push_back(airports[i].type);
            counts.push_back(1); // add new count and start it at 1
        }
    }

    cout << "\nAirports by genre:\n";
    for (int i = 0; i < types.size(); i++) {
        cout << types[i] << ": " << counts[i] << endl;
    }
}

// ----- ADD AIRPORT -----
void AirportManager::addAirport(vector<Airport>& airports) {
    Airport a;
    string input;

    try {

        cout << "Ident (local code): ";
        getline(cin, a.ident);
        getline(cin, a.local_code);

        cout << "Type (e.g. large_airport): ";
        getline(cin, a.type);

        cout << "Name: ";
        getline(cin, a.name);

        cout << "Elevation (ft): ";
        getline(cin, input);
        a.elevation_ft = stoi(input);

        cout << "Continent (e.g. EU, NA): ";
        getline(cin, a.continent);

        cout << "Country Code (e.g. GB, US): ";
        getline(cin, a.iso_country);

        cout << "Region: ";
        getline(cin, a.iso_region);

        cout << "Municipality: ";
        getline(cin, a.municipality);

        cout << "ICAO Code: ";
        getline(cin, a.icao_code);

        cout << "IATA Code: ";
        getline(cin, a.iata_code);

        cout << "GPS Code: ";
        getline(cin, a.gps_code);

        cout << "Latitude: ";
        getline(cin, input);
        a.latitude = stod(input);

        cout << "Longitude: ";
        getline(cin, input);
        a.longitude = stod(input);

    }
    catch (...) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Airport not added.\n";
        return;
    }

    airports.push_back(a);
    cout << "Airport added successfully.\n";
}

// ----- SAVE -----
void AirportManager::saveAirports(const vector<Airport>& airports) {
    ofstream file("airports.csv");

    if (!file.is_open()) {
        cout << "Error saving file.\n";
        return;
    }

    file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,coordinates\n";

    for (int i = 0; i < airports.size(); i++) {
        file << airports[i].ident << ","
            << airports[i].type << ","
            << airports[i].name << ","
            << airports[i].elevation_ft << ","
            << airports[i].continent << ","
            << airports[i].iso_country << ","
            << airports[i].iso_region << ","
            << airports[i].municipality << ","
            << airports[i].icao_code << ","
            << airports[i].iata_code << ","
            << airports[i].gps_code << ","
            << airports[i].local_code << ","
            << "\"" << airports[i].latitude << ", " << airports[i].longitude << "\"" << "\n";
    }


    file.close();
    cout << "Saved to airports_updated.csv\n";
}
