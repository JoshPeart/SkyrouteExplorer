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


// ------ FUNCTION DECLERATIONS ------
void loadAirports(vector<Airport>& airports);
void printAirport(const Airport& a);

void searchByCountry(const vector<Airport>& airports);
void searchByName(const vector<Airport>& airports);
void searchByIATA(const vector<Airport>& airports); 

void countByType(const vector<Airport>& airports); 
void addAirport(vector<Airport>& airports);
void saveAirports(const vector<Airport>& airports);


// ------ MAIN ------

int main() 
{
	vector<Airport> airports;

	int choice = 0;

    loadAirports(airports);
    cout << "Loaded " << airports.size() << " airports.\n";

    do {
        cout << "\n====== Nottingham SkyRoute Explorer ======\n";
        cout << "1. Search airports by country\n";
        cout << "2. Search airports by name\n";
        cout << "3. Search by IATA code\n";
        cout << "4. Count airports by type\n";
        cout << "5. Add a new airport\n";
        cout << "6. Advanced options(radius search, nearest airport, high / low elevation, etc.)\n";
        cout << "7. Save airports\n";
        cout << "8. Exit\n";
        cout << "==========================================\n";
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
            case 1: searchByCountry(airports); break;
            case 2: searchByName(airports); break;
            case 3: searchByIATA(airports); break;
            case 4: countByType(airports); break;
            case 5: addAirport(airports); break;
            case 6: cout << "\nAdvanced options coming soon.\n"; break;
            case 7: saveAirports(airports); break;
            case 8: cout << "Exiting program...\n"; break;
            default: cout << "\nInvalid option.Try again.\n";
        }

    } while (choice != 8);

    return 0;
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
            getline(ss, a.ident, ',');
            getline(ss, a.type, ',');
            getline(ss, a.name, ',');

            getline(ss, a.elevation_ft, ','); 
         
            getline(ss, a.continent, ',');
            getline(ss, a.iso_country, ',');
            getline(ss, a.iso_region, ',');
            getline(ss, a.municipality, ','); 
            getline(ss, a.icao_code, ','); 
            getline(ss, a.iata_code, ','); 
            getline(ss, a.gps_code, ',');
            getline(ss, a.local_code, ',');

            getline(ss, a.latitude, ',');
            getline(ss, a.longitude, ',');

           

            airports.push_back(a);
        }
        catch (...) {
            // Skip bad rows but do not crash
            cout << "Warning: skipped an invalid row in CSV.\n";
        }
    }
}

// ------ PRINT -----
void printAirport(const Airport& a) {
    cout << "----------------------------------\n";
    cout << "ID: " << a.ident << endl;
    cout << "Name: " << a.name << endl;
    cout << "Continent: " << a.continent << endl;
    cout << "Type: " << a.type << endl;
    cout << "Elevation (ft): " << a.elevation_ft << endl;
    cout << "Coordinates: " << a.latitude << ", " << a.longitude << endl;
}

// ----- SEARCH -----
void searchByCountry(const vector<Airport>& airports) {
    string country;
    cout << "Enter country code (e.g. GB, US): ";
    getline(cin, country);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iso_country == country) {
            printAirport(airports[i]);
        }
     }
}

void searchByName(const vector<Airport>& airports) {
    string Name;
    cout << "Enter flight name: ";
    getline(cin, Name);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].name == Name) {
            printAirport(airports[i]);
        }
    }
}

void searchByIATA(const vector<Airport>& airports) {
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
void countByType(const vector<Airport>& airports) {
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

        if (!found) {
            types.push_back(airports[i].type);
            counts.push_back(1);
        }
    }

    cout << "\nAirports by genre:\n";
    for (int i = 0; i < types.size(); i++) {
        cout << types[i] << ": " << counts[i] << endl;
    }
}

// ----- ADD AIRPORT -----
void addAirport(vector<Airport>& airports) {
    Airport a;


    try {

        cout << "Ident: ";
        getline(cin, a.ident);

        cout << "Type (e.g. large_airport): ";
        getline(cin, a.type);

        cout << "Name: ";
        getline(cin, a.name);

        cout << "Elevation (ft): ";
        cin >> a.elevation_ft;

        cout << "Continent: ";
        cin >> a.continent;

        cout << "Country Code (e.g. GB, US): ";
        cin >> a.iso_country;

        cout << "Region: ";
        cin >> a.iso_region;

        cin.ignore();

        cout << "Municipality: ";
        getline(cin, a.municipality);

        cout << "ICAO Code: ";
        cin >> a.icao_code;

        cout << "IATA Code: ";
        cin >> a.iata_code;

        cout << "GPS Code: ";
        cin >> a.gps_code;

        cout << "Local Code: ";
        cin >> a.local_code;

        cout << "Latitude: ";
        cin >> a.latitude;

        cout << "Longitude: ";
        cin >> a.longitude;

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
void saveAirports(const vector<Airport>& airports) {
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
            << "\"" << airports[i].latitude << "," << airports[i].longitude << "\"" << "\n";
    }
    

    file.close();
    cout << "Saved to airports_updated.csv\n";
}