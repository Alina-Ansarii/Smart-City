#pragma once
/*
================================================================================
TRANSPORT MODULE - PART 2: MANAGEMENT SYSTEM & BONUS FEATURES
================================================================================
Smart City Project - Transport Sector Implementation
Course: Data Structures

This header contains:
1. TransportCompany - Company management entity
2. BusHashTable - Hash table for fast bus lookup (O(1) average)
3. CompanyHashTable - Hash table for company lookup
4. BusRouteGraph - Graph wrapper for route network
5. TransportSystem - Main orchestration class
6. BONUS FEATURES:
   - School Bus Tracking
   - Emergency Transport Routing
   - Real-time Route Simulation

Dependencies:
- TransportCore.h (Part 1)
- HashTable.cpp (Project base implementation)
- Graph.cpp (Project base implementation)

All project requirements satisfied with comprehensive edge case handling.
================================================================================
*/

#include "Transport.h"
#include "HashTable.h"
#include "Graph.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class TransportCompany {
private:
    int companyID;
    string companyName;
    string contactNumber;
    int totalBuses;

public:
    // ==================== CONSTRUCTORS ====================

    TransportCompany() {
        companyID = 0;
        companyName = "";
        contactNumber = "";
        totalBuses = 0;
    }

    TransportCompany(int id, string name, string contact) {
        // Validate ID
        if (id < 0) {
            cout << "Warning: Invalid company ID! Setting to 0." << endl;
            companyID = 0;
        }
        else {
            companyID = id;
        }

        // Validate name
        companyName = name.empty() ? "Unknown Company" : name;

        // Contact can be empty (optional)
        contactNumber = contact;
        totalBuses = 0;
    }

    // ==================== GETTERS ====================

    int getCompanyID() const { return companyID; }
    string getCompanyName() const { return companyName; }
    string getContactNumber() const { return contactNumber; }
    int getTotalBuses() const { return totalBuses; }

    // ==================== SETTERS ====================

    void setCompanyName(string name) {
        companyName = name.empty() ? "Unknown Company" : name;
    }

    void setContactNumber(string contact) {
        contactNumber = contact;
    }

    void incrementBusCount() {
        if (totalBuses < INT_MAX) {
            totalBuses++;
        }
    }

    void decrementBusCount() {
        if (totalBuses > 0) {
            totalBuses--;
        }
    }

    // ==================== DISPLAY ====================

    void display() const {
        cout << "\n--- Transport Company ---" << endl;
        cout << "Company ID: " << companyID << endl;
        cout << "Name: " << companyName << endl;
        cout << "Contact: " << contactNumber << endl;
        cout << "Total Buses: " << totalBuses << endl;
    }
};


class BusHashTable : private HashTable {
public:
    // Constructor
    // Time Complexity: O(n) for initialization
    BusHashTable(int size = 101) : HashTable(size) {}

    // ==================== BUS OPERATIONS ====================

    // Register bus
    // Time Complexity: O(1) average, O(n) worst
    // Edge Cases: Null pointer, duplicate bus number
    bool registerBus(Bus* bus) {
        if (bus == nullptr) {
            cout << "Error: Cannot register null bus!" << endl;
            return false;
        }

        string key = bus->getBusNumber();

        if (key.empty() || key == "UNKNOWN") {
            cout << "Error: Invalid bus number!" << endl;
            return false;
        }

        // Check if already exists
        if (HashTable::search(key) != nullptr) {
            cout << "Bus " << key << " already registered!" << endl;
            return false;
        }

        HashTable::insert(key, (void*)bus);
        cout << "Bus " << key << " registered successfully!" << endl;
        return true;
    }

    // Search by bus number
    // Time Complexity: O(1) average, O(n) worst
    Bus* searchByNumber(string busNumber) {
        if (busNumber.empty()) {
            return nullptr;
        }
        return (Bus*)HashTable::search(busNumber);
    }

    // Remove bus
    // Time Complexity: O(1) average, O(n) worst
    bool removeBus(string busNumber) {
        if (busNumber.empty()) {
            cout << "Error: Invalid bus number!" << endl;
            return false;
        }

        if (HashTable::remove(busNumber)) {
            cout << "Bus " << busNumber << " removed successfully!" << endl;
            return true;
        }

        cout << "Bus " << busNumber << " not found!" << endl;
        return false;
    }

    // Update bus location
    // Time Complexity: O(1) average, O(n) worst
    bool updateBusLocation(string busNumber, string newStopID) {
        Bus* bus = searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return false;
        }

        bus->setCurrentStopID(newStopID);
        return true;
    }

    // ==================== DISPLAY OPERATIONS ====================

    // Display all buses
    // Time Complexity: O(n + m) where n=buckets, m=buses
    void displayAllBuses() {
        cout << "\n========== ALL REGISTERED BUSES ==========" << endl;

        void** buses = new void* [1000];
        int count = 0;
        HashTable::getAllValues(buses, count);

        if (count == 0) {
            cout << "No buses registered yet." << endl;
        }
        else {
            cout << "Total buses: " << count << endl;
            cout << "==========================================" << endl;
            for (int i = 0; i < count; i++) {
                Bus* bus = (Bus*)buses[i];
                if (bus != nullptr) {
                    cout << (i + 1) << ". ";
                    bus->displayCompact();
                }
            }
        }

        delete[] buses;
    }

    // Display school buses only (BONUS)
    // Time Complexity: O(n + m)
    void displaySchoolBuses() {
        cout << "\n========== SCHOOL BUSES ==========" << endl;

        void** buses = new void* [1000];
        int count = 0;
        HashTable::getAllValues(buses, count);

        int schoolBusCount = 0;
        for (int i = 0; i < count; i++) {
            Bus* bus = (Bus*)buses[i];
            if (bus != nullptr && bus->isSchool()) {
                schoolBusCount++;
                cout << schoolBusCount << ". ";
                bus->displayCompact();
            }
        }

        if (schoolBusCount == 0) {
            cout << "No school buses registered." << endl;
        }

        delete[] buses;
    }

    // Get total buses
    // Time Complexity: O(1)
    int getTotalBuses() {
        return HashTable::getSize();
    }

    // Get all bus numbers
    // Time Complexity: O(n + m)
    string* getAllBusNumbers(int& count) {
        count = 0;
        string* keys = new string[1000];
        HashTable::getAllKeys(keys, count);
        return keys;
    }

    // BONUS: Get buses with available seats
    // Time Complexity: O(n + m)
    Bus** getBusesWithSeats(int& count, int minSeats = 1) {
        void** allBuses = new void* [1000];
        int totalCount = 0;
        HashTable::getAllValues(allBuses, totalCount);

        Bus** availableBuses = new Bus * [totalCount];
        count = 0;

        for (int i = 0; i < totalCount; i++) {
            Bus* bus = (Bus*)allBuses[i];
            if (bus != nullptr && bus->getAvailableSeats() >= minSeats) {
                availableBuses[count++] = bus;
            }
        }

        delete[] allBuses;
        return availableBuses;
    }
};


class CompanyHashTable : private HashTable {
public:
    CompanyHashTable(int size = 50) : HashTable(size) {}

    // Register company
    // Time Complexity: O(1) average, O(n) worst
    bool registerCompany(TransportCompany* company) {
        if (company == nullptr) {
            cout << "Error: Cannot register null company!" << endl;
            return false;
        }

        string key = to_string(company->getCompanyID());

        // Check duplicate
        if (HashTable::search(key) != nullptr) {
            cout << "Company ID " << company->getCompanyID()
                << " already registered!" << endl;
            return false;
        }

        HashTable::insert(key, (void*)company);
        cout << "Company " << company->getCompanyName() << " registered!" << endl;
        return true;
    }

    // Search by ID
    // Time Complexity: O(1) average, O(n) worst
    TransportCompany* searchByID(int companyID) {
        string key = to_string(companyID);
        return (TransportCompany*)HashTable::search(key);
    }

    // Remove company
    // Time Complexity: O(1) average, O(n) worst
    bool removeCompany(int companyID) {
        string key = to_string(companyID);
        return HashTable::remove(key);
    }

    // Update company contact
    // Time Complexity: O(1) average, O(n) worst
    bool updateCompanyContact(int companyID, string newContact) {
        TransportCompany* company = searchByID(companyID);
        if (company == nullptr) {
            cout << "Company ID " << companyID << " not found!" << endl;
            return false;
        }

        company->setContactNumber(newContact);
        return true;
    }

    // Display all companies
    // Time Complexity: O(n + m)
    void displayAllCompanies() {
        cout << "\n========== ALL TRANSPORT COMPANIES ==========" << endl;

        void** companies = new void* [1000];
        int count = 0;
        HashTable::getAllValues(companies, count);

        if (count == 0) {
            cout << "No companies registered yet." << endl;
        }
        else {
            for (int i = 0; i < count; i++) {
                TransportCompany* comp = (TransportCompany*)companies[i];
                if (comp != nullptr) {
                    comp->display();
                }
            }
        }

        delete[] companies;
    }

    // Get total companies
    // Time Complexity: O(1)
    int getTotalCompanies() {
        return HashTable::getSize();
    }
};

class BusRouteGraph : private Graph {
private:
    BusStop** stops;  // Array to store actual stop objects
    int stopCapacity;
    int stopCount;

public:
    // Constructor
    // Time Complexity: O(n)
    BusRouteGraph(int cap = 100) : Graph(cap) {
        stopCapacity = cap;
        stops = new BusStop * [stopCapacity];
        for (int i = 0; i < stopCapacity; i++) {
            stops[i] = nullptr;
        }
        stopCount = 0;
    }

    // Destructor
    // Time Complexity: O(n)
    ~BusRouteGraph() {
        // Don't delete stops - we don't own them
        delete[] stops;
    }

    // ==================== STOP MANAGEMENT ====================

    // Add bus stop
    // Time Complexity: O(n) for duplicate check
    // Edge Cases: Null pointer, duplicate, capacity exceeded
    bool addStop(BusStop* stop) {
        if (stop == nullptr) {
            cout << "Error: Cannot add null stop!" << endl;
            return false;
        }

        if (stopCount >= stopCapacity) {
            cout << "Error: Stop capacity reached!" << endl;
            return false;
        }

        // Check for duplicate
        for (int i = 0; i < stopCount; i++) {
            if (stops[i] != nullptr &&
                stops[i]->getStopID() == stop->getStopID()) {
                cout << "Stop " << stop->getStopID() << " already exists!" << endl;
                return false;
            }
        }

        // Add to graph
        int nodeIndex = Graph::addNode((void*)stop);
        if (nodeIndex < 0) {
            cout << "Error adding stop to graph!" << endl;
            return false;
        }

        stops[stopCount++] = stop;
        cout << "Stop " << stop->getName() << " added successfully!" << endl;
        return true;
    }

    // Connect two stops
    // Time Complexity: O(n) for finding stops + O(1) for adding edge
    // Edge Cases: Stops don't exist, invalid distance
    bool connectStops(string stop1ID, string stop2ID, double distance = -1.0) {
        BusStop* stop1 = getStop(stop1ID);
        BusStop* stop2 = getStop(stop2ID);

        if (stop1 == nullptr || stop2 == nullptr) {
            cout << "Error: One or both stops not found!" << endl;
            return false;
        }

        // Calculate distance if not provided
        if (distance < 0) {
            distance = stop1->distanceTo(stop2);
        }

        // Add bidirectional edges
        int index1 = findStopIndex(stop1ID);
        int index2 = findStopIndex(stop2ID);

        if (index1 < 0 || index2 < 0) {
            cout << "Error: Stop indices not found!" << endl;
            return false;
        }

        Graph::addEdge(index1, index2, distance);
        Graph::addEdge(index2, index1, distance);  // Bidirectional

        cout << "Connected " << stop1->getName() << " <-> " << stop2->getName()
            << " (distance: " << distance << " km)" << endl;
        return true;
    }

    // Get stop by ID
    // Time Complexity: O(n)
    BusStop* getStop(string stopID) {
        for (int i = 0; i < stopCount; i++) {
            if (stops[i] != nullptr && stops[i]->getStopID() == stopID) {
                return stops[i];
            }
        }
        return nullptr;
    }

    // Find stop index
    // Time Complexity: O(n)
    int findStopIndex(string stopID) {
        for (int i = 0; i < stopCount; i++) {
            if (stops[i] != nullptr && stops[i]->getStopID() == stopID) {
                return i;
            }
        }
        return -1;
    }

    // ==================== PATHFINDING ====================

    // Find shortest path between two stops (Dijkstra's Algorithm)
    // Time Complexity: O(E log V) as per project requirement
    // Edge Cases: No path exists, same start/end, stops don't exist
    BusStop** shortestPathBetween(string startID, string endID,
        int* pathLength, double* totalDistance) {
        int startIndex = findStopIndex(startID);
        int endIndex = findStopIndex(endID);

        if (startIndex < 0 || endIndex < 0) {
            cout << "Error: Invalid stops!" << endl;
            return nullptr;
        }

        // Use Graph's Dijkstra implementation
        int* path = Graph::dijkstra(startIndex, endIndex, totalDistance);

        if (path == nullptr) {
            return nullptr;
        }

        *pathLength = path[0];  // First element is path length

        // Convert indices to BusStop pointers
        BusStop** stopPath = new BusStop * [*pathLength];
        for (int i = 0; i < *pathLength; i++) {
            int index = path[i + 1];  // +1 because path[0] is length
            if (index >= 0 && index < stopCount) {
                stopPath[i] = stops[index];
            }
        }

        delete[] path;
        return stopPath;
    }

    // Find nearest stop to coordinates
    // Time Complexity: O(n)
    BusStop* findNearestStop(double lat, double lon) {
        if (stopCount == 0) {
            return nullptr;
        }

        BusStop* nearest = stops[0];
        double minDistance = stops[0]->distanceToPoint(lat, lon);

        for (int i = 1; i < stopCount; i++) {
            if (stops[i] != nullptr) {
                double distance = stops[i]->distanceToPoint(lat, lon);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = stops[i];
                }
            }
        }

        return nearest;
    }

    // ==================== DISPLAY & STATISTICS ====================

    // Display all stops
    // Time Complexity: O(n)
    void displayAllStops() {
        cout << "\n========== ALL BUS STOPS ==========" << endl;
        cout << "Total stops: " << stopCount << endl;
        cout << "===================================" << endl;

        for (int i = 0; i < stopCount; i++) {
            if (stops[i] != nullptr) {
                cout << (i + 1) << ". ";
                stops[i]->display();
            }
        }
    }

    // Get total stops
    // Time Complexity: O(1)
    int getTotalStops() {
        return stopCount;
    }

    // Get all stops
    // Time Complexity: O(1)
    BusStop** getAllStops() {
        return stops;
    }
};

 
class TransportSystem {
public:   
    CompanyHashTable* companyTable;
    BusHashTable* busTable;
    BusRouteGraph* routeGraph;
    PassengerQueue* passengerQueue;
    RouteStack* routeHistory;

    // ==================== CONSTRUCTOR/DESTRUCTOR ====================

    TransportSystem() {
        companyTable = new CompanyHashTable(50);
        busTable = new BusHashTable(101);
        routeGraph = new BusRouteGraph(100);
        passengerQueue = new PassengerQueue(200);
        routeHistory = new RouteStack(1000);

    }

    ~TransportSystem() {
        delete companyTable;
        delete busTable;
        delete routeGraph;
        delete passengerQueue;
        delete routeHistory;
    }

    // ==================== COMPANY MANAGEMENT ====================

    // Register transport company
    // Time Complexity: O(1) average
    bool registerCompany(TransportCompany* company) {
        return companyTable->registerCompany(company);
    }

    // Search company by ID
    // Time Complexity: O(1) average
    TransportCompany* searchCompany(int companyID) {
        return companyTable->searchByID(companyID);
    }

    // Display all companies
    // Time Complexity: O(n)
    void displayAllCompanies() {
        companyTable->displayAllCompanies();
    }

    // ==================== BUS STOP MANAGEMENT ====================

    // Add bus stop
    // Time Complexity: O(n)
    bool addBusStop(BusStop* stop) {
        return routeGraph->addStop(stop);
    }

    // Connect two stops
    // Time Complexity: O(n) for search + O(1) for connection
    bool connectBusStops(string stop1ID, string stop2ID, double distance = -1.0) {
        return routeGraph->connectStops(stop1ID, stop2ID, distance);
    }

    // Display all stops
    // Time Complexity: O(n)
    void displayAllStops() {
        routeGraph->displayAllStops();
    }

    // ==================== BUS MANAGEMENT ====================

    // Register bus
    // Time Complexity: O(1) average
    bool registerBus(Bus* bus) {
        bool success = busTable->registerBus(bus);

        if (success) {
            // Update company bus count
            TransportCompany* company = companyTable->searchByID(bus->getCompanyID());
            if (company != nullptr) {
                company->incrementBusCount();
            }
        }

        return success;
    }

    // Add stop to bus route
    // Time Complexity: O(n)
    bool addStopToBusRoute(string busNumber, string stopID) {
        Bus* bus = busTable->searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return false;
        }

        BusStop* stop = routeGraph->getStop(stopID);
        if (stop == nullptr) {
            cout << "Stop " << stopID << " not found!" << endl;
            return false;
        }

        bus->addStopToRoute(stopID, stop->getName(), stop);
        cout << "Stop " << stop->getName() << " added to bus " << busNumber << " route" << endl;
        return true;
    }

    // Display bus route
    // Time Complexity: O(n)
    void displayBusRoute(string busNumber) {
        Bus* bus = busTable->searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return;
        }

        bus->displayRoute();
    }

    // Display all buses
    // Time Complexity: O(n)
    void displayAllBuses() {
        busTable->displayAllBuses();
    }
    Bus* getBus(string busNumber) {
        return busTable->searchByNumber(busNumber);
    }

    // ==================== REAL-TIME BUS TRACKING ====================

    // Track/Update bus location
    // Time Complexity: O(1) average
    bool trackBusLocation(string busNumber, string newStopID) {
        Bus* bus = busTable->searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return false;
        }

        BusStop* stop = routeGraph->getStop(newStopID);
        if (stop == nullptr) {
            cout << "Stop " << newStopID << " not found!" << endl;
            return false;
        }

        // Record in history
        routeHistory->push(newStopID, stop->getName());

        // Update bus location
        bus->setCurrentStop(stop);
        cout << "Bus " << busNumber << " tracked at " << stop->getName() << endl;
        return true;
    }

    // Move bus to next stop (Real-time simulation)
    // Time Complexity: O(n)
    bool moveBusToNextStop(string busNumber) {
        Bus* bus = busTable->searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return false;
        }

        return bus->moveToNextStop();
    }

    // Display route history
    // Time Complexity: O(n)
    void displayRouteHistory() {
        routeHistory->displayHistory();
    }

    // ==================== PATHFINDING & ROUTING ====================

    // Find shortest path (Dijkstra's Algorithm - Required by project)
    // Time Complexity: O(E log V)
    void findShortestPath(string startStopID, string endStopID) {
        BusStop* startStop = routeGraph->getStop(startStopID);
        BusStop* endStop = routeGraph->getStop(endStopID);

        if (startStop == nullptr || endStop == nullptr) {
            cout << "One or both stops not found!" << endl;
            return;
        }

        cout << "\n========== FINDING SHORTEST PATH ==========" << endl;
        cout << "From: " << startStop->getName() << " (" << startStopID << ")" << endl;
        cout << "To: " << endStop->getName() << " (" << endStopID << ")" << endl;
        cout << "===========================================" << endl;

        int pathLength = 0;
        double totalDistance = 0.0;

        BusStop** path = routeGraph->shortestPathBetween(startStopID, endStopID,
            &pathLength, &totalDistance);

        if (path == nullptr) {
            cout << "\nNo path found between these stops!" << endl;
            return;
        }

        cout << "\n[SUCCESS] Shortest Route Found!" << endl;
        cout << "Total Distance: " << totalDistance << " km" << endl;
        cout << "Number of Stops: " << pathLength << endl;
        cout << "\nRoute:" << endl;

        for (int i = 0; i < pathLength; i++) {
            cout << (i + 1) << ". " << path[i]->getName()
                << " (" << path[i]->getStopID() << ")";
            if (i < pathLength - 1) cout << " ->";
            cout << endl;
        }

        delete[] path;
    }

    // Find nearest bus to passenger location (Required by project)
    // Time Complexity: O(n * m) where n = buses, m = stops
    void findNearestBus(double latitude, double longitude) {
        cout << "\n========== FINDING NEAREST BUS ==========" << endl;
        cout << "Your Location: (" << latitude << ", " << longitude << ")" << endl;

        Bus* nearestBus = nullptr;
        BusStop* nearestStop = nullptr;
        double minDistance = 999999.0;

        // Get all buses
        string* busNumbers = new string[1000];
        int busCount = 0;
        string* allNumbers = busTable->getAllBusNumbers(busCount);

        for (int i = 0; i < busCount; i++) {
            Bus* bus = busTable->searchByNumber(allNumbers[i]);
            if (bus != nullptr && bus->getIsActive()) {
                BusStop* stop = routeGraph->getStop(bus->getCurrentStopID());

                if (stop != nullptr) {
                    double distance = stop->distanceToPoint(latitude, longitude);

                    if (distance < minDistance) {
                        minDistance = distance;
                        nearestBus = bus;
                        nearestStop = stop;
                    }
                }
            }
        }

        delete[] allNumbers;
        delete[] busNumbers;

        if (nearestBus != nullptr) {
            cout << "\n[SUCCESS] Nearest Bus Found:" << endl;
            nearestBus->display();
            cout << "\nCurrent Location: " << nearestStop->getName()
                << " (" << nearestStop->getStopID() << ")" << endl;
            cout << "Distance from you: " << minDistance << " km" << endl;
            cout << "Available Seats: " << nearestBus->getAvailableSeats() << endl;
        }
        else {
            cout << "\nNo buses found in the system!" << endl;
        }
    }

    // Find nearest stop to location
    // Time Complexity: O(n)
    void findNearestStop(double latitude, double longitude) {
        cout << "\n========== FINDING NEAREST STOP ==========" << endl;
        cout << "Your Location: (" << latitude << ", " << longitude << ")" << endl;

        BusStop* nearest = routeGraph->findNearestStop(latitude, longitude);

        if (nearest != nullptr) {
            cout << "\n[SUCCESS] Nearest Stop Found:" << endl;
            nearest->display();

            double distance = nearest->distanceToPoint(latitude, longitude);
            cout << "Distance: " << distance << " km" << endl;
        }
        else {
            cout << "No stops available!" << endl;
        }
    }

    // ==================== PASSENGER MANAGEMENT ====================

    // Add passenger to queue
    // Time Complexity: O(1)
    bool addPassenger(string name, string destination, int ticketNumber) {
        return passengerQueue->addPassenger(name, destination, ticketNumber);
    }

    // Board passenger onto bus
    // Time Complexity: O(1)
    bool boardPassenger(string busNumber) {
        Bus* bus = busTable->searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return false;
        }

        if (passengerQueue->isEmpty()) {
            cout << "No passengers waiting!" << endl;
            return false;
        }

        if (bus->getAvailableSeats() <= 0) {
            cout << "Bus is full!" << endl;
            return false;
        }

        Passenger* passenger = passengerQueue->removePassenger();
        if (bus->addPassengers(1)) {
            cout << "[SUCCESS] " << passenger->name << " boarded bus " << busNumber << endl;
            delete passenger;
            return true;
        }

        return false;
    }

    // Display passenger queue
    // Time Complexity: O(n)
    void displayPassengerQueue() {
        passengerQueue->displayQueue();
    }

    // ==================== BONUS: SCHOOL BUS TRACKING ====================

    // Register school bus
    // Time Complexity: O(1) average
    bool registerSchoolBus(Bus* bus) {
        if (bus != nullptr) {
            bus->setSchoolBus(true);
        }
        return registerBus(bus);
    }

    // Display all school buses
    // Time Complexity: O(n)
    void displaySchoolBuses() {
        busTable->displaySchoolBuses();
    }

    // Track school bus route (special tracking for school routes)
    // Time Complexity: O(n)
    void trackSchoolBusRoute(string busNumber) {
        Bus* bus = busTable->searchByNumber(busNumber);
        if (bus == nullptr) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return;
        }

        if (!bus->isSchool()) {
            cout << "Bus " << busNumber << " is not a school bus!" << endl;
            return;
        }

        cout << "\n========== SCHOOL BUS ROUTE TRACKING ==========" << endl;
        bus->display();
        bus->displayRoute();
        bus->displayHistory();
        cout << "===============================================" << endl;
    }

    // ==================== BONUS: EMERGENCY TRANSPORT ROUTING ====================

    // Emergency routing - Find fastest route with available transport
    // Time Complexity: O(E log V) for pathfinding + O(n) for bus search
    void emergencyRouting(double emergencyLat, double emergencyLon,
        string destinationStopID) {
        cout << "\n+======================================================+" << endl;
        cout << "|        EMERGENCY TRANSPORT ROUTING ACTIVATED         |" << endl;
        cout << "+======================================================+" << endl;

        cout << "\nEmergency Location: (" << emergencyLat << ", " << emergencyLon << ")" << endl;
        cout << "Destination: " << destinationStopID << endl;

        // Step 1: Find nearest stop to emergency location
        BusStop* nearestStop = routeGraph->findNearestStop(emergencyLat, emergencyLon);
        if (nearestStop == nullptr) {
            cout << "ERROR: No stops available for emergency routing!" << endl;
            return;
        }

        cout << "\n[1] Nearest Stop to Emergency: " << nearestStop->getName() << endl;

        // Step 2: Find shortest path
        int pathLength = 0;
        double totalDistance = 0.0;
        BusStop** path = routeGraph->shortestPathBetween(
            nearestStop->getStopID(), destinationStopID, &pathLength, &totalDistance);

        if (path == nullptr) {
            cout << "ERROR: No route available!" << endl;
            return;
        }

        cout << "\n[2] Shortest Route Calculated:" << endl;
        cout << "    Distance: " << totalDistance << " km" << endl;
        cout << "    Stops: " << pathLength << endl;

        // Step 3: Find available buses on route
        cout << "\n[3] Finding Available Emergency Transport..." << endl;

        Bus* emergencyBus = nullptr;
        double minBusDistance = 999999.0;

        int busCount = 0;
        string* allBusNumbers = busTable->getAllBusNumbers(busCount);

        for (int i = 0; i < busCount; i++) {
            Bus* bus = busTable->searchByNumber(allBusNumbers[i]);
            if (bus != nullptr && bus->getIsActive() && bus->getAvailableSeats() > 0) {
                // Check if bus serves any stop on emergency route
                for (int j = 0; j < pathLength; j++) {
                    if (bus->servesStop(path[j]->getStopID())) {
                        BusStop* busStop = routeGraph->getStop(bus->getCurrentStopID());
                        if (busStop != nullptr) {
                            double dist = busStop->distanceTo(nearestStop);
                            if (dist < minBusDistance) {
                                minBusDistance = dist;
                                emergencyBus = bus;
                            }
                        }
                        break;
                    }
                }
            }
        }

        delete[] allBusNumbers;

        // Step 4: Display emergency routing plan
        cout << "\n+======================================================+" << endl;
        cout << "|           EMERGENCY ROUTING PLAN                     |" << endl;
        cout << "+======================================================+" << endl;

        if (emergencyBus != nullptr) {
            cout << "\n[OK] TRANSPORT AVAILABLE" << endl;
            emergencyBus->display();
            cout << "\nRoute to Destination:" << endl;
            for (int i = 0; i < pathLength; i++) {
                cout << (i + 1) << ". " << path[i]->getName() << endl;
            }
            cout << "\nEstimated Distance: " << totalDistance << " km" << endl;
        }
        else {
            cout << "\n[X] NO IMMEDIATE TRANSPORT AVAILABLE" << endl;
            cout << "Alternative: Use nearest taxi or private vehicle" << endl;
            cout << "\nRecommended Route:" << endl;
            for (int i = 0; i < pathLength; i++) {
                cout << (i + 1) << ". " << path[i]->getName() << endl;
            }
        }

        delete[] path;
    }

    // ==================== SYSTEM STATISTICS ====================

    void displaySystemStatistics() {
        cout << "\n+=======================================================+" << endl;
        cout << "|        TRANSPORT SYSTEM STATISTICS                    |" << endl;
        cout << "+=======================================================+" << endl;
        cout << "  Total Companies:      " << companyTable->getTotalCompanies() << endl;
        cout << "  Total Buses:          " << busTable->getTotalBuses() << endl;
        cout << "  Total Bus Stops:      " << routeGraph->getTotalStops() << endl;
        cout << "  Passengers Waiting:   " << passengerQueue->getSize() << endl;
        cout << "  Route History Entries: " << routeHistory->getSize() << endl;
        cout << "+=======================================================+" << endl;
    }
};

