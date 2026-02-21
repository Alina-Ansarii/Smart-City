//#define _CRT_SECURE_NO_WARNINGS  // Disable fopen deprecation warning
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "HashTable.h"
//#include "Graph.h"
//#include "Transport.h"
//#include "TransportSector.h"
//using namespace std;
//
//// Helper function to trim whitespace from string
//string trim(const string& str) {
//    size_t first = str.find_first_not_of(" \t\r\n");
//    if (first == string::npos) return "";
//    size_t last = str.find_last_not_of(" \t\r\n");
//    return str.substr(first, (last - first + 1));
//}
//
//// Helper function to parse coordinates from string like "33.684, 73.025"
//bool parseCoordinates(const string& coordStr, double& lat, double& lon) {
//    stringstream ss(coordStr);
//    string latStr, lonStr;
//
//    getline(ss, latStr, ',');
//    getline(ss, lonStr);
//
//    try {
//        lat = stod(trim(latStr));
//        lon = stod(trim(lonStr));
//        return true;
//    }
//    catch (...) {
//        return false;
//    }
//}
//
//void printMenu() {
//    cout << "\n======================================================" << endl;
//    cout << "      TRANSPORT SECTOR - SMART CITY" << endl;
//    cout << "======================================================" << endl;
//    cout << "COMPANY MANAGEMENT:" << endl;
//    cout << "1.  Register Transport Company" << endl;
//    cout << "2.  Display All Companies" << endl;
//    cout << "3.  Search Company by ID" << endl;
//    cout << "\nBUS STOP MANAGEMENT:" << endl;
//    cout << "4.  Add Bus Stop" << endl;
//    cout << "5.  Connect Bus Stops" << endl;
//    cout << "6.  Display All Stops" << endl;
//    cout << "7.  Find Nearest Stop to Location" << endl;
//    cout << "\nBUS MANAGEMENT:" << endl;
//    cout << "8.  Register Bus" << endl;
//    cout << "9.  Register School Bus" << endl;
//    cout << "10. Add Stop to Bus Route" << endl;
//    cout << "11. Display Bus Route" << endl;
//    cout << "12. Display All Buses" << endl;
//    cout << "13. Display School Buses Only" << endl;
//    cout << "14. Search Bus by Number" << endl;
//    cout << "\nPASSENGER MANAGEMENT:" << endl;
//    cout << "15. Add Passenger to Queue" << endl;
//    cout << "16. Board Passenger on Bus" << endl;
//    cout << "17. Display Passenger Queue" << endl;
//    cout << "\nROUTING & NAVIGATION:" << endl;
//    cout << "18. Find Shortest Path (Dijkstra)" << endl;
//    cout << "19. Find Nearest Bus to Location" << endl;
//    cout << "20. Emergency Routing" << endl;
//    cout << "\nREAL-TIME TRACKING:" << endl;
//    cout << "21. Track Bus Location" << endl;
//    cout << "22. Move Bus to Next Stop" << endl;
//    cout << "23. Display Route History" << endl;
//    cout << "24. Track School Bus Route" << endl;
//    cout << "\nREPORTS & STATISTICS:" << endl;
//    cout << "25. Display System Statistics" << endl;
//    cout << "\nDATA LOADING:" << endl;
//    cout << "26. Load Sample Data (From Project)" << endl;
//    cout << "27. Load Stops from CSV File" << endl;
//    cout << "28. Load Buses from CSV File" << endl;
//    cout << "0.  Exit" << endl;
//    cout << "======================================================" << endl;
//    cout << "Enter your choice: ";
//}
//
//// Load sample data from project appendix
//void loadSampleData(TransportSystem& system) {
//    cout << "\n========================================" << endl;
//    cout << "Loading Sample Data from Project..." << endl;
//    cout << "========================================" << endl;
//
//    // Register Companies
//    cout << "\n[1/5] Registering Transport Companies..." << endl;
//    TransportCompany* metro = new TransportCompany(1, "MetroBus", "051-1111111");
//    TransportCompany* capital = new TransportCompany(2, "CapitalTrans", "051-2222222");
//    TransportCompany* green = new TransportCompany(3, "GreenWheels", "051-3333333");
//    TransportCompany* north = new TransportCompany(4, "NorthFleet", "051-4444444");
//    TransportCompany* sky = new TransportCompany(5, "SkyLine", "051-5555555");
//
//    system.registerCompany(metro);
//    system.registerCompany(capital);
//    system.registerCompany(green);
//    system.registerCompany(north);
//    system.registerCompany(sky);
//    cout << "   5 companies registered" << endl;
//
//    // Add Bus Stops
//    cout << "\n[2/5] Adding Bus Stops..." << endl;
//    BusStop* stop1 = new BusStop("Stop1", "G-10 Markaz", 33.684, 73.025);
//    BusStop* stop2 = new BusStop("Stop2", "F-10 Park", 33.691, 73.019);
//    BusStop* stop3 = new BusStop("Stop3", "PIMS Hospital", 33.706, 73.055);
//    BusStop* stop4 = new BusStop("Stop4", "F-8 Kacheri", 33.709, 73.037);
//    BusStop* stop5 = new BusStop("Stop5", "G-9 Bus Adda", 33.700, 73.030);
//    BusStop* stop6 = new BusStop("Stop6", "Blue Area", 33.720, 73.065);
//    BusStop* stop7 = new BusStop("Stop7", "Centaurus", 33.708, 73.041);
//    BusStop* stop8 = new BusStop("Stop8", "Faisal Mosque", 33.729, 73.038);
//    BusStop* stop9 = new BusStop("Stop9", "Lake View", 33.719, 73.100);
//    BusStop* stop10 = new BusStop("Stop10", "F-7 Jinnah", 33.721, 73.052);
//    BusStop* stop11 = new BusStop("Stop11", "F-6 Super", 33.727, 73.075);
//
//    system.addBusStop(stop1);
//    system.addBusStop(stop2);
//    system.addBusStop(stop3);
//    system.addBusStop(stop4);
//    system.addBusStop(stop5);
//    system.addBusStop(stop6);
//    system.addBusStop(stop7);
//    system.addBusStop(stop8);
//    system.addBusStop(stop9);
//    system.addBusStop(stop10);
//    system.addBusStop(stop11);
//    cout << "   11 bus stops added" << endl;
//
//    // Connect Stops (Create Network)
//    cout << "\n[3/5] Creating Route Network..." << endl;
//    // Route 1: Stop1 -> Stop2 -> Stop3 -> Stop4
//    system.connectBusStops("Stop1", "Stop2");
//    system.connectBusStops("Stop2", "Stop3");
//    system.connectBusStops("Stop3", "Stop4");
//
//    // Route 2: Stop1 -> Stop5 -> Stop8
//    system.connectBusStops("Stop1", "Stop5");
//    system.connectBusStops("Stop5", "Stop8");
//
//    // Route 3: Stop6 -> Stop2 -> Stop7 -> Stop9
//    system.connectBusStops("Stop6", "Stop2");
//    system.connectBusStops("Stop2", "Stop7");
//    system.connectBusStops("Stop7", "Stop9");
//
//    // Route 4: Stop4 -> Stop10 -> Stop11
//    system.connectBusStops("Stop4", "Stop10");
//    system.connectBusStops("Stop10", "Stop11");
//
//    // Route 5: Stop8 -> Stop6 -> Stop3
//    system.connectBusStops("Stop8", "Stop6");
//    system.connectBusStops("Stop6", "Stop3");
//
//    // Additional connections for better network
//    system.connectBusStops("Stop3", "Stop7");
//    system.connectBusStops("Stop5", "Stop6");
//    system.connectBusStops("Stop7", "Stop10");
//    cout << "   Route network created" << endl;
//
//    // Register Buses
//    cout << "\n[4/5] Registering Buses..." << endl;
//    Bus* b101 = new Bus("B101", 1, "MetroBus", "Stop3", 50);
//    Bus* b102 = new Bus("B102", 2, "CapitalTrans", "Stop1", 45);
//    Bus* b201 = new Bus("B201", 3, "GreenWheels", "Stop6", 40);
//    Bus* b305 = new Bus("B305", 4, "NorthFleet", "Stop4", 35);
//    Bus* b402 = new Bus("B402", 5, "SkyLine", "Stop8", 48);
//
//    system.registerBus(b101);
//    system.registerBus(b102);
//    system.registerBus(b201);
//    system.registerBus(b305);
//    system.registerBus(b402);
//    cout << "   5 buses registered" << endl;
//
//    // Build Bus Routes
//    cout << "\n[5/5] Building Bus Routes..." << endl;
//
//    // B101: Stop1 -> Stop2 -> Stop3 -> Stop4
//    system.addStopToBusRoute("B101", "Stop1");
//    system.addStopToBusRoute("B101", "Stop2");
//    system.addStopToBusRoute("B101", "Stop3");
//    system.addStopToBusRoute("B101", "Stop4");
//
//    // B102: Stop1 -> Stop5 -> Stop8
//    system.addStopToBusRoute("B102", "Stop1");
//    system.addStopToBusRoute("B102", "Stop5");
//    system.addStopToBusRoute("B102", "Stop8");
//
//    // B201: Stop6 -> Stop2 -> Stop7 -> Stop9
//    system.addStopToBusRoute("B201", "Stop6");
//    system.addStopToBusRoute("B201", "Stop2");
//    system.addStopToBusRoute("B201", "Stop7");
//    system.addStopToBusRoute("B201", "Stop9");
//
//    // B305: Stop4 -> Stop10 -> Stop11
//    system.addStopToBusRoute("B305", "Stop4");
//    system.addStopToBusRoute("B305", "Stop10");
//    system.addStopToBusRoute("B305", "Stop11");
//
//    // B402: Stop8 -> Stop6 -> Stop3
//    system.addStopToBusRoute("B402", "Stop8");
//    system.addStopToBusRoute("B402", "Stop6");
//    system.addStopToBusRoute("B402", "Stop3");
//
//    cout << "   All bus routes configured" << endl;
//
//    cout << "\n========================================" << endl;
//    cout << "Sample Data Loaded Successfully!" << endl;
//    cout << "========================================" << endl;
//    cout << "- 5 Transport Companies" << endl;
//    cout << "- 11 Bus Stops" << endl;
//    cout << "- 5 Buses with Routes" << endl;
//    cout << "- Complete Route Network" << endl;
//    cout << "========================================\n" << endl;
//}
//
//// Load bus stops from CSV file
//bool loadStopsFromCSV(TransportSystem& system, const string& filename) {
//    cout << "\n========================================" << endl;
//    cout << "Loading Bus Stops from CSV: " << filename << endl;
//    cout << "========================================" << endl;
//
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Error: Could not open file '" << filename << "'" << endl;
//        cout << "Make sure the file exists in the same directory." << endl;
//        return false;
//    }
//
//    string line;
//    int lineNumber = 0;
//    int stopsLoaded = 0;
//
//    // Skip header
//    if (getline(file, line)) {
//        lineNumber++;
//        cout << "Header: " << trim(line) << endl;
//    }
//
//    // Read data lines
//    while (getline(file, line)) {
//        lineNumber++;
//
//        if (trim(line).empty()) continue;
//
//        stringstream ss(line);
//        string stopID, name, coordStr;
//
//        // Parse: StopID,Name,Coordinates
//        getline(ss, stopID, ',');
//        getline(ss, name, ',');
//        getline(ss, coordStr);
//
//        // Trim fields
//        stopID = trim(stopID);
//        name = trim(name);
//        coordStr = trim(coordStr);
//
//        // Remove quotes from coordinates
//        if (coordStr.front() == '"' && coordStr.back() == '"') {
//            coordStr = coordStr.substr(1, coordStr.length() - 2);
//        }
//
//        // Parse coordinates
//        double lat, lon;
//        if (!parseCoordinates(coordStr, lat, lon)) {
//            cout << "Warning: Invalid coordinates on line " << lineNumber << endl;
//            continue;
//        }
//
//        // Validate fields
//        if (stopID.empty() || name.empty()) {
//            cout << "Warning: Missing fields on line " << lineNumber << endl;
//            continue;
//        }
//
//        // Create and add stop
//        BusStop* stop = new BusStop(stopID, name, lat, lon);
//        if (system.addBusStop(stop)) {
//            stopsLoaded++;
//        }
//    }
//
//    file.close();
//
//    cout << "\n========================================" << endl;
//    cout << "Stops loaded: " << stopsLoaded << endl;
//    cout << "Total lines processed: " << (lineNumber - 1) << endl;
//    cout << "========================================\n" << endl;
//
//    return stopsLoaded > 0;
//}
//
//// Load buses from CSV file
//bool loadBusesFromCSV(TransportSystem& system, const string& filename) {
//    cout << "\n========================================" << endl;
//    cout << "Loading Buses from CSV: " << filename << endl;
//    cout << "========================================" << endl;
//
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Error: Could not open file '" << filename << "'" << endl;
//        cout << "Make sure the file exists in the same directory." << endl;
//        return false;
//    }
//
//    string line;
//    int lineNumber = 0;
//    int busesLoaded = 0;
//    int companiesAdded = 0;
//
//    // Track companies
//    string addedCompanies[50];
//    int companyCount = 0;
//
//    // Skip header
//    if (getline(file, line)) {
//        lineNumber++;
//        cout << "Header: " << trim(line) << endl;
//    }
//
//    // Read data lines
//    while (getline(file, line)) {
//        lineNumber++;
//
//        if (trim(line).empty()) continue;
//
//        stringstream ss(line);
//        string busNo, company, currentStop, routeStr;
//
//        // Parse: BusNo,Company,CurrentStop,Route
//        getline(ss, busNo, ',');
//        getline(ss, company, ',');
//        getline(ss, currentStop, ',');
//        getline(ss, routeStr);
//
//        // Trim fields
//        busNo = trim(busNo);
//        company = trim(company);
//        currentStop = trim(currentStop);
//        routeStr = trim(routeStr);
//
//        // Validate fields
//        if (busNo.empty() || company.empty() || currentStop.empty()) {
//            cout << "Warning: Missing fields on line " << lineNumber << endl;
//            continue;
//        }
//
//        // Add company if not already added
//        bool companyExists = false;
//        int companyID = 0;
//        for (int i = 0; i < companyCount; i++) {
//            if (addedCompanies[i] == company) {
//                companyExists = true;
//                companyID = i + 1;
//                break;
//            }
//        }
//
//        if (!companyExists) {
//            companyID = companyCount + 1;
//            TransportCompany* comp = new TransportCompany(companyID, company, "");
//            if (system.registerCompany(comp)) {
//                addedCompanies[companyCount++] = company;
//                companiesAdded++;
//            }
//        }
//        else {
//            companyID = companyCount;
//            for (int i = 0; i < companyCount; i++) {
//                if (addedCompanies[i] == company) {
//                    companyID = i + 1;
//                    break;
//                }
//            }
//        }
//
//        // Create bus
//        Bus* bus = new Bus(busNo, companyID, company, currentStop, 50);
//        if (system.registerBus(bus)) {
//            busesLoaded++;
//
//            // Parse and add route stops
//            // Route format: "Stop1 > Stop2 > Stop3 > Stop4"
//            stringstream routeSS(routeStr);
//            string stopID;
//
//            while (getline(routeSS, stopID, '>')) {
//                stopID = trim(stopID);
//                if (!stopID.empty()) {
//                    system.addStopToBusRoute(busNo, stopID);
//                }
//            }
//        }
//    }
//
//    file.close();
//
//    cout << "\n========================================" << endl;
//    cout << "Companies added: " << companiesAdded << endl;
//    cout << "Buses loaded: " << busesLoaded << endl;
//    cout << "Total lines processed: " << (lineNumber - 1) << endl;
//    cout << "========================================\n" << endl;
//
//    return busesLoaded > 0;
//}
//
//int main() {
//    TransportSystem system;
//    int choice;
//
//    do {
//        printMenu();
//        cin >> choice;
//        cin.ignore(); // Clear newline
//
//        switch (choice) {
//        case 1: {
//            // Register Transport Company
//            int id;
//            string name, contact;
//
//            cout << "\n--- Register Transport Company ---" << endl;
//            cout << "Enter Company ID: ";
//            cin >> id;
//            cin.ignore();
//
//            cout << "Enter Company Name: ";
//            getline(cin, name);
//
//            cout << "Enter Contact Number: ";
//            getline(cin, contact);
//
//            TransportCompany* company = new TransportCompany(id, name, contact);
//            system.registerCompany(company);
//            break;
//        }
//
//        case 2: {
//            // Display All Companies
//            cout << "\n--- All Transport Companies ---" << endl;
//            system.displayAllCompanies();
//            break;
//        }
//
//        case 3: {
//            // Search Company by ID
//            int id;
//            cout << "\n--- Search Company by ID ---" << endl;
//            cout << "Enter Company ID: ";
//            cin >> id;
//
//            TransportCompany* comp = system.searchCompany(id);
//            if (comp != nullptr) {
//                comp->display();
//            }
//            else {
//                cout << "Company not found!" << endl;
//            }
//            break;
//        }
//
//        case 4: {
//            // Add Bus Stop
//            string stopID, name;
//            double lat, lon;
//
//            cout << "\n--- Add Bus Stop ---" << endl;
//            cout << "Enter Stop ID (e.g., Stop1): ";
//            getline(cin, stopID);
//
//            cout << "Enter Stop Name: ";
//            getline(cin, name);
//
//            cout << "Enter Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Longitude: ";
//            cin >> lon;
//
//            BusStop* stop = new BusStop(stopID, name, lat, lon);
//            system.addBusStop(stop);
//            break;
//        }
//
//        case 5: {
//            // Connect Bus Stops
//            string stop1, stop2;
//
//            cout << "\n--- Connect Bus Stops ---" << endl;
//            cout << "Enter First Stop ID: ";
//            getline(cin, stop1);
//
//            cout << "Enter Second Stop ID: ";
//            getline(cin, stop2);
//
//            system.connectBusStops(stop1, stop2);
//            break;
//        }
//
//        case 6: {
//            // Display All Stops
//            cout << "\n--- All Bus Stops ---" << endl;
//            system.displayAllStops();
//            break;
//        }
//
//        case 7: {
//            // Find Nearest Stop
//            double lat, lon;
//
//            cout << "\n--- Find Nearest Stop to Location ---" << endl;
//            cout << "Enter Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Longitude: ";
//            cin >> lon;
//
//            system.findNearestStop(lat, lon);
//            break;
//        }
//
//        case 8: {
//            // Register Bus
//            string busNo, companyName, currentStop;
//            int companyID, capacity;
//
//            cout << "\n--- Register Bus ---" << endl;
//            cout << "Enter Bus Number (e.g., B101): ";
//            getline(cin, busNo);
//
//            cout << "Enter Company ID: ";
//            cin >> companyID;
//            cin.ignore();
//
//            cout << "Enter Company Name: ";
//            getline(cin, companyName);
//
//            cout << "Enter Current Stop ID: ";
//            getline(cin, currentStop);
//
//            cout << "Enter Capacity: ";
//            cin >> capacity;
//
//            Bus* bus = new Bus(busNo, companyID, companyName, currentStop, capacity);
//            system.registerBus(bus);
//            break;
//        }
//
//        case 9: {
//            // Register School Bus
//            string busNo, companyName, currentStop;
//            int companyID, capacity;
//
//            cout << "\n--- Register School Bus ---" << endl;
//            cout << "Enter Bus Number (e.g., SB01): ";
//            getline(cin, busNo);
//
//            cout << "Enter Company ID: ";
//            cin >> companyID;
//            cin.ignore();
//
//            cout << "Enter Company Name: ";
//            getline(cin, companyName);
//
//            cout << "Enter Current Stop ID: ";
//            getline(cin, currentStop);
//
//            cout << "Enter Capacity: ";
//            cin >> capacity;
//
//            Bus* schoolBus = new Bus(busNo, companyID, companyName, currentStop, capacity, true);
//            system.registerSchoolBus(schoolBus);
//            break;
//        }
//
//        case 10: {
//            // Add Stop to Bus Route
//            string busNo, stopID;
//
//            cout << "\n--- Add Stop to Bus Route ---" << endl;
//            cout << "Enter Bus Number: ";
//            getline(cin, busNo);
//
//            cout << "Enter Stop ID: ";
//            getline(cin, stopID);
//
//            system.addStopToBusRoute(busNo, stopID);
//            break;
//        }
//
//        case 11: {
//            // Display Bus Route
//            string busNo;
//
//            cout << "\n--- Display Bus Route ---" << endl;
//            cout << "Enter Bus Number: ";
//            getline(cin, busNo);
//
//            system.displayBusRoute(busNo);
//            break;
//        }
//
//        case 12: {
//            // Display All Buses
//            cout << "\n--- All Buses ---" << endl;
//            system.displayAllBuses();
//            break;
//        }
//
//        case 13: {
//            // Display School Buses Only
//            cout << "\n--- School Buses ---" << endl;
//            system.displaySchoolBuses();
//            break;
//        }
//
//        case 14: {
//            // Search Bus by Number
//            string busNo;
//
//            cout << "\n--- Search Bus by Number ---" << endl;
//            cout << "Enter Bus Number: ";
//            getline(cin, busNo);
//
//            Bus* bus = system.getBus(busNo);
//            if (bus != nullptr) {
//                bus->display();
//            }
//            else {
//                cout << "Bus not found!" << endl;
//            }
//            break;
//        }
//
//        case 15: {
//            // Add Passenger to Queue
//            string name, destination;
//            int ticketNo;
//
//            cout << "\n--- Add Passenger to Queue ---" << endl;
//            cout << "Enter Passenger Name: ";
//            getline(cin, name);
//
//            cout << "Enter Destination Stop: ";
//            getline(cin, destination);
//
//            cout << "Enter Ticket Number: ";
//            cin >> ticketNo;
//
//            system.addPassenger(name, destination, ticketNo);
//            break;
//        }
//
//        case 16: {
//            // Board Passenger on Bus
//            string busNo;
//
//            cout << "\n--- Board Passenger on Bus ---" << endl;
//            cout << "Enter Bus Number: ";
//            getline(cin, busNo);
//
//            system.boardPassenger(busNo);
//            break;
//        }
//
//        case 17: {
//            // Display Passenger Queue
//            cout << "\n--- Passenger Queue ---" << endl;
//            system.displayPassengerQueue();
//            break;
//        }
//
//        case 18: {
//            // Find Shortest Path
//            string start, end;
//
//            cout << "\n--- Find Shortest Path (Dijkstra) ---" << endl;
//            cout << "Enter Start Stop ID: ";
//            getline(cin, start);
//
//            cout << "Enter End Stop ID: ";
//            getline(cin, end);
//
//            system.findShortestPath(start, end);
//            break;
//        }
//
//        case 19: {
//            // Find Nearest Bus
//            double lat, lon;
//
//            cout << "\n--- Find Nearest Bus to Location ---" << endl;
//            cout << "Enter Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Longitude: ";
//            cin >> lon;
//
//            system.findNearestBus(lat, lon);
//            break;
//        }
//
//        case 20: {
//            // Emergency Routing
//            double lat, lon;
//            string destination;
//
//            cout << "\n--- Emergency Transport Routing ---" << endl;
//            cout << "Enter Emergency Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Emergency Longitude: ";
//            cin >> lon;
//            cin.ignore();
//
//            cout << "Enter Destination Stop ID: ";
//            getline(cin, destination);
//
//            system.emergencyRouting(lat, lon, destination);
//            break;
//        }
//
//        case 21: {
//            // Track Bus Location
//            string busNo, newStop;
//
//            cout << "\n--- Track Bus Location ---" << endl;
//            cout << "Enter Bus Number: ";
//            getline(cin, busNo);
//
//            cout << "Enter New Stop ID: ";
//            getline(cin, newStop);
//
//            system.trackBusLocation(busNo, newStop);
//            break;
//        }
//
//        case 22: {
//            // Move Bus to Next Stop
//            string busNo;
//
//            cout << "\n--- Move Bus to Next Stop ---" << endl;
//            cout << "Enter Bus Number: ";
//            getline(cin, busNo);
//
//            system.moveBusToNextStop(busNo);
//            break;
//        }
//
//        case 23: {
//            // Display Route History
//            cout << "\n--- Route History ---" << endl;
//            system.displayRouteHistory();
//            break;
//        }
//
//        case 24: {
//            // Track School Bus Route
//            string busNo;
//
//            cout << "\n--- Track School Bus Route ---" << endl;
//            cout << "Enter School Bus Number: ";
//            getline(cin, busNo);
//
//            system.trackSchoolBusRoute(busNo);
//            break;
//        }
//
//        case 25: {
//            // Display System Statistics
//            cout << "\n--- System Statistics ---" << endl;
//            system.displaySystemStatistics();
//            break;
//        }
//
//        case 26: {
//            // Load Sample Data
//            loadSampleData(system);
//            break;
//        }
//
//        case 27: {
//            // Load Stops from CSV
//            string filename;
//
//            cout << "\n--- Load Stops from CSV ---" << endl;
//            cout << "Enter CSV filename (e.g., stops.csv): ";
//            getline(cin, filename);
//
//            loadStopsFromCSV(system, filename);
//            break;
//        }
//
//        case 28: {
//            // Load Buses from CSV
//            string filename;
//
//            cout << "\n--- Load Buses from CSV ---" << endl;
//            cout << "Enter CSV filename (e.g., buses.csv): ";
//            getline(cin, filename);
//
//            loadBusesFromCSV(system, filename);
//            break;
//        }
//
//        case 0: {
//            cout << "\n========================================" << endl;
//            cout << "Exiting Transport Sector Module..." << endl;
//            cout << "Thank you for using Smart City!" << endl;
//            cout << "========================================" << endl;
//            break;
//        }
//
//        default: {
//            cout << "\nInvalid choice! Please try again." << endl;
//            break;
//        }
//        }
//
//        if (choice != 0) {
//            cout << "\nPress Enter to continue...";
//            cin.get();
//        }
//
//    } while (choice != 0);
//
//    return 0;
//}