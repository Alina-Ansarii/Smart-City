////#pragma once
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "PopulationSector.h"
//using namespace std;
//
//void printMenu() {
//    cout << "\n======================================================" << endl;
//    cout << "      POPULATION & HOUSING SECTOR - SMART CITY" << endl;
//    cout << "======================================================" << endl;
//    cout << "HIERARCHY MANAGEMENT:" << endl;
//    cout << "1.  Add Sector" << endl;
//    cout << "2.  Add Street to Sector" << endl;
//    cout << "3.  Add House to Street" << endl;
//    cout << "4.  Add Family to House" << endl;
//    cout << "\nCITIZEN MANAGEMENT:" << endl;
//    cout << "5.  Register Citizen" << endl;
//    cout << "6.  Add Family Member (with Family Tree)" << endl;
//    cout << "7.  Search Citizen by CNIC" << endl;
//    cout << "\nREPORTS:" << endl;
//    cout << "8.  Age Distribution Report" << endl;
//    cout << "9.  Gender Ratio Report" << endl;
//    cout << "10. Occupation Summary" << endl;
//    cout << "11. Population Density Report" << endl;
//    cout << "12. Comprehensive Report (All)" << endl;
//    cout << "\nDISPLAY:" << endl;
//    cout << "13. Display Islamabad Hierarchy" << endl;
//    cout << "14. Display All Citizens" << endl;
//    cout << "15. Display Statistics" << endl;
//    cout << "\nDATA:" << endl;
//    cout << "16. Load Sample Data" << endl;
//    cout << "17. Load Data from CSV File" << endl;
//    cout << "18. BONUS - Heatmap Logic" << endl;
//    cout << "0.  Exit" << endl;
//    cout << "======================================================" << endl;
//    cout << "Enter your choice: ";
//}
//
//// Load sample data based on project PDF
//void loadSampleData(PopulationSector& sector) {
//    cout << "\nLoading sample data from project..." << endl;
//
//    // Add Sectors
//    sector.addSector("G-10");
//    sector.addSector("F-8");
//    sector.addSector("G-9");
//    sector.addSector("F-6");
//    sector.addSector("Blue Area");
//    sector.addSector("I-8");
//
//    // Add Streets
//    sector.addStreet("G-10", "Street 22");
//    sector.addStreet("G-10", "Street 5");
//    sector.addStreet("F-8", "Street 5");
//    sector.addStreet("F-8", "Street 12");
//    sector.addStreet("G-9", "Street 17");
//    sector.addStreet("F-6", "Street 9");
//    sector.addStreet("Blue Area", "Street 1");
//    sector.addStreet("I-8", "Street 3");
//
//    // Add Houses
//    sector.addHouse("G-10", "Street 22", 180);
//    sector.addHouse("G-10", "Street 22", 181);
//    sector.addHouse("F-8", "Street 5", 12);
//    sector.addHouse("G-9", "Street 17", 90);
//    sector.addHouse("F-6", "Street 9", 33);
//    sector.addHouse("Blue Area", "Street 1", 5);
//    sector.addHouse("I-8", "Street 3", 25);
//
//    // Add Families
//    sector.addFamily("G-10", "Street 22", 180, "Khan Family");
//    sector.addFamily("F-8", "Street 5", 12, "Zahra Family");
//    sector.addFamily("G-9", "Street 17", 90, "Raza Family");
//    sector.addFamily("F-6", "Street 9", 33, "Malik Family");
//    sector.addFamily("Blue Area", "Street 1", 5, "Noor Family");
//
//    // Register Citizens from Project Sample Data
//    sector.registerCitizen("61101-1111111-1", "Ahmed Khan", 45, 'M', "Engineer",
//        "G-10", "Street 22", 180, "Master", 150000);
//
//    sector.registerCitizen("61101-2222222-2", "Fatima Zahra", 38, 'F', "Teacher",
//        "F-8", "Street 5", 12, "Bachelor", 80000);
//
//    sector.registerCitizen("61101-3333333-3", "Ali Raza", 29, 'M', "Doctor",
//        "G-9", "Street 17", 90, "PhD", 200000);
//
//    sector.registerCitizen("61101-4444444-4", "Sara Malik", 22, 'F', "Student",
//        "F-6", "Street 9", 33, "Bachelor", 0);
//
//    sector.registerCitizen("61101-5555555-5", "Hamza Noor", 50, 'M', "Business",
//        "Blue Area", "Street 1", 5, "Bachelor", 300000);
//
//    // Add more diverse citizens for better reports
//    sector.registerCitizen("61101-6666666-6", "Ayesha Ahmed", 35, 'F', "Software Engineer",
//        "G-10", "Street 22", 180, "Master", 180000);
//
//    sector.registerCitizen("61101-7777777-7", "Usman Ali", 42, 'M', "Businessman",
//        "F-8", "Street 5", 12, "Bachelor", 250000);
//
//    sector.registerCitizen("61101-8888888-8", "Zainab Hassan", 28, 'F', "Nurse",
//        "G-9", "Street 17", 90, "Bachelor", 70000);
//
//    sector.registerCitizen("61101-9999999-9", "Hassan Iqbal", 19, 'M', "Student",
//        "F-6", "Street 9", 33, "Secondary", 0);
//
//    sector.registerCitizen("61101-1010101-0", "Mariam Siddiqui", 65, 'F', "Retired",
//        "Blue Area", "Street 1", 5, "Master", 50000);
//
//    sector.registerCitizen("61101-1111111-2", "Bilal Khan", 15, 'M', "Student",
//        "G-10", "Street 22", 180, "Secondary", 0);
//
//    sector.registerCitizen("61101-2222222-3", "Hira Zahra", 10, 'F', "Student",
//        "F-8", "Street 5", 12, "Primary", 0);
//
//    sector.registerCitizen("61101-3333333-4", "Imran Raza", 55, 'M', "Accountant",
//        "G-9", "Street 17", 90, "Bachelor", 120000);
//
//    sector.registerCitizen("61101-4444444-5", "Sana Malik", 48, 'F', "Teacher",
//        "F-6", "Street 9", 33, "Master", 90000);
//
//    sector.registerCitizen("61101-5555555-6", "Farhan Noor", 23, 'M', "Engineer",
//        "Blue Area", "Street 1", 5, "Bachelor", 100000);
//
//    cout << "\nSample data loaded successfully!" << endl;
//    cout << "- 6 Sectors added" << endl;
//    cout << "- 8 Streets added" << endl;
//    cout << "- 7 Houses added" << endl;
//    cout << "- 5 Families added" << endl;
//    cout << "- 15 Citizens registered" << endl;
//}
//
//// ==================== CSV FILE LOADING ====================
//
//
//// Helper function to trim whitespace from string
//string trim(const string& str) {
//    size_t first = str.find_first_not_of(" \t\r\n");
//    if (first == string::npos) return "";
//    size_t last = str.find_last_not_of(" \t\r\n");
//    return str.substr(first, (last - first + 1));
//}
//
//// Load population data from CSV file
//// Expected format: CNIC,Name,Age,Sector,Street,HouseNo,Occupation
//bool loadFromCSV(PopulationSector& sector, const string& filename) {
//    cout << "\nLoading data from CSV file: " << filename << endl;
//
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Error: Could not open file '" << filename << "'" << endl;
//        cout << "Make sure the file exists in the same directory as the program." << endl;
//        return false;
//    }
//
//    string line;
//    int lineNumber = 0;
//    int citizensLoaded = 0;
//    int sectorsAdded = 0;
//    int streetsAdded = 0;
//    int housesAdded = 0;
//
//    // Track what's been added to avoid duplicates
//    string addedSectors[100];
//    int sectorCount = 0;
//    string addedStreets[200];
//    int streetCount = 0;
//    string addedHouses[500];
//    int houseCount = 0;
//
//    // Read header line
//    if (getline(file, line)) {
//        lineNumber++;
//        cout << "Reading CSV header: " << trim(line) << endl;
//    }
//
//    // Read data lines
//    while (getline(file, line)) {
//        lineNumber++;
//
//        // Skip empty lines
//        if (trim(line).empty()) continue;
//
//        stringstream ss(line);
//        string cnic, name, ageStr, sectorName, streetStr, houseStr, occupation;
//
//        // Parse CSV: CNIC,Name,Age,Sector,Street,HouseNo,Occupation
//        getline(ss, cnic, ',');
//        getline(ss, name, ',');
//        getline(ss, ageStr, ',');
//        getline(ss, sectorName, ',');
//        getline(ss, streetStr, ',');
//        getline(ss, houseStr, ',');
//        getline(ss, occupation, ',');
//
//        // Trim all fields
//        cnic = trim(cnic);
//        name = trim(name);
//        ageStr = trim(ageStr);
//        sectorName = trim(sectorName);
//        streetStr = trim(streetStr);
//        houseStr = trim(houseStr);
//        occupation = trim(occupation);
//
//        // Validate critical fields
//        if (cnic.empty() || name.empty() || sectorName.empty() || streetStr.empty()) {
//            cout << "Warning: Line " << lineNumber << " has missing critical fields, skipping..." << endl;
//            continue;
//        }
//
//        // Parse numbers
//        int age = 0;
//        int houseNumber = 0;
//        try {
//            age = stoi(ageStr);
//            houseNumber = stoi(houseStr);
//        }
//        catch (...) {
//            cout << "Warning: Error parsing numbers on line " << lineNumber << ", skipping..." << endl;
//            continue;
//        }
//
//        // Build full street name (e.g., "Street 22")
//        string streetName = "Street " + streetStr;
//
//        // Default values for missing fields
//        char gender = 'M';  // Default gender
//        string education = "None";
//        int income = 0;
//
//        // Add sector if not already added
//        string sectorKey = sectorName;
//        bool sectorExists = false;
//        for (int i = 0; i < sectorCount; i++) {
//            if (addedSectors[i] == sectorKey) {
//                sectorExists = true;
//                break;
//            }
//        }
//        if (!sectorExists) {
//            if (sector.addSector(sectorName)) {
//                addedSectors[sectorCount++] = sectorKey;
//                sectorsAdded++;
//            }
//        }
//
//        // Add street if not already added
//        string streetKey = sectorName + "|" + streetName;
//        bool streetExists = false;
//        for (int i = 0; i < streetCount; i++) {
//            if (addedStreets[i] == streetKey) {
//                streetExists = true;
//                break;
//            }
//        }
//        if (!streetExists) {
//            if (sector.addStreet(sectorName, streetName)) {
//                addedStreets[streetCount++] = streetKey;
//                streetsAdded++;
//            }
//        }
//
//        // Add house if not already added
//        string houseKey = sectorName + "|" + streetName + "|" + to_string(houseNumber);
//        bool houseExists = false;
//        for (int i = 0; i < houseCount; i++) {
//            if (addedHouses[i] == houseKey) {
//                houseExists = true;
//                break;
//            }
//        }
//        if (!houseExists) {
//            if (sector.addHouse(sectorName, streetName, houseNumber)) {
//                addedHouses[houseCount++] = houseKey;
//                housesAdded++;
//            }
//        }
//
//        // Register citizen
//        if (sector.registerCitizen(cnic, name, age, gender, occupation,
//            sectorName, streetName, houseNumber,
//            education, income)) {
//            citizensLoaded++;
//        }
//    }
//
//    file.close();
//
//    cout << "\n========== CSV Loading Complete ==========" << endl;
//    cout << "Sectors added: " << sectorsAdded << endl;
//    cout << "Streets added: " << streetsAdded << endl;
//    cout << "Houses added: " << housesAdded << endl;
//    cout << "Citizens loaded: " << citizensLoaded << endl;
//    cout << "Total lines processed: " << (lineNumber - 1) << endl;
//    cout << "=========================================\n" << endl;
//
//    return citizensLoaded > 0;
//}
//
//int main() {
//    PopulationSector populationSector;
//    int choice;
//
//    do {
//        printMenu();
//        cin >> choice;
//        cin.ignore(); // Clear newline from buffer
//
//        switch (choice) {
//        case 1: {
//            // Add Sector
//            string sectorName;
//
//            cout << "\n--- Add Sector ---" << endl;
//            cout << "Enter Sector Name (e.g., G-10, F-8): ";
//            getline(cin, sectorName);
//
//            populationSector.addSector(sectorName);
//            break;
//        }
//
//        case 2: {
//            // Add Street
//            string sectorName, streetName;
//
//            cout << "\n--- Add Street to Sector ---" << endl;
//            cout << "Enter Sector Name: ";
//            getline(cin, sectorName);
//
//            cout << "Enter Street Name (e.g., Street 22): ";
//            getline(cin, streetName);
//
//            populationSector.addStreet(sectorName, streetName);
//            break;
//        }
//
//        case 3: {
//            // Add House
//            string sectorName, streetName;
//            int houseNumber;
//
//            cout << "\n--- Add House to Street ---" << endl;
//            cout << "Enter Sector Name: ";
//            getline(cin, sectorName);
//
//            cout << "Enter Street Name: ";
//            getline(cin, streetName);
//
//            cout << "Enter House Number: ";
//            cin >> houseNumber;
//
//            populationSector.addHouse(sectorName, streetName, houseNumber);
//            break;
//        }
//
//        case 4: {
//            // Add Family
//            string sectorName, streetName, familyName;
//            int houseNumber;
//
//            cout << "\n--- Add Family to House ---" << endl;
//            cout << "Enter Sector Name: ";
//            getline(cin, sectorName);
//
//            cout << "Enter Street Name: ";
//            getline(cin, streetName);
//
//            cout << "Enter House Number: ";
//            cin >> houseNumber;
//            cin.ignore();
//
//            cout << "Enter Family Name: ";
//            getline(cin, familyName);
//
//            populationSector.addFamily(sectorName, streetName, houseNumber, familyName);
//            break;
//        }
//
//        case 5: {
//            // Register Citizen
//            string cnic, name, occupation, sector, street, education;
//            int age, houseNumber, income;
//            char gender;
//
//            cout << "\n--- Register Citizen ---" << endl;
//            cout << "Enter CNIC (e.g., 61101-1111111-1): ";
//            getline(cin, cnic);
//
//            cout << "Enter Name: ";
//            getline(cin, name);
//
//            cout << "Enter Age: ";
//            cin >> age;
//
//            cout << "Enter Gender (M/F): ";
//            cin >> gender;
//            cin.ignore();
//
//            cout << "Enter Occupation: ";
//            getline(cin, occupation);
//
//            cout << "Enter Sector: ";
//            getline(cin, sector);
//
//            cout << "Enter Street: ";
//            getline(cin, street);
//
//            cout << "Enter House Number: ";
//            cin >> houseNumber;
//            cin.ignore();
//
//            cout << "Enter Education Level (Primary/Secondary/Bachelor/Master/PhD/None): ";
//            getline(cin, education);
//
//            cout << "Enter Monthly Income (PKR): ";
//            cin >> income;
//
//            populationSector.registerCitizen(cnic, name, age, gender, occupation,
//                sector, street, houseNumber, education, income);
//            break;
//        }
//
//        case 6: {
//            // Add Family Member with Family Tree
//            int familyId;
//            string parentCnic, cnic, name, occupation, education;
//            int age, income;
//            char gender;
//
//            cout << "\n--- Add Family Member (Family Tree) ---" << endl;
//            cout << "Enter Family ID: ";
//            cin >> familyId;
//            cin.ignore();
//
//            cout << "Enter Parent CNIC (leave empty if head of family): ";
//            getline(cin, parentCnic);
//
//            cout << "Enter CNIC: ";
//            getline(cin, cnic);
//
//            cout << "Enter Name: ";
//            getline(cin, name);
//
//            cout << "Enter Age: ";
//            cin >> age;
//
//            cout << "Enter Gender (M/F): ";
//            cin >> gender;
//            cin.ignore();
//
//            cout << "Enter Occupation: ";
//            getline(cin, occupation);
//
//            cout << "Enter Education: ";
//            getline(cin, education);
//
//            cout << "Enter Income: ";
//            cin >> income;
//
//            populationSector.addFamilyMember(familyId, parentCnic, cnic, name,
//                age, gender, occupation, education, income);
//            break;
//        }
//
//        case 7: {
//            // Search Citizen by CNIC
//            string cnic;
//
//            cout << "\n--- Search Citizen by CNIC ---" << endl;
//            cout << "Enter CNIC: ";
//            getline(cin, cnic);
//
//            populationSector.searchCitizen(cnic);
//            break;
//        }
//
//        case 8: {
//            // Age Distribution Report
//            populationSector.generateAgeDistributionReport();
//            break;
//        }
//
//        case 9: {
//            // Gender Ratio Report
//            populationSector.generateGenderRatioReport();
//            break;
//        }
//
//        case 10: {
//            // Occupation Summary
//            populationSector.generateOccupationSummary();
//            break;
//        }
//
//        case 11: {
//            // Population Density Report
//            populationSector.generatePopulationDensityReport();
//            break;
//        }
//
//        case 12: {
//            // Comprehensive Report
//            populationSector.generateComprehensiveReport();
//            break;
//        }
//
//        case 13: {
//            // Display Hierarchy
//            populationSector.displayIslamabadHierarchy();
//            break;
//        }
//
//        case 14: {
//            // Display All Citizens
//            populationSector.displayAllCitizens();
//            break;
//        }
//
//        case 15: {
//            // Display Statistics
//            populationSector.displayStatistics();
//            break;
//        }
//
//
//        case 16: {
//            // Load Sample Data
//            loadSampleData(populationSector);
//            break;
//        }
//
//        case 17: {
//            // Load Data from CSV File
//            string filename;
//
//            cout << "\n--- Load Data from CSV File ---" << endl;
//            cout << "Enter CSV filename (e.g., population.csv): ";
//            getline(cin, filename);
//
//            loadFromCSV(populationSector, filename);
//            break;
//        }
//
//        case 18: {
//            populationSector.generatePopulationHeatmap();
//            break;
//        }
//        case 0: {
//            cout << "\nExiting Population & Housing Sector Module..." << endl;
//            cout << "Thank you for using Smart City!" << endl;
//            break;
//        }
//
//        default: {
//            cout << "\nInvalid choice! Please try again." << endl;
//            break;
//        }
//        }
//
//        if (choice != 0) {
//            cout << "\nPress Enter to continue...";
//            cin.get();
//        }
//
//    } while (choice != 0);
//
//    return 0;
//}