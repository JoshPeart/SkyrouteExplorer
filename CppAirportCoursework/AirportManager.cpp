#include "AirportManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// ------ LOAD CSV ------

void AirportManager::loadAirports() {
    ifstream file("airports.csv");
    string line;


    if (!file.is_open()) {
        cout << "Error: airports.csv could not be opened.\n";
        return;
    }

    getline(file, line); // skip header

    while (getline(file, line)) {
        
        bool inQuotes = false;
        for (char& c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
                c = ' '; 
            }
            else if (c == ',' && inQuotes) {
                c = ';'; 
            }
        }
        
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

    file.close();
    cout << "Airports loaded: " << airports.size() << endl;
}

// ------ PRINT -----
void AirportManager::dataSorting() {
    int choice;

    do {
        cout << "\n====== Data Sorting ======\n";
        cout << "1. Sort by name\n";
        cout << "2. Sort by country\n";
        cout << "3. Sort by type\n";
        cout << "4. Sort by latitude / longitude\n";
        cout << "5. Sort by elevation\n";
        cout << "6. Exit to Main Menu\n";
        cout << "============================\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        switch (choice) {
        case 1: sortByName(); printFirstN(5); break;
        case 2: sortByCountry(); printFirstN(5); break;
        case 3: sortByType(); printFirstN(5); break;
        case 4: sortByLatLon(); printFirstN(5); break;
        case 5: sortByElevation(); printFirstN(5); break;
        case 6: cout << "Going Back...\n"; break;
        default: cout << "\nInvalid option.Try again.\n";
        }

    } while (choice != 6);
}

// ----- SEARCH -----
void AirportManager::searchByCountry() {
    string country;
    cout << "Enter country code (e.g. GB, US): ";
    getline(cin, country);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iso_country == country) {
            airports[i].print();
        }
    }
}

void AirportManager::searchByName() {
    string Name;
    cout << "Enter flight name: ";
    getline(cin, Name);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].name.find(Name) != string::npos) {
            airports[i].print();
        }
    }
}

void AirportManager::searchByIATA() {
    string IATA;
    cout << "Enter IATA code: ";
    getline(cin, IATA);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iata_code == IATA) {
            airports[i].print();
        }
    }
}

// ----- COUNT BY TYPE -----
void AirportManager::countByType() {
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
void AirportManager::addAirport() {
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
void AirportManager::saveAirports() {
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

void AirportManager::sortByName() {
    sort(airports.begin(), airports.end(), // sorts whole vector
        [](Airport a, Airport b) { return a.name < b.name; }); // comparator
    // checks if a is alphabetically less than b
}

void AirportManager::sortByCountry() {
    sort(airports.begin(), airports.end(), 
        [](Airport a, Airport b) { return a.iso_country < b.iso_country; }); 
}

void AirportManager::sortByType() {
    sort(airports.begin(), airports.end(),
        [](Airport a, Airport b) { return a.type < b.type; }); 
}

void AirportManager::sortByLatLon() {
    int choice;

    cout << "Latitude (1) or Longitude (2): ";
    cin >> choice;

    if (choice == 1) {
        sort(airports.begin(), airports.end(),
            [](Airport a, Airport b) { return a.latitude < b.latitude; }); 
    }
    else if (choice == 2) {
        sort(airports.begin(), airports.end(), 
            [](Airport a, Airport b) { return a.longitude < b.longitude; }); 
    }
}

void AirportManager::sortByElevation() {
    sort(airports.begin(), airports.end(),
        [](Airport a, Airport b) { return a.elevation_ft < b.elevation_ft; });
}

void AirportManager::printFirstN(int n) {
    for (int i = 0; i < n && i < airports.size(); i++) {
        airports[i].print();
    }
}