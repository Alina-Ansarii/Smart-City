

#pragma once
#include "HashTable.h"
#include "MaxHeap.h"
#include "School.h"
#include <iostream>
#include <string>
using namespace std;


// ============================================================================
class SchoolHashTable : public HashTable {
public:
    SchoolHashTable(int cap = 100) : HashTable(cap) {}

    void insertSchool(School* school) {
        if (!school || school->getSchoolID().empty()) return;
        insert(school->getSchoolID(), (void*)school);
    }

    School* searchSchool(const string& id) {
        return id.empty() ? nullptr : (School*)search(id);
    }

    bool removeSchool(const string& id) {
        return id.empty() ? false : remove(id);
    }

    // Search by subject - O(n*s)
    void searchBySubject(const string& subject, School** results, int& count, int max) {
        count = 0;
        if (!results || max <= 0 || subject.empty() || isEmpty()) return;

        void** all = new void* [getSize()];
        int total = 0;
        getAllValues(all, total);

        for (int i = 0; i < total && count < max; i++) {
            School* s = (School*)all[i];
            if (s && s->hasSubject(subject))
                results[count++] = s;
        }
        delete[] all;
    }

    // Find nearest - O(n)
    School* findNearestSchool(double lat, double lon) {
        if (isEmpty()) return nullptr;

        void** all = new void* [getSize()];
        int total = 0;
        getAllValues(all, total);

        School* nearest = nullptr;
        double minDist = -1;

        for (int i = 0; i < total; i++) {
            School* s = (School*)all[i];
            if (s) {
                double d = s->distanceFrom(lat, lon);
                if (!nearest || d < minDist) {
                    minDist = d;
                    nearest = s;
                }
            }
        }
        delete[] all;
        return nearest;
    }

    // Search by sector - O(n)
    void searchBySector(const string& sector, School** results, int& count, int max) {
        count = 0;
        if (!results || max <= 0 || sector.empty() || isEmpty()) return;

        void** all = new void* [getSize()];
        int total = 0;
        getAllValues(all, total);

        for (int i = 0; i < total && count < max; i++) {
            School* s = (School*)all[i];
            if (s && s->getSector() == sector)
                results[count++] = s;
        }
        delete[] all;
    }

    void displayAllSchools() {
        if (isEmpty()) {
            cout << "No schools" << endl;
            return;
        }

        void** all = new void* [getSize()];
        int count = 0;
        getAllValues(all, count);

        cout << "\n=== ALL SCHOOLS ===" << endl;
        for (int i = 0; i < count; i++) {
            School* s = (School*)all[i];
            if (s) {
                cout << "\n" << (i + 1) << ". ";
                s->display();
                cout << "---" << endl;
            }
        }
        delete[] all;
    }

    void displayStatistics() {
        cout << "\n--- Hash Table Stats ---" << endl;
        cout << "Size: " << getSize() << ", Load: " << getLoadFactor() << endl;
        getStatistics();
    }
};

// ============================================================================
// SCHOOL RANKING QUEUE  
// Complexity: Insert O(log n), ExtractMax O(log n), Top O(1)
// ============================================================================
class SchoolRankingQueue : public MaxHeap {
public:
    SchoolRankingQueue(int cap = 100) : MaxHeap(cap) {}

    void insertSchool(School* school) {
        if (!school) return;
        int priority = (int)(school->getRating() * 100);
        insert((void*)school, priority);
    }

    School* getTopSchool() {
        return (School*)peekMax();
    }

    School* extractTopSchool() {
        return (School*)extractMax();
    }

    // Display top N - O(N log n)
    void displayTopSchools(int n) {
        if (isEmpty()) {
            cout << "No schools" << endl;
            return;
        }

        cout << "\n=== TOP " << n << " SCHOOLS ===" << endl;

        School** top = new School * [n];
        int* pri = new int[n];
        int count = 0;

        for (int i = 0; i < n && !isEmpty(); i++) {
            pri[i] = ((HeapNode*)peekMax())->priority;
            top[i] = (School*)extractMax();
            if (top[i]) count++;
        }

        for (int i = 0; i < count; i++) {
            cout << (i + 1) << ". " << top[i]->getName()
                << " - " << top[i]->getRating() << "/5.0" << endl;
        }

        for (int i = 0; i < count; i++) {
            insert((void*)top[i], pri[i]);
        }

        delete[] top;
        delete[] pri;
    }

    // Display all - O(n log n)
    void displayAllRankings() {
        if (isEmpty()) {
            cout << "No schools" << endl;
            return;
        }

        cout << "\n=== ALL RANKINGS ===" << endl;

        int total = size();
        School** all = new School * [total];
        int* pri = new int[total];

        for (int i = 0; i < total; i++) {
            pri[i] = ((HeapNode*)peekMax())->priority;
            all[i] = (School*)extractMax();
        }

        for (int i = 0; i < total; i++) {
            if (all[i]) {
                cout << (i + 1) << ". " << all[i]->getName()
                    << " (" << all[i]->getSector() << ") - "
                    << all[i]->getRating() << "/5.0" << endl;
            }
        }

        for (int i = 0; i < total; i++) {
            insert((void*)all[i], pri[i]);
        }

        delete[] all;
        delete[] pri;
    }

    // Get schools above rating - O(n)
    void getSchoolsAboveRating(float minRating, School** results, int& count, int max) {
        count = 0;
        if (!results || max <= 0 || isEmpty()) return;

        int total = size();
        School** all = new School * [total];
        int* pri = new int[total];

        for (int i = 0; i < total; i++) {
            pri[i] = ((HeapNode*)peekMax())->priority;
            all[i] = (School*)extractMax();
        }

        for (int i = 0; i < total && count < max; i++) {
            if (all[i] && all[i]->getRating() >= minRating) {
                results[count++] = all[i];
            }
        }

        for (int i = 0; i < total; i++) {
            insert((void*)all[i], pri[i]);
        }

        delete[] all;
        delete[] pri;
    }

    void displayStatus() {
        cout << "Schools in ranking: " << size() << endl;
        if (!isEmpty()) {
            School* top = getTopSchool();
            if (top) {
                cout << "Top: " << top->getName()
                    << " (" << top->getRating() << "/5.0)" << endl;
            }
        }
    }
};

// ============================================================================
// EDUCATION SYSTEM - Main Controller
// Manages: Schools, Departments, Classes, Students, Faculty
// Data Structures: Hash tables (O(1)), Priority queue (O(log n)), N-ary tree
// Memory: All entities in arrays, hash/heap store pointers only
// ============================================================================
class EducationSystem {
private:
    SchoolHashTable* schoolTable;
    HashTable* studentTable;
    HashTable* facultyTable;
    SchoolRankingQueue* rankingQueue;

    School** allSchools;
    Department** allDepartments;
    Class** allClasses;
    Student** allStudents;
    Faculty** allFaculty;

    int schoolCount, schoolCapacity;
    int deptCount, deptCapacity;
    int classCount, classCapacity;
    int studentCount, studentCapacity;
    int facultyCount, facultyCapacity;

    School** searchResults;

public:
    // Constructor - O(1)
    EducationSystem(int sCap = 100, int dCap = 500, int cCap = 2000,
        int stCap = 50000, int fCap = 5000) {
        schoolTable = new SchoolHashTable(sCap);
        studentTable = new HashTable(stCap);
        facultyTable = new HashTable(fCap);
        rankingQueue = new SchoolRankingQueue(sCap);

        schoolCapacity = sCap;
        schoolCount = 0;
        allSchools = new School * [sCap];
        for (int i = 0; i < sCap; i++) allSchools[i] = nullptr;

        deptCapacity = dCap;
        deptCount = 0;
        allDepartments = new Department * [dCap];
        for (int i = 0; i < dCap; i++) allDepartments[i] = nullptr;

        classCapacity = cCap;
        classCount = 0;
        allClasses = new Class * [cCap];
        for (int i = 0; i < cCap; i++) allClasses[i] = nullptr;

        studentCapacity = stCap;
        studentCount = 0;
        allStudents = new Student * [stCap];
        for (int i = 0; i < stCap; i++) allStudents[i] = nullptr;

        facultyCapacity = fCap;
        facultyCount = 0;
        allFaculty = new Faculty * [fCap];
        for (int i = 0; i < fCap; i++) allFaculty[i] = nullptr;

        searchResults = new School * [sCap];
    }

    // Destructor - O(n)
    ~EducationSystem() {
        delete schoolTable;
        delete studentTable;
        delete facultyTable;
        delete rankingQueue;

        for (int i = 0; i < schoolCount; i++) delete allSchools[i];
        for (int i = 0; i < deptCount; i++) delete allDepartments[i];
        for (int i = 0; i < classCount; i++) delete allClasses[i];
        for (int i = 0; i < studentCount; i++) delete allStudents[i];
        for (int i = 0; i < facultyCount; i++) delete allFaculty[i];

        delete[] allSchools;
        delete[] allDepartments;
        delete[] allClasses;
        delete[] allStudents;
        delete[] allFaculty;
        delete[] searchResults;
    }

    // Register school - O(log n)
    bool registerSchool(string id, string name, string sector, double lat, double lon, float rating) {
        if (id.empty() || schoolCount >= schoolCapacity) return false;
        if (schoolTable->searchSchool(id)) {
            cout << "School exists" << endl;
            return false;
        }

        School* s = new School(id, name, sector, lat, lon, rating);
        allSchools[schoolCount++] = s;
        schoolTable->insertSchool(s);
        rankingQueue->insertSchool(s);

        cout << "School '" << name << "' registered" << endl;
        return true;
    }

    // Register department - O(1)
    bool registerDepartment(string schoolID, string deptID, string deptName) {
        if (schoolID.empty() || deptID.empty() || deptCount >= deptCapacity) return false;

        School* school = schoolTable->searchSchool(schoolID);
        if (!school) {
            cout << "School not found" << endl;
            return false;
        }

        Department* dept = new Department(deptID, deptName);
        allDepartments[deptCount++] = dept;

        if (!school->addDepartment(dept)) {
            cout << "Failed to add department" << endl;
            return false;
        }

        cout << "Department '" << deptName << "' added" << endl;
        return true;
    }

    // Register class - O(d)
    bool registerClass(string schoolID, string deptID, string classID, string className) {
        if (schoolID.empty() || deptID.empty() || classID.empty() || classCount >= classCapacity)
            return false;

        School* school = schoolTable->searchSchool(schoolID);
        if (!school) {
            cout << "School not found" << endl;
            return false;
        }

        Department* dept = school->findDepartment(deptID);
        if (!dept) {
            cout << "Department not found" << endl;
            return false;
        }

        Class* cls = new Class(classID, className);
        allClasses[classCount++] = cls;

        if (!dept->addClass(cls)) {
            cout << "Failed to add class" << endl;
            return false;
        }

        cout << "Class '" << className << "' added" << endl;
        return true;
    }

    // Register student - O(d*c)
    bool registerStudent(string schoolID, string deptID, string classID,
        string studentID, string name, int age) {
        if (studentID.empty() || studentCount >= studentCapacity) return false;
        if (studentTable->contains(studentID)) {
            cout << "Student exists" << endl;
            return false;
        }

        School* school = schoolTable->searchSchool(schoolID);
        if (!school) {
            cout << "School not found" << endl;
            return false;
        }

        Department* dept = school->findDepartment(deptID);
        if (!dept) {
            cout << "Department not found" << endl;
            return false;
        }

        Class* cls = dept->findClass(classID);
        if (!cls) {
            cout << "Class not found" << endl;
            return false;
        }

        Student* student = new Student(studentID, name, age);
        student->setSchoolID(schoolID);
        student->setDeptID(deptID);
        allStudents[studentCount++] = student;

        cls->addStudent(student);
        studentTable->insert(studentID, (void*)student);

        cout << "Student '" << name << "' registered" << endl;
        return true;
    }

    // Register faculty - O(1)
    bool registerFaculty(string facultyID, string name, string subject, int age,
        string qualification, int exp, string schoolID, string deptID) {
        if (facultyID.empty() || facultyCount >= facultyCapacity) return false;
        if (facultyTable->contains(facultyID)) {
            cout << "Faculty exists" << endl;
            return false;
        }

        Faculty* faculty = new Faculty(facultyID, name, subject, age, qualification, exp);
        faculty->setSchoolID(schoolID);
        faculty->setDeptID(deptID);
        allFaculty[facultyCount++] = faculty;

        facultyTable->insert(facultyID, (void*)faculty);

        cout << "Faculty '" << name << "' registered" << endl;
        return true;
    }

    // Find operations - O(1)
    School* findSchool(const string& id) {
        return schoolTable->searchSchool(id);
    }

    Student* findStudent(const string& id) {
        return (Student*)studentTable->search(id);
    }

    Faculty* findFaculty(const string& id) {
        return (Faculty*)facultyTable->search(id);
    }

    // Search by subject - O(n*s)
    void searchSchoolsBySubject(const string& subject) {
        if (subject.empty()) return;

        cout << "\n=== Schools offering " << subject << " ===" << endl;
        int count = 0;
        schoolTable->searchBySubject(subject, searchResults, count, schoolCapacity);

        if (count == 0) {
            cout << "None found" << endl;
        }
        else {
            cout << "Found " << count << " school(s):\n" << endl;
            for (int i = 0; i < count; i++) {
                cout << (i + 1) << ". ";
                searchResults[i]->display();
                cout << "---" << endl;
            }
        }
    }

    // Find nearest - O(n)
    School* findNearestSchool(double lat, double lon) {
        if (lat < -90 || lat > 90 || lon < -180 || lon > 180) {
            cout << "Invalid GPS" << endl;
            return nullptr;
        }

        School* nearest = schoolTable->findNearestSchool(lat, lon);
        if (nearest) {
            double dist = nearest->distanceFrom(lat, lon);
            cout << "\nNearest: " << nearest->getName() << endl;
            cout << "Distance: " << dist << " units" << endl;
            nearest->display();
        }
        else {
            cout << "No schools" << endl;
        }
        return nearest;
    }

    // Ranking operations
    void displayTopRankedSchools(int n) {
        if (n <= 0) return;
        rankingQueue->displayTopSchools(n);
    }

    void displayAllRankedSchools() {
        rankingQueue->displayAllRankings();
    }

    void getSchoolsAboveRating(float minRating) {
        if (minRating < 0 || minRating > 5) return;

        int count = 0;
        rankingQueue->getSchoolsAboveRating(minRating, searchResults, count, schoolCapacity);

        cout << "\n=== Schools >= " << minRating << " ===" << endl;
        if (count == 0) {
            cout << "None" << endl;
        }
        else {
            for (int i = 0; i < count; i++) {
                cout << (i + 1) << ". " << searchResults[i]->getName()
                    << " - " << searchResults[i]->getRating() << "/5.0" << endl;
            }
        }
    }

    // Display operations
    void displayAllSchools() {
        schoolTable->displayAllSchools();
    }

    void displaySchoolHierarchy(const string& schoolID) {
        School* school = findSchool(schoolID);
        if (school) {
            school->displayHierarchy();
        }
        else {
            cout << "School not found" << endl;
        }
    }

    void displayStatistics() {
        cout << "\n=== EDUCATION SYSTEM STATISTICS ===" << endl;
        cout << "Schools: " << schoolCount << endl;
        cout << "Departments: " << deptCount << endl;
        cout << "Classes: " << classCount << endl;
        cout << "Students: " << studentCount << endl;
        cout << "Faculty: " << facultyCount << endl;
        cout << "===================================" << endl;

        if (schoolTable) schoolTable->displayStatistics();
        if (rankingQueue) {
            cout << "\nRanking:" << endl;
            rankingQueue->displayStatus();
        }
    }

    // Getters
    int getTotalSchools() const { return schoolCount; }
    int getTotalDepartments() const { return deptCount; }
    int getTotalClasses() const { return classCount; }
    int getTotalStudents() const { return studentCount; }
    int getTotalFaculty() const { return facultyCount; }
};
