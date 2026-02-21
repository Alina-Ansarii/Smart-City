//#include <iostream>
//#include "Facility.h"
//#include "PublicFacilitiesSector.h"
//
//using namespace std;
//
//void displayMenu();
//void runInteractiveDemo(PublicFacilitiesSector& sector);
//
//int main() {
//    cout << "========================================" << endl;
//    cout << "PUBLIC FACILITIES SECTOR MANAGEMENT" << endl;
//    cout << "========================================\n" << endl;
//
//    // Create sector with capacity for 100 facilities
//    PublicFacilitiesSector sector(100, 17);
//
//    cout << "--- Demo 1: Registering Public Facilities ---\n" << endl;
//
//    Facility* mosque1 = sector.registerFacility(
//        "Faisal Mosque", "Mosque", "G-5", 33.7294, 73.1786
//    );
//    cout << "Registered Mosque: " << (mosque1 ? mosque1->getFacilityId() : "Failed") << endl;
//
//    Facility* mosque2 = sector.registerFacility(
//        "Al-Habib Mosque", "Mosque", "F-8", 33.7452, 73.1934
//    );
//    cout << "Registered Mosque: " << (mosque2 ? mosque2->getFacilityId() : "Failed") << endl;
//
//    Facility* park1 = sector.registerFacility(
//        "Shakarparian Park", "Park", "G-6", 33.7234, 73.1924
//    );
//    cout << "Registered Park: " << (park1 ? park1->getFacilityId() : "Failed") << endl;
//
//    Facility* park2 = sector.registerFacility(
//        "Margalla Park", "Park", "F-7", 33.7512, 73.2034
//    );
//    cout << "Registered Park: " << (park2 ? park2->getFacilityId() : "Failed") << endl;
//
//    Facility* cooler1 = sector.registerFacility(
//        "Water Cooler A", "Water Cooler", "G-5", 33.7300, 73.1800
//    );
//    cout << "Registered Cooler: " << (cooler1 ? cooler1->getFacilityId() : "Failed") << endl;
//
//    Facility* cooler2 = sector.registerFacility(
//        "Water Cooler B", "Water Cooler", "F-8", 33.7460, 73.1950
//    );
//    cout << "Registered Cooler: " << (cooler2 ? cooler2->getFacilityId() : "Failed") << endl;
//
//    cout << "\nTotal Facilities Registered: " << sector.getFacilityCount() << endl;
//
//    cout << "\n--- Demo 2: Display All Facilities ---\n" << endl;
//    sector.displayAllFacilities();
//
//    cout << "\n--- Demo 3: Connecting Facilities (Creating Routes) ---\n" << endl;
//
//    if (mosque1 && mosque2) {
//        bool connected = sector.connectFacilities(
//            mosque1->getFacilityId(), mosque2->getFacilityId(), 3.5
//        );
//        cout << (connected ? "Connected" : "Failed to connect") << " "
//            << mosque1->getName() << " <-> " << mosque2->getName() << endl;
//    }
//
//    if (mosque2 && park2) {
//        bool connected = sector.connectFacilities(
//            mosque2->getFacilityId(), park2->getFacilityId(), 2.1
//        );
//        cout << (connected ? "Connected" : "Failed to connect") << " "
//            << mosque2->getName() << " <-> " << park2->getName() << endl;
//    }
//
//    if (park2 && cooler2) {
//        bool connected = sector.connectFacilities(
//            park2->getFacilityId(), cooler2->getFacilityId(), 1.5
//        );
//        cout << (connected ? "Connected" : "Failed to connect") << " "
//            << park2->getName() << " <-> " << cooler2->getName() << endl;
//    }
//
//    if (mosque1 && cooler1) {
//        bool connected = sector.connectFacilities(
//            mosque1->getFacilityId(), cooler1->getFacilityId(), 0.8
//        );
//        cout << (connected ? "Connected" : "Failed to connect") << " "
//            << mosque1->getName() << " <-> " << cooler1->getName() << endl;
//    }
//
//    // ==================== Demo 4: Get Facilities by Type ====================
//    cout << "\n--- Demo 4: Search by Type (Hash Table Lookup) ---\n" << endl;
//
//    sector.displayFacilitiesByType("Mosque");
//    sector.displayFacilitiesByType("Park");
//    sector.displayFacilitiesByType("Water Cooler");
//
//    // ==================== Demo 5: Get by Facility ID ====================
//    cout << "\n--- Demo 5: Get Facility by ID ---\n" << endl;
//
//    if (mosque1) {
//        Facility* found = sector.getFacilityById(mosque1->getFacilityId());
//        if (found) {
//            cout << "Found: ";
//            found->displayCompact();
//        }
//    }
//
//    // ==================== Demo 6: Find Nearest Facility ====================
//    cout << "\n--- Demo 6: Find Nearest Facility to Location ---\n" << endl;
//
//    double searchLat = 33.7350;
//    double searchLon = 73.1850;
//
//    cout << "Searching near (" << searchLat << ", " << searchLon << ")" << endl;
//    Facility* nearest = sector.findNearestFacility(searchLat, searchLon);
//    if (nearest) {
//        cout << "Nearest Facility:\n";
//        nearest->displayCompact();
//    }
//
//    // ==================== Demo 7: Find Nearest by Type ====================
//    cout << "\n--- Demo 7: Find Nearest Facility of Specific Type ---\n" << endl;
//
//    Facility* nearestMosque = sector.findNearestFacilityByType(searchLat, searchLon, "Mosque");
//    if (nearestMosque) {
//        cout << "Nearest Mosque:\n";
//        nearestMosque->displayCompact();
//    }
//
//    Facility* nearestPark = sector.findNearestFacilityByType(searchLat, searchLon, "Park");
//    if (nearestPark) {
//        cout << "Nearest Park:\n";
//        nearestPark->displayCompact();
//    }
//
//    // ==================== Demo 8: Find Nearest in Sector ====================
//    cout << "\n--- Demo 8: Find Nearest Facility in Sector ---\n" << endl;
//
//    Facility* nearestInSector = sector.findNearestFacilityInSector(searchLat, searchLon, "G-5");
//    if (nearestInSector) {
//        cout << "Nearest facility in sector G-5:\n";
//        nearestInSector->displayCompact();
//    }
//
//    // ==================== Demo 9: Shortest Path ====================
//    cout << "\n--- Demo 9: Find Shortest Path Between Facilities ---\n" << endl;
//
//    if (mosque1 && cooler2) {
//        int pathLength = 0;
//        double totalDistance = 0.0;
//
//        Facility** path = sector.findShortestPath(
//            mosque1->getFacilityId(),
//            cooler2->getFacilityId(),
//            &pathLength,
//            &totalDistance
//        );
//
//        if (path != nullptr && pathLength > 0) {
//            cout << "Shortest path from " << mosque1->getName()
//                << " to " << cooler2->getName() << ":\n";
//            cout << "Path length: " << pathLength << " facilities\n";
//            cout << "Total distance: " << totalDistance << " km\n";
//            cout << "Route:\n";
//
//            for (int i = 0; i < pathLength; i++) {
//                if (path[i] != nullptr) {
//                    cout << "  [" << (i + 1) << "] " << path[i]->getName()
//                        << " (" << path[i]->getType() << ")\n";
//                }
//            }
//            delete[] path;
//        }
//        else {
//            cout << "No path found between facilities\n";
//        }
//    }
//
//    // ==================== Demo 10: Statistics ====================
//    cout << "\n--- Demo 10: Sector Statistics ---\n" << endl;
//    sector.printStatistics();
//
//    // ==================== Demo 11: Graph Display ====================
//    cout << "\n--- Demo 11: Facility Graph Structure ---\n" << endl;
//    sector.displayGraph();
//
//    // ==================== Demo 12: Hash Table Display ====================
//    cout << "\n--- Demo 12: Hash Table by Type ---\n" << endl;
//    sector.displayHashTable();
//
//    // ==================== Demo 13: Interactive Menu (Optional) ====================
//    cout << "\n--- Demo 13: Interactive Mode ---\n" << endl;
//    cout << "Would you like to enter interactive mode? (y/n): ";
//    char choice;
//    cin >> choice;
//
//    if (choice == 'y' || choice == 'Y') {
//        runInteractiveDemo(sector);
//    }
//
//    cout << "\n========================================" << endl;
//    cout << "Program Complete" << endl;
//    cout << "========================================\n" << endl;
//
//    return 0;
//}
//
//void displayMenu() {
//    cout << "\n--- Interactive Menu ---\n" << endl;
//    cout << "1. Register new facility" << endl;
//    cout << "2. Display all facilities" << endl;
//    cout << "3. Search facility by ID" << endl;
//    cout << "4. Find nearest facility" << endl;
//    cout << "5. Find nearest facility by type" << endl;
//    cout << "6. Display statistics" << endl;
//    cout << "7. Display facilities by type" << endl;
//    cout << "8. Exit interactive mode" << endl;
//    cout << "\nEnter choice (1-8): ";
//}
//
//void runInteractiveDemo(PublicFacilitiesSector& sector) {
//    int choice = 0;
//
//    while (true) {
//        displayMenu();
//        cin >> choice;
//        cin.ignore();  // Clear input buffer
//
//        switch (choice) {
//        case 1: {
//            // Register new facility
//            string name, type, sector_name;
//            double lat, lon;
//
//            cout << "Enter facility name: ";
//            getline(cin, name);
//            cout << "Enter facility type (e.g., Mosque, Park, School): ";
//            getline(cin, type);
//            cout << "Enter sector (e.g., G-5, F-8): ";
//            getline(cin, sector_name);
//            cout << "Enter latitude: ";
//            cin >> lat;
//            cout << "Enter longitude: ";
//            cin >> lon;
//
//            Facility* newFac = sector.registerFacility(name, type, sector_name, lat, lon);
//            if (newFac) {
//                cout << "\nFacility registered successfully with ID: "
//                    << newFac->getFacilityId() << endl;
//            }
//            else {
//                cout << "\nFailed to register facility" << endl;
//            }
//            break;
//        }
//
//        case 2: {
//            // Display all facilities
//            sector.displayAllFacilities();
//            break;
//        }
//
//        case 3: {
//            // Search by ID
//            string id;
//            cout << "Enter facility ID: ";
//            getline(cin, id);
//
//            Facility* found = sector.getFacilityById(id);
//            if (found) {
//                cout << "\nFacility found:\n";
//                found->display();
//            }
//            else {
//                cout << "\nFacility not found" << endl;
//            }
//            break;
//        }
//
//        case 4: {
//            // Find nearest facility
//            double lat, lon;
//            cout << "Enter latitude: ";
//            cin >> lat;
//            cout << "Enter longitude: ";
//            cin >> lon;
//
//            Facility* nearest = sector.findNearestFacility(lat, lon);
//            if (nearest) {
//                cout << "\nNearest facility:\n";
//                nearest->display();
//            }
//            else {
//                cout << "\nNo facilities found" << endl;
//            }
//            break;
//        }
//
//        case 5: {
//            // Find nearest by type
//            double lat, lon;
//            string type;
//
//            cout << "Enter latitude: ";
//            cin >> lat;
//            cout << "Enter longitude: ";
//            cin >> lon;
//            cin.ignore();
//            cout << "Enter facility type: ";
//            getline(cin, type);
//
//            Facility* nearest = sector.findNearestFacilityByType(lat, lon, type);
//            if (nearest) {
//                cout << "\nNearest facility of type " << type << ":\n";
//                nearest->display();
//            }
//            else {
//                cout << "\nNo facilities of this type found" << endl;
//            }
//            break;
//        }
//
//        case 6: {
//            // Display statistics
//            sector.printStatistics();
//            break;
//        }
//
//        case 7: {
//            // Display by type
//            string type;
//            cout << "Enter facility type: ";
//            getline(cin, type);
//            sector.displayFacilitiesByType(type);
//            break;
//        }
//
//        case 8: {
//            // Exit interactive mode
//            cout << "\nExiting interactive mode..." << endl;
//            return;
//        }
//
//        default:
//            cout << "\nInvalid choice. Please try again." << endl;
//        }
//    }
//}
