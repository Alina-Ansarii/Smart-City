#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <climits>
using namespace std;

class BusStop {
private:
    string stopID;
    string name;
    double latitude;
    double longitude;

public:

    // Default constructor
    BusStop() : stopID(""), name(""), latitude(0.0), longitude(0.0) {}

    // Parameterized constructor with validation
    // Time Complexity: O(1)
    // Edge Cases: Empty strings, out-of-bounds coordinates
    BusStop(string id, string stopName, double lat, double lon) {
        // Validate ID (cannot be empty)
        if (id.empty()) {
            cout << "Warning: Stop ID cannot be empty! Setting to UNKNOWN." << endl;
            stopID = "UNKNOWN";
        }
        else {
            stopID = id;
        }

        // Validate name (cannot be empty)
        name = stopName.empty() ? "Unnamed Stop" : stopName;

        // Validate Islamabad coordinates
        // Islamabad bounds: Lat 33.0-34.0N, Lon 72.5-73.5E
        if (lat < 33.0 || lat > 34.0 || lon < 72.5 || lon > 73.5) {
            cout << "Warning: Coordinates (" << lat << ", " << lon
                << ") outside Islamabad region!" << endl;
        }

        latitude = lat;
        longitude = lon;
    }

    // Copy constructor (Rule of Three - though no dynamic memory here)
    // Time Complexity: O(1)
    BusStop(const BusStop& other)
        : stopID(other.stopID), name(other.name),
        latitude(other.latitude), longitude(other.longitude) {
    }

    // Assignment operator (Rule of Three)
    // Time Complexity: O(1)
    BusStop& operator=(const BusStop& other) {
        if (this != &other) {
            stopID = other.stopID;
            name = other.name;
            latitude = other.latitude;
            longitude = other.longitude;
        }
        return *this;
    }

    // ==================== GETTERS (const-correct) ====================

    string getStopID() const { return stopID; }
    string getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    // ==================== SETTERS WITH VALIDATION ====================

    // Set name with validation
    // Time Complexity: O(1)
    void setName(string stopName) {
        name = stopName.empty() ? "Unnamed Stop" : stopName;
    }

    // Set coordinates with validation
    // Time Complexity: O(1)
    void setCoordinates(double lat, double lon) {
        if (lat < 33.0 || lat > 34.0 || lon < 72.5 || lon > 73.5) {
            cout << "Warning: Coordinates outside Islamabad region!" << endl;
        }
        latitude = lat;
        longitude = lon;
    }

    // ==================== DISTANCE CALCULATIONS ====================

    // Calculate Euclidean distance to another stop
    // Time Complexity: O(1)
    // Edge Cases: Null pointer returns infinity
    double distanceTo(const BusStop* other) const {
        if (other == nullptr) {
            return 999999.0; // Infinity
        }

        double dx = latitude - other->latitude;
        double dy = longitude - other->longitude;
        return sqrt(dx * dx + dy * dy);
    }

    // Calculate distance to specific coordinates
    // Time Complexity: O(1)
    double distanceToPoint(double lat, double lon) const {
        double dx = latitude - lat;
        double dy = longitude - lon;
        return sqrt(dx * dx + dy * dy);
    }

    // ==================== COMPARISON OPERATORS ====================

    bool operator==(const BusStop& other) const {
        return stopID == other.stopID;
    }

    bool operator!=(const BusStop& other) const {
        return !(*this == other);
    }

    // ==================== DISPLAY ====================

    void display() const {
        cout << "Stop ID: " << stopID << " | Name: " << name
            << " | Location: (" << latitude << ", " << longitude << ")" << endl;
    }
};

// ==================== ROUTE NODE ====================
/*
 * Purpose: Node for singly linked list representing bus route
 *
 * As per project requirement: "Bus routes must use a singly linked list"
 */
struct RouteStopNode {
    string stopID;
    string stopName;
    BusStop* stopPtr;  // Pointer to actual stop object 
    RouteStopNode* next;

    RouteStopNode(string id, string name, BusStop* ptr = nullptr) {
        stopID = id;
        stopName = name;
        stopPtr = ptr;
        next = nullptr;
    }
};


class RouteList {
private:
    RouteStopNode* head;
    int stopCount;

public:
    // ==================== CONSTRUCTOR/DESTRUCTOR ====================

    RouteList() : head(nullptr), stopCount(0) {}

    // Destructor - O(n)
    ~RouteList() {
        clear();
    }

    // Copy constructor for deep copy - O(n)
    RouteList(const RouteList& other) {
        head = nullptr;
        stopCount = 0;

        RouteStopNode* current = other.head;
        while (current != nullptr) {
            addStop(current->stopID, current->stopName, current->stopPtr);
            current = current->next;
        }
    }

    // Assignment operator - O(n)
    RouteList& operator=(const RouteList& other) {
        if (this != &other) {
            clear();

            RouteStopNode* current = other.head;
            while (current != nullptr) {
                addStop(current->stopID, current->stopName, current->stopPtr);
                current = current->next;
            }
        }
        return *this;
    }

    // ==================== ADD OPERATIONS ====================

    // Add stop to END of route
    // Time Complexity: O(n) - must traverse to end
    // Edge Cases: Empty ID, duplicate stops
    void addStop(string stopID, string stopName, BusStop* stopPtr = nullptr) {
        // Validation
        if (stopID.empty()) {
            cout << "Error: Cannot add stop with empty ID!" << endl;
            return;
        }

        // Check for duplicates
        if (hasStop(stopID)) {
            cout << "Warning: Stop " << stopID << " already in route!" << endl;
            return;
        }

        RouteStopNode* newNode = new RouteStopNode(stopID, stopName, stopPtr);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            RouteStopNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        stopCount++;
    }

    // Add stop at specific position
    // Time Complexity: O(n)
    // Edge Cases: Invalid position, empty list
    bool addStopAt(string stopID, string stopName, int position, BusStop* stopPtr = nullptr) {
        if (position < 0 || position > stopCount) {
            cout << "Error: Invalid position " << position << endl;
            return false;
        }

        if (stopID.empty()) {
            cout << "Error: Cannot add stop with empty ID!" << endl;
            return false;
        }

        RouteStopNode* newNode = new RouteStopNode(stopID, stopName, stopPtr);

        if (position == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            RouteStopNode* temp = head;
            for (int i = 0; i < position - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        stopCount++;
        return true;
    }

    // ==================== REMOVE OPERATIONS ====================

    // Remove stop from route
    // Time Complexity: O(n)
    // Edge Cases: Empty list, stop not found, removing head
    bool removeStop(string stopID) {
        if (head == nullptr) {
            cout << "Error: Route is empty!" << endl;
            return false;
        }

        // Remove from head
        if (head->stopID == stopID) {
            RouteStopNode* temp = head;
            head = head->next;
            delete temp;
            stopCount--;
            return true;
        }

        // Remove from middle or end
        RouteStopNode* current = head;
        while (current->next != nullptr) {
            if (current->next->stopID == stopID) {
                RouteStopNode* temp = current->next;
                current->next = temp->next;
                delete temp;
                stopCount--;
                return true;
            }
            current = current->next;
        }

        cout << "Error: Stop " << stopID << " not found in route!" << endl;
        return false;
    }

    // ==================== SEARCH OPERATIONS ====================

    // Check if stop exists in route
    // Time Complexity: O(n)
    bool hasStop(string stopID) const {
        RouteStopNode* temp = head;
        while (temp != nullptr) {
            if (temp->stopID == stopID) return true;
            temp = temp->next;
        }
        return false;
    }

    // Get next stop in route
    // Time Complexity: O(n)
    // Edge Cases: Stop not found, at end of route
    string getNextStop(string currentStopID) const {
        if (head == nullptr) return "EMPTY_ROUTE";

        RouteStopNode* temp = head;
        while (temp != nullptr) {
            if (temp->stopID == currentStopID) {
                if (temp->next != nullptr) {
                    return temp->next->stopID;
                }
                else {
                    return "END_OF_ROUTE";
                }
            }
            temp = temp->next;
        }
        return "STOP_NOT_FOUND";
    }

    // Get previous stop in route
    // Time Complexity: O(n)
    // Edge Cases: Stop not found, at start of route
    string getPreviousStop(string currentStopID) const {
        if (head == nullptr || head->stopID == currentStopID) {
            return "START_OF_ROUTE";
        }

        RouteStopNode* temp = head;
        while (temp != nullptr && temp->next != nullptr) {
            if (temp->next->stopID == currentStopID) {
                return temp->stopID;
            }
            temp = temp->next;
        }
        return "STOP_NOT_FOUND";
    }

    // Get first stop
    // Time Complexity: O(1)
    string getFirstStop() const {
        return (head != nullptr) ? head->stopID : "";
    }

    // Get last stop
    // Time Complexity: O(n)
    string getLastStop() const {
        if (head == nullptr) return "";

        RouteStopNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->stopID;
    }

    // Get stop pointer by ID
    // Time Complexity: O(n)
    BusStop* getStopPointer(string stopID) const {
        RouteStopNode* temp = head;
        while (temp != nullptr) {
            if (temp->stopID == stopID) {
                return temp->stopPtr;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Get stop at position
    // Time Complexity: O(n)
    // Edge Cases: Invalid position
    string getStopAt(int position) const {
        if (position < 0 || position >= stopCount) {
            return "";
        }

        RouteStopNode* temp = head;
        for (int i = 0; i < position; i++) {
            temp = temp->next;
        }
        return temp->stopID;
    }

    // ==================== UTILITY OPERATIONS ====================

    // Get total stops in route
    // Time Complexity: O(1)
    int getStopCount() const {
        return stopCount;
    }

    // Check if route is empty
    // Time Complexity: O(1)
    bool isEmpty() const {
        return head == nullptr;
    }

    // Reverse the route
    // Time Complexity: O(n)
    void reverseRoute() {
        RouteStopNode* prev = nullptr;
        RouteStopNode* current = head;
        RouteStopNode* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    // Get all stop IDs as array
    // Time Complexity: O(n)
    // Note: Caller must delete returned array
    string* getAllStopIDs(int& count) const {
        count = stopCount;
        if (stopCount == 0) {
            return nullptr;
        }

        string* stopIDs = new string[stopCount];
        RouteStopNode* temp = head;
        int i = 0;

        while (temp != nullptr) {
            stopIDs[i++] = temp->stopID;
            temp = temp->next;
        }

        return stopIDs;
    }

    // Copy route from another RouteList
    // Time Complexity: O(n)
    void copyFrom(const RouteList* other) {
        if (other == nullptr) return;

        clear();

        if (other->isEmpty()) return;

        RouteStopNode* temp = other->head;
        while (temp != nullptr) {
            addStop(temp->stopID, temp->stopName, temp->stopPtr);
            temp = temp->next;
        }
    }

    // Clear entire route
    // Time Complexity: O(n)
    void clear() {
        RouteStopNode* current = head;
        while (current != nullptr) {
            RouteStopNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        stopCount = 0;
    }

    // ==================== DISPLAY OPERATIONS ====================

    // Display route
    // Time Complexity: O(n)
    void displayRoute() const {
        if (head == nullptr) {
            cout << "Route is empty." << endl;
            return;
        }

        cout << "Route: ";
        RouteStopNode* temp = head;

        while (temp != nullptr) {
            cout << temp->stopName << " (" << temp->stopID << ")";
            if (temp->next != nullptr) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
        cout << "Total stops: " << stopCount << endl;
    }

    // Display route with numbers
    // Time Complexity: O(n)
    void displayRouteNumbered() const {
        if (head == nullptr) {
            cout << "Route is empty." << endl;
            return;
        }

        cout << "Route Details:" << endl;
        RouteStopNode* temp = head;
        int count = 1;

        while (temp != nullptr) {
            cout << count << ". " << temp->stopName << " (ID: " << temp->stopID << ")";
            if (temp->next != nullptr) {
                cout << " ->";
            }
            cout << endl;
            temp = temp->next;
            count++;
        }
        cout << "Total stops: " << stopCount << endl;
    }

    // Get head for iteration (advanced use)
    RouteStopNode* getHead() const {
        return head;
    }
};

// ==================== PASSENGER ====================
/*
 * Purpose: Represents a passenger waiting at a stop
 *
 * Data Structure: Simple entity class
 */
struct Passenger {
    string name;
    string destination;
    int ticketNumber;
    string passengerID;  // Added for better tracking

    Passenger(string pName, string dest, int ticket, string pID = "") {
        name = pName.empty() ? "Unknown Passenger" : pName;
        destination = dest;
        ticketNumber = ticket;
        passengerID = pID.empty() ? ("P" + to_string(ticket)) : pID;
    }

    void display() const {
        cout << "Passenger: " << name << " (ID: " << passengerID << ")"
            << " | Destination: " << destination
            << " | Ticket #" << ticketNumber << endl;
    }
};


class PassengerQueue {
private:
    Passenger** queue;
    int front, rear, size, capacity;

public:
    // Constructor
    // Time Complexity: O(n) for initialization
    PassengerQueue(int cap = 100) {
        if (cap <= 0) {
            cout << "Warning: Invalid capacity! Setting to 100." << endl;
            cap = 100;
        }

        capacity = cap;
        queue = new Passenger * [capacity];
        for (int i = 0; i < capacity; i++) {
            queue[i] = nullptr;
        }
        front = -1;
        rear = -1;
        size = 0;
    }

    // Destructor
    // Time Complexity: O(1)
    // Note: We don't delete passengers - caller owns them
    ~PassengerQueue() {
        delete[] queue;
    }

    // ==================== QUEUE OPERATIONS ====================

    // Check if empty
    // Time Complexity: O(1)
    bool isEmpty() const { return size == 0; }

    // Check if full
    // Time Complexity: O(1)
    bool isFull() const { return size == capacity; }

    // Get size
    // Time Complexity: O(1)
    int getSize() const { return size; }

    // Get capacity
    // Time Complexity: O(1)
    int getCapacity() const { return capacity; }

    // Enqueue passenger
    // Time Complexity: O(1)
    // Edge Cases: Null pointer, queue full
    bool enqueue(Passenger* p) {
        if (p == nullptr) {
            cout << "Error: Cannot enqueue null passenger!" << endl;
            return false;
        }

        if (isFull()) {
            cout << "Queue full! Cannot add more passengers." << endl;
            return false;
        }

        if (front == -1) {
            front = 0;
        }

        rear = (rear + 1) % capacity;
        queue[rear] = p;
        size++;

        cout << "Passenger " << p->name << " added to queue (Ticket #"
            << p->ticketNumber << ")" << endl;
        return true;
    }

    // Add passenger directly (creates Passenger object)
    // Time Complexity: O(1)
    bool addPassenger(string name, string destination, int ticketNumber) {
        if (isFull()) {
            cout << "Queue full! Cannot add more passengers." << endl;
            return false;
        }

        Passenger* newPassenger = new Passenger(name, destination, ticketNumber);
        return enqueue(newPassenger);
    }

    // Dequeue passenger
    // Time Complexity: O(1)
    // Edge Cases: Empty queue, circular wrapping
    Passenger* dequeue() {
        if (isEmpty()) {
            cout << "Queue empty! No passengers to dequeue." << endl;
            return nullptr;
        }

        Passenger* p = queue[front];
        queue[front] = nullptr;

        if (front == rear) {
            // Last element
            front = rear = -1;
        }
        else {
            front = (front + 1) % capacity;
        }
        size--;
        return p;
    }

    // Remove passenger (wrapper for dequeue)
    // Time Complexity: O(1)
    Passenger* removePassenger() {
        return dequeue();
    }

    // Peek at front passenger
    // Time Complexity: O(1)
    Passenger* peek() const {
        if (isEmpty()) return nullptr;
        return queue[front];
    }

    // Peek at next passenger (alias for peek)
    // Time Complexity: O(1)
    Passenger* peekNext() const {
        return peek();
    }

    // ==================== DISPLAY OPERATIONS ====================

    // Display all passengers
    // Time Complexity: O(n)
    void displayQueue() const {
        if (isEmpty()) {
            cout << "Passenger queue is empty." << endl;
            return;
        }

        cout << "\n========== PASSENGER QUEUE ==========" << endl;
        cout << "Total passengers waiting: " << size << endl;
        cout << "=====================================" << endl;

        int i = front;
        int count = 0;
        while (count < size) {
            if (queue[i] != nullptr) {
                cout << (count + 1) << ". ";
                queue[i]->display();
            }
            i = (i + 1) % capacity;
            count++;
        }
    }

    // Clear queue
    // Time Complexity: O(n)
    void clear() {
        // Delete all passenger objects
        int i = front;
        int count = 0;
        while (count < size) {
            if (queue[i] != nullptr) {
                delete queue[i];
                queue[i] = nullptr;
            }
            i = (i + 1) % capacity;
            count++;
        }

        front = rear = -1;
        size = 0;
    }
};

// ==================== ROUTE HISTORY NODE ====================
/*
 * Purpose: Node for route history stack
 */
struct RouteHistoryNode {
    string stopID;
    string stopName;
    double timestamp;  // Can be enhanced with actual time tracking

    RouteHistoryNode(string id, string name, double time = 0.0) {
        stopID = id;
        stopName = name;
        timestamp = time;
    }
};

class RouteStack {
private:
    struct StackNode {
        RouteHistoryNode* data;
        StackNode* next;

        StackNode(RouteHistoryNode* routeData) {
            data = routeData;
            next = nullptr;
        }
    };

    StackNode* top;
    int size;
    int maxSize;  // Optional size limit

public:
    // Constructor
    // Time Complexity: O(1)
    RouteStack(int max = 1000) : top(nullptr), size(0), maxSize(max) {}

    // Destructor
    // Time Complexity: O(n)
    ~RouteStack() {
        while (!isEmpty()) {
            RouteHistoryNode* data = pop();
            delete data;
        }
    }

    // ==================== STACK OPERATIONS ====================

    // Check if empty
    // Time Complexity: O(1)
    bool isEmpty() const { return top == nullptr; }

    // Check if full
    // Time Complexity: O(1)
    bool isFull() const { return size >= maxSize; }

    // Get size
    // Time Complexity: O(1)
    int getSize() const { return size; }

    // Push route history
    // Time Complexity: O(1)
    // Edge Cases: Stack full, empty strings
    bool push(string stopID, string stopName, double timestamp = 0.0) {
        if (isFull()) {
            cout << "Route history stack full! Removing oldest entry..." << endl;
            // Could implement removal of bottom element here
            return false;
        }

        if (stopID.empty()) {
            cout << "Warning: Cannot push empty stop ID!" << endl;
            return false;
        }

        RouteHistoryNode* routeData = new RouteHistoryNode(stopID, stopName, timestamp);
        StackNode* newNode = new StackNode(routeData);
        newNode->next = top;
        top = newNode;
        size++;
        return true;
    }

    // Pop route history
    // Time Complexity: O(1)
    // Edge Cases: Empty stack
    RouteHistoryNode* pop() {
        if (isEmpty()) {
            cout << "Route history is empty!" << endl;
            return nullptr;
        }

        StackNode* temp = top;
        RouteHistoryNode* data = temp->data;
        top = top->next;
        delete temp;
        size--;
        return data;
    }

    // Peek at top
    // Time Complexity: O(1)
    RouteHistoryNode* peek() const {
        if (isEmpty()) return nullptr;
        return top->data;
    }

    // ==================== DISPLAY OPERATIONS ====================

    // Display route history
    // Time Complexity: O(n)
    void displayHistory() const {
        if (isEmpty()) {
            cout << "No route history available." << endl;
            return;
        }

        cout << "\n========== ROUTE HISTORY (Most Recent First) ==========" << endl;
        StackNode* current = top;
        int count = 1;

        while (current != nullptr) {
            cout << count << ". Stop ID: " << current->data->stopID
                << " | Name: " << current->data->stopName;
            if (current->data->timestamp > 0) {
                cout << " | Time: " << current->data->timestamp;
            }
            cout << endl;
            current = current->next;
            count++;
        }
        cout << "========================================================" << endl;
    }

    // Clear history
    // Time Complexity: O(n)
    void clear() {
        while (!isEmpty()) {
            RouteHistoryNode* data = pop();
            delete data;
        }
    }
};


class Bus {
private:
    string busNumber;
    int companyID;
    string companyName;
    string currentStopID;
    BusStop* currentStop;  // For real-time tracking
    int capacity;
    int currentPassengers;
    RouteList* route;  // Linked list of stops
    RouteStack* history;  // Stack for route history
    bool isActive;  // For real-time simulation
    bool isSchoolBus;  // BONUS: School bus tracking

public:
    // ==================== CONSTRUCTORS ====================

    // Default constructor
    Bus() {
        busNumber = "";
        companyID = 0;
        companyName = "";
        currentStopID = "";
        currentStop = nullptr;
        capacity = 50;
        currentPassengers = 0;
        route = new RouteList();
        history = new RouteStack();
        isActive = true;
        isSchoolBus = false;
    }

    // Parameterized constructor with validation
    // Time Complexity: O(1)
    Bus(string busNo, int compID, string compName, string stopID, int cap = 50, bool schoolBus = false) {
        // Validate bus number
        if (busNo.empty()) {
            cout << "Warning: Bus number cannot be empty! Setting to UNKNOWN." << endl;
            busNumber = "UNKNOWN";
        }
        else {
            busNumber = busNo;
        }

        // Validate company ID
        companyID = (compID < 0) ? 0 : compID;

        // Validate company name
        companyName = compName.empty() ? "Unknown Company" : compName;

        currentStopID = stopID;
        currentStop = nullptr;

        // Validate capacity (reasonable limits: 10-200)
        if (cap <= 0 || cap > 200) {
            cout << "Warning: Invalid capacity " << cap << "! Setting to 50." << endl;
            capacity = 50;
        }
        else {
            capacity = cap;
        }

        currentPassengers = 0;
        route = new RouteList();
        history = new RouteStack();
        isActive = true;
        isSchoolBus = schoolBus;
    }

    // Copy constructor - CRITICAL (Rule of Three)
    // Time Complexity: O(n) where n = number of stops in route
    Bus(const Bus& other) {
        busNumber = other.busNumber;
        companyID = other.companyID;
        companyName = other.companyName;
        currentStopID = other.currentStopID;
        currentStop = other.currentStop;  // Shallow copy OK - we don't own the stop
        capacity = other.capacity;
        currentPassengers = other.currentPassengers;
        isActive = other.isActive;
        isSchoolBus = other.isSchoolBus;

        // Deep copy route
        route = new RouteList(*other.route);

        // History not copied - new bus starts fresh
        history = new RouteStack();
    }

    // Assignment operator - CRITICAL (Rule of Three)
    // Time Complexity: O(n)
    Bus& operator=(const Bus& other) {
        if (this != &other) {
            // Clean up existing resources
            delete route;
            delete history;

            // Copy all fields
            busNumber = other.busNumber;
            companyID = other.companyID;
            companyName = other.companyName;
            currentStopID = other.currentStopID;
            currentStop = other.currentStop;
            capacity = other.capacity;
            currentPassengers = other.currentPassengers;
            isActive = other.isActive;
            isSchoolBus = other.isSchoolBus;

            // Deep copy route
            route = new RouteList(*other.route);
            history = new RouteStack();
        }
        return *this;
    }

    // Destructor
    // Time Complexity: O(n)
    ~Bus() {
        delete route;
        delete history;
    }

    // ==================== GETTERS (const-correct) ====================

    string getBusNumber() const { return busNumber; }
    int getCompanyID() const { return companyID; }
    string getCompanyName() const { return companyName; }
    string getCurrentStopID() const { return currentStopID; }
    BusStop* getCurrentStop() const { return currentStop; }
    int getCapacity() const { return capacity; }
    int getCurrentPassengers() const { return currentPassengers; }
    int getAvailableSeats() const { return capacity - currentPassengers; }
    RouteList* getRoute() { return route; }
    RouteStack* getHistory() { return history; }
    bool getIsActive() const { return isActive; }
    bool isSchool() const { return isSchoolBus; }

    // ==================== SETTERS WITH VALIDATION ====================

    void setCurrentStopID(string stopID) {
        if (route == nullptr) {
            cout << "Error: No route defined!" << endl;
            return;
        }

        if (route->hasStop(stopID)) {
            currentStopID = stopID;
            currentStop = route->getStopPointer(stopID);
        }
        else {
            cout << "Error: Stop " << stopID << " not in bus route!" << endl;
        }
    }

    void setCurrentStop(BusStop* stop) {
        if (stop != nullptr) {
            currentStop = stop;
            currentStopID = stop->getStopID();
        }
    }

    void setCompanyName(string name) {
        companyName = name.empty() ? "Unknown Company" : name;
    }

    void setActive(bool active) {
        isActive = active;
    }

    void setSchoolBus(bool schoolBus) {
        isSchoolBus = schoolBus;
    }

    // ==================== PASSENGER MANAGEMENT ====================

    // Add passengers with validation
    // Time Complexity: O(1)
    // Edge Cases: Negative count, overflow, capacity exceeded
    bool addPassengers(int count) {
        if (count < 0) {
            cout << "Error: Cannot add negative passengers!" << endl;
            return false;
        }
        if (count == 0) return true;

        // Check overflow
        if (currentPassengers > INT_MAX - count) {
            cout << "Error: Passenger count overflow!" << endl;
            return false;
        }

        if (currentPassengers + count <= capacity) {
            currentPassengers += count;
            cout << count << " passenger(s) boarded. Available seats: "
                << getAvailableSeats() << endl;
            return true;
        }

        cout << "Not enough seats! Requested: " << count
            << " | Available: " << getAvailableSeats() << endl;
        return false;
    }

    // Remove passengers with validation
    // Time Complexity: O(1)
    // Edge Cases: Negative count, more than current passengers
    bool removePassengers(int count) {
        if (count < 0) {
            cout << "Error: Cannot remove negative passengers!" << endl;
            return false;
        }
        if (count == 0) return true;

        if (currentPassengers >= count) {
            currentPassengers -= count;
            cout << count << " passenger(s) deboarded. Current passengers: "
                << currentPassengers << endl;
            return true;
        }

        cout << "Error: Only " << currentPassengers << " passengers on bus!" << endl;
        return false;
    }

    // ==================== ROUTE MANAGEMENT ====================

    // Add stop to route with validation
    // Time Complexity: O(n)
    void addStopToRoute(string stopID, string stopName, BusStop* stopPtr = nullptr) {
        if (route == nullptr) {
            cout << "Error: Route not initialized!" << endl;
            return;
        }
        route->addStop(stopID, stopName, stopPtr);
    }

    // Display route
    // Time Complexity: O(n)
    void displayRoute() const {
        if (route == nullptr) {
            cout << "No route available!" << endl;
            return;
        }

        cout << "\n=== Route for Bus " << busNumber;
        if (isSchoolBus) cout << " (SCHOOL BUS)";
        cout << " ===" << endl;

        route->displayRoute();
        cout << "Total stops: " << route->getStopCount() << endl;
    }

    // Get next stop in route
    // Time Complexity: O(n)
    string getNextStop() const {
        if (route == nullptr) return "";
        return route->getNextStop(currentStopID);
    }

    // Get previous stop in route
    // Time Complexity: O(n)
    string getPreviousStop() const {
        if (route == nullptr) return "";
        return route->getPreviousStop(currentStopID);
    }

    // Check if bus serves a specific stop
    // Time Complexity: O(n)
    bool servesStop(string stopID) const {
        if (route == nullptr) return false;
        return route->hasStop(stopID);
    }

    // ==================== REAL-TIME TRACKING ====================

    // Move bus to next stop (BONUS: Real-time simulation)
    // Time Complexity: O(n)
    bool moveToNextStop() {
        if (!isActive) {
            cout << "Bus " << busNumber << " is not active!" << endl;
            return false;
        }

        if (route == nullptr || route->isEmpty()) {
            cout << "Bus " << busNumber << " has no route!" << endl;
            return false;
        }

        // Record current stop in history
        if (!currentStopID.empty() && history != nullptr) {
            history->push(currentStopID,
                currentStop ? currentStop->getName() : "Unknown");
        }

        string nextStopID = getNextStop();
        if (nextStopID.empty() || nextStopID == "END_OF_ROUTE") {
            cout << "Bus " << busNumber << " has reached end of route!" << endl;
            return false;
        }

        // Update current location
        currentStopID = nextStopID;
        currentStop = route->getStopPointer(nextStopID);

        cout << "Bus " << busNumber << " -> " << currentStopID;
        if (currentStop != nullptr) {
            cout << " (" << currentStop->getName() << ")";
        }
        cout << endl;

        return true;
    }

    // Move bus to previous stop (for backtracking)
    // Time Complexity: O(n)
    bool moveToPreviousStop() {
        if (!isActive) {
            cout << "Bus " << busNumber << " is not active!" << endl;
            return false;
        }

        string prevStopID = getPreviousStop();
        if (prevStopID.empty() || prevStopID == "START_OF_ROUTE") {
            cout << "Bus " << busNumber << " is at start of route!" << endl;
            return false;
        }

        if (history != nullptr) {
            history->push(currentStopID,
                currentStop ? currentStop->getName() : "Unknown");
        }

        currentStopID = prevStopID;
        currentStop = route->getStopPointer(prevStopID);

        cout << "Bus " << busNumber << " <- " << currentStopID << endl;
        return true;
    }

    // Reset bus to start of route
    // Time Complexity: O(1)
    void resetToStartOfRoute() {
        if (route == nullptr || route->isEmpty()) {
            cout << "Cannot reset: No route defined!" << endl;
            return;
        }

        currentStopID = route->getFirstStop();
        currentStop = route->getStopPointer(currentStopID);
        currentPassengers = 0;

        if (history != nullptr) {
            history->clear();
        }

        cout << "Bus " << busNumber << " reset to start: " << currentStopID << endl;
    }

    // ==================== DISTANCE CALCULATIONS ====================

    // Calculate distance to a given location
    // Time Complexity: O(1)
    // Required for "Search nearest bus to passenger location"
    double distanceToLocation(double lat, double lon) const {
        if (currentStop == nullptr) {
            cout << "Warning: Bus has no current stop location!" << endl;
            return 999999.0;
        }

        return currentStop->distanceToPoint(lat, lon);
    }

    // Calculate distance to another bus
    // Time Complexity: O(1)
    double distanceToBus(const Bus* other) const {
        if (other == nullptr || currentStop == nullptr || other->currentStop == nullptr) {
            return 999999.0;
        }

        return currentStop->distanceTo(other->currentStop);
    }

    // Get current coordinates
    // Time Complexity: O(1)
    void getCurrentCoordinates(double& lat, double& lon) const {
        if (currentStop != nullptr) {
            lat = currentStop->getLatitude();
            lon = currentStop->getLongitude();
        }
        else {
            lat = lon = 0.0;
        }
    }

    // ==================== ROUTE HISTORY ====================

    void displayHistory() const {
        cout << "\n=== History for Bus " << busNumber << " ===" << endl;
        if (history != nullptr) {
            history->displayHistory();
        }
        else {
            cout << "No history available." << endl;
        }
    }

    void clearHistory() {
        if (history != nullptr) {
            history->clear();
        }
    }

    // ==================== DISPLAY ====================

    void display() const {
        cout << "\n+=======================================+" << endl;
        cout << "|        BUS INFORMATION                |" << endl;
        cout << "+=======================================+" << endl;
        cout << "  Bus Number:       " << busNumber;
        if (isSchoolBus) cout << " [SCHOOL BUS]";
        cout << endl;
        cout << "  Company:          " << companyName << " (ID: " << companyID << ")" << endl;
        cout << "  Current Stop:     " << currentStopID;
        if (currentStop != nullptr) {
            cout << " (" << currentStop->getName() << ")";
        }
        cout << endl;
        cout << "  Status:           " << (isActive ? "Active" : "Inactive") << endl;
        cout << "  Passengers:       " << currentPassengers << "/" << capacity << endl;
        cout << "  Available Seats:  " << getAvailableSeats() << endl;
        cout << "  Route Stops:      " << (route ? route->getStopCount() : 0) << endl;
        cout << "+=======================================+" << endl;
    }

    // Compact display for lists
    void displayCompact() const {
        cout << busNumber;
        if (isSchoolBus) cout << " [SCHOOL]";
        cout << " | " << companyName << " | Stop: " << currentStopID
            << " | Seats: " << getAvailableSeats() << "/" << capacity << endl;
    }
};


