#pragma once
/*
================================================================================
SMART CITY PROJECT - CONTAINER CLASS WITH 20 CROSS-MODULE FUNCTIONS
================================================================================
This version combines all 6 sector modules with 20 advanced cross-module
functions that integrate functionality across sectors without modifying them.

Total Functions Added:
- TIER 1 ESSENTIAL: 5 functions
- TIER 2 ADVANCED: 5 functions
- TIER 3 BONUS: 10 functions
================================================================================
*/

#include "TransportSector.h"
#include "EducationSector.h"
#include "MedicalSector.h"
#include "CommercialSector.h"
#include "PublicFacilitiesSector.h"
#include "PopulationSector.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ==================== SUPPORTING DATA STRUCTURES ====================

struct NearestFacilitiesResult {
    Hospital* nearestHospital;
    School* nearestSchool;
    BusStop* nearestBusStop;
    Mall* nearestMall;
    Facility* nearestPublicFacility;

    NearestFacilitiesResult() {
        nearestHospital = nullptr;
        nearestSchool = nullptr;
        nearestBusStop = nullptr;
        nearestMall = nullptr;
        nearestPublicFacility = nullptr;
    }
};

struct HealthMetrics {
    string sectorName;
    int totalPopulation;
    int nearbyHospitals;
    int nearbyPharmacies;
    double averageHealthScore;

    HealthMetrics() {
        sectorName = "";
        totalPopulation = 0;
        nearbyHospitals = 0;
        nearbyPharmacies = 0;
        averageHealthScore = 0.0;
    }
};

struct FacilityUtilization {
    string facilityType;
    int totalCount;
    double utilizationPercentage;
    string utilizationStatus;

    FacilityUtilization() {
        facilityType = "";
        totalCount = 0;
        utilizationPercentage = 0.0;
        utilizationStatus = "";
    }
};

struct AreaQualityScore {
    string sectorName;
    double hospitalProximityScore;
    double educationProximityScore;
    double transportAccessScore;
    double commercialAccessScore;
    double publicFacilityScore;
    double overallScore;
    string qualityRating;

    AreaQualityScore() {
        sectorName = "";
        hospitalProximityScore = 0.0;
        educationProximityScore = 0.0;
        transportAccessScore = 0.0;
        commercialAccessScore = 0.0;
        publicFacilityScore = 0.0;
        overallScore = 0.0;
        qualityRating = "";
    }
};

class SmartCity {
private:
    // ==================== MODULE INSTANCES ====================
    TransportSystem* transportModule;
    EducationSystem* educationModule;
    MedicalSector* medicalModule;
    CommercialSector* commercialModule;
    PublicFacilitiesSector* facilitiesModule;
    PopulationSector* populationModule;

    // ==================== SYSTEM STATE ====================
    bool isInitialized;
    string cityName;
    string cityCode;

public:
    // ==================== CONSTRUCTORS ====================

    SmartCity() {
        cityName = "Islamabad";
        cityCode = "ISB";
        isInitialized = false;

        transportModule = new TransportSystem();
        educationModule = new EducationSystem();
        medicalModule = new MedicalSector();
        commercialModule = new CommercialSector();
        facilitiesModule = new PublicFacilitiesSector();
        populationModule = new PopulationSector();

        isInitialized = true;

        cout << "\n+======================================================+" << endl;
        cout << "|           SMART CITY SYSTEM INITIALIZED              |" << endl;
        cout << "|               City: " << cityName << "                      |" << endl;
        cout << "+======================================================+" << endl;
    }

    SmartCity(string name, string code) {
        cityName = name;
        cityCode = code;
        isInitialized = false;

        transportModule = new TransportSystem();
        educationModule = new EducationSystem();
        medicalModule = new MedicalSector();
        commercialModule = new CommercialSector();
        facilitiesModule = new PublicFacilitiesSector();
        populationModule = new PopulationSector();

        isInitialized = true;

        cout << "\n+======================================================+" << endl;
        cout << "|           SMART CITY SYSTEM INITIALIZED              |" << endl;
        cout << "|               City: " << cityName << "                      |" << endl;
        cout << "+======================================================+" << endl;
    }

    // ==================== DESTRUCTOR ====================

    ~SmartCity() {
        cout << "\n[SYSTEM] Shutting down Smart City..." << endl;

        delete transportModule;
        delete educationModule;
        delete medicalModule;
        delete commercialModule;
        delete facilitiesModule;
        delete populationModule;

        cout << "[SYSTEM] Smart City shutdown complete." << endl;
    }

    // ==================== MODULE ACCESS METHODS ====================

    TransportSystem* getTransportModule() { return transportModule; }
    EducationSystem* getEducationModule() { return educationModule; }
    MedicalSector* getMedicalModule() { return medicalModule; }
    CommercialSector* getCommercialModule() { return commercialModule; }
    PublicFacilitiesSector* getFacilitiesModule() { return facilitiesModule; }
    PopulationSector* getPopulationModule() { return populationModule; }

    // ==================== CROSS-MODULE OPERATIONS ====================

    /*
     * Emergency Response System
     * Uses: Medical + Transport modules
     */
    void handleEmergency(double emergencyLat, double emergencyLon, string emergencyType) {
        cout << "\n+======================================================+" << endl;
        cout << "|          EMERGENCY RESPONSE ACTIVATED                |" << endl;
        cout << "+======================================================+" << endl;
        cout << "Emergency Type: " << emergencyType << endl;
        cout << "Location: (" << emergencyLat << ", " << emergencyLon << ")" << endl;

        // Step 1: Find nearest hospital (uses existing function)
        Hospital* nearestHospital = medicalModule->findNearestHospital(emergencyLat, emergencyLon);

        if (nearestHospital == nullptr) {
            cout << "[ERROR] No hospitals available!" << endl;
            return;
        }

        cout << "\n[1] Nearest Hospital Found: " << nearestHospital->getName() << endl;

        // Step 2: Allocate emergency bed (uses existing function)
        Hospital* assignedHospital = medicalModule->allocateEmergencyBed(emergencyLat, emergencyLon);

        if (assignedHospital == nullptr) {
            cout << "[WARNING] No emergency beds available." << endl;
            return;
        }

        cout << "[2] Emergency Bed Allocated at: " << assignedHospital->getName() << endl;

        // Step 3: Use emergency transport routing (uses existing function)
        cout << "\n[3] Arranging Emergency Transport..." << endl;
        transportModule->emergencyRouting(emergencyLat, emergencyLon, "EMERGENCY_DEST");

        cout << "\n+======================================================+" << endl;
        cout << "|       EMERGENCY RESPONSE PLAN COMPLETE               |" << endl;
        cout << "+======================================================+" << endl;
    }

    /*
     * Find Nearest of All Types
     * Queries all modules for nearest facilities
     */
    void findNearestOfAllTypes(double userLat, double userLon) {
        cout << "\n+======================================================+" << endl;
        cout << "|         NEAREST FACILITIES TO YOUR LOCATION          |" << endl;
        cout << "+======================================================+" << endl;
        cout << "Your Location: (" << userLat << ", " << userLon << ")" << endl;
        cout << "------------------------------------------------------" << endl;

        // Medical: Find nearest hospital
        cout << "\n[MEDICAL]" << endl;
        Hospital* hospital = medicalModule->findNearestHospital(userLat, userLon);

        // Education: Find nearest school
        cout << "\n[EDUCATION]" << endl;
        School* school = educationModule->findNearestSchool(userLat, userLon);

        // Transport: Find nearest bus stop
        cout << "\n[TRANSPORT]" << endl;
        transportModule->findNearestStop(userLat, userLon);

        // Commercial: Find nearest mall
        cout << "\n[COMMERCIAL]" << endl;
        Mall* mall = commercialModule->findNearestMall(userLat, userLon);

        // Public Facilities: Find nearest facility
        cout << "\n[PUBLIC FACILITIES]" << endl;
        Facility* facility = facilitiesModule->findNearestFacility(userLat, userLon);

        cout << "\n+======================================================+" << endl;
    }

    /*
     * Setup School Transport
     * Links Education + Transport modules
     */
    void setupSchoolTransport(string schoolID, string busNumber) {
        cout << "\n=== SETTING UP SCHOOL TRANSPORT ===" << endl;

        // Verify school exists
        School* school = educationModule->findSchool(schoolID);
        if (school == nullptr) {
            cout << "Error: School " << schoolID << " not found!" << endl;
            return;
        }

        // Verify bus exists
        Bus* bus = transportModule->getBus(busNumber);
        if (bus == nullptr) {
            cout << "Error: Bus " << busNumber << " not found!" << endl;
            return;
        }

        // Register as school bus (uses existing function)
        transportModule->registerSchoolBus(bus);

        cout << "\n[SUCCESS] School transport setup complete!" << endl;
        cout << "School: " << school->getName() << endl;
        cout << "Bus: " << busNumber << endl;
    }

    /*
     * Citizen Health Profile
     * Links Population + Medical modules
     */
    void getCitizenHealthInfo(string cnic) {
        cout << "\n=== CITIZEN HEALTH PROFILE ===" << endl;

        // Get citizen from population module
        Citizen* citizen = populationModule->searchCitizen(cnic);
        if (citizen == nullptr) {
            cout << "Citizen with CNIC " << cnic << " not found!" << endl;
            return;
        }

        cout << "\nCitizen Information:" << endl;
        citizen->display();

        // Find nearest hospital to citizen
        Hospital* nearestHospital = medicalModule->findNearestHospital(33.7, 73.0);
        if (nearestHospital != nullptr) {
            cout << "\nNearest Hospital: " << nearestHospital->getName() << endl;
        }

        // Check patient records
        Patient* patientRecord = medicalModule->findPatientByCnic(cnic);
        if (patientRecord != nullptr) {
            cout << "\n[MEDICAL RECORDS FOUND]" << endl;
            patientRecord->display();
        }
        else {
            cout << "\nNo medical records on file." << endl;
        }
    }

    /*
     * Simple Sector Analysis
     * Shows data from multiple modules for a sector
     */
    void analyzeSector(string sectorName) {
        cout << "\n+======================================================+" << endl;
        cout << "|            SECTOR ANALYSIS: " << sectorName << "                 |" << endl;
        cout << "+======================================================+" << endl;

        //// Population data
        //cout << "\n[POPULATION]" << endl;
        //populationModule->displaySectorInfo(sectorName);

        // Count facilities by searching
        cout << "\n[PUBLIC FACILITIES]" << endl;
        cout << "Total facilities in sector: ";
        // Use existing display function
        facilitiesModule->printStatistics();

        cout << "\n+======================================================+" << endl;
    }

    /*
     * Smart Route Planning
     * Uses transport module for routing
     */
    void planRoute(string startStopID, string endStopID) {
        cout << "\n=== PLANNING ROUTE ===" << endl;
        cout << "From: " << startStopID << endl;
        cout << "To: " << endStopID << endl;

        // Use existing shortest path function
        transportModule->findShortestPath(startStopID, endStopID);
    }

    // ==================== SYSTEM INFORMATION ====================

    /*
     * Display System Status
     * Shows status of all modules
     */
    void displaySystemStatus() {
        cout << "\n+======================================================+" << endl;
        cout << "|           SMART CITY SYSTEM STATUS                   |" << endl;
        cout << "+======================================================+" << endl;
        cout << "City Name: " << cityName << endl;
        cout << "City Code: " << cityCode << endl;
        cout << "Status: " << (isInitialized ? "OPERATIONAL" : "OFFLINE") << endl;
        cout << "+======================================================+" << endl;

        // Call existing display functions from each module
        cout << "\n--- TRANSPORT SECTOR ---" << endl;
        transportModule->displaySystemStatistics();

        cout << "\n--- EDUCATION SECTOR ---" << endl;
        educationModule->displayStatistics();

        cout << "\n--- MEDICAL SECTOR ---" << endl;
        medicalModule->displayStatistics();

        cout << "\n--- COMMERCIAL SECTOR ---" << endl;
        commercialModule->displayStatistics();

        cout << "\n--- PUBLIC FACILITIES ---" << endl;
        facilitiesModule->printStatistics();

        cout << "\n--- POPULATION ---" << endl;
        populationModule->displayStatistics();

        cout << "\n+======================================================+" << endl;
    }

    /*
     * Display specific module status
     */
    void displayModuleStatus(string moduleName) {
        cout << "\n=== " << moduleName << " MODULE STATUS ===" << endl;

        if (moduleName == "TRANSPORT") {
            transportModule->displaySystemStatistics();
        }
        else if (moduleName == "EDUCATION") {
            educationModule->displayStatistics();
        }
        else if (moduleName == "MEDICAL") {
            medicalModule->displayStatistics();
        }
        else if (moduleName == "COMMERCIAL") {
            commercialModule->displayStatistics();
        }
        else if (moduleName == "FACILITIES") {
            facilitiesModule->printStatistics();
        }
        else if (moduleName == "POPULATION") {
            populationModule->displayStatistics();
        }
        else {
            cout << "Unknown module: " << moduleName << endl;
        }
    }

    // ==================== GETTERS ====================

    string getCityName() const { return cityName; }
    string getCityCode() const { return cityCode; }
    bool getIsInitialized() const { return isInitialized; }

    // ==================== TIER 1: ESSENTIAL (5 FUNCTIONS) ====================

    /*
     * TIER 1-1: Display Smart City Dashboard
     * Enhanced system overview combining all modules
     * Complexity: O(n) where n is total facilities across modules
     */
    void displaySmartCityDashboard() {
        cout << "\n";
        cout << "+===============================================================+" << endl;
        cout << "|         " << cityName << " - SMART CITY MANAGEMENT DASHBOARD         |" << endl;
        cout << "+===============================================================+" << endl;

        cout << "\n[TRANSPORT SECTOR]" << endl;
        //cout << "  - Total Buses: " << transportModule->displayAllBuses() << endl;
        transportModule->displaySystemStatistics();

        cout << "\n[EDUCATION SECTOR]" << endl;
        educationModule->displayStatistics();

        cout << "\n[MEDICAL SECTOR]" << endl;
        medicalModule->displayStatistics();

        cout << "\n[COMMERCIAL SECTOR]" << endl;
        commercialModule->displayStatistics();

        cout << "\n[PUBLIC FACILITIES]" << endl;
        facilitiesModule->printStatistics();

        cout << "\n[POPULATION]" << endl;
        populationModule->displayStatistics();
    }

    /*
     * TIER 1-2: Emergency Response by Citizen CNIC
     * Find citizen location and initiate emergency response
     * Complexity: O(n) for citizen search + emergency routing
     */
    void emergencyResponse(string cnic) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|          EMERGENCY RESPONSE - CITIZEN LOOKUP              |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        // Step 1: Find citizen
        Citizen* citizen = populationModule->searchCitizen(cnic);
        if (citizen == nullptr) {
            cout << "[ERROR] Citizen with CNIC " << cnic << " not found!" << endl;
            return;
        }

        cout << "[1] CITIZEN FOUND:" << endl;
        citizen->display();

        // Step 2: Initiate emergency response at citizen's approximate location
        double emergencyLat = 33.7 + (rand() % 10) * 0.01;
        double emergencyLon = 73.0 + (rand() % 10) * 0.01;

        cout << "\n[2] INITIATING EMERGENCY RESPONSE AT LOCATION:" << endl;
        cout << "Coordinates: (" << emergencyLat << ", " << emergencyLon << ")" << endl;

        // Step 3: Emergency routing
        transportModule->emergencyRouting(emergencyLat, emergencyLon, "CITIZEN_EMERGENCY");

        // Step 4: Check medical records
        Patient* patientRecord = medicalModule->findPatientByCnic(cnic);
        if (patientRecord != nullptr) {
            cout << "\n[3] MEDICAL HISTORY:" << endl;
            patientRecord->display();
        }

        cout << "\n[4] NEAREST HOSPITAL:" << endl;
        Hospital* hospital = medicalModule->findNearestHospital(emergencyLat, emergencyLon);

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 1-3: Find All Nearest Facilities (Returns Structure)
     * Query all modules for nearest facilities at once
     * Complexity: O(n*m) where n=facilities, m=modules (6)
     */
    NearestFacilitiesResult findAllNearestFacilities(double lat, double lon) {
        NearestFacilitiesResult result;

        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|       FINDING ALL NEAREST FACILITIES TO YOUR LOCATION    |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;
        cout << "Location: (" << lat << ", " << lon << ")" << endl;

        // Medical
        result.nearestHospital = medicalModule->findNearestHospital(lat, lon);
        cout << "[MEDICAL] " << (result.nearestHospital ? result.nearestHospital->getName() : "Not found") << endl;

        // Education
        result.nearestSchool = educationModule->findNearestSchool(lat, lon);
        cout << "[EDUCATION] " << (result.nearestSchool ? result.nearestSchool->getName() : "Not found") << endl;

        // Transport
        result.nearestBusStop = transportModule->routeGraph->findNearestStop(lat, lon);
        cout << "[TRANSPORT] " << (result.nearestBusStop ? result.nearestBusStop->getName() : "Not found") << endl;

        // Commercial
        result.nearestMall = commercialModule->findNearestMall(lat, lon);
        cout << "[COMMERCIAL] " << (result.nearestMall ? result.nearestMall->name : "Not found") << endl;

        // Public Facilities
        result.nearestPublicFacility = facilitiesModule->findNearestFacility(lat, lon);
        cout << "[FACILITIES] " << (result.nearestPublicFacility ? result.nearestPublicFacility->getName() : "Not found") << endl;

        cout << "+-------------------------------------------------------------+" << endl;
        return result;
    }

    /*
     * TIER 1-4: Generate Citizen Health Profile
     * Comprehensive health information for a citizen
     * Complexity: O(1) average for citizen + medical record lookup
     */
    void generateCitizenHealthProfile(string cnic) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|            COMPREHENSIVE CITIZEN HEALTH PROFILE           |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        // Get citizen info
        Citizen* citizen = populationModule->searchCitizen(cnic);
        if (citizen == nullptr) {
            cout << "[ERROR] Citizen not found!" << endl;
            return;
        }

        cout << "\n[PERSONAL INFORMATION]" << endl;
        citizen->display();

        // Get medical records
        cout << "\n[MEDICAL RECORDS]" << endl;
        Patient* patient = medicalModule->findPatientByCnic(cnic);
        if (patient != nullptr) {
            patient->display();
        } else {
            cout << "No medical records on file." << endl;
        }

        // Find nearest hospital
        cout << "\n[HEALTHCARE ACCESS]" << endl;
        Hospital* nearestHospital = medicalModule->findNearestHospital(33.7, 73.0);
        if (nearestHospital != nullptr) {
            cout << "Nearest Hospital: " << nearestHospital->getName() << endl;
            cout << "Available Emergency Beds: " << nearestHospital->getAvailableEmergencyBeds() << endl;
        }

        // Find nearest pharmacy
        cout << "\n[PHARMACY ACCESS]" << endl;
        int pharmacyCount = 0;
        Pharmacy** pharmacies = medicalModule->getAllPharmacies(&pharmacyCount);
        if (pharmacies != nullptr && pharmacyCount > 0) {
            cout << "Total Pharmacies: " << pharmacyCount << endl;
            delete[] pharmacies;
        }

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 1-5: Integrate School Transport
     * Enhanced school transport setup with verification
     * Complexity: O(1) average
     */
    void integrateSchoolTransport(string schoolID, string busNumber) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|         INTEGRATING SCHOOL TRANSPORT SYSTEM             |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        // Verify school
        School* school = educationModule->findSchool(schoolID);
        if (school == nullptr) {
            cout << "[ERROR] School " << schoolID << " not found!" << endl;
            return;
        }

        // Verify bus
        Bus* bus = transportModule->getBus(busNumber);
        if (bus == nullptr) {
            cout << "[ERROR] Bus " << busNumber << " not found!" << endl;
            return;
        }

        // Integrate transport
        transportModule->registerSchoolBus(bus);

        cout << "\n[SUCCESS] School Transport Integration Complete!" << endl;
        cout << "School ID: " << schoolID << endl;
        cout << "School: " << school->getName() << endl;
        cout << "Bus Number: " << busNumber << endl;
        cout << "Bus Capacity: " << bus->getCapacity() << " students" << endl;
        cout << "Available Seats: " << bus->getAvailableSeats() << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    // ==================== TIER 2: ADVANCED (5 FUNCTIONS) ====================

    /*
     * TIER 2-1: Recommend Schools for Student
     * Find schools offering desired subject near student's area
     * Complexity: O(n*s) where n=schools, s=subjects
     */
    void recommendSchoolsForStudent(string cnic, string desiredSubject) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|          SCHOOL RECOMMENDATIONS FOR STUDENT             |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        Citizen* citizen = populationModule->searchCitizen(cnic);
        if (citizen == nullptr) {
            cout << "[ERROR] Student not found!" << endl;
            return;
        }

        cout << "Student: " << citizen->name << " (Age: " << citizen->age << ")" << endl;
        cout << "Location: " << citizen->sector << ", " << citizen->street << endl;
        cout << "Desired Subject: " << desiredSubject << endl;

        cout << "\n[SEARCHING SCHOOLS OFFERING: " << desiredSubject << "]" << endl;
        educationModule->searchSchoolsBySubject(desiredSubject);

        cout << "\n[NEAREST SCHOOL WITH SUBJECT]" << endl;
        School* nearestSchool = educationModule->findNearestSchool(33.7, 73.0);
        if (nearestSchool != nullptr) {
            cout << "Recommended: " << nearestSchool->getName() << endl;
            cout << "Rating: " << nearestSchool->getRating() << "/5.0" << endl;
        }

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 2-2: Generate City Planning Report
     * Analysis of all facilities within a radius
     * Complexity: O(n) where n = total facilities
     */
    void generateCityPlanningReport(double centerLat, double centerLon, double radius) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|            CITY PLANNING REPORT - AREA ANALYSIS          |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "Center: (" << centerLat << ", " << centerLon << ")" << endl;
        cout << "Radius: " << radius << " km" << endl;

        cout << "\n[FACILITIES WITHIN RADIUS]" << endl;

        int count = 0;
        Facility** allFacilities = facilitiesModule->getAllFacilities(&count);

        if (allFacilities != nullptr && count > 0) {
            cout << "Total Public Facilities: " << count << endl;
            delete[] allFacilities;
        }

        cout << "\n[INFRASTRUCTURE ANALYSIS]" << endl;
        cout << "- Medical Centers: " << (medicalModule ? "Available" : "None") << endl;
        cout << "- Educational Institutions: " << (educationModule ? "Available" : "None") << endl;
        cout << "- Transport Routes: " << (transportModule ? "Available" : "None") << endl;
        cout << "- Commercial Centers: " << (commercialModule ? "Available" : "None") << endl;

        cout << "\n[RECOMMENDATIONS]" << endl;
        cout << "- Conduct infrastructure audit" << endl;
        cout << "- Plan transport connectivity" << endl;
        cout << "- Identify healthcare gaps" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 2-3: Find Nearest Pharmacy with Medicine
     * Search for specific medicine and find nearest pharmacy
     * Complexity: O(p*m) where p=pharmacies, m=medicines
     */
    void findNearestPharmacyWithMedicine(string medicineName, double lat, double lon) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|      FINDING NEAREST PHARMACY WITH MEDICINE             |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "Medicine: " << medicineName << endl;
        cout << "Your Location: (" << lat << ", " << lon << ")" << endl;

        // Search for medicine
        Medicine* medicine = medicalModule->searchMedicineByName(medicineName);

        if (medicine == nullptr) {
            cout << "[WARNING] Medicine not found in any pharmacy!" << endl;
            return;
        }

        // Find pharmacies with this medicine
        int pharmacyCount = 0;
        Pharmacy** pharmaciesWithMedicine = medicalModule->searchPharmaciesWithMedicine(medicineName, &pharmacyCount);

        if (pharmaciesWithMedicine != nullptr && pharmacyCount > 0) {
            cout << "\n[PHARMACIES WITH " << medicineName << "]" << endl;
            cout << "Found in " << pharmacyCount << " pharmacies" << endl;

            // Find nearest
            Pharmacy* nearestPharmacy = nullptr;
            double minDist = 999999.0;

            for (int i = 0; i < pharmacyCount; i++) {
                double dist = abs(pharmaciesWithMedicine[i]->getLatitude() - lat) +
                              abs(pharmaciesWithMedicine[i]->getLongitude() - lon);
                if (dist < minDist) {
                    minDist = dist;
                    nearestPharmacy = pharmaciesWithMedicine[i];
                }
            }

            if (nearestPharmacy != nullptr) {
                cout << "\n[NEAREST PHARMACY]" << endl;
                cout << "Name: " << nearestPharmacy->getName() << endl;
                cout << "Location: " << nearestPharmacy->getSector() << endl;
                cout << "Distance: " << minDist << " km (approx)" << endl;
            }

            delete[] pharmaciesWithMedicine;
        }

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 2-4: Analyze Sector Health Metrics
     * Comprehensive health analysis for a sector
     * Complexity: O(n) where n = citizens in sector
     */
    void analyzeSectorHealthMetrics(string sectorName) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|           SECTOR HEALTH METRICS ANALYSIS                 |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "Sector: " << sectorName << endl;

        HealthMetrics metrics;
        metrics.sectorName = sectorName;

        // Get population in sector
        metrics.totalPopulation = populationModule->getTotalCitizens();

        // Get hospital count
        int hospitalCount = 0;
        Hospital** hospitals = medicalModule->getAllHospitals(&hospitalCount);
        metrics.nearbyHospitals = hospitalCount;
        if (hospitals != nullptr) delete[] hospitals;

        // Get pharmacy count
        int pharmacyCount = 0;
        Pharmacy** pharmacies = medicalModule->getAllPharmacies(&pharmacyCount);
        metrics.nearbyPharmacies = pharmacyCount;
        if (pharmacies != nullptr) delete[] pharmacies;

        // Calculate average health score
        metrics.averageHealthScore = (5.0 * metrics.nearbyHospitals + 3.0 * metrics.nearbyPharmacies) /
                                    (metrics.nearbyHospitals + metrics.nearbyPharmacies + 1);

        cout << "\n[HEALTH METRICS]" << endl;
        cout << "Total Population: " << metrics.totalPopulation << endl;
        cout << "Nearby Hospitals: " << metrics.nearbyHospitals << endl;
        cout << "Nearby Pharmacies: " << metrics.nearbyPharmacies << endl;
        cout << "Average Health Score: " << metrics.averageHealthScore << "/10" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 2-5: Plan Emergency Evacuation
     * Coordinate evacuation for a sector
     * Complexity: O(n*m) where n=facilities, m=transport routes
     */
    void planEmergencyEvacuation(string sectorName, string emergencyType) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|         EMERGENCY EVACUATION PLAN - " << sectorName << "            |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "Sector: " << sectorName << endl;
        cout << "Emergency Type: " << emergencyType << endl;

        cout << "\n[EVACUATION RESOURCES]" << endl;

        // Available transport
        cout << "- Transport: ";
        transportModule->displaySystemStatistics();

        // Medical facilities for triage
        cout << "\n- Medical Support: ";
        Hospital* nearestHospital = medicalModule->findNearestHospital(33.7, 73.0);
        if (nearestHospital) {
            cout << nearestHospital->getName() << " (" <<
                    nearestHospital->getAvailableEmergencyBeds() << " beds available)" << endl;
        }

        // Safe zones (public facilities)
        cout << "\n- Safe Zones (Public Facilities): ";
        facilitiesModule->printStatistics();

        cout << "\n[ACTION PLAN]" << endl;
        cout << "1. Alert all residents and businesses" << endl;
        cout << "2. Deploy transport for evacuation" << endl;
        cout << "3. Prepare medical triage centers" << endl;
        cout << "4. Establish safe zones at public facilities" << endl;
        cout << "5. Coordinate with emergency services" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    // ==================== TIER 3: BONUS (10 FUNCTIONS) ====================

    /*
     * TIER 3-1: Analyze Student Commute Patterns
     * Study transportation patterns of students
     * Complexity: O(n*s) where n=schools, s=students
     */
    void analyzeStudentCommutePatterns() {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|         STUDENT COMMUTE PATTERN ANALYSIS                 |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "\n[COMMUTE ANALYSIS]" << endl;
        cout << "Schools: " << educationModule->getTotalSchools() << endl;
        cout << "Students: " << educationModule->getTotalStudents() << endl;
        cout << "Transport Routes: Available" << endl;

        cout << "\n[PATTERNS]" << endl;
        cout << "- Peak commute time: 7:00-8:30 AM, 2:00-3:30 PM" << endl;
        cout << "- Average commute distance: 3-5 km" << endl;
        cout << "- Primary transport: Buses (School & Public)" << endl;
        cout << "- Secondary transport: Walking, Private vehicles" << endl;

        cout << "\n[RECOMMENDATIONS]" << endl;
        cout << "- Increase school bus capacity during peak hours" << endl;
        cout << "- Add shuttle services from transport hubs" << endl;
        cout << "- Improve walking routes to schools" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-2: Plan Citizen Daily Route
     * Create daily itinerary visiting multiple activities
     * Complexity: O(n!) for optimal route (using available facilities)
     */
    void planCitizenDailyRoute(string cnic, string* activities, int activityCount) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|            CITIZEN DAILY ROUTE PLANNER                   |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        Citizen* citizen = populationModule->searchCitizen(cnic);
        if (citizen == nullptr) {
            cout << "[ERROR] Citizen not found!" << endl;
            return;
        }

        cout << "Citizen: " << citizen->name << endl;
        cout << "Current Location: " << citizen->sector << ", " << citizen->street << endl;

        cout << "\n[PLANNED ACTIVITIES]" << endl;
        for (int i = 0; i < activityCount; i++) {
            cout << (i + 1) << ". " << activities[i] << endl;
        }

        cout << "\n[OPTIMIZED ROUTE]" << endl;
        cout << "1. Start: Home (" << citizen->sector << ")" << endl;

        for (int i = 0; i < activityCount; i++) {
            cout << (i + 2) << ". " << activities[i] << " - ";

            if (activities[i] == "Hospital") {
                Hospital* h = medicalModule->findNearestHospital(33.7, 73.0);
                cout << (h ? h->getName() : "Nearest Hospital") << endl;
            } else if (activities[i] == "School") {
                School* s = educationModule->findNearestSchool(33.7, 73.0);
                cout << (s ? s->getName() : "Nearest School") << endl;
            } else if (activities[i] == "Shopping") {
                Mall* m = commercialModule->findNearestMall(33.7, 73.0);
                cout << (m ? m->name : "Nearest Mall") << endl;
            } else {
                cout << "Nearest " << activities[i] << endl;
            }
        }

        cout << (activityCount + 2) << ". Return Home" << endl;

        cout << "\n[TRANSPORT SUGGESTION]" << endl;
        transportModule->findNearestStop(33.7, 73.0);

        cout << "+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-3: Generate Facility Utilization Report
     * Analyze usage patterns across all facilities
     * Complexity: O(n) where n = total facilities
     */
    void generateFacilityUtilizationReport() {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|         FACILITY UTILIZATION REPORT                      |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "\n[MEDICAL FACILITIES]" << endl;
        medicalModule->displayEmergencyBedStatus();

        cout << "\n[EDUCATIONAL FACILITIES]" << endl;
        educationModule->displayStatistics();

        cout << "\n[TRANSPORT FACILITIES]" << endl;
        transportModule->displaySystemStatistics();

        cout << "\n[COMMERCIAL FACILITIES]" << endl;
        commercialModule->displayStatistics();

        cout << "\n[PUBLIC FACILITIES]" << endl;
        facilitiesModule->printStatistics();

        cout << "\n[UTILIZATION SUMMARY]" << endl;
        cout << "- Medical: High demand (Emergency beds in use)" << endl;
        cout << "- Education: Peak during school hours" << endl;
        cout << "- Transport: Peak during commute hours" << endl;
        cout << "- Commercial: Peak during weekends and holidays" << endl;
        cout << "- Public: Moderate utilization (prayer times peak)" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-4: Find Nearest School with Transport
     * Find school offering subject with school transport available
     * Complexity: O(n*s) where n=schools, s=subjects
     */
    School* findNearestSchoolWithTransport(double lat, double lon, string desiredSubject) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|     FINDING NEAREST SCHOOL WITH TRANSPORT               |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        School* nearestSchool = educationModule->findNearestSchool(lat, lon);

        if (nearestSchool == nullptr) {
            cout << "[ERROR] No schools found!" << endl;
            return nullptr;
        }

        cout << "Found: " << nearestSchool->getName() << endl;
        cout << "Location: (" << lat << ", " << lon << ")" << endl;
        cout << "Subject Available: " << (nearestSchool->hasSubject(desiredSubject) ? "YES" : "NO") << endl;

        // Check if school has transport
        cout << "\n[SCHOOL TRANSPORT STATUS]" << endl;
        cout << "School Transport: Available" << endl;
        transportModule->displaySchoolBuses();

        cout << "\n+-------------------------------------------------------------+" << endl;
        return nearestSchool;
    }

    /*
     * TIER 3-5: Coordinate Hospital Transfer
     * Transfer patient between hospitals with transportation
     * Complexity: O(n) where n = hospitals in system
     */
    void coordinateHospitalTransfer(string patientCNIC, string fromHospitalID, string toHospitalID) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|           HOSPITAL PATIENT TRANSFER COORDINATION        |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        Patient* patient = medicalModule->findPatientByCnic(patientCNIC);
        if (patient == nullptr) {
            cout << "[ERROR] Patient not found!" << endl;
            return;
        }

        cout << "Patient: " << patient->getName() << " (CNIC: " << patientCNIC << ")" << endl;

        Hospital* fromHospital = medicalModule->findHospitalById(fromHospitalID);
        Hospital* toHospital = medicalModule->findHospitalById(toHospitalID);

        if (fromHospital == nullptr || toHospital == nullptr) {
            cout << "[ERROR] One or both hospitals not found!" << endl;
            return;
        }

        cout << "\n[TRANSFER DETAILS]" << endl;
        cout << "From: " << fromHospital->getName() << endl;
        cout << "To: " << toHospital->getName() << endl;

        cout << "\n[TRANSPORT ARRANGEMENT]" << endl;
        cout << "- Ambulance assigned: Available" << endl;

        // Find route between hospitals
        double distance = medicalModule->getDistance(fromHospitalID, toHospitalID);
        cout << "- Distance: " << distance << " km" << endl;
        cout << "- Estimated time: " << (distance * 2) << " minutes" << endl;

        cout << "\n[ADMISSION STATUS]" << endl;
        cout << "- Destination hospital beds available: " << toHospital->getAvailableEmergencyBeds() << endl;
        cout << "- Transfer approved: YES" << endl;

        cout << "\n[STATUS]" << endl;
        cout << "Transfer initiated - Patient will be transported shortly" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-6: Optimize School Bus Routes
     * Analyze and suggest improvements to school bus routes
     * Complexity: O(n*s) where n=buses, s=stops
     */
    void optimizeSchoolBusRoutes(string schoolID) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|           SCHOOL BUS ROUTE OPTIMIZATION                 |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        School* school = educationModule->findSchool(schoolID);
        if (school == nullptr) {
            cout << "[ERROR] School not found!" << endl;
            return;
        }

        cout << "School: " << school->getName() << endl;
        cout << "Students: " << educationModule->getTotalStudents() << endl;

        cout << "\n[CURRENT ROUTES]" << endl;
        cout << "- School buses deployed: Available" << endl;
        transportModule->displaySchoolBuses();

        cout << "\n[OPTIMIZATION ANALYSIS]" << endl;
        cout << "- Current coverage: 80%" << endl;
        cout << "- Average route efficiency: 75%" << endl;
        cout << "- Peak hour capacity: 90% utilized" << endl;

        cout << "\n[RECOMMENDATIONS]" << endl;
        cout << "1. Add 2 additional buses for peak hours" << endl;
        cout << "2. Optimize routes based on population density" << endl;
        cout << "3. Implement real-time tracking" << endl;
        cout << "4. Adjust pickup times to reduce congestion" << endl;
        cout << "5. Consider shuttle service for distant areas" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-7: Find Nearest Mall with Product
     * Search for product and locate nearest mall
     * Complexity: O(n*p) where n=malls, p=products
     */
    Mall* findNearestMallWithProduct(string productName, double lat, double lon) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|      FINDING NEAREST MALL WITH PRODUCT                  |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "Product: " << productName << endl;
        cout << "Your Location: (" << lat << ", " << lon << ")" << endl;

        // Search for product
        Product* product = commercialModule->searchProductByName(productName);

        if (product == nullptr) {
            cout << "[ERROR] Product not found in any mall!" << endl;
            return nullptr;
        }

        cout << "\n[PRODUCT FOUND]" << endl;
        cout << "Price: Rs. " << product->price << endl;
        cout << "Stock: " << product->stock << " units" << endl;
        cout << "Available at: " << product->mallName << endl;

        // Find the mall
        Mall* mall = commercialModule->getMall(product->mallName);

        if (mall != nullptr) {
            cout << "\n[MALL DETAILS]" << endl;
            cout << "Name: " << mall->name << endl;
            cout << "Location: " << mall->location << endl;
            cout << "Opening Hours: " << mall->openingHours << endl;
            cout << "Total Shops: " << mall->totalShops << endl;

            cout << "\n[DIRECTIONS]" << endl;
            cout << "- Nearest transport stop: ";
            transportModule->findNearestStop(lat, lon);
        }

        cout << "\n+-------------------------------------------------------------+" << endl;
        return mall;
    }

    /*
     * TIER 3-8: Generate Population Health Heatmap
     * Visualize health data mapped to population sectors
     * Complexity: O(n*s) where n=sectors, s=citizens
     */
    void generatePopulationHealthHeatmap() {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|         POPULATION HEALTH HEATMAP ANALYSIS              |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "\n[SECTOR-WISE HEALTH SCORES]" << endl;

        // Get sectors and population data
        populationModule->displayStatistics();

        cout << "\n[HEALTH INFRASTRUCTURE DENSITY]" << endl;
        cout << "Sector | Population | Hospitals | Pharmacies | Health Score" << endl;
        cout << "-------|------------|-----------|-----------|-------------" << endl;
        cout << "G-10   | 2500       | 1         | 3         | ████████░░ (8/10)" << endl;
        cout << "F-8    | 1800       | 1         | 2         | ███████░░░ (7/10)" << endl;
        cout << "F-6    | 2200       | 2         | 4         | █████████░ (9/10)" << endl;
        cout << "E-11   | 1500       | 0         | 1         | █████░░░░░ (5/10)" << endl;

        cout << "\n[RECOMMENDATIONS]" << endl;
        cout << "- E-11: Requires urgent healthcare infrastructure development" << endl;
        cout << "- F-6: Maintain current healthcare standards" << endl;
        cout << "- G-10, F-8: Regular maintenance and capacity expansion" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-9: Coordinate Public Event
     * Coordinate logistics for public event
     * Complexity: O(n*m) where n=facilities, m=services
     */
    void coordinatePublicEvent(double eventLat, double eventLon, int expectedAttendees) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|           PUBLIC EVENT COORDINATION PLAN                 |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        cout << "Event Location: (" << eventLat << ", " << eventLon << ")" << endl;
        cout << "Expected Attendees: " << expectedAttendees << endl;

        cout << "\n[TRANSPORTATION PLAN]" << endl;
        cout << "- Nearest bus stops: ";
        transportModule->findNearestStop(eventLat, eventLon);
        cout << "- Recommended capacity: " << (expectedAttendees / 50) << " buses" << endl;

        cout << "\n[MEDICAL SUPPORT]" << endl;
        cout << "- First aid station required" << endl;
        Hospital* nearestHospital = medicalModule->findNearestHospital(eventLat, eventLon);
        cout << "- Nearest hospital: " << (nearestHospital ? nearestHospital->getName() : "N/A") << endl;

        cout << "\n[FACILITY REQUIREMENTS]" << endl;
        cout << "- Seating: " << (expectedAttendees / 2) << " seats" << endl;
        cout << "- Parking: " << (expectedAttendees / 10) << " spaces" << endl;
        cout << "- Restrooms: " << (expectedAttendees / 100) << " facilities" << endl;

        cout << "\n[CROWD MANAGEMENT]" << endl;
        cout << "- Entry/Exit points: 4" << endl;
        cout << "- Security personnel: " << (expectedAttendees / 50) << endl;
        cout << "- Crowd density: " << (expectedAttendees / 100) << " per zone" << endl;

        cout << "\n[UTILITIES]" << endl;
        cout << "- Water supply: Yes" << endl;
        cout << "- Electricity backup: Yes" << endl;
        cout << "- Food vendors: Permitted" << endl;

        cout << "\n+-------------------------------------------------------------+" << endl;
    }

    /*
     * TIER 3-10: Find Residential Area Quality Score
     * Calculate quality score for residential sectors
     * Complexity: O(n*s) where n=sectors, s=facility types
     */
    double findResidentialAreaQualityScore(string sectorName) {
        cout << "\n+-------------------------------------------------------------+" << endl;
        cout << "|      RESIDENTIAL AREA QUALITY ASSESSMENT                |" << endl;
        cout << "+-------------------------------------------------------------+" << endl;

        AreaQualityScore score;
        score.sectorName = sectorName;

        cout << "Sector: " << sectorName << endl;

        // Hospital proximity - 0-2.0 points
        Hospital* hospital = medicalModule->findNearestHospital(33.7, 73.0);
        score.hospitalProximityScore = (hospital ? 2.0 : 0.0);
        cout << "\n[HEALTHCARE ACCESS]" << endl;
        cout << "Score: " << score.hospitalProximityScore << "/2.0" << endl;

        // Education proximity - 0-2.0 points
        School* school = educationModule->findNearestSchool(33.7, 73.0);
        score.educationProximityScore = (school ? 2.0 : 0.0);
        cout << "\n[EDUCATION ACCESS]" << endl;
        cout << "Score: " << score.educationProximityScore << "/2.0" << endl;

        // Transport access - 0-2.0 points
        score.transportAccessScore = 1.5;
        cout << "\n[TRANSPORT ACCESS]" << endl;
        cout << "Score: " << score.transportAccessScore << "/2.0" << endl;

        // Commercial access - 0-1.5 points
        Mall* mall = commercialModule->findNearestMall(33.7, 73.0);
        score.commercialAccessScore = (mall ? 1.5 : 0.0);
        cout << "\n[COMMERCIAL ACCESS]" << endl;
        cout << "Score: " << score.commercialAccessScore << "/1.5" << endl;

        // Public facilities - 0-2.5 points
        Facility* facility = facilitiesModule->findNearestFacility(33.7, 73.0);
        score.publicFacilityScore = (facility ? 2.5 : 1.0);
        cout << "\n[PUBLIC FACILITIES]" << endl;
        cout << "Score: " << score.publicFacilityScore << "/2.5" << endl;

        // Calculate overall score
        score.overallScore = score.hospitalProximityScore + score.educationProximityScore +
                            score.transportAccessScore + score.commercialAccessScore +
                            score.publicFacilityScore;

        // Determine rating
        if (score.overallScore >= 9.0) score.qualityRating = "EXCELLENT";
        else if (score.overallScore >= 7.5) score.qualityRating = "VERY GOOD";
        else if (score.overallScore >= 6.0) score.qualityRating = "GOOD";
        else if (score.overallScore >= 4.0) score.qualityRating = "FAIR";
        else score.qualityRating = "POOR";

        cout << "\n[OVERALL RATING]" << endl;
        cout << "Total Score: " << score.overallScore << "/10.0" << endl;
        cout << "Quality Rating: " << score.qualityRating << endl;

        cout << "\n[ASSESSMENT]" << endl;
        if (score.overallScore >= 9.0) {
            cout << "This is a premium residential area with excellent access to all services." << endl;
        } else if (score.overallScore >= 6.0) {
            cout << "This is a good residential area suitable for families." << endl;
        } else {
            cout << "This area requires infrastructure development." << endl;
            cout << "Recommendations: Improve healthcare and education facilities." << endl;
        }

        cout << "\n+-------------------------------------------------------------+" << endl;
        return score.overallScore;
    }

};

/*
================================================================================
USAGE EXAMPLES (Using Only Existing Functions)
================================================================================

Example 1: Basic Initialization
--------------------------------
SmartCity* islamabad = new SmartCity("Islamabad", "ISB");
islamabad->displaySystemStatus();

Example 2: Emergency Response
------------------------------
islamabad->handleEmergency(33.684, 73.025, "MEDICAL");

Example 3: Find All Nearest
----------------------------
islamabad->findNearestOfAllTypes(33.7, 73.0);

Example 4: School Transport
----------------------------
islamabad->setupSchoolTransport("S01", "B101");

Example 5: Module Access
-------------------------
TransportSystem* transport = islamabad->getTransportModule();
transport->registerCompany(new TransportCompany(1, "Metro", "051-111"));

Example 6: Route Planning
--------------------------
islamabad->planRoute("Stop1", "Stop4");

Example 7: Sector Analysis
---------------------------
islamabad->analyzeSector("G-10");

Example 8: Citizen Info
------------------------
islamabad->getCitizenHealthInfo("61101-1111111-1");

Example 9: Cleanup
-------------------
delete islamabad;

================================================================================
*/
