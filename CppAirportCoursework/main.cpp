#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "AirportManager.h"


using namespace std;

// ------ MAIN ------

int main() 
{
    vector<Airport> airports;

    AirportManager manager;
    int choice = 0;

    manager.loadAirports(airports);

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
            case 1: manager.searchByCountry(airports); break;
            case 2: manager.searchByName(airports); break;
            case 3: manager.searchByIATA(airports); break;
            case 4: manager.countByType(airports); break;
            case 5: manager.addAirport(airports); break;
            case 6: cout << "\nAdvanced options coming soon.\n"; break;
            case 7: manager.saveAirports(airports); break;
            case 8: cout << "Exiting program...\n"; break;
            default: cout << "\nInvalid option.Try again.\n";
        }

    } while (choice != 8); // Closes program on the number 8

    return 0;
}

