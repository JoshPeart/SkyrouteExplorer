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
    AirportManager manager;

    int choice = 0;

    cout << "Loading...\n";

    manager.loadAirports();

    do {
        cout << "\n====== Nottingham SkyRoute Explorer ======\n";
        cout << "1. Search airports by country\n";
        cout << "2. Search airports by name\n";
        cout << "3. Search by IATA code\n";
        cout << "4. Count airports by type\n";
        cout << "5. Add a new airport\n";
        cout << "6. Advanced options\n";
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
            case 1: manager.searchByCountry(); break;
            case 2: manager.searchByName(); break;
            case 3: manager.searchByIATA(); break;
            case 4: manager.countByType(); break;
            case 5: manager.addAirport(); break;
            case 6: manager.dataSorting(); break;
            case 7: manager.saveAirports(); break;
            case 8: cout << "Exiting program...\n"; break;
            default: cout << "\nInvalid option.Try again.\n";
        }

    } while (choice != 8); // Closes program on the number 8

    return 0;
}

