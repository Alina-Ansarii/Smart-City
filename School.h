#pragma once
// ============================================================================
// SMART CITY PROJECT - EDUCATION MODULE (PART 1: ENTITY CLASSES)
// ============================================================================
// Student: Haleema Sadia (24-0654), Section: CS-D
// File: School.h
//
// PROJECT REQUIREMENTS MET:
// [X] 4-level N-ary tree: School -> Department -> Class -> Student
// [X] Manual implementations (no STL containers)
// [X] Linked lists for dynamic data
// [X] Faculty registration support
// [X] Complexity analysis documented
//
// DATA STRUCTURES:
// 1. N-ARY TREE - Organizational hierarchy via composition
// 2. SINGLY LINKED LIST - Students in class, subjects
// 3. DYNAMIC ARRAYS - Departments, classes (fixed capacity)
//
// TREE STRUCTURE: School IS root, departments[] = children pointers
// This satisfies "School organogram using a tree structure" requirement
// ============================================================================

#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Subject node for linked list
struct SubjectNode {
    string subject;
    SubjectNode* next;
    SubjectNode(string s) : subject(s), next(nullptr) {}
};

// ============================================================================
// STUDENT CLASS (Leaf - Level 4)
// Complexity: Constructor O(1), Destructor O(s), addSubject O(s), hasSubject O(s)
// ============================================================================
class Student {
private:
    string studentID, name;
    int age;
    string classID, deptID, schoolID;
    SubjectNode* subjectHead;

public:
    Student(string id = "", string studentName = "", int studentAge = 0) {
        studentID = id;
        name = studentName;
        age = (studentAge >= 0 && studentAge <= 150) ? studentAge : 0;
        subjectHead = nullptr;
    }

    ~Student() {
        SubjectNode* curr = subjectHead;
        while (curr) {
            SubjectNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // Getters
    string getStudentID() const { return studentID; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getClassID() const { return classID; }
    string getDeptID() const { return deptID; }
    string getSchoolID() const { return schoolID; }

    // Setters
    void setStudentID(const string& id) { studentID = id; }
    void setName(const string& n) { name = n; }
    void setAge(int a) { if (a >= 0 && a <= 150) age = a; }
    void setClassID(const string& id) { classID = id; }
    void setDeptID(const string& id) { deptID = id; }
    void setSchoolID(const string& id) { schoolID = id; }

    // Subject operations - O(s) where s = subjects
    void addSubject(const string& subject) {
        SubjectNode* newNode = new SubjectNode(subject);
        if (!subjectHead) {
            subjectHead = newNode;
            return;
        }
        SubjectNode* curr = subjectHead;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
    }

    bool hasSubject(const string& subject) const {
        SubjectNode* curr = subjectHead;
        while (curr) {
            if (curr->subject == subject) return true;
            curr = curr->next;
        }
        return false;
    }

    bool removeSubject(const string& subject) {
        if (!subjectHead) return false;
        if (subjectHead->subject == subject) {
            SubjectNode* temp = subjectHead;
            subjectHead = subjectHead->next;
            delete temp;
            return true;
        }
        SubjectNode* curr = subjectHead;
        while (curr->next && curr->next->subject != subject)
            curr = curr->next;
        if (!curr->next) return false;
        SubjectNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        return true;
    }

    void display() const {
        cout << "ID: " << studentID << ", Name: " << name << ", Age: " << age << endl;
    }

    bool operator<(const Student& other) const {
        return studentID < other.studentID;
    }
};

// Student node for linked list in class
struct StudentNode {
    Student* data;
    StudentNode* next;
    StudentNode(Student* s) : data(s), next(nullptr) {}
};

// ============================================================================
// CLASS ENTITY (Level 3)
// Uses singly linked list for students (PROJECT REQUIREMENT)
// Complexity: addStudent O(1), findStudent O(n), removeStudent O(n)
// ============================================================================
class Class {
private:
    string classID, className, deptID, schoolID;
    StudentNode* studentsHead;
    int studentCount;

public:
    Class(string id = "", string name = "") {
        classID = id;
        className = name;
        studentsHead = nullptr;
        studentCount = 0;
    }

    ~Class() {
        StudentNode* curr = studentsHead;
        while (curr) {
            StudentNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // Getters
    string getClassID() const { return classID; }
    string getClassName() const { return className; }
    string getDeptID() const { return deptID; }
    string getSchoolID() const { return schoolID; }
    int getStudentCount() const { return studentCount; }

    // Setters
    void setClassID(const string& id) { classID = id; }
    void setClassName(const string& n) { className = n; }
    void setDeptID(const string& id) { deptID = id; }
    void setSchoolID(const string& id) { schoolID = id; }

    // Add student - O(1) insert at head
    void addStudent(Student* student) {
        if (!student) return;
        StudentNode* newNode = new StudentNode(student);
        newNode->next = studentsHead;
        studentsHead = newNode;
        studentCount++;
        student->setClassID(classID);
    }

    // Find student - O(n)
    Student* findStudent(const string& studentID) {
        StudentNode* curr = studentsHead;
        while (curr) {
            if (curr->data && curr->data->getStudentID() == studentID)
                return curr->data;
            curr = curr->next;
        }
        return nullptr;
    }

    // Remove student - O(n)
    bool removeStudent(const string& studentID) {
        if (!studentsHead) return false;
        if (studentsHead->data && studentsHead->data->getStudentID() == studentID) {
            StudentNode* temp = studentsHead;
            studentsHead = studentsHead->next;
            delete temp;
            studentCount--;
            return true;
        }
        StudentNode* curr = studentsHead;
        while (curr->next) {
            if (curr->next->data && curr->next->data->getStudentID() == studentID) {
                StudentNode* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                studentCount--;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void display() const {
        cout << "Class: " << className << " (" << classID << "), Students: " << studentCount << endl;
    }

    void displayStudents() const {
        if (!studentsHead) {
            cout << "No students" << endl;
            return;
        }
        StudentNode* curr = studentsHead;
        int i = 1;
        while (curr) {
            if (curr->data)
                cout << i++ << ". " << curr->data->getName() << " (" << curr->data->getStudentID() << ")" << endl;
            curr = curr->next;
        }
    }
};

// ============================================================================
// DEPARTMENT CLASS (Level 2)
// Uses dynamic array for classes (children in tree)
// Complexity: addClass O(1), findClass O(c), getTotalStudents O(c*s)
// ============================================================================
class Department {
private:
    string deptID, deptName, schoolID;
    Class** classes;
    int classCount, maxClasses;

public:
    Department(string id = "", string name = "", int classCap = 10) {
        deptID = id;
        deptName = name;
        maxClasses = (classCap > 0) ? classCap : 10;
        classCount = 0;
        classes = new Class * [maxClasses];
        for (int i = 0; i < maxClasses; i++)
            classes[i] = nullptr;
    }

    ~Department() {
        delete[] classes;
    }

    // Getters
    string getDeptID() const { return deptID; }
    string getDeptName() const { return deptName; }
    string getSchoolID() const { return schoolID; }
    int getClassCount() const { return classCount; }

    // Setters
    void setDeptID(const string& id) { deptID = id; }
    void setDeptName(const string& n) { deptName = n; }
    void setSchoolID(const string& id) { schoolID = id; }

    // Add class - O(1)
    bool addClass(Class* cls) {
        if (!cls || classCount >= maxClasses) return false;
        classes[classCount++] = cls;
        cls->setDeptID(deptID);
        cls->setSchoolID(schoolID);
        return true;
    }

    // Find class - O(c)
    Class* findClass(const string& classID) {
        for (int i = 0; i < classCount; i++) {
            if (classes[i] && classes[i]->getClassID() == classID)
                return classes[i];
        }
        return nullptr;
    }

    Class* getClass(int index) {
        if (index >= 0 && index < classCount)
            return classes[index];
        return nullptr;
    }

    // Get total students - O(c)
    int getTotalStudents() const {
        int total = 0;
        for (int i = 0; i < classCount; i++) {
            if (classes[i])
                total += classes[i]->getStudentCount();
        }
        return total;
    }

    void display() const {
        cout << "Dept: " << deptName << " (" << deptID << "), Classes: " << classCount
            << ", Students: " << getTotalStudents() << endl;
    }
};

// ============================================================================
// FACULTY CLASS
// PROJECT REQUIREMENT: "Faculty registration"
// Complexity: All operations O(1)
// ============================================================================
class Faculty {
private:
    string facultyID, name, subject, qualification, deptID, schoolID, email, phoneNumber;
    int age, yearsOfExperience;

public:
    Faculty(string id = "", string n = "", string sub = "", int a = 0, string qual = "", int exp = 0) {
        facultyID = id;
        name = n;
        subject = sub;
        age = (a >= 18 && a <= 100) ? a : 0;
        qualification = qual;
        yearsOfExperience = (exp >= 0) ? exp : 0;
    }

    // Getters
    string getFacultyID() const { return facultyID; }
    string getName() const { return name; }
    string getSubject() const { return subject; }
    int getAge() const { return age; }
    string getQualification() const { return qualification; }
    int getYearsOfExperience() const { return yearsOfExperience; }
    string getDeptID() const { return deptID; }
    string getSchoolID() const { return schoolID; }
    string getEmail() const { return email; }
    string getPhoneNumber() const { return phoneNumber; }

    // Setters
    void setFacultyID(const string& id) { facultyID = id; }
    void setName(const string& n) { name = n; }
    void setSubject(const string& s) { subject = s; }
    void setAge(int a) { if (a >= 18 && a <= 100) age = a; }
    void setQualification(const string& q) { qualification = q; }
    void setYearsOfExperience(int e) { if (e >= 0) yearsOfExperience = e; }
    void setDeptID(const string& id) { deptID = id; }
    void setSchoolID(const string& id) { schoolID = id; }
    void setEmail(const string& e) { email = e; }
    void setPhoneNumber(const string& p) { phoneNumber = p; }

    void display() const {
        cout << "Faculty: " << name << " (" << facultyID << "), Subject: " << subject
            << ", Exp: " << yearsOfExperience << " yrs" << endl;
    }

    void displayBrief() const {
        cout << facultyID << " - " << name << " (" << subject << ")" << endl;
    }

    bool operator<(const Faculty& other) const {
        return facultyID < other.facultyID;
    }
};

// ============================================================================
// SCHOOL CLASS (Root - Level 1)
// N-ARY TREE ROOT using composition pattern
// departments[] array = children pointers (equivalent to node->children[])
// PROJECT REQUIREMENT: "School organogram using a tree structure"
// 
// Complexity:
// - addDepartment: O(1)
// - findDepartment: O(d)
// - getTotalClasses: O(d)
// - getTotalStudents: O(d*c)
// - distanceFrom: O(1)
// - displayHierarchy: O(d*c*s) - PRE-ORDER tree traversal
// ============================================================================
class School {
private:
    string schoolID, name, sector;
    double latitude, longitude;
    float rating;
    string* subjects;
    int subjectCount, maxSubjects;
    Department** departments;
    int deptCount, maxDepts;

public:
    School(string id = "", string n = "", string sec = "", double lat = 0, double lon = 0,
        float rate = 0, int subCap = 20, int deptCap = 10) {
        schoolID = id;
        name = n;
        sector = sec;
        latitude = lat;
        longitude = lon;
        rating = (rate < 0) ? 0 : (rate > 5) ? 5 : rate;

        maxSubjects = (subCap > 0) ? subCap : 20;
        subjectCount = 0;
        subjects = new string[maxSubjects];

        maxDepts = (deptCap > 0) ? deptCap : 10;
        deptCount = 0;
        departments = new Department * [maxDepts];
        for (int i = 0; i < maxDepts; i++)
            departments[i] = nullptr;
    }

    ~School() {
        delete[] subjects;
        delete[] departments;
    }

    // Getters
    string getSchoolID() const { return schoolID; }
    string getName() const { return name; }
    string getSector() const { return sector; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    float getRating() const { return rating; }
    int getSubjectCount() const { return subjectCount; }
    int getDeptCount() const { return deptCount; }

    // Setters
    void setSchoolID(const string& id) { schoolID = id; }
    void setName(const string& n) { name = n; }
    void setSector(const string& s) { sector = s; }
    void setLocation(double lat, double lon) { latitude = lat; longitude = lon; }
    void setRating(float r) { rating = (r < 0) ? 0 : (r > 5) ? 5 : r; }

    // Subject operations - O(s)
    bool addSubject(const string& subject) {
        if (subject.empty() || subjectCount >= maxSubjects) return false;
        if (hasSubject(subject)) return false;
        subjects[subjectCount++] = subject;
        return true;
    }

    bool hasSubject(const string& subject) const {
        for (int i = 0; i < subjectCount; i++) {
            if (subjects[i] == subject) return true;
        }
        return false;
    }

    string getSubject(int index) const {
        return (index >= 0 && index < subjectCount) ? subjects[index] : "";
    }

    bool removeSubject(const string& subject) {
        for (int i = 0; i < subjectCount; i++) {
            if (subjects[i] == subject) {
                for (int j = i; j < subjectCount - 1; j++)
                    subjects[j] = subjects[j + 1];
                subjects[--subjectCount] = "";
                return true;
            }
        }
        return false;
    }

    // Tree operations
    bool addDepartment(Department* dept) {
        if (!dept || deptCount >= maxDepts) return false;
        departments[deptCount++] = dept;
        dept->setSchoolID(schoolID);
        return true;
    }

    Department* findDepartment(const string& deptID) {
        for (int i = 0; i < deptCount; i++) {
            if (departments[i] && departments[i]->getDeptID() == deptID)
                return departments[i];
        }
        return nullptr;
    }

    Department* getDepartment(int index) {
        return (index >= 0 && index < deptCount) ? departments[index] : nullptr;
    }

    bool removeDepartment(const string& deptID) {
        for (int i = 0; i < deptCount; i++) {
            if (departments[i] && departments[i]->getDeptID() == deptID) {
                for (int j = i; j < deptCount - 1; j++)
                    departments[j] = departments[j + 1];
                departments[--deptCount] = nullptr;
                return true;
            }
        }
        return false;
    }

    // Aggregation operations
    int getTotalClasses() const {
        int total = 0;
        for (int i = 0; i < deptCount; i++) {
            if (departments[i])
                total += departments[i]->getClassCount();
        }
        return total;
    }

    int getTotalStudents() const {
        int total = 0;
        for (int i = 0; i < deptCount; i++) {
            if (departments[i])
                total += departments[i]->getTotalStudents();
        }
        return total;
    }

    // Distance calculation - O(1)
    // PROJECT REQUIREMENT: "Locate nearest school"
    double distanceFrom(double lat, double lon) const {
        double dx = latitude - lat;
        double dy = longitude - lon;
        return sqrt(dx * dx + dy * dy);
    }

    void display() const {
        cout << "School: " << name << " (" << schoolID << ")" << endl;
        cout << "Sector: " << sector << ", Rating: " << rating << "/5.0" << endl;
        cout << "Location: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Depts: " << deptCount << ", Classes: " << getTotalClasses()
            << ", Students: " << getTotalStudents() << endl;
        cout << "Subjects: ";
        for (int i = 0; i < subjectCount; i++) {
            cout << subjects[i];
            if (i < subjectCount - 1) cout << ", ";
        }
        cout << endl;
    }

    // PRE-ORDER tree traversal - O(d*c*s)
    // PROJECT REQUIREMENT: "School organogram using a tree structure"
    void displayHierarchy() const {
        cout << "\n=== SCHOOL ORGANOGRAM (N-ARY TREE) ===" << endl;
        cout << "4-Level Hierarchy: School -> Dept -> Class -> Student" << endl;
        display();

        cout << "\n--- DEPARTMENTS ---" << endl;
        for (int i = 0; i < deptCount; i++) {
            if (departments[i]) {
                cout << "\n" << (i + 1) << ". ";
                departments[i]->display();

                cout << "   Classes:" << endl;
                for (int j = 0; j < departments[i]->getClassCount(); j++) {
                    Class* cls = departments[i]->getClass(j);
                    if (cls)
                        cout << "     - " << cls->getClassName()
                        << " (" << cls->getStudentCount() << " students)" << endl;
                }
            }
        }
    }

    // Comparison operators for MAX HEAP
    // PROJECT REQUIREMENT: "Ranking of Schools via priority queue"
    bool operator>(const School& other) const {
        return (rating != other.rating) ? (rating > other.rating) : (name < other.name);
    }

    bool operator<(const School& other) const {
        return (rating != other.rating) ? (rating < other.rating) : (name > other.name);
    }
};