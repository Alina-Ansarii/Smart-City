#pragma once
#include "LQS.h"
#include "Medicine.h"
#include "HashTable.h"

#include <cstring>
#include <string>
using namespace std;
#include <fstream>
#include <sstream>



class Medicine {
private:
    string name;
    string formula;
    double price;
public:
    Medicine(string n, string f, double p) :
        name(n), formula(f), price(p) {
    }

    string getName() const { return name; }
    string getFormula() const { return formula; }
    double getPrice() const { return price; }
    void setPrice(double newPrice) { this->price = newPrice; }

    void display() const {
        //cout << "Name: " << name << ", Formula: " << formula << ", Price: Rs." << price;
    }
};

class MedicineHashTable {
private:
    struct MedicineEntry {
        string name;
        Medicine* medicine;

        MedicineEntry(const string& n, Medicine* med) : name(n), medicine(med)
        {
        }
        bool operator==(const MedicineEntry& other) const {
            return name == other.name;
        }
    };

    SinglyLinkedList<MedicineEntry*>** buckets;
    int tableSize;
    int count;

    int getHashIndex(const string& key) const {
        int idx = hashString(key, tableSize);
        if (idx < 0 || idx >= tableSize) {
            cout << "ERROR: Invalid hash index " << idx << " for key '" << key << "'" << endl;
            return 0;
        }
        return idx;
    }

public:
    MedicineHashTable(int size = 50) : tableSize(size), count(0) {
        buckets = new SinglyLinkedList<MedicineEntry*>*[tableSize];

        for (int i = 0; i < tableSize; i++) {
            buckets[i] = new SinglyLinkedList<MedicineEntry*>();
        }
    }

    ~MedicineHashTable() {
        for (int i = 0; i < tableSize; i++) {
            if (buckets[i] != nullptr) {
                Node<MedicineEntry*>* current = buckets[i]->getHead();
                while (current != nullptr) {
                    if (current->data != nullptr) {
                        delete current->data;
                    }
                    current = current->next;
                }
                delete buckets[i];
            }
        }
        delete[] buckets;
    }

    void insert(const string& name, Medicine* medicine) {
        if (medicine == nullptr) return;

        int index = getHashIndex(name);

        // Check if already exists
        Node<MedicineEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {
            if (current->data != nullptr && current->data->name == name) {
                // Update existing
                current->data->medicine = medicine;
                return;
            }
            current = current->next;
        }

        MedicineEntry* entry = new MedicineEntry(name, medicine);
        buckets[index]->insert(entry);
        count++;
    }

    Medicine* searchByName(const string& name) const {
        int index = getHashIndex(name);

        if (buckets[index] == nullptr) {
            return nullptr;
        }

        Node<MedicineEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {
            // NULL CHECK CRITICAL
            if (current->data != nullptr) {
                if (current->data->name == name) {
                    return current->data->medicine;
                }
            }
            current = current->next;
        }
        return nullptr;
    }

    Medicine* searchByFormula(const string& formula) const {
        for (int i = 0; i < tableSize; i++) {
            if (buckets[i] == nullptr) continue;

            Node<MedicineEntry*>* current = buckets[i]->getHead();
            while (current != nullptr) {
                // NULL CHECKS CRITICAL
                if (current->data != nullptr &&
                    current->data->medicine != nullptr &&
                    current->data->medicine->getFormula() == formula) {
                    return current->data->medicine;
                }
                current = current->next;
            }
        }
        return nullptr;
    }

    void remove(const string& name) {
        int index = getHashIndex(name);

        Node<MedicineEntry*>* current = buckets[index]->getHead();

        while (current != nullptr) {
            if (current->data->name == name) {
                MedicineEntry* entry = current->data;


                buckets[index]->remove(entry);

                delete entry;
                count--;
                return;
            }
            current = current->next;
        }
    }

    Medicine** getAllMedicines(int* resultCount) const {
        if (count == 0) {
            *resultCount = 0;
            return nullptr;
        }

        Medicine** result = new Medicine * [count];
        int index = 0;

        for (int i = 0; i < tableSize; i++) {
            Node<MedicineEntry*>* current = buckets[i]->getHead();
            while (current != nullptr) {
                result[index++] = current->data->medicine;
                current = current->next;
            }
        }

        *resultCount = count;
        return result;
    }

    int getCount() const {
        return count;
    }

    void displayAll() const {
        cout << "\n=== Medicine Hash Table ===" << endl;
        cout << "Total medicines: " << count << endl;
        cout << "Table size: " << tableSize << endl;
        cout << "Load factor: " << (double)count / tableSize << endl;
        cout << "---" << endl;

        for (int i = 0; i < tableSize; i++) {
            if (buckets[i]->getHead() != NULL) {
                cout << "Bucket " << i << ": ";
                Node<MedicineEntry*>* current = buckets[i]->getHead();
                while (current != NULL) {
                    cout << "[" << current->data->name << " ("
                        << current->data->medicine->getFormula() << ")] -> ";
                    current = current->next;
                }
                cout << "NULL" << endl;
            }
        }
    }
};


class Pharmacy {
private:
    string id;
    string name;
    string sector;
    double latitude;
    double longitude;
    MedicineHashTable* medicines;

public:
    Pharmacy(string id, string n, string s, double lat, double lon) :
        id(id), name(n), sector(s), latitude(lat), longitude(lon) {
        cout << "Created Pharmacy: " << id << endl;
        medicines = new MedicineHashTable(50);
    }

    ~Pharmacy() {
        delete medicines;
    }

    void addMedicine(Medicine* medicine) {
        if (medicine != nullptr) {
            medicines->insert(medicine->getName(), medicine);
            cout << "  -> Added: " << medicine->getName() << endl;
        }
    }

    Medicine* searchMedicine(const string& name) {
        return medicines->searchByName(name);
    }

    Medicine* searchByFormula(const string& formula) {
        return medicines->searchByFormula(formula);
    }

    void removeMedicine(const string& name) {
        medicines->remove(name);
    }

    Medicine** getAllMedicines(int* count) {
        return medicines->getAllMedicines(count);
    }

    int getMedicineCount() const {
        return medicines->getCount();
    }

    string getId() const { return id; }
    string getName() const { return name; }
    string getSector() const { return sector; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    void display() const {
        cout << "\n=== Pharmacy Information ===" << endl;
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Location: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Medicines in stock: " << medicines->getCount() << endl;
    }

    void displayMedicines() const {
        medicines->displayAll();
    }
};