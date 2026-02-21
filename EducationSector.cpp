//#define _CRT_SECURE_NO_WARNINGS  // Disable fopen deprecation warning
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "EducationSector.h"
//using namespace std;
//
//void printMenu() {
//    cout << "\n==========================================================" << endl;
//    cout << "      EDUCATION SECTOR - SMART CITY MANAGEMENT" << endl;
//    cout << "==========================================================" << endl;
//    cout << "SCHOOL MANAGEMENT:" << endl;
//    cout << "1.  Register School" << endl;
//    cout << "2.  Register Department" << endl;
//    cout << "3.  Register Class" << endl;
//    cout << "4.  Add Subject to School" << endl;
//    cout << "\nSTUDENT & FACULTY MANAGEMENT:" << endl;
//    cout << "5.  Register Student" << endl;
//    cout << "6.  Register Faculty" << endl;
//    cout << "7.  Add Subject to Student" << endl;
//    cout << "\nSEARCH OPERATIONS:" << endl;
//    cout << "8.  Find School by ID" << endl;
//    cout << "9.  Find Student by ID" << endl;
//    cout << "10. Find Faculty by ID" << endl;
//    cout << "11. Search Schools by Subject" << endl;
//    cout << "12. Search Schools by Sector" << endl;
//    cout << "13. Find Nearest School (GPS)" << endl;
//    cout << "\nRANKING & REPORTS:" << endl;
//    cout << "14. Display Top N Ranked Schools" << endl;
//    cout << "15. Display All School Rankings" << endl;
//    cout << "16. Display Schools Above Rating" << endl;
//    cout << "\nDISPLAY & HIERARCHY:" << endl;
//    cout << "17. Display School Hierarchy (Tree Structure)" << endl;
//    cout << "18. Display All Schools" << endl;
//    cout << "19. Display System Statistics" << endl;
//    cout << "\nDATA LOADING:" << endl;
//    cout << "20. Load Sample Data (From Project)" << endl;
//    cout << "21. Load Schools from CSV File" << endl;
//    cout << "0.  Exit" << endl;
//    cout << "==========================================================" << endl;
//    cout << "Enter your choice: ";
//}
//
//// ==================== SAMPLE DATA LOADING ====================
//void loadSampleData(EducationSystem& eduSystem) {
//    cout << "\nLoading sample data from project specification..." << endl;
//
//    // Register Schools from Project PDF (Page 9)
//    eduSystem.registerSchool("S01", "City School", "G-10", 33.684, 73.025, 4.5);
//    eduSystem.registerSchool("S02", "Allied School", "F-8", 33.691, 73.019, 4.0);
//    eduSystem.registerSchool("S03", "Beaconhouse", "F-6", 33.706, 73.055, 4.7);
//    eduSystem.registerSchool("S04", "Iqra Academy", "G-9", 33.700, 73.030, 4.2);
//    eduSystem.registerSchool("S05", "Roots Millennium", "F-7", 33.721, 73.052, 4.8);
//
//    // Find and add subjects to schools
//    School* citySchool = eduSystem.findSchool("S01");
//    if (citySchool) {
//        citySchool->addSubject("Math");
//        citySchool->addSubject("Physics");
//        citySchool->addSubject("English");
//    }
//
//    School* alliedSchool = eduSystem.findSchool("S02");
//    if (alliedSchool) {
//        alliedSchool->addSubject("CS");
//        alliedSchool->addSubject("Math");
//        alliedSchool->addSubject("Urdu");
//    }
//
//    School* beaconhouse = eduSystem.findSchool("S03");
//    if (beaconhouse) {
//        beaconhouse->addSubject("Bio");
//        beaconhouse->addSubject("Chem");
//        beaconhouse->addSubject("English");
//    }
//
//    School* iqra = eduSystem.findSchool("S04");
//    if (iqra) {
//        iqra->addSubject("Islamiat");
//        iqra->addSubject("Arabic");
//    }
//
//    School* roots = eduSystem.findSchool("S05");
//    if (roots) {
//        roots->addSubject("AI");
//        roots->addSubject("Robotics");
//        roots->addSubject("Math");
//    }
//
//    // Register Departments
//    eduSystem.registerDepartment("S01", "D01", "Computer Science");
//    eduSystem.registerDepartment("S01", "D02", "Mathematics");
//    eduSystem.registerDepartment("S01", "D03", "Physics");
//
//    eduSystem.registerDepartment("S02", "D04", "Computer Science");
//    eduSystem.registerDepartment("S02", "D05", "Languages");
//
//    eduSystem.registerDepartment("S03", "D06", "Sciences");
//    eduSystem.registerDepartment("S03", "D07", "Humanities");
//
//    eduSystem.registerDepartment("S04", "D08", "Islamic Studies");
//    eduSystem.registerDepartment("S05", "D09", "Technology");
//
//    // Register Classes
//    eduSystem.registerClass("S01", "D01", "C01", "CS-101");
//    eduSystem.registerClass("S01", "D01", "C02", "CS-102");
//    eduSystem.registerClass("S01", "D02", "C03", "Math-101");
//    eduSystem.registerClass("S01", "D03", "C04", "Physics-101");
//
//    eduSystem.registerClass("S02", "D04", "C05", "CS-A");
//    eduSystem.registerClass("S02", "D05", "C06", "Urdu-A");
//
//    eduSystem.registerClass("S03", "D06", "C07", "Biology-A");
//    eduSystem.registerClass("S03", "D07", "C08", "English-A");
//
//    eduSystem.registerClass("S04", "D08", "C09", "Islamiat-A");
//    eduSystem.registerClass("S05", "D09", "C10", "AI-101");
//
//    // Register Faculty
//    eduSystem.registerFaculty("F001", "Dr. Ahmed Hassan", "Data Structures", 45,
//        "PhD Computer Science", 15, "S01", "D01");
//    eduSystem.registerFaculty("F002", "Prof. Fatima Ali", "Mathematics", 50,
//        "PhD Mathematics", 20, "S01", "D02");
//    eduSystem.registerFaculty("F003", "Dr. Usman Khan", "Physics", 42,
//        "PhD Physics", 12, "S01", "D03");
//    eduSystem.registerFaculty("F004", "Ms. Ayesha Malik", "Computer Science", 35,
//        "MS Computer Science", 8, "S02", "D04");
//    eduSystem.registerFaculty("F005", "Mr. Hassan Raza", "Artificial Intelligence", 38,
//        "PhD AI", 10, "S05", "D09");
//
//    // Register Students
//    eduSystem.registerStudent("S01", "D01", "C01", "ST001", "Ali Ahmed", 20);
//    eduSystem.registerStudent("S01", "D01", "C01", "ST002", "Sara Khan", 19);
//    eduSystem.registerStudent("S01", "D01", "C01", "ST003", "Hassan Ali", 21);
//    eduSystem.registerStudent("S01", "D01", "C02", "ST004", "Fatima Zahra", 20);
//    eduSystem.registerStudent("S01", "D02", "C03", "ST005", "Usman Malik", 19);
//
//    eduSystem.registerStudent("S02", "D04", "C05", "ST006", "Zainab Hassan", 18);
//    eduSystem.registerStudent("S02", "D05", "C06", "ST007", "Bilal Ahmed", 17);
//
//    eduSystem.registerStudent("S03", "D06", "C07", "ST008", "Mariam Siddiqui", 19);
//    eduSystem.registerStudent("S03", "D07", "C08", "ST009", "Imran Khan", 18);
//
//    eduSystem.registerStudent("S04", "D08", "C09", "ST010", "Hira Fatima", 16);
//    eduSystem.registerStudent("S05", "D09", "C10", "ST011", "Farhan Noor", 21);
//    eduSystem.registerStudent("S05", "D09", "C10", "ST012", "Sana Malik", 20);
//
//    // Add subjects to some students
//    Student* st001 = eduSystem.findStudent("ST001");
//    if (st001) {
//        st001->addSubject("Data Structures");
//        st001->addSubject("Algorithms");
//        st001->addSubject("Database Systems");
//    }
//
//    Student* st002 = eduSystem.findStudent("ST002");
//    if (st002) {
//        st002->addSubject("Programming");
//        st002->addSubject("Web Development");
//    }
//
//    cout << "\n========== Sample Data Loaded Successfully ==========" << endl;
//    cout << "Schools registered: 5" << endl;
//    cout << "Departments added: 9" << endl;
//    cout << "Classes created: 10" << endl;
//    cout << "Faculty registered: 5" << endl;
//    cout << "Students enrolled: 12" << endl;
//    cout << "===================================================\n" << endl;
//}
//
//// ==================== CSV FILE LOADING ====================
//
//// Helper function to trim whitespace
//string trim(const string& str) {
//    size_t first = str.find_first_not_of(" \t\r\n\"");
//    if (first == string::npos) return "";
//    size_t last = str.find_last_not_of(" \t\r\n\"");
//    return str.substr(first, (last - first + 1));
//}
//
//// Parse comma-separated subjects (handling quoted strings)
//void parseSubjects(const string& subjectStr, School* school) {
//    string subjects = trim(subjectStr);
//
//    // Remove quotes if present
//    if (subjects.front() == '"' && subjects.back() == '"') {
//        subjects = subjects.substr(1, subjects.length() - 2);
//    }
//
//    stringstream ss(subjects);
//    string subject;
//
//    while (getline(ss, subject, ',')) {
//        subject = trim(subject);
//        if (!subject.empty() && school) {
//            school->addSubject(subject);
//        }
//    }
//}
//
//// Load schools from CSV file
//bool loadSchoolsFromCSV(EducationSystem& eduSystem, const string& filename) {
//    cout << "\nLoading schools from CSV file: " << filename << endl;
//
//    ifstream file(filename.c_str());
//    if (!file.is_open()) {
//        cout << "Error: Could not open file '" << filename << "'" << endl;
//        cout << "Make sure the file exists in the same directory." << endl;
//        return false;
//    }
//
//    string line;
//    int lineNumber = 0;
//    int schoolsLoaded = 0;
//
//    // Read header line
//    if (getline(file, line)) {
//        lineNumber++;
//        cout << "CSV Header: " << trim(line) << endl;
//    }
//
//    // Default GPS coordinates for Islamabad sectors
//    struct SectorGPS {
//        string sector;
//        double lat;
//        double lon;
//    };
//
//    SectorGPS sectorCoords[] = {
//        {"G-10", 33.684, 73.025},
//        {"F-8", 33.691, 73.019},
//        {"F-6", 33.706, 73.055},
//        {"G-9", 33.700, 73.030},
//        {"F-7", 33.721, 73.052},
//        {"G-11", 33.670, 73.040},
//        {"I-8", 33.660, 73.045},
//        {"E-7", 33.710, 73.050}
//    };
//    int coordCount = 8;
//
//    // Read data lines
//    while (getline(file, line)) {
//        lineNumber++;
//
//        // Skip empty lines
//        if (trim(line).empty()) continue;
//
//        // Parse CSV: SchoolID,Name,Sector,Rating,Subjects
//        stringstream ss(line);
//        string schoolID, name, sector, ratingStr, subjectsStr;
//
//        getline(ss, schoolID, ',');
//        getline(ss, name, ',');
//        getline(ss, sector, ',');
//        getline(ss, ratingStr, ',');
//
//        // Get rest of line for subjects (may contain commas)
//        getline(ss, subjectsStr);
//
//        // Trim fields
//        schoolID = trim(schoolID);
//        name = trim(name);
//        sector = trim(sector);
//        ratingStr = trim(ratingStr);
//        subjectsStr = trim(subjectsStr);
//
//        // Validate required fields
//        if (schoolID.empty() || name.empty()) {
//            cout << "Warning: Line " << lineNumber << " missing required fields, skipping..." << endl;
//            continue;
//        }
//
//        // Parse rating
//        float rating = 0.0;
//        try {
//            rating = stof(ratingStr);
//        }
//        catch (...) {
//            rating = 3.0; // Default rating
//        }
//
//        // Find GPS coordinates for sector
//        double lat = 33.700; // Default latitude
//        double lon = 73.040; // Default longitude
//        for (int i = 0; i < coordCount; i++) {
//            if (sectorCoords[i].sector == sector) {
//                lat = sectorCoords[i].lat;
//                lon = sectorCoords[i].lon;
//                break;
//            }
//        }
//
//        // Register school
//        if (eduSystem.registerSchool(schoolID, name, sector, lat, lon, rating)) {
//            schoolsLoaded++;
//
//            // Add subjects to school
//            School* school = eduSystem.findSchool(schoolID);
//            if (school && !subjectsStr.empty()) {
//                parseSubjects(subjectsStr, school);
//            }
//        }
//    }
//
//    file.close();
//
//    cout << "\n========== CSV Loading Complete ==========" << endl;
//    cout << "Schools loaded: " << schoolsLoaded << endl;
//    cout << "Lines processed: " << (lineNumber - 1) << endl;
//    cout << "==========================================\n" << endl;
//
//    return schoolsLoaded > 0;
//}
//
//// ==================== MAIN PROGRAM ====================
//
//int main() {
//    // Initialize Education System
//    EducationSystem eduSystem(100, 500, 2000, 50000, 5000);
//    int choice;
//
//    cout << "\n==========================================================" << endl;
//    cout << "    WELCOME TO SMART CITY - EDUCATION SECTOR MODULE" << endl;
//    cout << "==========================================================" << endl;
//    cout << "This system manages schools, students, faculty using:" << endl;
//    cout << "- N-ary Tree (School -> Department -> Class -> Student)" << endl;
//    cout << "- Hash Tables (O(1) lookup)" << endl;
//    cout << "- Priority Queue (School ranking)" << endl;
//    cout << "==========================================================" << endl;
//
//    do {
//        printMenu();
//        cin >> choice;
//        cin.ignore(); // Clear newline
//
//        switch (choice) {
//        case 1: {
//            // Register School
//            string id, name, sector;
//            double lat, lon;
//            float rating;
//
//            cout << "\n--- Register School ---" << endl;
//            cout << "Enter School ID (e.g., S01): ";
//            getline(cin, id);
//
//            cout << "Enter School Name: ";
//            getline(cin, name);
//
//            cout << "Enter Sector (e.g., G-10): ";
//            getline(cin, sector);
//
//            cout << "Enter Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Longitude: ";
//            cin >> lon;
//
//            cout << "Enter Rating (0.0-5.0): ";
//            cin >> rating;
//
//            eduSystem.registerSchool(id, name, sector, lat, lon, rating);
//            break;
//        }
//
//        case 2: {
//            // Register Department
//            string schoolID, deptID, deptName;
//
//            cout << "\n--- Register Department ---" << endl;
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            cout << "Enter Department ID (e.g., D01): ";
//            getline(cin, deptID);
//
//            cout << "Enter Department Name: ";
//            getline(cin, deptName);
//
//            eduSystem.registerDepartment(schoolID, deptID, deptName);
//            break;
//        }
//
//        case 3: {
//            // Register Class
//            string schoolID, deptID, classID, className;
//
//            cout << "\n--- Register Class ---" << endl;
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            cout << "Enter Department ID: ";
//            getline(cin, deptID);
//
//            cout << "Enter Class ID (e.g., C01): ";
//            getline(cin, classID);
//
//            cout << "Enter Class Name (e.g., CS-101): ";
//            getline(cin, className);
//
//            eduSystem.registerClass(schoolID, deptID, classID, className);
//            break;
//        }
//
//        case 4: {
//            // Add Subject to School
//            string schoolID, subject;
//
//            cout << "\n--- Add Subject to School ---" << endl;
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            School* school = eduSystem.findSchool(schoolID);
//            if (school) {
//                cout << "Enter Subject Name: ";
//                getline(cin, subject);
//
//                if (school->addSubject(subject)) {
//                    cout << "Subject '" << subject << "' added to " << school->getName() << endl;
//                }
//                else {
//                    cout << "Failed to add subject" << endl;
//                }
//            }
//            else {
//                cout << "School not found!" << endl;
//            }
//            break;
//        }
//
//        case 5: {
//            // Register Student
//            string schoolID, deptID, classID, studentID, name;
//            int age;
//
//            cout << "\n--- Register Student ---" << endl;
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            cout << "Enter Department ID: ";
//            getline(cin, deptID);
//
//            cout << "Enter Class ID: ";
//            getline(cin, classID);
//
//            cout << "Enter Student ID (e.g., ST001): ";
//            getline(cin, studentID);
//
//            cout << "Enter Student Name: ";
//            getline(cin, name);
//
//            cout << "Enter Age: ";
//            cin >> age;
//
//            eduSystem.registerStudent(schoolID, deptID, classID, studentID, name, age);
//            break;
//        }
//
//        case 6: {
//            // Register Faculty
//            string facultyID, name, subject, qualification, schoolID, deptID;
//            int age, experience;
//
//            cout << "\n--- Register Faculty ---" << endl;
//            cout << "Enter Faculty ID (e.g., F001): ";
//            getline(cin, facultyID);
//
//            cout << "Enter Name: ";
//            getline(cin, name);
//
//            cout << "Enter Subject: ";
//            getline(cin, subject);
//
//            cout << "Enter Age: ";
//            cin >> age;
//            cin.ignore();
//
//            cout << "Enter Qualification (e.g., PhD Computer Science): ";
//            getline(cin, qualification);
//
//            cout << "Enter Years of Experience: ";
//            cin >> experience;
//            cin.ignore();
//
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            cout << "Enter Department ID: ";
//            getline(cin, deptID);
//
//            eduSystem.registerFaculty(facultyID, name, subject, age,
//                qualification, experience, schoolID, deptID);
//            break;
//        }
//
//        case 7: {
//            // Add Subject to Student
//            string studentID, subject;
//
//            cout << "\n--- Add Subject to Student ---" << endl;
//            cout << "Enter Student ID: ";
//            getline(cin, studentID);
//
//            Student* student = eduSystem.findStudent(studentID);
//            if (student) {
//                cout << "Enter Subject Name: ";
//                getline(cin, subject);
//
//                student->addSubject(subject);
//                cout << "Subject '" << subject << "' added to " << student->getName() << endl;
//            }
//            else {
//                cout << "Student not found!" << endl;
//            }
//            break;
//        }
//
//        case 8: {
//            // Find School by ID
//            string schoolID;
//
//            cout << "\n--- Find School by ID ---" << endl;
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            School* school = eduSystem.findSchool(schoolID);
//            if (school) {
//                cout << "\nSchool Found:\n" << endl;
//                school->display();
//            }
//            else {
//                cout << "School not found!" << endl;
//            }
//            break;
//        }
//
//        case 9: {
//            // Find Student by ID
//            string studentID;
//
//            cout << "\n--- Find Student by ID ---" << endl;
//            cout << "Enter Student ID: ";
//            getline(cin, studentID);
//
//            Student* student = eduSystem.findStudent(studentID);
//            if (student) {
//                cout << "\nStudent Found:\n" << endl;
//                student->display();
//            }
//            else {
//                cout << "Student not found!" << endl;
//            }
//            break;
//        }
//
//        case 10: {
//            // Find Faculty by ID
//            string facultyID;
//
//            cout << "\n--- Find Faculty by ID ---" << endl;
//            cout << "Enter Faculty ID: ";
//            getline(cin, facultyID);
//
//            Faculty* faculty = eduSystem.findFaculty(facultyID);
//            if (faculty) {
//                cout << "\nFaculty Found:\n" << endl;
//                faculty->display();
//            }
//            else {
//                cout << "Faculty not found!" << endl;
//            }
//            break;
//        }
//
//        case 11: {
//            // Search Schools by Subject
//            string subject;
//
//            cout << "\n--- Search Schools by Subject ---" << endl;
//            cout << "Enter Subject Name: ";
//            getline(cin, subject);
//
//            eduSystem.searchSchoolsBySubject(subject);
//            break;
//        }
//
//        case 12: {
//            // Search Schools by Sector
//            string sector;
//
//            cout << "\n--- Search Schools by Sector ---" << endl;
//            cout << "Enter Sector Name (e.g., G-10): ";
//            getline(cin, sector);
//
//            // Implementation would go here
//            cout << "Feature: Search schools in sector " << sector << endl;
//            break;
//        }
//
//        case 13: {
//            // Find Nearest School
//            double lat, lon;
//
//            cout << "\n--- Find Nearest School (GPS) ---" << endl;
//            cout << "Enter Your Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Your Longitude: ";
//            cin >> lon;
//
//            eduSystem.findNearestSchool(lat, lon);
//            break;
//        }
//
//        case 14: {
//            // Display Top N Schools
//            int n;
//
//            cout << "\n--- Display Top N Ranked Schools ---" << endl;
//            cout << "Enter N (number of top schools): ";
//            cin >> n;
//
//            eduSystem.displayTopRankedSchools(n);
//            break;
//        }
//
//        case 15: {
//            // Display All Rankings
//            cout << "\n--- All School Rankings ---" << endl;
//            eduSystem.displayAllRankedSchools();
//            break;
//        }
//
//        case 16: {
//            // Display Schools Above Rating
//            float minRating;
//
//            cout << "\n--- Schools Above Rating ---" << endl;
//            cout << "Enter Minimum Rating (0.0-5.0): ";
//            cin >> minRating;
//
//            eduSystem.getSchoolsAboveRating(minRating);
//            break;
//        }
//
//        case 17: {
//            // Display School Hierarchy
//            string schoolID;
//
//            cout << "\n--- Display School Hierarchy (Tree) ---" << endl;
//            cout << "Enter School ID: ";
//            getline(cin, schoolID);
//
//            eduSystem.displaySchoolHierarchy(schoolID);
//            break;
//        }
//
//        case 18: {
//            // Display All Schools
//            cout << "\n--- All Registered Schools ---" << endl;
//            eduSystem.displayAllSchools();
//            break;
//        }
//
//        case 19: {
//            // Display Statistics
//            eduSystem.displayStatistics();
//            break;
//        }
//
//        case 20: {
//            // Load Sample Data
//            loadSampleData(eduSystem);
//            break;
//        }
//
//        case 21: {
//            // Load from CSV
//            string filename;
//
//            cout << "\n--- Load Schools from CSV File ---" << endl;
//            cout << "Enter CSV filename (e.g., schools.csv): ";
//            getline(cin, filename);
//
//            loadSchoolsFromCSV(eduSystem, filename);
//            break;
//        }
//
//        case 0: {
//            cout << "\n==========================================================" << endl;
//            cout << "  Thank you for using Smart City Education Module!" << endl;
//            cout << "==========================================================" << endl;
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