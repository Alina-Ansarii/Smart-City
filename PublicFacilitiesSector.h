#pragma once


#include <iostream>
#include <string>
#include "Facility.h"
#include "LQS.h"

using namespace std;



class PublicFacilitiesSector {
private:
    FacilityGraph* facilityGraph;               // Graph for connectivity and pathfinding
    FacilityHashTable* facilityByType;           // Hash table for type-based lookup
    SinglyLinkedList<Facility*>* allFacilities;  // Master list owning all Facility objects

    int facilityCount;
    int maxCapacity;

    // ID generation counter
    int nextIdNumber;


    /*
     * Generate Unique Facility ID - O(1)
     * Format: "FAC-XXXX" where XXXX is incrementing number
     */
    string generateFacilityId() {
        string id = "FAC-";
        int num = nextIdNumber++;

        // Pad with zeros
        if (num < 10) id += "000";
        else if (num < 100) id += "00";
        else if (num < 1000) id += "0";

        // Manual int to string conversion (no STL)
        char buffer[10];
        int i = 0;
        int temp = num;

        if (temp == 0) {
            buffer[i++] = '0';
        }
        else {
            while (temp > 0) {
                buffer[i++] = '0' + (temp % 10);
                temp /= 10;
            }
        }

        // Reverse
        for (int j = i - 1; j >= 0; j--) {
            id += buffer[j];
        }

        return id;
    }

    /*
     * Find Facility in Master List - O(n)
     */
    Facility* findInMasterList(const string& facilityID) const {
        Node<Facility*>* current = allFacilities->getHead();

        while (current != nullptr) {
            if (current->data->getFacilityId() == facilityID) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

public:

    PublicFacilitiesSector(int capacity = 100, int hashTableSize = 17)
        : maxCapacity(capacity), facilityCount(0), nextIdNumber(1)
    {
        facilityGraph = new FacilityGraph(capacity);
        facilityByType = new FacilityHashTable(hashTableSize);
        allFacilities = new SinglyLinkedList<Facility*>();
    }

    /*
     * Deletes: FacilityGraph, FacilityHashTable, all Facility objects
     */
    ~PublicFacilitiesSector() {
        // Delete all Facility objects from master list
        Node<Facility*>* current = allFacilities->getHead();
        while (current != nullptr) {
            delete current->data;
            current = current->next;
        }

        delete allFacilities;
        delete facilityGraph;
        delete facilityByType;
    }

    int getFacilityCount() const { return facilityCount; }
    int getMaxCapacity() const { return maxCapacity; }
    bool isEmpty() const { return facilityCount == 0; }
    bool isFull() const { return facilityCount >= maxCapacity; }


    Facility* registerFacility(const string& name, const string& type,
        const string& sector, double latitude, double longitude) {
        if (facilityCount >= maxCapacity) {
            cout << "Error: Facility capacity reached (" << maxCapacity << ")" << endl;
            return nullptr;
        }

        // Generate unique ID and create facility
        string id = generateFacilityId();
        Facility* facility = new Facility(id, name, type, sector, latitude, longitude);

        // Add to all data structures
        allFacilities->insertEnd(facility);
        facilityGraph->addFacility(facility);
        facilityByType->addFacility(type, facility);

        facilityCount++;
        return facility;
    }

    /*
     * Register Facility with Custom ID - O(1) amortized
     * For loading from file/database with pre-existing IDs
     */
    Facility* registerFacilityWithId(const string& id, const string& name,
        const string& type, const string& sector,
        double latitude, double longitude) {
        if (facilityCount >= maxCapacity) {
            cout << "Error: Facility capacity reached (" << maxCapacity << ")" << endl;
            return nullptr;
        }

        // Check for duplicate ID
        if (findInMasterList(id) != nullptr) {
            cout << "Error: Facility ID " << id << " already exists" << endl;
            return nullptr;
        }

        Facility* facility = new Facility(id, name, type, sector, latitude, longitude);

        allFacilities->insertEnd(facility);
        facilityGraph->addFacility(facility);
        facilityByType->addFacility(type, facility);

        facilityCount++;
        return facility;
    }

    /*
     * Connect Two Facilities - O(n)
     * Creates bidirectional weighted edge in graph
     */
    bool connectFacilities(const string& id1, const string& id2, double distance) {
        return facilityGraph->connectFacilities(id1, id2, distance);
    }

    /*
     * Auto-connect Facilities Within Distance - O(n²)
     * Connects all facilities that are within specified distance of each other
     */
    void autoConnectByDistance(double maxDistance) {
        int count;
        Facility** facilities = facilityGraph->getAllFacilities(&count);

        if (facilities == nullptr) return;

        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                // Calculate distance between facilities
                double lat1 = facilities[i]->getLatitude();
                double lon1 = facilities[i]->getLongitude();
                double lat2 = facilities[j]->getLatitude();
                double lon2 = facilities[j]->getLongitude();

                // Simple Euclidean approximation (scaled)
                double dLat = lat2 - lat1;
                double dLon = lon2 - lon1;
                double dist = sqrt(dLat * dLat + dLon * dLon) * 111.0; // ~111 km per degree

                if (dist <= maxDistance) {
                    connectFacilities(facilities[i]->getFacilityId(),
                        facilities[j]->getFacilityId(), dist);
                }
            }
        }

        delete[] facilities;
    }


    /*
     * Get Facility by ID - O(n)
     */
    Facility* getFacilityById(const string& facilityID) const {
        return facilityGraph->getFacilityById(facilityID);
    }

    /*
     * Find Nearest Facility (any type) - O(n)
     */
    Facility* findNearestFacility(double latitude, double longitude) const {
        return facilityGraph->findNearestFacility(latitude, longitude);
    }

    /*
     * Find Nearest Facility by Type - O(n)
     * E.g., find nearest "Mosque" or "Park"
     */
    Facility* findNearestFacilityByType(double latitude, double longitude,
        const string& type) const {
        return facilityGraph->findNearestFacilityByType(latitude, longitude, type);
    }

    /*
     * Find Nearest Facility by Name and Location - O(n)
     * Searches for facility matching name pattern near given location
     */
    Facility* findNearestFacilityByName(double latitude, double longitude,
        const string& namePattern) const {
        int count;
        Facility** facilities = facilityGraph->getAllFacilities(&count);

        if (facilities == nullptr) return nullptr;

        Facility* nearest = nullptr;
        double minDist = 999999.0;

        for (int i = 0; i < count; i++) {
            if (facilities[i]->getName().find(namePattern) != string::npos) {
                double dLat = facilities[i]->getLatitude() - latitude;
                double dLon = facilities[i]->getLongitude() - longitude;
                double dist = sqrt(dLat * dLat + dLon * dLon);

                if (dist < minDist) {
                    minDist = dist;
                    nearest = facilities[i];
                }
            }
        }

        delete[] facilities;
        return nearest;
    }

    /*
     * Find Nearest Facility in Sector - O(n)
     */
    Facility* findNearestFacilityInSector(double latitude, double longitude,
        const string& sector) const {
        return facilityGraph->findNearestFacilityInSector(latitude, longitude, sector);
    }

    /*
     * Get All Facilities of Type - O(1) average via hash table
     * Caller must delete returned array
     */
    Facility** getFacilitiesByType(const string& type, int* count) const {
        return facilityByType->getFacilitiesByType(type, count);
    }

    /*
     * Get All Facilities - O(n)
     * Caller must delete returned array
     */
    Facility** getAllFacilities(int* count) const {
        return facilityGraph->getAllFacilities(count);
    }

    /*
     * Get All Facility Types - O(n)
     * Caller must delete returned array
     */
    string* getAllTypes(int* count) const {
        return facilityByType->getAllTypes(count);
    }

    
    Facility** findShortestPath(const string& startId, const string& endId,
        int* pathLength, double* totalDistance) const {
        return facilityGraph->shortestPathBetween(startId, endId, pathLength, totalDistance);
    }


    /*
     * Get Facility Count by Type - O(1) average
     */
    int getCountByType(const string& type) const {
        return facilityByType->getFacilityCountByType(type);
    }

    /*
     * Get Statistics Summary
     */
    void printStatistics() const {
        cout << "\n=== PUBLIC FACILITIES STATISTICS ===" << endl;
        cout << "Total Facilities: " << facilityCount << "/" << maxCapacity << endl;
        cout << "Unique Facility Types: " << facilityByType->getUniqueTypeCount() << endl;

        // Count by type
        int typeCount;
        string* types = facilityByType->getAllTypes(&typeCount);

        if (types != nullptr) {
            cout << "\nBreakdown by Type:" << endl;
            for (int i = 0; i < typeCount; i++) {
                cout << "  " << types[i] << ": "
                    << facilityByType->getFacilityCountByType(types[i]) << endl;
            }
            delete[] types;
        }
    }


    void displayAllFacilities() const {
        cout << "\n=== ALL PUBLIC FACILITIES ===" << endl;
        cout << "ID | Name | Type | Sector | Location" << endl;
        cout << string(60, '-') << endl;

        Node<Facility*>* current = allFacilities->getHead();
        while (current != nullptr) {
            current->data->displayCompact();
            current = current->next;
        }
    }

    void displayFacilitiesByType(const string& type) const {
        int count;
        Facility** facilities = facilityByType->getFacilitiesByType(type, &count);

        cout << "\n=== FACILITIES OF TYPE: " << type << " ===" << endl;

        if (facilities == nullptr || count == 0) {
            cout << "No facilities found of this type." << endl;
            return;
        }

        cout << "Found " << count << " facilities:" << endl;
        for (int i = 0; i < count; i++) {
            cout << (i + 1) << ". ";
            facilities[i]->displayCompact();
        }

        delete[] facilities;
    }

    void displayGraph() const {
        facilityGraph->displayGraph();
    }

    void displayHashTable() const {
        facilityByType->display();
    }

    bool loadFacilityData(const string& id, const string& name, const string& type,
        const string& sector, double lat, double lon) {
        Facility* f = registerFacilityWithId(id, name, type, sector, lat, lon);
        return (f != nullptr);
    }
};


