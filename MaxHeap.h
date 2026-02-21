#pragma once
// File: DataStructures/MaxHeap.h
#include <iostream>
#include <string>
using namespace std;


class MaxHeap {
protected:
    struct HeapNode {
        void* data;           // Generic pointer to ANY object
        int priority;         // The value to compare (higher = higher priority)

        HeapNode() {
            data = nullptr;
            priority = 0;
        }
    };

    HeapNode* heap;           // Array-based heap
    int heapSize;
    int capacity;

    // Helper functions
    int parent(int i);        // O(1)
    int leftChild(int i);     // O(1)
    int rightChild(int i);    // O(1)
    void heapifyUp(int i);    // O(log n)
    void heapifyDown(int i);  // O(log n)
    void swap(int i, int j);  // O(1)

public:
    MaxHeap(int capacity = 100);
    virtual ~MaxHeap();

    // Heap operations
    void insert(void* data, int priority);     // O(log n)
    void* extractMax();                        // O(log n)
    void* peekMax();                           // O(1)
    int findIndex(void* data);                 // O(n)
    void updatePriority(void* data, int newPriority); // O(n + log n)

    // Status
    bool isEmpty();                            // O(1)
    bool isFull();                             // O(1)
    int size();                                // O(1)

    // Display (for debugging)
    void display() const;
};



MaxHeap::MaxHeap(int cap) {
    capacity = cap;
    heapSize = 0;
    heap = new HeapNode[capacity];
}

MaxHeap::~MaxHeap() {
    delete[] heap;
    // Note: Does NOT delete the data pointers - we don't own them!
}

int MaxHeap::parent(int i) {
    return (i - 1) / 2;
}

int MaxHeap::leftChild(int i) {
    return 2 * i + 1;
}

int MaxHeap::rightChild(int i) {
    return 2 * i + 2;
}

void MaxHeap::swap(int i, int j) {
    HeapNode temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// O(log n) - Bubble up to maintain max-heap property
void MaxHeap::heapifyUp(int i) {
    while (i > 0) {
        int p = parent(i);

        // MAX-HEAP: Parent must be >= child
        if (heap[i].priority > heap[p].priority) {
            swap(i, p);
            i = p;
        }
        else {
            break;
        }
    }
}

// O(log n) - Bubble down to maintain max-heap property
void MaxHeap::heapifyDown(int i) {
    int maxIndex = i;
    int left = leftChild(i);
    int right = rightChild(i);

    // Find largest among node and its children
    if (left < heapSize && heap[left].priority > heap[maxIndex].priority) {
        maxIndex = left;
    }

    if (right < heapSize && heap[right].priority > heap[maxIndex].priority) {
        maxIndex = right;
    }

    // If largest is not the current node, swap and continue
    if (maxIndex != i) {
        swap(i, maxIndex);
        heapifyDown(maxIndex);
    }
}

// O(log n)
void MaxHeap::insert(void* data, int priority) {
    if (heapSize >= capacity) {
        return;  // Heap full
    }

    // Add at end
    heap[heapSize].data = data;
    heap[heapSize].priority = priority;

    // Heapify up
    heapifyUp(heapSize);
    heapSize++;
}

// O(log n)
void* MaxHeap::extractMax() {
    if (heapSize == 0) {
        return nullptr;  // Heap empty
    }

    void* maxData = heap[0].data;

    // Move last element to root
    heap[0] = heap[heapSize - 1];
    heapSize--;

    // Heapify down from root
    if (heapSize > 0) {
        heapifyDown(0);
    }

    return maxData;
}

// O(1)
void* MaxHeap::peekMax() {
    if (heapSize == 0) {
        return nullptr;
    }
    return heap[0].data;
}

// O(n) - Linear search
int MaxHeap::findIndex(void* data) {
    for (int i = 0; i < heapSize; i++) {
        if (heap[i].data == data) {
            return i;
        }
    }
    return -1;
}

// O(n + log n)
void MaxHeap::updatePriority(void* data, int newPriority) {
    int index = findIndex(data);

    if (index == -1) {
        return;  // Not found
    }

    int oldPriority = heap[index].priority;
    heap[index].priority = newPriority;

    // Determine which direction to heapify
    if (newPriority > oldPriority) {
        heapifyUp(index);      // Priority increased
    }
    else if (newPriority < oldPriority) {
        heapifyDown(index);    // Priority decreased
    }
}

bool MaxHeap::isEmpty() {
    return heapSize == 0;
}

bool MaxHeap::isFull() {
    return heapSize >= capacity;
}

int MaxHeap::size() {
    return heapSize;
}

void MaxHeap::display() const {
    cout << "MaxHeap (size=" << heapSize << "):" << endl;
    for (int i = 0; i < heapSize; i++) {
        cout << "  [" << i << "] priority=" << heap[i].priority << endl;
    }
}
