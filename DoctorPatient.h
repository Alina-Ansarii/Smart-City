#pragma once
#include <iostream>
#include <string>
#include <cstring> 
#include <fstream>
#include <sstream>
using namespace std;
#include "LQS.h"
#include "HashTable.h"
#include "Hospital.h"

class Doctor {
private:
    string id;
    string name;
    string specialization;
    Hospital* assignedHospital; // Reference 

public:
    Doctor(string id, string name, string specialization,
        Hospital* hospital) :
        id(id), name(name), specialization(specialization),
        assignedHospital(hospital) {
    }

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    string getSpecialization() const { return specialization; }
    Hospital* getAssignedHospital() const { return assignedHospital; }

    // Setters
    void setAssignedHospital(Hospital* hospital) {
        assignedHospital = hospital;
    }

    // Display
    void display() const {
        cout << "Doctor ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Specialization: " << specialization << endl;
        if (assignedHospital != nullptr) {
            cout << "Hospital: " << assignedHospital->getName() << endl;
        }
    }
};

class DoctorHashTable {
private:
    struct DoctorEntry {
        string specialization;     // Key 
        Doctor* doctor;            // Value (doesn't own doctor)

        DoctorEntry(const string& spec, Doctor* doc) : specialization(spec), doctor(doc) {
        }

        bool operator==(const DoctorEntry& other) const {
            return specialization == other.specialization &&
                doctor == other.doctor;
        }
    };

    SinglyLinkedList<DoctorEntry*>** buckets;
    int tableSize;
    int count;

    int getHashIndex(const string& key) const {
        return hashString(key, tableSize);
    }

public:
    DoctorHashTable(int size = 100) : tableSize(size), count(0) {
        buckets = new SinglyLinkedList<DoctorEntry*>*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            buckets[i] = new SinglyLinkedList<DoctorEntry*>();
        }
    }

    ~DoctorHashTable() {
        for (int i = 0; i < tableSize; i++) {
            if (buckets[i] != nullptr) {
                Node<DoctorEntry*>* current = buckets[i]->getHead();
                while (current != nullptr) {
                    delete current->data;
                    current = current->next;
                }
                delete buckets[i];
            }
        }
        delete[] buckets;
    }


    void insert(const string& specialization, Doctor* doctor) {
        int index = getHashIndex(specialization);


        DoctorEntry* entry = new DoctorEntry(specialization, doctor);
        buckets[index]->insert(entry);
        count++;
    }

    Doctor** searchBySpecialization(const string& spec, int* resultCount) {
        int index = getHashIndex(spec);
        int found = 0;

        // First pass: count how many doctors with this specialization
        Node<DoctorEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {
            if (current->data->specialization == spec) {
                found++;
            }
            current = current->next;
        }

        if (found == 0) {
            *resultCount = 0;
            return nullptr;
        }

        // Second pass: collect all doctors with this specialization
        Doctor** result = new Doctor * [found];
        int index_result = 0;
        current = buckets[index]->getHead();
        while (current != nullptr) {

            if (current->data->specialization == spec) {
                result[index_result++] = current->data->doctor;
            }
            current = current->next;
        }

        *resultCount = found;
        return result;
    }

    // Get First Doctor by Specialization (
    Doctor* getFirstBySpecialization(const string& spec) {
        int index = getHashIndex(spec);

        Node<DoctorEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {
            if (current->data->specialization == spec) {
                return current->data->doctor;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Remove a specific doctor 
    void remove(const string& specialization, Doctor* doctor) {
        int index = getHashIndex(specialization);

        Node<DoctorEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {

            if (current->data->specialization == specialization &&
                current->data->doctor == doctor) {

                DoctorEntry* entry = current->data;
                buckets[index]->remove(entry);

                delete entry;
                count--;
                return;
            }
            current = current->next;
        }
    }

    int getCount() const {
        return count;
    }

    void displayAll() const {
        cout << "\n=== Doctor Hash Table ===" << endl;
        cout << "Total doctors: " << count << endl;
        cout << "Table size: " << tableSize << endl;
        cout << "Load factor: " << (double)count / tableSize << endl;
        cout << "---" << endl;

        for (int i = 0; i < tableSize; i++) {
            if (buckets[i]->getHead() != NULL) {
                cout << "Bucket " << i << ": ";
                Node<DoctorEntry*>* current = buckets[i]->getHead();
                while (current != NULL) {
                    cout << "[" << current->data->doctor->getName()
                        << " (" << current->data->specialization << ")] -> ";
                    current = current->next;
                }
                cout << "NULL" << endl;
            }
        }
    }
};

class Patient {
private:
    string patientId;       // e.g., "PT001"
    string name;
    int age;
    string cnic;           // For hashing
    string ailment;
    Doctor* assignedDoctor;    // Reference to doctor
    Hospital* admittedHospital; // Reference to hospital

public:
    Patient(string id, string n, int a, string cnic, string ailment)
        : patientId(id), name(n), age(a), cnic(cnic), ailment(ailment),
        assignedDoctor(nullptr), admittedHospital(nullptr) {
    }

    // Getters
    string getPatientId() const { return patientId; }
    string getName() const { return name; }
    string getCnic() const { return cnic; }
    string getAilment() const { return ailment; }
    Doctor* getAssignedDoctor() const { return assignedDoctor; }
    Hospital* getAdmittedHospital() const { return admittedHospital; }

    // Setters
    void assignToDoctor(Doctor* doc) { assignedDoctor = doc; }
    void admitToHospital(Hospital* hosp) { admittedHospital = hosp; }

    void display() const {
        cout << "Patient ID: " << patientId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Ailment: " << ailment << endl;
        if (assignedDoctor) {
            cout << "Doctor: " << assignedDoctor->getName() << endl;
        }
        if (admittedHospital) {
            cout << "Hospital: " << admittedHospital->getName() << endl;
        }
    }
};

class PatientHashTable {
private:
    struct PatientEntry {
        string cnic;          // Key (unique identifier)
        Patient* patient;     // Value

        PatientEntry(const string& c, Patient* p) : cnic(c), patient(p) {}
    };

    SinglyLinkedList<PatientEntry*>** buckets;
    int tableSize;
    int count;

    int getHashIndex(const string& key) const {
        return hashString(key, tableSize);
    }

public:
    PatientHashTable(int size = 100) : tableSize(size), count(0) {
        buckets = new SinglyLinkedList<PatientEntry*>*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            buckets[i] = new SinglyLinkedList<PatientEntry*>();
        }
    }

    ~PatientHashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node<PatientEntry*>* current = buckets[i]->getHead();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete buckets[i];
        }
        delete[] buckets;
    }

    // Insert patient by CNIC - O(1) avg
    void insert(const string& cnic, Patient* patient) {
        int index = getHashIndex(cnic);

        // Check if CNIC already exists (update)
        Node<PatientEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {
            if (current->data->cnic == cnic) {
                current->data->patient = patient;
                return;
            }
            current = current->next;
        }

        // Add new entry
        PatientEntry* entry = new PatientEntry(cnic, patient);
        buckets[index]->insert(entry);
        count++;
    }

    // Search patient by CNIC - O(1) avg
    Patient* searchByCnic(const string& cnic) {
        int index = getHashIndex(cnic);

        Node<PatientEntry*>* current = buckets[index]->getHead();
        while (current != nullptr) {
            if (current->data->cnic == cnic) {
                return current->data->patient;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Get all patients - O(n)
    Patient** getAllPatients(int* resultCount) {
        if (count == 0) {
            *resultCount = 0;
            return nullptr;
        }

        Patient** result = new Patient * [count];
        int idx = 0;

        for (int i = 0; i < tableSize; i++) {
            Node<PatientEntry*>* current = buckets[i]->getHead();
            while (current != nullptr) {
                result[idx++] = current->data->patient;
                current = current->next;
            }
        }

        *resultCount = count;
        return result;
    }

    int getCount() const { return count; }
};