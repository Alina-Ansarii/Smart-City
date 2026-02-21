#pragma once
#include <iostream>
using namespace std;



// ==================== GENERIC SINGLY LINKED LIST ====================
// Generic Node for any data type using void pointers
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T d) : data(d), next(NULL) {}
};

// Generic Singly Linked List - Based on LQS.h LinkedList pattern
template <typename T>
class SinglyLinkedList {
public:

    Node<T>* head;
    int length;

    SinglyLinkedList() {
        head = NULL;
        length = 0;
    }

    ~SinglyLinkedList() {
        clear();
    }

    // Insert at front - O(1)
    void insertFront(T data) {
        Node<T>* n = new Node<T>(data);
        n->next = head;
        head = n;
        length++;
    }

    // Insert at end - O(n)
    void insertEnd(T data) {
        Node<T>* n = new Node<T>(data);
        if (head == NULL) {
            head = n;
            length++;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
        length++;
    }

    // Insert (alias for insertFront) - O(1)
    void insert(T data) {
        insertFront(data);
    }

    // Search for element - O(n)
    Node<T>* search(T data) {
        Node<T>* temp = head;
        while (temp != NULL) {
            if (temp->data == data)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    // Check if list contains element - O(n)
    bool contains(T data) {
        return search(data) != NULL;
    }

    // Remove specific element - O(n)
    bool remove(T data) {
        if (head == NULL)
            return false;

        if (head->data == data) {
            Node<T>* del = head;
            head = head->next;
            delete del;
            length--;
            return true;
        }

        Node<T>* temp = head;
        while (temp->next != NULL && temp->next->data != data)
            temp = temp->next;

        if (temp->next == NULL)
            return false;

        Node<T>* del = temp->next;
        temp->next = del->next;
        delete del;
        length--;
        return true;
    }

    // Get head node
    Node<T>* getHead() {
        return head;
    }

    // Get length - O(1)
    int getLength() const {
        return length;
    }

    // Check if empty - O(1)
    bool isEmpty() const {
        return head == NULL;
    }

    // Clear entire list - O(n)
    void clear() {
        while (head != NULL) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        length = 0;
    }

    // Display list contents - O(n)
    void display() {
        Node<T>* temp = head;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};











// ==================== SINGLY LINKED LIST ====================
struct ListNode {
    int key;
    ListNode* next;
    ListNode(int k) {
        key = k;
        next = NULL;
    }
};

class LinkedList {
private:
    ListNode* head;
    int length;
public:
    LinkedList() {
        head = NULL;
        length = 0;
    }

    ~LinkedList() {
        clear();
    }

    void insertFront(int key) {
        ListNode* n = new ListNode(key);
        n->next = head;
        head = n;
        length++;
    }

    void insertEnd(int key) {
        ListNode* n = new ListNode(key);
        if (head == NULL) {
            head = n;
            length++;
            return;
        }
        ListNode* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
        length++;
    }

    void insertAt(int key, int position) {
        if (position < 0 || position > length) return;
        if (position == 0) {
            insertFront(key);
            return;
        }
        ListNode* n = new ListNode(key);
        ListNode* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;
        n->next = temp->next;
        temp->next = n;
        length++;
    }

    bool search(int key) {
        ListNode* temp = head;
        while (temp != NULL) {
            if (temp->key == key) return true;
            temp = temp->next;
        }
        return false;
    }

    bool remove(int key) {
        if (head == NULL) return false;
        if (head->key == key) {
            ListNode* del = head;
            head = head->next;
            delete del;
            length--;
            return true;
        }
        ListNode* temp = head;
        while (temp->next != NULL && temp->next->key != key)
            temp = temp->next;
        if (temp->next == NULL) return false;
        ListNode* del = temp->next;
        temp->next = del->next;
        delete del;
        length--;
        return true;
    }

    bool removeAt(int position) {
        if (position < 0 || position >= length || head == NULL) return false;
        if (position == 0) {
            ListNode* del = head;
            head = head->next;
            delete del;
            length--;
            return true;
        }
        ListNode* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;
        ListNode* del = temp->next;
        temp->next = del->next;
        delete del;
        length--;
        return true;
    }

    void reverse() {
        ListNode* prev = NULL;
        ListNode* current = head;
        ListNode* next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    int getLength() { return length; }

    bool isEmpty() { return head == NULL; }

    void clear() {
        while (head != NULL) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        length = 0;
    }

    void display() {
        ListNode* temp = head;
        while (temp != NULL) {
            cout << temp->key << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    ListNode* getHead() { return head; }
};

// ==================== DOUBLY LINKED LIST ====================
struct DListNode {
    int key;
    DListNode* next;
    DListNode* prev;
    DListNode(int k) {
        key = k;
        next = NULL;
        prev = NULL;
    }
};

class DoublyLinkedList {
private:
    DListNode* head;
    DListNode* tail;
    int length;
public:
    DoublyLinkedList() {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    ~DoublyLinkedList() {
        clear();
    }

    void insertFront(int key) {
        DListNode* n = new DListNode(key);
        if (head == NULL) {
            head = tail = n;
        }
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        length++;
    }

    void insertEnd(int key) {
        DListNode* n = new DListNode(key);
        if (tail == NULL) {
            head = tail = n;
        }
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        length++;
    }

    void insertAt(int key, int position) {
        if (position < 0 || position > length) return;
        if (position == 0) {
            insertFront(key);
            return;
        }
        if (position == length) {
            insertEnd(key);
            return;
        }
        DListNode* n = new DListNode(key);
        DListNode* temp = head;
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;
        n->next = temp->next;
        n->prev = temp;
        temp->next->prev = n;
        temp->next = n;
        length++;
    }

    bool search(int key) {
        DListNode* temp = head;
        while (temp != NULL) {
            if (temp->key == key) return true;
            temp = temp->next;
        }
        return false;
    }

    bool remove(int key) {
        if (head == NULL) return false;
        DListNode* temp = head;
        while (temp != NULL && temp->key != key)
            temp = temp->next;
        if (temp == NULL) return false;

        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
        length--;
        return true;
    }

    bool removeAt(int position) {
        if (position < 0 || position >= length || head == NULL) return false;
        DListNode* temp = head;
        for (int i = 0; i < position; i++)
            temp = temp->next;

        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
        length--;
        return true;
    }

    void reverse() {
        DListNode* temp = NULL;
        DListNode* current = head;
        tail = head;
        while (current != NULL) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != NULL)
            head = temp->prev;
    }

    int getLength() { return length; }

    bool isEmpty() { return head == NULL; }

    void clear() {
        while (head != NULL) {
            DListNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;
        length = 0;
    }

    void displayForward() {
        DListNode* temp = head;
        while (temp != NULL) {
            cout << temp->key << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    void displayBackward() {
        DListNode* temp = tail;
        while (temp != NULL) {
            cout << temp->key << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }

    DListNode* getHead() { return head; }
    DListNode* getTail() { return tail; }
};

// ==================== CIRCULAR LINKED LIST ====================
class CircularLinkedList {
private:
    ListNode* tail;
    int length;
public:
    CircularLinkedList() {
        tail = NULL;
        length = 0;
    }

    ~CircularLinkedList() {
        clear();
    }

    void insertFront(int key) {
        ListNode* n = new ListNode(key);
        if (tail == NULL) {
            tail = n;
            n->next = n;
        }
        else {
            n->next = tail->next;
            tail->next = n;
        }
        length++;
    }

    void insertEnd(int key) {
        ListNode* n = new ListNode(key);
        if (tail == NULL) {
            tail = n;
            n->next = n;
        }
        else {
            n->next = tail->next;
            tail->next = n;
            tail = n;
        }
        length++;
    }

    bool search(int key) {
        if (tail == NULL) return false;
        ListNode* temp = tail->next;
        do {
            if (temp->key == key) return true;
            temp = temp->next;
        } while (temp != tail->next);
        return false;
    }

    bool remove(int key) {
        if (tail == NULL) return false;
        ListNode* current = tail->next;
        ListNode* prev = tail;

        do {
            if (current->key == key) {
                if (current == tail->next && current == tail) {
                    delete current;
                    tail = NULL;
                }
                else {
                    prev->next = current->next;
                    if (current == tail)
                        tail = prev;
                    delete current;
                }
                length--;
                return true;
            }
            prev = current;
            current = current->next;
        } while (current != tail->next);

        return false;
    }

    int getLength() { return length; }

    bool isEmpty() { return tail == NULL; }

    void clear() {
        if (tail == NULL) return;
        ListNode* current = tail->next;
        while (current != tail) {
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete tail;
        tail = NULL;
        length = 0;
    }

    void display() {
        if (tail == NULL) {
            cout << "Empty\n";
            return;
        }
        ListNode* temp = tail->next;
        do {
            cout << temp->key << " -> ";
            temp = temp->next;
        } while (temp != tail->next);
        cout << "(back to " << tail->next->key << ")\n";
    }

    ListNode* getTail() { return tail; }
};

// ==================== QUEUE ====================
class Queue {
private:
    int* arr;
    int front, rear, size, capacity;
public:
    Queue(int cap) {
        capacity = cap;
        arr = new int[cap];
        front = 0;
        size = 0;
        rear = cap - 1;
    }

    ~Queue() {
        delete[] arr;
    }

    bool isEmpty() { return size == 0; }

    bool isFull() { return size == capacity; }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        int val = arr[front];
        front = (front + 1) % capacity;
        size--;
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    int getSize() { return size; }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        int i = front;
        for (int count = 0; count < size; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

// ==================== CIRCULAR QUEUE ====================
class CircularQueue {
private:
    int* arr;
    int front, rear, size, capacity;
public:
    CircularQueue(int cap) {
        capacity = cap;
        arr = new int[cap];
        front = -1;
        rear = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() { return size == 0; }

    bool isFull() { return size == capacity; }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Circular Queue Overflow\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Circular Queue Underflow\n";
            return -1;
        }
        int val = arr[front];
        if (front == rear) {
            front = rear = -1;
        }
        else {
            front = (front + 1) % capacity;
        }
        size--;
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    int getSize() { return size; }

    void display() {
        if (isEmpty()) {
            cout << "Circular Queue is empty\n";
            return;
        }
        int i = front;
        for (int count = 0; count < size; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

// ==================== STACK ====================
class Stack {
private:
    int* arr;
    int top;
    int capacity;
public:
    Stack(int size) {
        capacity = size;
        arr = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isEmpty() { return top == -1; }

    bool isFull() { return top == capacity - 1; }

    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (isEmpty()) return -1;
        return arr[top];
    }

    int getSize() { return top + 1; }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

//// ==================== PRIORITY QUEUE (Min Heap) ====================
//class PriorityQueue {
//private:
//    int* arr;
//    int size;
//    int capacity;
//
//    void heapifyUp(int index) {
//        while (index > 0) {
//            int parent = (index - 1) / 2;
//            if (arr[index] < arr[parent]) {
//                swap(arr[index], arr[parent]);
//                index = parent;
//            }
//            else {
//                break;
//            }
//        }
//    }
//
//    void heapifyDown(int index) {
//        while (true) {
//            int smallest = index;
//            int left = 2 * index + 1;
//            int right = 2 * index + 2;
//
//            if (left < size && arr[left] < arr[smallest])
//                smallest = left;
//            if (right < size && arr[right] < arr[smallest])
//                smallest = right;
//
//            if (smallest != index) {
//                swap(arr[index], arr[smallest]);
//                index = smallest;
//            }
//            else {
//                break;
//            }
//        }
//    }
//
//public:
//    PriorityQueue(int cap) {
//        capacity = cap;
//        arr = new int[cap];
//        size = 0;
//    }
//
//    ~PriorityQueue() {
//        delete[] arr;
//    }
//
//    bool isEmpty() { return size == 0; }
//
//    bool isFull() { return size == capacity; }
//
//    void insert(int value) {
//        if (isFull()) {
//            cout << "Priority Queue Overflow\n";
//            return;
//        }
//        arr[size] = value;
//        heapifyUp(size);
//        size++;
//    }
//
//    int extractMin() {
//        if (isEmpty()) {
//            cout << "Priority Queue Underflow\n";
//            return -1;
//        }
//        int minVal = arr[0];
//        arr[0] = arr[size - 1];
//        size--;
//        heapifyDown(0);
//        return minVal;
//    }
//
//    int getMin() {
//        if (isEmpty()) return -1;
//        return arr[0];
//    }
//
//    int getSize() { return size; }
//
//    void display() {
//        if (isEmpty()) {
//            cout << "Priority Queue is empty\n";
//            return;
//        }
//        for (int i = 0; i < size; i++)
//            cout << arr[i] << " ";
//        cout << endl;
//    }
//};
