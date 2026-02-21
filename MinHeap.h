#pragma once
#pragma once
#include <iostream>
using namespace std;

// ==================== MIN HEAP (INTEGER) ====================
// Binary min-heap for integer values
// Used for: Basic priority queue operations, emergency bed availability
class MinHeap {
private:
    int* arr;
    int size;
    int capacity;

    // Heapify up to maintain min-heap property - O(log n)
    void heapifyUp(int i) {
        while (i != 0) {
            int parent = (i - 1) / 2;
            if (arr[parent] > arr[i]) {
                // Swap with parent
                int temp = arr[parent];
                arr[parent] = arr[i];
                arr[i] = temp;
                i = parent;
            }
            else {
                break;
            }
        }
    }

    // Heapify down to maintain min-heap property - O(log n)
    void heapifyDown(int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && arr[left] < arr[smallest])
                smallest = left;
            if (right < size && arr[right] < arr[smallest])
                smallest = right;

            if (smallest != i) {
                int temp = arr[i];
                arr[i] = arr[smallest];
                arr[smallest] = temp;
                i = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    // Constructor
    MinHeap(int cap) {
        capacity = cap;
        arr = new int[cap];
        size = 0;
    }

    // Destructor
    ~MinHeap() {
        delete[] arr;
    }

    // Check if heap is empty - O(1)
    bool isEmpty() {
        return size == 0;
    }

    // Check if heap is full - O(1)
    bool isFull() {
        return size == capacity;
    }

    // Get current size - O(1)
    int getSize() {
        return size;
    }

    // Insert element into heap - O(log n)
    void insert(int value) {
        if (isFull()) {
            cout << "Heap Overflow" << endl;
            return;
        }
        arr[size] = value;
        heapifyUp(size);
        size++;
    }

    // Get minimum element without removing - O(1)
    int getMin() {
        if (isEmpty()) {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return arr[0];
    }

    // Extract minimum element - O(log n)
    int extractMin() {
        if (isEmpty()) {
            cout << "Heap Underflow" << endl;
            return -1;
        }
        int root = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return root;
    }

    // Decrease key value at index - O(log n)
    void decreaseKey(int index, int newValue) {
        if (index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return;
        }
        if (newValue > arr[index]) {
            cout << "New value is greater than current value" << endl;
            return;
        }
        arr[index] = newValue;
        heapifyUp(index);
    }

    // Delete element at index - O(log n)
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return;
        }
        decreaseKey(index, arr[0] - 1);
        extractMin();
    }

    // Display heap elements - O(n)
    void display() {
        if (isEmpty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        cout << "Heap elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Build heap from array - O(n)
    void buildHeap(int* array, int n) {
        if (n > capacity) {
            cout << "Array size exceeds heap capacity" << endl;
            return;
        }
        size = n;
        for (int i = 0; i < n; i++) {
            arr[i] = array[i];
        }
        // Heapify from last non-leaf node to root
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Clear heap - O(1)
    void clear() {
        size = 0;
    }
};

// ==================== PRIORITY QUEUE NODE ====================
// Node structure for priority queue with generic data
struct PQNode {
    int priority;          // Priority value (lower = higher priority)
    void* data;           // Generic pointer to any object

    PQNode() {
        priority = 0;
        data = nullptr;
    }

    PQNode(int p, void* d) {
        priority = p;
        data = d;
    }
};

// ==================== PRIORITY QUEUE (GENERIC) ====================
// Min-heap based priority queue for generic objects
// Used for: Hospital ranking, nearest facility queries, emergency routing
class PriorityQueue {
private:
    PQNode* arr;
    int size;
    int capacity;

    // Heapify up - O(log n)
    void heapifyUp(int i) {
        while (i != 0) {
            int parent = (i - 1) / 2;
            if (arr[parent].priority > arr[i].priority) {
                // Swap with parent
                PQNode temp = arr[parent];
                arr[parent] = arr[i];
                arr[i] = temp;
                i = parent;
            }
            else {
                break;
            }
        }
    }

    // Heapify down - O(log n)
    void heapifyDown(int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && arr[left].priority < arr[smallest].priority)
                smallest = left;
            if (right < size && arr[right].priority < arr[smallest].priority)
                smallest = right;

            if (smallest != i) {
                PQNode temp = arr[i];
                arr[i] = arr[smallest];
                arr[smallest] = temp;
                i = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    // Constructor
    PriorityQueue(int cap) {
        capacity = cap;
        arr = new PQNode[cap];
        size = 0;
    }

    // Destructor
    ~PriorityQueue() {
        delete[] arr;
    }

    // Check if empty - O(1)
    bool isEmpty() {
        return size == 0;
    }

    // Check if full - O(1)
    bool isFull() {
        return size == capacity;
    }

    // Get current size - O(1)
    int getSize() {
        return size;
    }

    // Insert element with priority - O(log n)
    void insert(int priority, void* data) {
        if (isFull()) {
            cout << "Priority Queue Overflow" << endl;
            return;
        }
        arr[size].priority = priority;
        arr[size].data = data;
        heapifyUp(size);
        size++;
    }

    // Get element with highest priority (minimum) - O(1)
    void* peek() {
        if (isEmpty()) {
            cout << "Priority Queue is empty" << endl;
            return nullptr;
        }
        return arr[0].data;
    }

    // Get priority of top element - O(1)
    int peekPriority() {
        if (isEmpty()) {
            cout << "Priority Queue is empty" << endl;
            return -1;
        }
        return arr[0].priority;
    }

    // Extract element with highest priority - O(log n)
    void* extractMin() {
        if (isEmpty()) {
            cout << "Priority Queue Underflow" << endl;
            return nullptr;
        }
        void* data = arr[0].data;
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return data;
    }

    // Extract with both data and priority - O(log n)
    bool extractMin(void** data, int* priority) {
        if (isEmpty()) {
            cout << "Priority Queue Underflow" << endl;
            return false;
        }
        *data = arr[0].data;
        *priority = arr[0].priority;
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return true;
    }

    // Change priority of element at index - O(log n)
    void changePriority(int index, int newPriority) {
        if (index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return;
        }
        int oldPriority = arr[index].priority;
        arr[index].priority = newPriority;

        if (newPriority < oldPriority) {
            heapifyUp(index);
        }
        else {
            heapifyDown(index);
        }
    }

    // Remove element at specific index - O(log n)
    void removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return;
        }
        arr[index] = arr[size - 1];
        size--;

        // Fix heap property
        int parent = (index - 1) / 2;
        if (index > 0 && arr[index].priority < arr[parent].priority) {
            heapifyUp(index);
        }
        else {
            heapifyDown(index);
        }
    }

    // Find index of element by data pointer - O(n)
    int findIndex(void* data) {
        for (int i = 0; i < size; i++) {
            if (arr[i].data == data) {
                return i;
            }
        }
        return -1;
    }

    // Update priority of specific data - O(n) for search + O(log n) for update
    bool updatePriority(void* data, int newPriority) {
        int index = findIndex(data);
        if (index == -1) {
            return false;
        }
        changePriority(index, newPriority);
        return true;
    }

    // Remove specific data - O(n) for search + O(log n) for removal
    bool remove(void* data) {
        int index = findIndex(data);
        if (index == -1) {
            return false;
        }
        removeAt(index);
        return true;
    }

    // Display all elements with priorities - O(n)
    void display() {
        if (isEmpty()) {
            cout << "Priority Queue is empty" << endl;
            return;
        }
        cout << "Priority Queue elements (priority, data):" << endl;
        for (int i = 0; i < size; i++) {
            cout << "(" << arr[i].priority << ", " << arr[i].data << ") ";
        }
        cout << endl;
    }

    // Clear queue - O(1)
    void clear() {
        size = 0;
    }

    // Check if contains element - O(n)
    bool contains(void* data) {
        return findIndex(data) != -1;
    }
};


