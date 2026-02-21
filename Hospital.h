#pragma once
#pragma once
#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Graph.h"
#include <cmath>

// Forward declaration to avoid circular dependency
static const double MAX_DISTANCE_HOS = 999999.0;

class Hospital {
private:
    string id;
    string name;
    string sector;

    double latitude;
    double longitude;

    int totalEmergencyBeds;
    int availableEmergencyBeds;

    string* specializations;
    int specializationCount;

public:
    // Constructor - initializes all hospital attributes
    // All beds start as available (availableEmergencyBeds = totalEmergencyBeds)

    Hospital(string id, string name, string sector, double lat, double lon, int beds) :
        id(id), name(name), sector(sector),
        latitude(lat), longitude(lon),
        totalEmergencyBeds(beds), availableEmergencyBeds(beds),
        specializations(nullptr), specializationCount(0)
    {
        cout << "Built Hosptial id: " << id << endl;
    }

    // Destructor - frees dynamically allocated specializations array
    ~Hospital() {
        delete[] specializations;
    }

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    string getSector() const { return sector; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    int getTotalEmergencyBeds() const { return totalEmergencyBeds; }
    int getAvailableEmergencyBeds() const { return availableEmergencyBeds; }

    // allocateBed - assigns a bed to a patient
    // Returns true if successful, false if no beds available
    bool allocateBed() {
        if (availableEmergencyBeds > 0) {
            availableEmergencyBeds--;
            cout << "allocated an emergency bed" << endl;
            return true;
        }
        return false;
    }

    // releaseBed - called when patient is discharged
    // Increments available beds but won't exceed total capacity
    void releaseBed() {
        if (availableEmergencyBeds < totalEmergencyBeds) {
            availableEmergencyBeds++;
        }
    }

    // addSpecialization - dynamically grows the array to add new specialty
    // Creates new array with +1 size, copies existing elements, adds new one
    void addSpecialization(string spec) {
        string* newArray = new string[specializationCount + 1];

        if (specializations != nullptr) {
            for (int i = 0; i < specializationCount; i++) {
                newArray[i] = specializations[i];
            }
            delete[] specializations;
        }

        newArray[specializationCount] = spec;
        specializations = newArray;

        specializationCount++;
    }

    // hasSpecialization - linear search to check if hospital offers a specialty
    bool hasSpecialization(string spec) const {
        cout << "Searching for spec: " << spec << endl;
        for (int i = 0; i < specializationCount; i++) {
            if (specializations[i] == spec) {
                return true;
                cout << "Found\n";
            }
        }
        cout << "Not Found\n";
        return false;
    }

    // getSpecializations - returns array pointer and sets count via output parameter
    string* getSpecializations(int* count) const {
        *count = specializationCount;
        return specializations;
    }

    // display - prints all hospital information in readable format
    void display() const {
        cout << "Hospital ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Location: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Emergency Beds: " << availableEmergencyBeds << "/" << totalEmergencyBeds << " available" << endl;
        cout << "Specializations: ";
        for (int i = 0; i < specializationCount; i++) {
            cout << specializations[i];
            if (i < specializationCount - 1) cout << ", ";
        }
        cout << endl;
    }
};

class HospitalGraph : private Graph {
private:

    int findHospitalIndex(string hospitalID) {

        for (int i = 0; i < nodeCount; i++) {
            Hospital* hospital = (Hospital*)nodes[i]->data;

            if (hospital != NULL && hospitalID == hospital->getId()) {
                return i;
            }
        }
        return -1;
    }


    Hospital* getHospitalAt(int index) const {
        if (index < 0 || index >= nodeCount) {
            return nullptr;
        }
        return (Hospital*)(nodes[index]->data);
    }

public:
    HospitalGraph(int capacity = 100) : Graph(capacity) {}
    ~HospitalGraph() {}


    //adds hospital to graph - O(1)
    void addHospital(Hospital* hospital) {
        if (hospital != nullptr && nodeCount < capacity) {
            addNode((void*)hospital);
        }
    }

    /*
    *connects two hospitals with distance to find indices - O(n)
    * find indexes for both hospitals
    * add edges from both  (bidrectional connection)
    */
    bool connectHospitals(string id1, string id2, double distance) {
        int index1 = findHospitalIndex(id1);
        int index2 = findHospitalIndex(id2);

        if (index1 == -1 || index2 == -1) {
            return false;
        }

        bool result1 = addEdge(index1, index2, distance);
        bool result2 = addEdge(index2, index1, distance);

        return result1 && result2;
    }

    //finds nearest hospital by location - O(n)
    Hospital* findNearestHospital(double lat, double lon) {
        if (nodeCount == 0) {
            return nullptr;
        }

        double minDist = MAX_DISTANCE_HOS;
        Hospital* nearest = nullptr;

        for (int i = 0; i < nodeCount; i++) {
            Hospital* h = (Hospital*)nodes[i]->data;
            if (h == nullptr)  continue;

            double dist = calculateDistance(lat, lon, h->getLatitude(), h->getLongitude());

            if (dist < minDist) {
                minDist = dist;
                nearest = h;
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
    Hospital** shortestPathBetween(string startId, string endId, int* pathLength, double* totalDistance) {
        *pathLength = 0;
        *totalDistance = 0.0;

        int startIndex = findHospitalIndex(startId);
        int endIndex = findHospitalIndex(endId);

        if (startIndex == -1 || endIndex == -1) return nullptr;

        int* path = dijkstra(startIndex, endIndex, totalDistance);

        if (path == nullptr) {
            return nullptr;
        }

        *pathLength = path[0];

        if (*pathLength == 0) {
            delete[] path;
            return nullptr;
        }

        Hospital** hospitalPath = new Hospital * [*pathLength];

        for (int i = 0; i < *pathLength; i++) {
            int nodeIndex = path[i + 1];
            hospitalPath[i] = getHospitalAt(nodeIndex);
        }

        delete[] path;
        return hospitalPath;

    }

    // Get all hospitals in the graph - O(n)
    Hospital** getAllHospitals(int* count) {
        *count = nodeCount;

        if (nodeCount == 0) {
            *count = 0;
            return nullptr;
        }

        Hospital** hospitals = new Hospital * [nodeCount];
        int index = 0;

        for (int i = 0; i < nodeCount; i++) {
            hospitals[i] = getHospitalAt(i);
        }

        return hospitals;
    }

    // Get total number of hospitals - O(1)
    int getHospitalCount() {
        return nodeCount;
    }

    // Check if two hospitals are directly connected - O(E) where E is edges from source
    bool areConnected(string id1, string id2) {
        int index1 = findHospitalIndex(id1);
        int index2 = findHospitalIndex(id2);

        if (index1 == -1 || index2 == -1) {
            return false;
        }

        EdgeList* edges = getEdges(index1);
        if (edges == nullptr) {
            return false;
        }

        Edge* current = edges->head;
        while (current != nullptr) {
            if (current->destIndex == index2) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    // Get distance between two directly connected hospitals - O(E)
    double getDistance(string id1, string id2) {
        int index1 = findHospitalIndex(id1);
        int index2 = findHospitalIndex(id2);

        if (index1 == -1 || index2 == -1) {
            return -1.0;
        }

        EdgeList* edges = getEdges(index1);
        if (edges == nullptr) {
            return -1.0;
        }

        Edge* current = edges->head;
        while (current != nullptr) {
            if (current->destIndex == index2) {
                return current->weight;
            }
            current = current->next;
        }

        return -1.0;
    }

    // Get connected hospitals (direct connections) from a hospital - O(E)
    Hospital** getConnectedHospitals(string hospitalId, int* count) {
        int index = findHospitalIndex(hospitalId);

        if (index == -1) {
            *count = 0;
            return nullptr;
        }

        EdgeList* edges = getEdges(index);
        if (edges == nullptr || edges->head == nullptr) {
            *count = 0;
            return nullptr;
        }

        // Count edges
        int edgeCount = 0;
        Edge* current = edges->head;
        while (current != nullptr) {
            edgeCount++;
            current = current->next;
        }

        // Create result array
        Hospital** result = new Hospital * [edgeCount];
        int resultIndex = 0;
        current = edges->head;
        while (current != nullptr) {
            result[resultIndex++] = (Hospital*)nodes[current->destIndex]->data;
            current = current->next;
        }

        *count = edgeCount;
        return result;
    }


    // Get hospitals within distance range from a location - O(n)
    Hospital** getHospitalsWithinRange(double lat, double lon, double range, int* count) {
        if (nodeCount == 0) {
            *count = 0;
            return nullptr;
        }

        Hospital** temp = new Hospital * [nodeCount];
        int foundCount = 0;

        for (int i = 0; i < nodeCount; i++) {
            Hospital* hospital = (Hospital*)nodes[i]->data;
            if (hospital != nullptr) {

                double distance = calculateDistance(lat, lon, hospital->getLatitude(), hospital->getLongitude());

                if (distance <= range) {
                    temp[foundCount++] = hospital;
                }
            }
        }

        if (foundCount == 0) {
            *count = 0;
            delete[] temp;
            return nullptr;
        }

        Hospital** result = new Hospital * [foundCount];
        for (int i = 0; i < foundCount; i++) {
            result[i] = temp[i];
        }
        delete[] temp;

        *count = foundCount;
        return result;
    }

    //find hospital with most available beds - O(n)
    Hospital* findHospitalWithMostBeds() {
        if (nodeCount == 0) {
            return nullptr;
        }

        Hospital* maxBedHospital = nullptr;
        int maxBeds = -1;

        for (int i = 0; i < nodeCount; i++) {
            Hospital* hospital = (Hospital*)nodes[i]->data;
            if (hospital != nullptr && hospital->getAvailableEmergencyBeds() > maxBeds) {
                maxBeds = hospital->getAvailableEmergencyBeds();
                maxBedHospital = hospital;
            }
        }

        return maxBedHospital;
    }

    // Find hospital by ID - O(n)
    Hospital* findHospitalById(string hospitalId) {
        int index = findHospitalIndex(hospitalId);
        if (index == -1) {
            return nullptr;
        }
        return (Hospital*)nodes[index]->data;
    }

    // Display graph information - O(V + E)
    void displayGraph() {
        cout << "\n=== Hospital Network Graph ===" << endl;
        cout << "Total Hospitals: " << nodeCount << endl;
        cout << "---" << endl;

        for (int i = 0; i < nodeCount; i++) {
            Hospital* hospital = (Hospital*)nodes[i]->data;
            if (hospital != nullptr) {
                cout << "\nHospital: " << hospital->getName() << " (ID: " << hospital->getId() << ")" << endl;
                cout << "  Location: (" << hospital->getLatitude() << ", " << hospital->getLongitude() << ")" << endl;
                cout << "  Emergency Beds: " << hospital->getAvailableEmergencyBeds() << "/" << hospital->getTotalEmergencyBeds() << endl;

                EdgeList* edges = getEdges(i);
                if (edges != nullptr && edges->head != nullptr) {
                    cout << "  Connected to:" << endl;
                    Edge* current = edges->head;
                    while (current != nullptr) {
                        Hospital* connected = (Hospital*)nodes[current->destIndex]->data;
                        if (connected != nullptr) {
                            cout << "    - " << connected->getName() << " (Distance: " << current->weight << " km)" << endl;
                        }
                        current = current->next;
                    }
                }
                else {
                    cout << "  Connected to: None" << endl;
                }
            }
        }
    }

};


class EmergencyBedHeap {
private:
    struct HeapNode {
        Hospital* hospital;     // Reference to hospital
        int bedCount;           // Priority value (number of available beds)

        HeapNode() {
            hospital = nullptr;
            bedCount = 0;
        }
    };

    HeapNode* heap;             // Array-based heap
    int heapSize;
    int capacity;

    // Helper functions
    int parent(int i) {
        return (i - 1) / 2;
    }

    int leftChild(int i) {
        return 2 * i + 1;
    }

    int rightChild(int i) {
        return 2 * i + 2;
    }

    // Heapify up - O(log n) - used after insertion
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)].bedCount < heap[i].bedCount) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    // Heapify down - O(log n) - used after removal
    void heapifyDown(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heapSize && heap[left].bedCount > heap[largest].bedCount) {
            largest = left;
        }

        if (right < heapSize && heap[right].bedCount > heap[largest].bedCount) {
            largest = right;
        }

        if (largest != i) {
            swap(i, largest);
            heapifyDown(largest);
        }
    }

    // Swap two elements - O(1)
    void swap(int i, int j) {
        HeapNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // Find hospital index in heap - O(n)
    int findHospitalIndex(Hospital* hospital) {
        if (hospital == nullptr) return -1;

        for (int i = 0; i < heapSize; i++) {
            if (heap[i].hospital == hospital) {
                return i;
            }
        }
        return -1;
    }

public:
    EmergencyBedHeap(int cap = 100) {
        capacity = cap;
        heap = new HeapNode[capacity];
        heapSize = 0;
    }

    ~EmergencyBedHeap() {
        delete[] heap;
    }

    // Insert hospital with bed count - O(log n)
    void insert(Hospital* hospital, int bedCount) {
        if (heapSize >= capacity || hospital == nullptr) {
            return;
        }

        HeapNode newNode;
        newNode.hospital = hospital;
        newNode.bedCount = bedCount;

        heap[heapSize] = newNode;
        heapifyUp(heapSize);
        heapSize++;
    }

    // Extract hospital with maximum available beds - O(log n)
    Hospital* extractMax() {
        if (heapSize <= 0) {
            return nullptr;
        }

        Hospital* maxHospital = heap[0].hospital;

        heap[0] = heap[heapSize - 1];
        heapSize--;

        if (heapSize > 0) {
            heapifyDown(0);
        }

        return maxHospital;
    }

    // Get hospital with maximum available beds without removing - O(1)
    Hospital* peek() {
        if (heapSize <= 0) {
            return nullptr;
        }
        return heap[0].hospital;
    }

    // Get bed count of hospital at top - O(1)
    int peekBedCount() {
        if (heapSize <= 0) {
            return 0;
        }
        return heap[0].bedCount;
    }

    // Update bed count for a hospital - O(n) in worst case
    void updateBedCount(Hospital* hospital, int newCount) {
        int index = findHospitalIndex(hospital);

        if (index == -1) {
            return;  // Hospital not found
        }

        int oldCount = heap[index].bedCount;
        heap[index].bedCount = newCount;

        if (newCount > oldCount) {
            heapifyUp(index);
        }
        else if (newCount < oldCount) {
            heapifyDown(index);
        }
    }

    // Check if heap is empty - O(1)
    bool isEmpty() {
        return heapSize == 0;
    }

    // Get current size - O(1)
    int size() {
        return heapSize;
    }

    // Display heap contents - O(n)
    void displayHeap() const {
        cout << "\n=== Emergency Bed Heap ===" << endl;
        cout << "Heap Size: " << heapSize << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "---" << endl;

        for (int i = 0; i < heapSize; i++) {
            cout << "Position " << i << ": ";
            cout << heap[i].hospital->getName() << " - ";
            cout << heap[i].bedCount << " available beds" << endl;
        }
    }

    // Get all hospitals sorted by available beds (descending) - O(n log n)
    Hospital** getAllSorted(int* count) {
        if (heapSize == 0) {
            *count = 0;
            return nullptr;
        }

        Hospital** result = new Hospital * [heapSize];
        EmergencyBedHeap tempHeap(capacity);

        // Copy all elements
        for (int i = 0; i < heapSize; i++) {
            tempHeap.insert(heap[i].hospital, heap[i].bedCount);
        }

        // Extract all in sorted order (max to min)
        int index = 0;
        while (!tempHeap.isEmpty()) {
            result[index++] = tempHeap.extractMax();
        }

        *count = heapSize;
        return result;
    }

    // Find hospital with specific criteria (at least minBeds available) - O(n)
    Hospital* findHospitalWithMinBeds(int minBeds) {
        for (int i = 0; i < heapSize; i++) {
            if (heap[i].bedCount >= minBeds) {
                return heap[i].hospital;
            }
        }
        return nullptr;
    }

    // Check if hospital exists in heap - O(n)
    bool contains(Hospital* hospital) {
        return findHospitalIndex(hospital) != -1;
    }

    // Remove specific hospital - O(n)
    bool removeHospital(Hospital* hospital) {
        int index = findHospitalIndex(hospital);

        if (index == -1) {
            return false;  // Not found
        }

        heap[index] = heap[heapSize - 1];
        heapSize--;

        if (index < heapSize) {
            heapifyDown(index);
        }

        return true;
    }
};
