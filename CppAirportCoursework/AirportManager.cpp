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

    while (getline(file, line)) { // Quote handling mechanism to prevent CSV parsing errors caused by commas inside airport names
        
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

            getline(ss, temp, ';');
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
void AirportManager::advancedOptions() {
    int choice;

    do {
        cout << "\n====== Advanced Options ======\n";
        cout << "1. Sort by name\n";
        cout << "2. Sort by country\n";
        cout << "3. Sort by type\n";
        cout << "4. Sort by latitude / longitude\n";
        cout << "5. Sort by elevation\n";
        cout << "6. Find distance between airports\n";
        cout << "7. Exit to Main Menu\n";
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
        case 6: FindDistance(); break;
        case 7: cout << "Going Back...\n"; break;
        default: cout << "\nInvalid option.Try again.\n";
        }

    } while (choice != 7);
}

// ----- SEARCH -----
// Can make use of maps for faster lookup

void AirportManager::searchByCountry() {
    string country;
    cout << "Enter country code (e.g. GB, US): ";
    getline(cin, country);

    if (country.empty()) {
        cout << "Error: Name cannot be empty.\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iso_country == country) {
            airports[i].print();
            found = true;
        }
    }

    if (!found) {
        cout << "No airports found for country code: " << country << endl;
    }

}

void AirportManager::searchByName() {
    string Name;
    cout << "Enter flight name: ";
    getline(cin, Name);

    if (Name.empty()) {
        cout << "Error: Name cannot be empty.\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].name.find(Name) != string::npos) {
            airports[i].print();
            found = true;
        }
    }

    if (!found) {
        cout << "No airports found for name: " << Name << endl;
    }
}


void AirportManager::searchByIATA() {
    string IATA;
    cout << "Enter IATA code: ";
    getline(cin, IATA);

    if (IATA.empty()) {
        cout << "Error: Name cannot be empty.\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iata_code == IATA) {
            airports[i].print();
            found = true;
        }
    }

    if (!found) {
        cout << "No airports found for IATA code: " << IATA << endl;
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

        cout << "Local Code: ";
        getline(cin, a.local_code);

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

// ------- DATA SORTING --------
// Using lambda functions to allow custom sorting logic

void AirportManager::sortByName() {
    cout << "Sorting by name...\n\n";
    sort(airports.begin(), airports.end(), // sorts whole vector
        [](const Airport& a, const Airport& b) { return a.name < b.name; }); // comparator
    // checks if a is alphabetically less than b
}

void AirportManager::sortByCountry() {
    cout << "Sorting by country...\n\n";
    sort(airports.begin(), airports.end(), 
        [](Airport a, Airport b) { return a.iso_country < b.iso_country; }); 
}

void AirportManager::sortByType() {
    cout << "Sorting by type...\n\n";
    sort(airports.begin(), airports.end(),
        [](Airport a, Airport b) { return a.type < b.type; }); 
}

void AirportManager::sortByLatLon() {
    int choice;

    while (true) {
        cout << "Latitude (1) or Longitude (2): ";
        cin >> choice;

        // input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }

        if (choice == 1) {
            cout << "Sorting by latitude...\n\n";
            sort(airports.begin(), airports.end(),
                [](Airport a, Airport b) { return a.latitude < b.latitude; });
            break;
        }
        else if (choice == 2) {
            cout << "Sorting by longitude...\n\n";
            sort(airports.begin(), airports.end(),
                [](Airport a, Airport b) { return a.longitude < b.longitude; });
            break;
        }
        else {
            cout << "Invalid selection. Please enter 1 or 2.\n";
        }
    }
}

void AirportManager::sortByElevation() {
    cout << "Sorting by Elevation...\n\n";
    sort(airports.begin(), airports.end(),
        [](Airport a, Airport b) { return a.elevation_ft < b.elevation_ft; });
}

void AirportManager::printFirstN(int n) {
    for (int i = 0; i < n && i < airports.size(); i++) {
        airports[i].print();
    }
}

// ------ AIRPORT DISTANCE -------
double AirportManager::deg2rad(double deg) {
    double pi = 3.141592653589;
    return (deg * pi / 180);
}

// Stack overflow solution

double AirportManager::HaversineDistance(double lat1, double lon1, double lat2, double lon2) {

    double R = 6371.0; // Earth radius in km
    double lat1r, lon1r, lat2r, lon2r, u, v;

    lat1r = deg2rad(lat1);
    lon1r = deg2rad(lon1);
    lat2r = deg2rad(lat2);
    lon2r = deg2rad(lon2);
    u = sin((lat2r - lat1r) / 2); // half of latitude difference    
    v = sin((lon2r - lon1r) / 2); // half of longitude difference

    return (2.0 * R * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)));
}

// Using a reference to avoid copying a large object

bool AirportManager::getAirportByIdent(string ident, Airport& result) {
    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].ident == ident) {
            result = airports[i];
            return true;
        }
    }
    return false;
}

void AirportManager::FindDistance() {
    
    bool found = false;
    string id1, id2;
    Airport a1, a2;


    cout << "Enter the first airport ident: ";
    cin >> id1;

    if (!getAirportByIdent(id1, a1)) {
        cout << "First airport not found!\n";
        return;
    }

    cout << "Enter the second airport ident: ";
    cin >> id2;

    if (!getAirportByIdent(id2, a2)) {
        cout << "Second airport not found!\n";
        return;
    }

    double d = HaversineDistance(a1.latitude, a1.longitude, a2.latitude, a2.longitude);

    cout << "The distance between " << a1.name << " and " << a2.name << " is " << d << "km\n";
        

}