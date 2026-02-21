#pragma once
#include <iostream>
#include <string>
#include <cstring>

#include "Graph.h"
#include "LQS.h"
#include "HashTable.h"
using namespace std;


static const double MAX_DISTANCE = 999999.0;


class Facility {
private:
    string facilityID;
    string name;
    string type;      // e.g., "Mosque", "Park", "Water Cooler"
    string sector;    // e.g., "G-10", "F-8"
    double latitude;
    double longitude;

public:
    Facility(const string& id, const string& n, const string& t,
        const string& s, double lat, double lon)
        : facilityID(id), name(n), type(t), sector(s),
        latitude(lat), longitude(lon)
    {
    }

    Facility()
        : facilityID(""), name(""), type(""), sector(""),
        latitude(0.0), longitude(0.0)
    {
    }

    ~Facility() {}

    string getFacilityId() const { return facilityID; }
    string getName() const { return name; }
    string getType() const { return type; }
    string getSector() const { return sector; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    void setFacilityId(const string& id) { facilityID = id; }
    void setName(const string& n) { name = n; }
    void setType(const string& t) { type = t; }
    void setSector(const string& s) { sector = s; }
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }

    void display() const {
        cout << "Facility ID: " << facilityID << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Sector: " << sector << endl;
        cout << "Location: (" << latitude << ", " << longitude << ")" << endl;
    }

    void displayCompact() const {
        cout << facilityID << 
            " | " << name 
            << " | " << type
            << " | " << sector
            << " | (" << latitude 
            << ", " << longitude 
            << ")" << endl;
    }
};

class FacilityGraph : private Graph {
private:

    Facility* getFacilityAt(int index) const {
        if (index < 0 || index >= nodeCount) {
            return nullptr;
        }
        return static_cast<Facility*>(nodes[index]->data);
    }

    /*
     * Find Facility Index - O(n)
     * Purpose: Search through nodes to find facility by ID
     * Input: Facility ID string
     * Output: Index in nodes array, or -1 if not found
     */
    int findFacilityIndex(const string& facilityID) const {
        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f != nullptr && f->getFacilityId() == facilityID) {
                return i;
            }
        }
        return -1;
    }

public:
    FacilityGraph(int cap = 100) : Graph(cap) {}

    ~FacilityGraph() {}

    int getNodeCount() const { return nodeCount; }
    int getCapacity() const { return capacity; }
    bool isEmpty() const { return nodeCount == 0; }
    bool isFull() const { return nodeCount >= capacity; }

    /*
     * Add Facility to Graph - O(1) amortized
     * Returns: true if added successfully, false if null or at capacity
     */
    bool addFacility(Facility* facility) {
        if (facility == nullptr) {
            return false;
        }
        if (nodeCount >= capacity) {
            return false;
        }
        addNode(static_cast<void*>(facility));
        return true;
    }

    /*
     * Check if Facility Exists - O(n)
     */
    bool facilityExists(const string& facilityID) const {
        return findFacilityIndex(facilityID) != -1;
    }

    /*
     * Get Facility by ID - O(n)
     */
    Facility* getFacilityById(const string& facilityID) const {
        int index = findFacilityIndex(facilityID);
        return (index != -1) ? getFacilityAt(index) : nullptr;
    }

    /*
     * Connect Two Facilities - O(n) for finding indices
     * Creates bidirectional weighted edge
     * Returns: true if connected, false if either facility not found
     */
    bool connectFacilities(const string& id1, const string& id2, double distance) {
        int index1 = findFacilityIndex(id1);
        int index2 = findFacilityIndex(id2);

        if (index1 == -1 || index2 == -1) {
            return false;
        }

        // Bidirectional connection
        addEdge(index1, index2, distance);
        addEdge(index2, index1, distance);
        return true;
    }

    /*
     * Find Nearest Facility (any type) - O(n)
     * Uses Euclidean distance approximation
     */
    Facility* findNearestFacility(double lat, double lon) const {
        if (nodeCount == 0) {
            return nullptr;
        }

        Facility* nearest = nullptr;
        double minDist = MAX_DISTANCE;

        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f == nullptr) continue;

            double dist = calculateDistance(lat, lon, f->getLatitude(), f->getLongitude());

            if (dist < minDist) {
                minDist = dist;
                nearest = f;
            }
        }
        return nearest;
    }

    /*
     * Find Nearest Facility of Specific Type - O(n)
     * Filters by facility type before distance comparison
     */
    Facility* findNearestFacilityByType(double lat, double lon, const string& type) const {
        if (nodeCount == 0) {
            return nullptr;
        }

        Facility* nearest = nullptr;
        double minDist = MAX_DISTANCE;

        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f == nullptr) continue;

            if (f->getType() == type) {
                double dist = calculateDistance(lat, lon, f->getLatitude(), f->getLongitude());

                if (dist < minDist) {
                    minDist = dist;
                    nearest = f;
                }
            }
        }
        return nearest;
    }

    /*
     * Find Nearest Facility in Sector - O(n)
     */
    Facility* findNearestFacilityInSector(double lat, double lon, const string& sector) const {
        if (nodeCount == 0) {
            return nullptr;
        }

        Facility* nearest = nullptr;
        double minDist = MAX_DISTANCE;

        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f == nullptr) continue;

            if (f->getSector() == sector) {
                double dist = calculateDistance(lat, lon, f->getLatitude(), f->getLongitude());

                if (dist < minDist) {
                    minDist = dist;
                    nearest = f;
                }
            }
        }
        return nearest;
    }

    /*
     * Shortest Path Between Facilities - O(E log V) using Dijkstra
     * Returns: Array of Facility pointers representing the path
     * Output params: pathLength (number of facilities), totalDistance (sum of edge weights)
     * Caller is responsible for deleting returned array
     */
    Facility** shortestPathBetween(const string& startId, const string& endId,
        int* pathLength, double* totalDistance) {
        *pathLength = 0;
        *totalDistance = 0.0;

        int startIndex = findFacilityIndex(startId);
        int endIndex = findFacilityIndex(endId);

        if (startIndex == -1 || endIndex == -1) {
            return nullptr;
        }

        // dijkstra returns: [count, index0, index1, ..., indexN]
        int* path = dijkstra(startIndex, endIndex, totalDistance);

        if (path == nullptr) {
            return nullptr;
        }

        *pathLength = path[0];

        if (*pathLength == 0) {
            delete[] path;
            return nullptr;
        }

        Facility** facilityPath = new Facility * [*pathLength];

        // path[1..n] contains node indices
        for (int i = 0; i < *pathLength; i++) {
            int nodeIndex = path[i + 1];
            facilityPath[i] = getFacilityAt(nodeIndex);
        }

        delete[] path;
        return facilityPath;
    }

    /*
     * Get All Facilities - O(n)
     * Caller is responsible for deleting returned array (not the facilities themselves)
     */
    Facility** getAllFacilities(int* count) const {
        *count = nodeCount;

        if (nodeCount == 0) {
            return nullptr;
        }

        Facility** facilities = new Facility * [nodeCount];

        for (int i = 0; i < nodeCount; i++) {
            facilities[i] = getFacilityAt(i);
        }

        return facilities;
    }

    /*
     * Get Facilities by Type - O(n)
     * Returns array of facilities matching the type
     */
    Facility** getFacilitiesByType(const string& type, int* count) const {
        // First pass: count matching facilities
        int matchCount = 0;
        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f != nullptr && f->getType() == type) {
                matchCount++;
            }
        }

        *count = matchCount;
        if (matchCount == 0) {
            return nullptr;
        }

        // Second pass: collect matching facilities
        Facility** results = new Facility * [matchCount];
        int idx = 0;

        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f != nullptr && f->getType() == type) {
                results[idx++] = f;
            }
        }

        return results;
    }

    // Display full graph structure
    void displayGraph() const {
        cout << "\n=== FACILITY GRAPH ===" << endl;
        cout << "Total Facilities: " << nodeCount << "/" << capacity << endl;

        for (int i = 0; i < nodeCount; i++) {
            Facility* f = getFacilityAt(i);
            if (f == nullptr) continue;

            cout << "\n[" << i << "] " << f->getName()
                << " (" << f->getType() << ") - " << f->getSector() << endl;
            cout << "    Connected to:" << endl;

            EdgeList* edges = nodes[i]->edges;
            Edge* edge = edges->head;

            if (edge == nullptr) {
                cout << "      (no connections)" << endl;
            }

            while (edge != nullptr) {
                Facility* dest = getFacilityAt(edge->destIndex);
                if (dest != nullptr) {
                    cout << "      -> " << dest->getName()
                        << " (distance: " << edge->weight << " km)" << endl;
                }
                edge = edge->next;
            }
        }
    }
};

class FacilityHashTable {
private:
    struct FacilityTypeEntry {
        string type;                               // Key
        SinglyLinkedList<Facility*>* facilities;   // Value is a list of facility pointers

        FacilityTypeEntry(const string& t) : type(t) {
            facilities = new SinglyLinkedList<Facility*>();
        }

        ~FacilityTypeEntry() {
            delete facilities;  
            //deletes list, not the facilities
        }
    };

    SinglyLinkedList<FacilityTypeEntry*>** buckets;  
    int tableSize;
    int totalFacilities;
    int uniqueTypes;

    // Find entry for given type in bucket - O(chain length)
    FacilityTypeEntry* findEntry(const string& type) const {
        int index = hashString(type, tableSize);
        Node<FacilityTypeEntry*>* current = buckets[index]->getHead();

        while (current != nullptr) {
            if (current->data->type == type) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    // Constructor
    FacilityHashTable(int size = 17) : tableSize(size), totalFacilities(0), uniqueTypes(0) {
        buckets = new SinglyLinkedList<FacilityTypeEntry*>*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            buckets[i] = new SinglyLinkedList<FacilityTypeEntry*>();
        }
    }

    ~FacilityHashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node<FacilityTypeEntry*>* current = buckets[i]->getHead();

            while (current != nullptr) {
                delete current->data;  
                current = current->next;
            }

            delete buckets[i];  
        }
        delete[] buckets;
    }

    int getTotalCount() const { return totalFacilities; }
    int getUniqueTypeCount() const { return uniqueTypes; }
    int getTableSize() const { return tableSize; }
    bool isEmpty() const { return totalFacilities == 0; }

    /*
     * Add Facility - O(1) average, O(n) worst case
     * Automatically creates new type entry if needed
     */
    void addFacility(const string& type, Facility* facility) {
        if (facility == nullptr) return;

        int index = hashString(type, tableSize);
        FacilityTypeEntry* entry = findEntry(type);

        // Create new entry if type doesn't exist
        if (entry == nullptr) {
            entry = new FacilityTypeEntry(type);
            buckets[index]->insertEnd(entry);
            uniqueTypes++;
        }

        entry->facilities->insertEnd(facility);
        totalFacilities++;
    }

    /*
     * Check if Type Exists - O(1) average
     */
    bool typeExists(const string& type) const {
        return findEntry(type) != nullptr;
    }

    /*
     * Get Facility Count for Type - O(1) average
     */
    int getFacilityCountByType(const string& type) const {
        FacilityTypeEntry* entry = findEntry(type);
        return (entry != nullptr) ? entry->facilities->getLength() : 0;
    }

    /*
     * Get Facilities By Type - O(1) average for lookup, O(k) to build array
     * Caller is responsible for deleting returned array
     */
    Facility** getFacilitiesByType(const string& type, int* count) const {
        FacilityTypeEntry* entry = findEntry(type);

        if (entry == nullptr) {
            *count = 0;
            return nullptr;
        }

        int facilityCount = entry->facilities->getLength();

        if (facilityCount == 0) {
            *count = 0;
            return nullptr;
        }

        Facility** results = new Facility * [facilityCount];
        Node<Facility*>* fNode = entry->facilities->getHead();
        int idx = 0;

        while (fNode != nullptr) {
            results[idx++] = fNode->data;
            fNode = fNode->next;
        }

        *count = facilityCount;
        return results;
    }

    /*
     * Get All Types - O(n) where n is total entries
     * Caller is responsible for deleting returned array
     */
    string* getAllTypes(int* count) const {
        if (uniqueTypes == 0) {
            *count = 0;
            return nullptr;
        }

        string* types = new string[uniqueTypes];
        int idx = 0;

        for (int i = 0; i < tableSize; i++) {
            Node<FacilityTypeEntry*>* current = buckets[i]->getHead();

            while (current != nullptr) {
                types[idx++] = current->data->type;
                current = current->next;
            }
        }

        *count = uniqueTypes;
        return types;
    }

    // Display hash table contents
    void display() const {
        cout << "\n=== FACILITY TYPE HASH TABLE ===" << endl;
        cout << "Total Facilities: " << totalFacilities << endl;
        cout << "Unique Types: " << uniqueTypes << endl;
        cout << "Table Size: " << tableSize << endl;

        for (int i = 0; i < tableSize; i++) {
            Node<FacilityTypeEntry*>* current = buckets[i]->getHead();

            while (current != nullptr) {
                FacilityTypeEntry* entry = current->data;

                cout << "\n[Bucket " << i << "] Type: \"" << entry->type << "\"" << endl;
                cout << "  Facilities (" << entry->facilities->getLength() << "):" << endl;

                Node<Facility*>* fNode = entry->facilities->getHead();
                while (fNode != nullptr) {
                    Facility* f = fNode->data;
                    cout << "    - " << f->getName() << " (" << f->getSector() << ")" << endl;
                    fNode = fNode->next;
                }

                current = current->next;
            }
        }
    }
};
