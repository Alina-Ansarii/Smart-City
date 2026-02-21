#pragma once
#pragma once
#pragma once
#pragma once
#include <iostream>
#include <string>
using namespace std;






inline int hashString(const string& str, int tableSize) {
    unsigned long long hash = 0;
    const unsigned long long p = 31;

    for (char c : str) {
        hash = (hash * p + (unsigned long long)c);
    }

    return hash % tableSize;  // final modulo
}


inline int hashString(const char* str, int tableSize) {
    unsigned long long hash = 0;
    const unsigned long long p = 31;

    while (*str) {
        hash = (hash * p + (unsigned long long)(*str));
        str++;
    }

    return hash % tableSize;
}




// ==================== HASH NODE ====================
// Node for separate chaining in hash table
struct HashNode {
    string key;
    void* value;           // Generic pointer to store any object
    HashNode* next;

    HashNode(string k, void* v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

// ==================== HASH TABLE CLASS ====================
// Hash table with separate chaining for collision resolution
// Uses polynomial rolling hash function
// Used for: Bus lookup, CNIC search, medicine search, doctor search, etc.
class HashTable {
private:
    HashNode** table;
    int capacity;
    int size;              // Number of elements currently in table

    // Polynomial Rolling Hash Function - O(k) where k is key length
    // Uses prime number 31 as multiplier
    int hashFunction(string key) {
        long long hash = 0;
        long long p = 31;          // Prime multiplier
        long long power = 1;

        for (int i = 0; key[i] != '\0'; i++) {
            // Convert character to number (handle both lowercase and uppercase)
            int charValue;
            if (key[i] >= 'a' && key[i] <= 'z') {
                charValue = key[i] - 'a' + 1;
            }
            else if (key[i] >= 'A' && key[i] <= 'Z') {
                charValue = key[i] - 'A' + 1;
            }
            else if (key[i] >= '0' && key[i] <= '9') {
                charValue = key[i] - '0' + 27;  // Numbers after letters
            }
            else {
                charValue = key[i];  // Special characters
            }

            hash = (hash + charValue * power) % capacity;
            power = (power * p) % capacity;
        }
        return (int)hash;
    }

public:
    // Constructor
    HashTable(int cap = 100) {
        capacity = cap;
        size = 0;
        table = new HashNode * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Destructor
    ~HashTable() {
        clear();
        delete[] table;
    }

    // Insert key-value pair - O(1) average, O(n) worst case
    void insert(string key, void* value) {
        int index = hashFunction(key);

        // Check if key already exists
        HashNode* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                // Update existing value
                temp->value = value;
                return;
            }
            temp = temp->next;
        }

        // Insert at beginning of chain
        HashNode* newNode = new HashNode(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // Search by key - O(1) average, O(n) worst case
    void* search(string key) {
        int index = hashFunction(key);
        HashNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Check if key exists - O(1) average, O(n) worst case
    bool contains(string key) {
        return search(key) != nullptr;
    }

    // Remove key - O(1) average, O(n) worst case
    bool remove(string key) {
        int index = hashFunction(key);
        HashNode* temp = table[index];
        HashNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr) {
                    // Remove first node in chain
                    table[index] = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    // Update value for existing key - O(1) average, O(n) worst case
    bool update(string key, void* newValue) {
        int index = hashFunction(key);
        HashNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value = newValue;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Get all keys - O(n + m) where n is capacity, m is number of elements
    void getAllKeys(string* keyArray, int& count) {
        count = 0;
        for (int i = 0; i < capacity; i++) {
            HashNode* temp = table[i];
            while (temp != nullptr) {
                keyArray[count++] = temp->key;
                temp = temp->next;
            }
        }
    }

    // Get all values - O(n + m)
    void getAllValues(void** valueArray, int& count) {
        count = 0;
        for (int i = 0; i < capacity; i++) {
            HashNode* temp = table[i];
            while (temp != nullptr) {
                valueArray[count++] = temp->value;
                temp = temp->next;
            }
        }
    }

    // Get current size - O(1)
    int getSize() {
        return size;
    }

    // Check if empty - O(1)
    bool isEmpty() {
        return size == 0;
    }

    // Get load factor - O(1)
    double getLoadFactor() {
        return (double)size / capacity;
    }

    // Display hash table contents - O(n + m)
    void display() {
        cout << "Hash Table Contents:" << endl;
        cout << "Size: " << size << ", Capacity: " << capacity << endl;
        cout << "Load Factor: " << getLoadFactor() << endl;
        cout << "-----------------------------------" << endl;

        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                cout << "Bucket " << i << ": ";
                HashNode* temp = table[i];
                while (temp != nullptr) {
                    cout << "[" << temp->key << "] -> ";
                    temp = temp->next;
                }
                cout << "NULL" << endl;
            }
        }
    }

    // Display with values (for debugging) - O(n + m)
    void displayWithValues() {
        cout << "Hash Table Contents (with value pointers):" << endl;
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                cout << i << " -> ";
                HashNode* temp = table[i];
                while (temp != nullptr) {
                    cout << "[" << temp->key << " : " << temp->value << "] -> ";
                    temp = temp->next;
                }
                cout << "NULL" << endl;
            }
        }
    }

    // Clear entire hash table - O(n + m)
    void clear() {
        for (int i = 0; i < capacity; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
            table[i] = nullptr;
        }
        size = 0;
    }

    // Get statistics about hash table distribution - O(n)
    void getStatistics() {
        int emptyBuckets = 0;
        int maxChainLength = 0;
        int totalChainLength = 0;

        for (int i = 0; i < capacity; i++) {
            int chainLength = 0;
            HashNode* temp = table[i];

            if (temp == nullptr) {
                emptyBuckets++;
            }
            else {
                while (temp != nullptr) {
                    chainLength++;
                    temp = temp->next;
                }
                totalChainLength += chainLength;
                if (chainLength > maxChainLength) {
                    maxChainLength = chainLength;
                }
            }
        }

        cout << "Hash Table Statistics:" << endl;
        cout << "Total buckets: " << capacity << endl;
        cout << "Used buckets: " << (capacity - emptyBuckets) << endl;
        cout << "Empty buckets: " << emptyBuckets << endl;
        cout << "Total elements: " << size << endl;
        cout << "Max chain length: " << maxChainLength << endl;
        cout << "Average chain length: "
            << (capacity - emptyBuckets > 0 ?
                (double)totalChainLength / (capacity - emptyBuckets) : 0)
            << endl;
        cout << "Load factor: " << getLoadFactor() << endl;
    }
};

// ==================== STRING HASH TABLE ====================
// Hash table specifically for string key-value pairs
// Used for quick string-to-string mappings
class StringHashTable {
private:
    struct StringNode {
        string key;
        string value;
        StringNode* next;

        StringNode(string k, string v) {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    StringNode** table;
    int capacity;
    int size;

    int hashFunction(string key) {
        long long hash = 0;
        long long p = 31;
        long long power = 1;

        for (int i = 0; key[i] != '\0'; i++) {
            int charValue;
            if (key[i] >= 'a' && key[i] <= 'z') {
                charValue = key[i] - 'a' + 1;
            }
            else if (key[i] >= 'A' && key[i] <= 'Z') {
                charValue = key[i] - 'A' + 1;
            }
            else if (key[i] >= '0' && key[i] <= '9') {
                charValue = key[i] - '0' + 27;
            }
            else {
                charValue = key[i];
            }

            hash = (hash + charValue * power) % capacity;
            power = (power * p) % capacity;
        }
        return (int)hash;
    }

public:
    StringHashTable(int cap = 100) {
        capacity = cap;
        size = 0;
        table = new StringNode * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~StringHashTable() {
        clear();
        delete[] table;
    }

    // Insert key-value pair - O(1) average
    void insert(string key, string value) {
        int index = hashFunction(key);

        StringNode* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value = value;
                return;
            }
            temp = temp->next;
        }

        StringNode* newNode = new StringNode(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // Search by key - O(1) average
    string search(string key) {
        int index = hashFunction(key);
        StringNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return "NOT_FOUND";
    }

    // Check if key exists - O(1) average
    bool contains(string key) {
        return search(key) != "NOT_FOUND";
    }

    // Remove key - O(1) average
    bool remove(string key) {
        int index = hashFunction(key);
        StringNode* temp = table[index];
        StringNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr) {
                    table[index] = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    // Get size - O(1)
    int getSize() {
        return size;
    }

    // Check if empty - O(1)
    bool isEmpty() {
        return size == 0;
    }

    // Display - O(n)
    void display() {
        cout << "String Hash Table:" << endl;
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                cout << i << " -> ";
                StringNode* temp = table[i];
                while (temp != nullptr) {
                    cout << "[" << temp->key << " : " << temp->value << "] -> ";
                    temp = temp->next;
                }
                cout << "NULL" << endl;
            }
        }
    }

    // Clear - O(n)
    void clear() {
        for (int i = 0; i < capacity; i++) {
            StringNode* current = table[i];
            while (current != nullptr) {
                StringNode* next = current->next;
                delete current;
                current = next;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
};

// ==================== INTEGER HASH TABLE ====================
// Hash table for integer key to void* value mappings
// Used for quick integer-based lookups (IDs, etc.)
class IntHashTable {
private:
    struct IntNode {
        int key;
        void* value;
        IntNode* next;

        IntNode(int k, void* v) {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    IntNode** table;
    int capacity;
    int size;

    // Simple modulo hash for integers
    int hashFunction(int key) {
        return key % capacity;
    }

public:
    IntHashTable(int cap = 100) {
        capacity = cap;
        size = 0;
        table = new IntNode * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~IntHashTable() {
        clear();
        delete[] table;
    }

    // Insert key-value pair - O(1) average
    void insert(int key, void* value) {
        int index = hashFunction(key);

        IntNode* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value = value;
                return;
            }
            temp = temp->next;
        }

        IntNode* newNode = new IntNode(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // Search by key - O(1) average
    void* search(int key) {
        int index = hashFunction(key);
        IntNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Check if key exists - O(1) average
    bool contains(int key) {
        return search(key) != nullptr;
    }

    // Remove key - O(1) average
    bool remove(int key) {
        int index = hashFunction(key);
        IntNode* temp = table[index];
        IntNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr) {
                    table[index] = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    // Get size - O(1)
    int getSize() {
        return size;
    }

    // Check if empty - O(1)
    bool isEmpty() {
        return size == 0;
    }

    // Display - O(n)
    void display() {
        cout << "Integer Hash Table:" << endl;
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                cout << i << " -> ";
                IntNode* temp = table[i];
                while (temp != nullptr) {
                    cout << "[" << temp->key << " : " << temp->value << "] -> ";
                    temp = temp->next;
                }
                cout << "NULL" << endl;
            }
        }
    }

    // Clear - O(n)
    void clear() {
        for (int i = 0; i < capacity; i++) {
            IntNode* current = table[i];
            while (current != nullptr) {
                IntNode* next = current->next;
                delete current;
                current = next;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
};