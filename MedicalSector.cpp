//#include "MedicalSector.h"
//#include <iostream>
//#include <iomanip>
//#include <limits>
//using namespace std;
//
//// Trim whitespace from string
//string trim(const string& str) {
//    size_t start = 0;
//    while (start < str.length() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')) {
//        start++;
//    }
//    size_t end = str.length();
//    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\r' || str[end - 1] == '\n')) {
//        end--;
//    }
//    return str.substr(start, end - start);
//}
//
//void printLine(int width) {
//    for (int i = 0; i < width; i++) cout << "=";
//    cout << endl;
//}
//
//void printDashedLine(int width) {
//    for (int i = 0; i < width; i++) cout << "-";
//    cout << endl;
//}
//
//void waitForEnter() {
//    cout << "\nPress Enter to continue...";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//}
//
//void displayMenu() {
//    cout << "\n";
//    printLine(60);
//    cout << "          MEDICAL SECTOR MENU" << endl;
//    printLine(60);
//    cout << " HOSPITAL OPERATIONS:" << endl;
//    cout << "  1.  Display All Hospitals & Pharmacies" << endl;
//    cout << "  2.  Display Emergency Bed Status" << endl;
//    cout << "  3.  Find Nearest Hospital" << endl;
//    cout << "  4.  Allocate Emergency Bed" << endl;
//    cout << "  5.  Get Hospital with Most Beds" << endl;
//    printDashedLine(60);
//    cout << " MEDICINE OPERATIONS:" << endl;
//    cout << "  6.  Search Medicine by Name" << endl;
//    cout << "  7.  Search Medicine by Formula" << endl;
//    cout << "  8.  Find Pharmacies with Medicine" << endl;
//    printDashedLine(60);
//    cout << " PATIENT OPERATIONS:" << endl;
//    cout << "  9.  Register New Patient" << endl;
//    cout << "  10. Find Patient by CNIC" << endl;
//    cout << "  11. Admit Patient to Hospital" << endl;
//    cout << "  12. Display All Patients" << endl;
//    cout << "  13. Display Patients at Hospital" << endl;
//    printDashedLine(60);
//    cout << " DOCTOR OPERATIONS:" << endl;
//    cout << "  14. Display All Doctors" << endl;
//    cout << "  15. Find Doctors by Specialization" << endl;
//    printDashedLine(60);
//    cout << " SYSTEM:" << endl;
//    cout << "  16. Display System Statistics" << endl;
//    cout << "  0.  Exit" << endl;
//    printLine(60);
//    cout << "Enter choice: ";
//}
//
//void displayHospitalsTable(Hospital** hospitals, int count) {
//    cout << "\n";
//    printLine(100);
//    cout << "                                HOSPITALS" << endl;
//    printLine(100);
//
//    cout << left << setw(12) << "HospitalID"
//        << setw(25) << "Name"
//        << setw(10) << "Sector"
//        << setw(15) << "EmergencyBeds"
//        << "Specializations" << endl;
//    printDashedLine(100);
//
//    for (int i = 0; i < count; i++) {
//        Hospital* h = hospitals[i];
//        cout << left << setw(12) << h->getId()
//            << setw(25) << h->getName()
//            << setw(10) << h->getSector()
//            << setw(15) << (to_string(h->getAvailableEmergencyBeds()) + "/" +
//                to_string(h->getTotalEmergencyBeds()));
//
//        int specCount = 0;
//        string* specs = h->getSpecializations(&specCount);
//        if (specs != nullptr) {
//            for (int j = 0; j < specCount; j++) {
//                cout << specs[j];
//                if (j < specCount - 1) cout << ", ";
//            }
//        }
//        cout << endl;
//        printDashedLine(100);
//    }
//}
//
//void displayPharmaciesTable(Pharmacy** pharmacies, int count) {
//    cout << "\n";
//    printLine(140);
//    cout << "                                    PHARMACIES" << endl;
//    printLine(140);
//
//    cout << left << setw(12) << "PharmacyID"
//        << setw(28) << "Pharmacy Name"
//        << setw(12) << "Sector"
//        << setw(25) << "Medicine Name"
//        << setw(20) << "Formula"
//        << "Price (Rs.)" << endl;
//    printDashedLine(140);
//
//    for (int i = 0; i < count; i++) {
//        Pharmacy* p = pharmacies[i];
//        int medCount = 0;
//        Medicine** medicines = p->getAllMedicines(&medCount);
//
//        if (medicines && medCount > 0) {
//            for (int j = 0; j < medCount; j++) {
//                if (j == 0) {
//                    cout << left << setw(12) << p->getId()
//                        << setw(28) << p->getName()
//                        << setw(12) << p->getSector();
//                }
//                else {
//                    cout << left << setw(12) << ""
//                        << setw(28) << ""
//                        << setw(12) << "";
//                }
//                cout << setw(25) << medicines[j]->getName()
//                    << setw(20) << medicines[j]->getFormula()
//                    << medicines[j]->getPrice() << endl;
//            }
//            delete[] medicines;
//        }
//        else {
//            cout << left << setw(12) << p->getId()
//                << setw(28) << p->getName()
//                << setw(12) << p->getSector()
//                << "No medicines in stock" << endl;
//        }
//        printDashedLine(140);
//    }
//}
//
//int main() {
//    printLine(100);
//    cout << "                           MEDICAL SECTOR MANAGEMENT SYSTEM" << endl;
//    printLine(100);
//
//    MedicalSector sector;
//
//    // Load data from CSV files
//    cout << "\nLoading data from CSV files..." << endl;
//    printDashedLine(100);
//
//    if (sector.loadHospitalsFromCSV("hospitals.csv")) {
//        cout << " Hospitals loaded successfully" << endl;
//    }
//    else {
//        cout << " Failed to load hospitals.csv" << endl;
//    }
//
//    if (sector.loadPharmaciesFromCSV("pharmacies.csv")) {
//        cout << " Pharmacies and medicines loaded successfully" << endl;
//    }
//    else {
//        cout << " Failed to load pharmacies.csv" << endl;
//    }
//
//    // Connect hospitals
//    cout << "\nBuilding hospital network..." << endl;
//    sector.connectHospitals("H01", "H02", 5.5);
//    sector.connectHospitals("H02", "H03", 8.2);
//    sector.connectHospitals("H03", "H04", 6.7);
//    sector.connectHospitals("H01", "H03", 12.0);
//    sector.connectHospitals("H02", "H04", 10.5);
//    sector.connectHospitals("H04", "H05", 7.3);
//
//    // Register doctors
//    cout << "\nRegistering doctors..." << endl;
//    Hospital* pims = sector.findNearestHospital(33.706, 73.055);
//    Hospital* shifa = sector.findNearestHospital(33.684, 73.086);
//    Hospital* maroof = sector.findNearestHospital(33.691, 73.019);
//
//    if (pims) {
//        sector.registerDoctor(new Doctor("D001", "Dr. Ahmed Khan", "Cardiology", pims));
//        sector.registerDoctor(new Doctor("D002", "Dr. Sarah Ali", "General", pims));
//    }
//    if (shifa) {
//        sector.registerDoctor(new Doctor("D003", "Dr. Hassan Raza", "Oncology", shifa));
//        sector.registerDoctor(new Doctor("D004", "Dr. Fatima Noor", "Surgery", shifa));
//    }
//    if (maroof) {
//        sector.registerDoctor(new Doctor("D005", "Dr. Bilal Ahmed", "Orthopedics", maroof));
//    }
//
//    // Register patients
//    cout << "\nRegistering sample patients..." << endl;
//    sector.registerPatient(new Patient("PT001", "Ali Hassan", 35, "61101-1234567-1", "Chest Pain"));
//    sector.registerPatient(new Patient("PT002", "Ayesha Malik", 28, "61101-2345678-2", "Fracture"));
//    sector.registerPatient(new Patient("PT003", "Ahmed Raza", 52, "61101-3456789-3", "Diabetes"));
//    sector.registerPatient(new Patient("PT004", "Fatima Zahra", 41, "61101-4567890-4", "Flu"));
//    sector.registerPatient(new Patient("PT005", "Hamza Noor", 19, "61101-5678901-5", "Sports Injury"));
//
//    cout << "\n System initialized successfully!" << endl;
//    sector.displayStatistics();
//
//    int choice;
//    do {
//        displayMenu();
//        cin >> choice;
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//        switch (choice) {
//        case 1: {
//            int hospCount = 0, pharmCount = 0;
//            Hospital** hospitals = sector.getAllHospitals(&hospCount);
//            Pharmacy** pharmacies = sector.getAllPharmacies(&pharmCount);
//            if (hospitals) {
//                displayHospitalsTable(hospitals, hospCount);
//                delete[] hospitals;
//            }
//            if (pharmacies) {
//                displayPharmaciesTable(pharmacies, pharmCount);
//                delete[] pharmacies;
//            }
//            break;
//        }
//
//        case 2:
//            sector.displayEmergencyBedStatus();
//            break;
//
//        case 3: {
//            double lat, lon;
//            cout << "\nEnter latitude: ";
//            cin >> lat;
//            cout << "Enter longitude: ";
//            cin >> lon;
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//            Hospital* nearest = sector.findNearestHospital(lat, lon);
//            if (nearest) {
//                printLine(70);
//                cout << "NEAREST HOSPITAL" << endl;
//                printLine(70);
//                cout << left << setw(25) << "Name:" << nearest->getName() << endl;
//                cout << left << setw(25) << "Sector:" << nearest->getSector() << endl;
//                cout << left << setw(25) << "Location:" << "(" << nearest->getLatitude() << ", " << nearest->getLongitude() << ")" << endl;
//                cout << left << setw(25) << "Available Beds:" << nearest->getAvailableEmergencyBeds() << "/" << nearest->getTotalEmergencyBeds() << endl;
//                printLine(70);
//            }
//            break;
//        }
//
//        case 4: {
//            double lat, lon;
//            cout << "\nEnter patient latitude: ";
//            cin >> lat;
//            cout << "Enter patient longitude: ";
//            cin >> lon;
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//            Hospital* allocated = sector.allocateEmergencyBed(lat, lon);
//            if (allocated) {
//                printLine(70);
//                cout << " BED ALLOCATED!" << endl;
//                printLine(70);
//                cout << "Hospital: " << allocated->getName() << endl;
//                cout << "Remaining: " << allocated->getAvailableEmergencyBeds() << "/" << allocated->getTotalEmergencyBeds() << endl;
//                printLine(70);
//            }
//            break;
//        }
//
//        case 5: {
//            Hospital* mostBeds = sector.getHospitalWithMostBeds();
//            if (mostBeds) {
//                printLine(70);
//                cout << "HOSPITAL WITH MOST BEDS" << endl;
//                printLine(70);
//                cout << left << setw(25) << "Name:" << mostBeds->getName() << endl;
//                cout << left << setw(25) << "Available:" << mostBeds->getAvailableEmergencyBeds() << "/" << mostBeds->getTotalEmergencyBeds() << endl;
//                printLine(70);
//            }
//            break;
//        }
//
//        case 6: {
//            cout << "\nEnter medicine name: ";
//            string name;
//            getline(cin, name);
//            Medicine* med = sector.searchMedicineByName(name);
//            if (med) {
//                printLine(70);
//                cout << " MEDICINE FOUND" << endl;
//                printLine(70);
//                cout << left << setw(20) << "Name:" << med->getName() << endl;
//                cout << left << setw(20) << "Formula:" << med->getFormula() << endl;
//                cout << left << setw(20) << "Price:" << "Rs. " << med->getPrice() << endl;
//                printLine(70);
//            }
//            break;
//        }
//
//        case 7: {
//            cout << "\nEnter formula: ";
//            string formula;
//            getline(cin, formula);
//            formula = trim(formula);
//            Medicine* med = sector.searchMedicineByFormula(formula);
//            if (med) {
//                printLine(70);
//                cout << " MEDICINE FOUND" << endl;
//                printLine(70);
//                cout << left << setw(20) << "Name:" << med->getName() << endl;
//                cout << left << setw(20) << "Formula:" << med->getFormula() << endl;
//                cout << left << setw(20) << "Price:" << "Rs. " << med->getPrice() << endl;
//                printLine(70);
//            }
//            break;
//        }
//
//        case 8: {
//            cout << "\nEnter medicine name: ";
//            string name;
//            getline(cin, name);
//            int count = 0;
//            Pharmacy** pharmacies = sector.searchPharmaciesWithMedicine(name, &count);
//            if (pharmacies) {
//                printLine(70);
//                cout << "Pharmacies with " << name << " (" << count << " found)" << endl;
//                printLine(70);
//                for (int i = 0; i < count; i++) {
//                    cout << (i + 1) << ". " << pharmacies[i]->getName() << " (" << pharmacies[i]->getSector() << ")" << endl;
//                }
//                printLine(70);
//                delete[] pharmacies;
//            }
//            break;
//        }
//
//        case 9: {
//            string id, name, cnic, ailment;
//            int age;
//            cout << "\nPatient ID: ";
//            getline(cin, id);
//            cout << "Name: ";
//            getline(cin, name);
//            cout << "Age: ";
//            cin >> age;
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "CNIC: ";
//            getline(cin, cnic);
//            cout << "Ailment: ";
//            getline(cin, ailment);
//
//            sector.registerPatient(new Patient(id, name, age, cnic, ailment));
//            cout << "\n✓ Patient registered: " << id << endl;
//            break;
//        }
//
//        case 10: {
//            cout << "\nEnter CNIC: ";
//            string cnic;
//            getline(cin, cnic);
//            Patient* patient = sector.findPatientByCnic(cnic);
//            if (patient) {
//                printLine(70);
//                cout << " PATIENT FOUND" << endl;
//                printLine(70);
//                patient->display();
//                printLine(70);
//            }
//            break;
//        }
//
//        case 11: {
//            string cnic;
//            double lat, lon;
//            cout << "\nEnter patient CNIC: ";
//            getline(cin, cnic);
//
//            Patient* patient = sector.findPatientByCnic(cnic);
//            if (!patient) {
//                cout << "Patient not found!" << endl;
//                break;
//            }
//
//            cout << "Patient location - Latitude: ";
//            cin >> lat;
//            cout << "Longitude: ";
//            cin >> lon;
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//            if (sector.admitPatient(cnic, lat, lon)) {
//                printLine(70);
//                cout << "PATIENT ADMITTED" << endl;
//                printLine(70);
//                cout << "Patient: " << patient->getName() << endl;
//                cout << "Hospital: " << patient->getAdmittedHospital()->getName() << endl;
//                printLine(70);
//            }
//            break;
//        }
//
//        case 12:
//            sector.displayAllPatients();
//            break;
//
//        case 13: {
//            cout << "\nEnter hospital ID (H01-H05): ";
//            string hospId;
//            getline(cin, hospId);
//
//            Hospital* hospital = sector.findHospitalById(hospId);
//            if (hospital) {
//                int count = 0;
//                Patient** patients = sector.getPatientsAtHospital(hospital, &count);
//                if (patients && count > 0) {
//                    printLine(70);
//                    cout << "PATIENTS AT " << hospital->getName() << endl;
//                    printLine(70);
//                    for (int i = 0; i < count; i++) {
//                        patients[i]->display();
//                        printDashedLine(70);
//                    }
//                    delete[] patients;
//                }
//                else {
//                    cout << "No patients at this hospital." << endl;
//                }
//            }
//            break;
//        }
//
//        case 14:
//            sector.displayAllDoctors();
//            break;
//
//        case 15: {
//            cout << "\nEnter specialization: ";
//            string spec;
//            getline(cin, spec);
//            int count = 0;
//            Doctor** doctors = sector.findDoctorsBySpecialization(spec, &count);
//            if (doctors && count > 0) {
//                printLine(70);
//                cout << "DOCTORS: " << spec << " (" << count << " found)" << endl;
//                printLine(70);
//                for (int i = 0; i < count; i++) {
//                    cout << (i + 1) << ". " << doctors[i]->getName() << " at " << doctors[i]->getAssignedHospital()->getName() << endl;
//                }
//                printLine(70);
//                delete[] doctors;
//            }
//            break;
//        }
//
//        case 16:
//            sector.displayStatistics();
//            break;
//
//        case 0:
//            printLine(70);
//            cout << "         Thank you!" << endl;
//            printLine(70);
//            break;
//
//        default:
//            cout << "\n Invalid choice!" << endl;
//        }
//
//        if (choice != 0) {
//            waitForEnter();
//        }
//
//    } while (choice != 0);
//
//    return 0;
//}