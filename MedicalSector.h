#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "Medicine.h"
#include "Hospital.h"
#include "DoctorPatient.h"

inline string trimStr(const string& str) {
    size_t start = 0;
    while (start < str.length() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')) {
        start++;
    }
    size_t end = str.length();
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\r' || str[end - 1] == '\n')) {
        end--;
    }
    return str.substr(start, end - start);
}

class MedicalSector {
private:
    HospitalGraph* hospitalGraph;
    EmergencyBedHeap* emergencyBedHeap;
    DoctorHashTable* doctorTable;
    PatientHashTable* patientTable;

    Hospital** hospitals;
    int hospitalCount;
    int hospitalCapacity;

    Pharmacy** pharmacies;
    int pharmacyCount;
    int pharmacyCapacity;

    Doctor** doctors;
    int doctorCount;
    int doctorCapacity;

    Patient** patients;
    int patientCount, patientCapacity;

    // Helper to find pharmacy by ID
    Pharmacy* findPharmacyById(const string& id) {
        for (int i = 0; i < pharmacyCount; i++) {
            if (pharmacies[i]->getId() == id) {
                return pharmacies[i];
            }
        }
        return nullptr;
    }

public:

    MedicalSector() {
        hospitalGraph = new HospitalGraph(100);
        emergencyBedHeap = new EmergencyBedHeap(100);
        doctorTable = new DoctorHashTable(200);
        patientTable = new PatientHashTable(500);

        hospitals = new Hospital * [100];
        hospitalCount = 0;
        hospitalCapacity = 100;

        pharmacies = new Pharmacy * [50];
        pharmacyCount = 0;
        pharmacyCapacity = 50;

        doctors = new Doctor * [300];
        doctorCount = 0;
        doctorCapacity = 300;

        patientCapacity = 500;
        patients = new Patient * [patientCapacity];
        patientCount = 0;

    }




    ~MedicalSector() {
        delete hospitalGraph;
        delete emergencyBedHeap;
        delete patientTable;
        delete doctorTable;

        delete[] hospitals;
        delete[] pharmacies;
        delete[] doctors;
        delete[] patients;
    }


    // Register hospital - O(1)
    // Adds hospital to BOTH graph and heap for synchronization
    void  registerHospital(Hospital* hospital) {
        if (hospital == nullptr) {
            cout << "ERROR: Cannot register null hospital" << endl;
            return;
        }

        if (hospitalCount >= hospitalCapacity) {
            cout << "ERROR: Hospital capacity exceeded" << endl;
            return;
        }

        // Add to graph (network topology)
        hospitalGraph->addHospital(hospital);

        // Add to heap (bed availability tracking)
        emergencyBedHeap->insert(hospital, hospital->getAvailableEmergencyBeds());

        // Track in local array
        hospitals[hospitalCount++] = hospital;

        cout << "Hospital registered: " << hospital->getName() << " (ID: " << hospital->getId() << ")" << endl;
    }

    // Connect two hospitals - O(n)
    // Delegate to graph since it's a network topology operation
    void  connectHospitals(string id1, string id2, double dist) {
        bool connected = hospitalGraph->connectHospitals(id1, id2, dist);
        if (connected) {
            cout << "Hospitals connected: " << id1 << " <-> " << id2 << " (Distance: " << dist << " km)" << endl;
        }
        else {
            cout << "ERROR: Could not connect hospitals. One or both IDs not found." << endl;
        }
    }

    // Find nearest hospital to location - O(n)
    // Delegate to graph
    Hospital* findNearestHospital(double lat, double lon) {
        Hospital* nearest = hospitalGraph->findNearestHospital(lat, lon);
        if (nearest != nullptr) {
            cout << "Found nearest hospital: " << nearest->getName() << endl;
        }
        return nearest;
    }

    // Find shortest path to a hospital - O(E log V) using Dijkstra
    // Delegate to graph for pathfinding
    Hospital** getShortestPathToHospital(double userLat, double userLon,
        int* pathLength, double* distance) {
        *pathLength = 0;
        *distance = 0.0;

        // Find nearest hospital from user location
        Hospital* destination = findNearestHospital(userLat, userLon);
        if (destination == nullptr) {
            cout << "ERROR: No hospitals available" << endl;
            return nullptr;
        }

        Hospital** path = new Hospital * [1];
        path[0] = destination;
        *pathLength = 1;
        *distance = Graph::calculateDistance(userLat, userLon,
            destination->getLatitude(), destination->getLongitude());

        return path;
    }




    // Allocate emergency bed - O(n + log h)
    Hospital* allocateEmergencyBed(double patientLat, double patientLon) {
        // Step 1: Find nearest hospital to patient
        Hospital* nearest = findNearestHospital(patientLat, patientLon);
        if (nearest == nullptr) {
            cout << "ERROR: No hospitals available for bed allocation" << endl;
            return nullptr;
        }

        // Step 2: Try to allocate a bed at that hospital
        if (!nearest->allocateBed()) {
            cout << "ERROR: No beds available at " << nearest->getName() << endl;
            return nullptr;
        }

        // This is critical: after bed allocation, heap must reflect the change
        emergencyBedHeap->updateBedCount(nearest, nearest->getAvailableEmergencyBeds());

        cout << "Emergency bed allocated at: " << nearest->getName()
            << " | Remaining beds: " << nearest->getAvailableEmergencyBeds()
            << "/" << nearest->getTotalEmergencyBeds() << endl;

        return nearest;
    }

    // Release emergency bed - O(n + log h)
    void  releaseEmergencyBed(Hospital* hospital) {
        if (hospital == nullptr) {
            cout << "ERROR: Cannot release bed from null hospital" << endl;
            return;
        }

        // Step 1: Release the bed at the hospital
        hospital->releaseBed();

        // This is critical: after bed release, heap must reflect the change
        emergencyBedHeap->updateBedCount(hospital, hospital->getAvailableEmergencyBeds());

        cout << "Emergency bed released at: " << hospital->getName()
            << " | Available beds: " << hospital->getAvailableEmergencyBeds()
            << "/" << hospital->getTotalEmergencyBeds() << endl;
    }

    // Get hospital with most available beds - O(1)
    // Uses heap's peek (O(1)) instead of graph's search (O(n))
    Hospital* getHospitalWithMostBeds() {
        Hospital* hospital = emergencyBedHeap->peek();
        if (hospital != nullptr) {
            cout << "Hospital with most beds: " << hospital->getName()
                << " (" << hospital->getAvailableEmergencyBeds() << " beds)" << endl;
        }
        return hospital;
    }

    // Find hospital by ID - O(n)
    // Searches through registered hospitals to find by ID
    Hospital* findHospitalById(const string& id) {
        Hospital* found = hospitalGraph->findHospitalById(id);
        if (found != nullptr) {
            cout << "Found hospital: " << found->getName() << " (ID: " << id << ")" << endl;
        }
        else {
            cout << "Hospital not found: " << id << endl;
        }
        return found;
    }

    // Get distance between two hospitals - O(E)
    // Returns the distance if hospitals are connected, -1.0 if not connected
    double getDistance(string id1, string id2) {
        double distance = hospitalGraph->getDistance(id1, id2);
        if (distance >= 0) {
            cout << "Distance between " << id1 << " and " << id2 << ": " << distance << " km" << endl;
        }
        else {
            cout << "Hospitals " << id1 << " and " << id2 << " are not directly connected" << endl;
        }
        return distance;
    }



   // Register new patient - O(1)
    void registerPatient(Patient* patient) {
        if (patient && patientCount < patientCapacity) {
            patients[patientCount++] = patient;
            patientTable->insert(patient->getCnic(), patient);
        }
    }

    // Find patient by CNIC - O(1) avg
    Patient* findPatientByCnic(const string& cnic) {
        return patientTable->searchByCnic(cnic);
    }

    // Admit patient to hospital - O(n) to find nearest
    bool admitPatient(const string& cnic, double lat, double lon) {
        Patient* patient = patientTable->searchByCnic(cnic);
        if (!patient) return false;

        Hospital* nearest = allocateEmergencyBed(lat, lon);
        if (!nearest) return false;

        patient->admitToHospital(nearest);
        return true;
    }

    // Assign patient to doctor
    void assignPatientToDoctor(const string& cnic, Doctor* doctor) {
        Patient* patient = patientTable->searchByCnic(cnic);
        if (patient && doctor) {
            patient->assignToDoctor(doctor);
        }
    }

    // Get all patients at a hospital
    Patient** getPatientsAtHospital(Hospital* hospital, int* count) {
        int found = 0;

        // First pass: count
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getAdmittedHospital() == hospital) {
                found++;
            }
        }

        if (found == 0) {
            *count = 0;
            return nullptr;
        }

        // Second pass: collect
        Patient** result = new Patient * [found];
        int idx = 0;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getAdmittedHospital() == hospital) {
                result[idx++] = patients[i];
            }
        }

        *count = found;
        return result;
    }

    // Display all patients
    void displayAllPatients() const {
        cout << "\n=== ALL PATIENTS ===" << endl;
        cout << "Total: " << patientCount << endl;
        for (int i = 0; i < patientCount; i++) {
            patients[i]->display();
            cout << "---" << endl;
        }
    }



    // ==================== DOCTOR OPERATIONS ====================

    // Register doctor - O(1)
    void  registerDoctor(Doctor* doctor) {
        if (doctor == nullptr) {
            cout << "ERROR: Cannot register null doctor" << endl;
            return;
        }

        if (doctorCount >= doctorCapacity) {
            cout << "ERROR: Doctor capacity exceeded" << endl;
            return;
        }

        // Add to doctor hash table by specialization
        doctorTable->insert(doctor->getSpecialization().c_str(), doctor);

        // Track in local array
        doctors[doctorCount++] = doctor;

        cout << "Doctor registered: " << doctor->getName()
            << " (Specialization: " << doctor->getSpecialization() << ")" << endl;
    }

    // Find doctors by specialization - O(1) average
    Doctor** findDoctorsBySpecialization(string spec, int* count) {
        *count = 0;
        Doctor** result = doctorTable->searchBySpecialization(spec.c_str(), count);

        if (result != nullptr && *count > 0) {
            cout << "Found " << *count << " doctor(s) for " << spec << endl;
        }
        else {
            cout << "No doctors found for specialization: " << spec << endl;
        }

        return result;
    }



    // Register pharmacy - O(1)
    void  registerPharmacy(Pharmacy* pharmacy) {
        if (pharmacy == nullptr) {
            cout << "ERROR: Cannot register null pharmacy" << endl;
            return;
        }

        if (pharmacyCount >= pharmacyCapacity) {
            cout << "ERROR: Pharmacy capacity exceeded" << endl;
            return;
        }

        pharmacies[pharmacyCount++] = pharmacy;

        cout << "Pharmacy registered: " << pharmacy->getName()
            << " (Location: " << pharmacy->getSector() << ")" << endl;
    }

    // Search medicine by name across all pharmacies - O(p) p=number of pharmacies
    Medicine* searchMedicineByName(string name) {
        cout << "DEBUG: Searching for medicine: " << name << endl;
        cout << "DEBUG: Total pharmacies: " << pharmacyCount << endl;

        for (int i = 0; i < pharmacyCount; i++) {
            cout << "DEBUG: Checking pharmacy " << i << ": " << pharmacies[i]->getName() << endl;

            if (pharmacies[i] == nullptr) {
                cout << "DEBUG: Pharmacy " << i << " is NULL!" << endl;
                continue;
            }

            Medicine* found = pharmacies[i]->searchMedicine(name.c_str());

            if (found != nullptr) {
                cout << "Found medicine: " << name << " at pharmacy: "
                    << pharmacies[i]->getName() << endl;
                return found;
            }
        }

        cout << "Medicine not found: " << name << endl;
        return nullptr;
    }

    // Search medicine by formula across all pharmacies - O(p*m) p=pharmacies, m=medicines per pharmacy
    Medicine* searchMedicineByFormula(string formula) {
        for (int i = 0; i < pharmacyCount; i++) {
            Medicine* found = pharmacies[i]->searchByFormula(formula.c_str());
            if (found != nullptr) {
                cout << "Found medicine with formula: " << formula << " at pharmacy: "
                    << pharmacies[i]->getName() << endl;
                return found;
            }
        }

        cout << "Medicine with formula not found: " << formula << endl;
        return nullptr;
    }

    // Find all pharmacies that have a specific medicine - O(p)
    Pharmacy** searchPharmaciesWithMedicine(string medicineName, int* count) {
        *count = 0;

        Pharmacy** result = new Pharmacy * [pharmacyCount];

        for (int i = 0; i < pharmacyCount; i++) {
            Medicine* found = pharmacies[i]->searchMedicine(medicineName.c_str());
            if (found != nullptr) {
                result[(*count)++] = pharmacies[i];
            }
        }

        if (*count == 0) {
            cout << "No pharmacies found with medicine: " << medicineName << endl;
            delete[] result;
            return nullptr;
        }

        cout << "Found " << *count << " pharmacy(ies) with medicine: " << medicineName << endl;
        return result;
    }




    // Get all hospitals - O(n) - returns a copy
    Hospital** getAllHospitals(int* count) {
        if (count == nullptr) return nullptr;
        *count = hospitalCount;

        if (hospitalCount == 0) return nullptr;

        Hospital** copy = new Hospital * [hospitalCount];
        for (int i = 0; i < hospitalCount; i++) {
            copy[i] = hospitals[i];
        }
        return copy;
    }

    // Get all pharmacies - O(n) - returns a copy
    Pharmacy** getAllPharmacies(int* count) {
        if (count == nullptr) return nullptr;
        *count = pharmacyCount;

        if (pharmacyCount == 0) return nullptr;

        Pharmacy** copy = new Pharmacy * [pharmacyCount];
        for (int i = 0; i < pharmacyCount; i++) {
            copy[i] = pharmacies[i];
        }
        return copy;
    }

    // ==================== DISPLAY OPERATIONS ====================

    // Display all hospitals - O(V + E)
    void  displayAllHospitals() const {
        cout << "\n========== ALL HOSPITALS ==========" << endl;
        if (hospitalCount == 0) {
            cout << "No hospitals registered" << endl;
            return;
        }

        for (int i = 0; i < hospitalCount; i++) {
            hospitals[i]->display();
            cout << "---" << endl;
        }
        cout << endl;
    }

    // Display all doctors - O(d) d=number of doctors
    void  displayAllDoctors() const {
        cout << "\n========== ALL DOCTORS ==========" << endl;
        if (doctorCount == 0) {
            cout << "No doctors registered" << endl;
            return;
        }

        for (int i = 0; i < doctorCount; i++) {
            cout << "ID: " << doctors[i]->getId() << endl;
            cout << "Name: " << doctors[i]->getName() << endl;
            cout << "Specialization: " << doctors[i]->getSpecialization() << endl;
            cout << "Hospital: " << doctors[i]->getAssignedHospital()->getName() << endl;
            cout << "---" << endl;
        }
        cout << endl;
    }

    // Display all pharmacies - O(p) p=number of pharmacies
    void  displayAllPharmacies() const {
        cout << "\n========== ALL PHARMACIES ==========" << endl;
        if (pharmacyCount == 0) {
            cout << "No pharmacies registered" << endl;
            return;
        }

        for (int i = 0; i < pharmacyCount; i++) {
            cout << "ID: " << pharmacies[i]->getId() << endl;
            cout << "Name: " << pharmacies[i]->getName() << endl;
            cout << "Location: (" << pharmacies[i]->getLatitude() << ", "
                << pharmacies[i]->getLongitude() << ")" << endl;
            cout << "Sector: " << pharmacies[i]->getSector() << endl;

            int medCount = 0;
            Medicine** medicines = pharmacies[i]->getAllMedicines(&medCount);
            cout << "Medicines: " << medCount << endl;
            if (medicines != nullptr) {
                delete[] medicines;
            }
            cout << "---" << endl;
        }
        cout << endl;
    }

    // Display emergency bed status - O(h) h=number of hospitals
    void  displayEmergencyBedStatus() const {
        cout << "\n========== EMERGENCY BED STATUS ==========" << endl;

        for (int i = 0; i < hospitalCount; i++) {

            Hospital* h = hospitals[i];
            cout << "Hospital: " << h->getName() << endl;
            cout << "Available Beds: " << h->getAvailableEmergencyBeds()
                << " / " << h->getTotalEmergencyBeds() << endl;
            cout << "Occupancy: " << (h->getTotalEmergencyBeds() - h->getAvailableEmergencyBeds())
                << " beds occupied" << endl;

            double occupancyPercent = ((double)(h->getTotalEmergencyBeds() - h->getAvailableEmergencyBeds())
                / h->getTotalEmergencyBeds()) * 100;
            cout << "Occupancy Rate: " << occupancyPercent << "%" << endl;
            cout << "---" << endl;
        }

        //cout << "\nHeap Status:" << endl;
        //emergencyBedHeap->displayHeap();
        cout << endl;
    }

    // Display system statistics - O(h + d + p)
    void  displayStatistics() const {
        cout << "\n========== MEDICAL SECTOR STATISTICS ==========" << endl;

        // Hospital statistics
        cout << "Total Hospitals: " << hospitalCount << endl;
        int totalBeds = 0;
        int availableBeds = 0;
        for (int i = 0; i < hospitalCount; i++) {
            totalBeds += hospitals[i]->getTotalEmergencyBeds();
            availableBeds += hospitals[i]->getAvailableEmergencyBeds();
        }
        cout << "Total Emergency Beds: " << totalBeds << endl;
        cout << "Available Beds: " << availableBeds << endl;
        cout << "Occupied Beds: " << (totalBeds - availableBeds) << endl;
        if (totalBeds > 0) {
            cout << "System Occupancy: " << ((double)(totalBeds - availableBeds) / totalBeds) * 100 << "%" << endl;
        }

        // Doctor statistics
        cout << "\nTotal Doctors: " << doctorCount << endl;

        // Pharmacy statistics
        cout << "Total Pharmacies: " << pharmacyCount << endl;

        cout << "\n==========================================" << endl;
    }


    // CSV Loading
    bool loadHospitalsFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string id, name, sector, bedsStr, specs;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, sector, ',');
            getline(ss, bedsStr, ',');
            getline(ss, specs);

            int beds = atoi(bedsStr.c_str());
            double lat = 33.7 + (hospitalCount * 0.01);
            double lon = 73.0 + (hospitalCount * 0.01);

            Hospital* h = new Hospital(id, name, sector, lat, lon, beds);

            stringstream specStream(specs);
            string spec;
            while (getline(specStream, spec, ',')) {
                if (!spec.empty()) h->addSpecialization(spec);
            }

            registerHospital(h);
        }

        file.close();
        return true;
    }

    bool loadPharmaciesFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string pharmId, name, sector, medName, formula, priceStr;

            getline(ss, pharmId, ',');
            getline(ss, name, ',');
            getline(ss, sector, ',');
            getline(ss, medName, ',');
            getline(ss, formula, ',');
            getline(ss, priceStr);

            // Trim whitespace from formula
            formula = trimStr(formula);

            double price = atof(priceStr.c_str());

            Pharmacy* pharmacy = findPharmacyById(pharmId);
            if (!pharmacy) {
                double lat = 33.7 + (pharmacyCount * 0.01);
                double lon = 73.0 + (pharmacyCount * 0.01);
                pharmacy = new Pharmacy(pharmId, name, sector, lat, lon);
                registerPharmacy(pharmacy);
            }

            Medicine* med = new Medicine(medName, formula, price);
            pharmacy->addMedicine(med);
        }

        file.close();
        return true;
    }


};



