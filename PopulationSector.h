#pragma once
#include <iostream>
#include <string>
#include "Tree.h"
#include "HashTable.h"
using namespace std;




////////// POPULATION MODULE  /////////////////

//PopulationSector
//---- NaryTree(islamabadHierarchy)
//|   ---- Islamabad(root)
//|   |   ---- Sector G - 10
//|   |   |   ----Street 22
//|   |   |   |   ---- House 180
//|   |   |   |   |   ---- Families
//|   |   |   |   ---- House 181
//|   |   |   ---- Street 5
//|   |   ----Sector F - 8
//|   |   ----...
//|
//|-- HashTable(citizenRegistry)
//|  ---- Key : CNIC(string)
//|  ---- Value : Citizen * pointer
//|
//---- HashTable(familyRegistry)
//|--- Key : Family ID(string)
//|--- Value : Family * pointer
//|---Contains : Family Tree(TreeNode)




// ==================== CITIZEN STRUCTURE ====================
struct Citizen {
    string cnic;              // Unique identifier (13 digits)
    string name;
    int age;
    char gender;              // 'M' or 'F'
    string occupation;
    string sector;
    string street;
    int houseNumber;
    string education;         // Primary, Secondary, Bachelor, Master, PhD, None
    int income;               // Monthly income in PKR
    bool isEmployed;

    Citizen() {
        cnic = "";
        name = "";
        age = 0;
        gender = 'M';
        occupation = "";
        sector = "";
        street = "";
        houseNumber = 0;
        education = "";
        income = 0;
        isEmployed = false;
    }

    Citizen(string c, string n, int a, char g, string occ, string sect, string str, int house, string edu = "None", int inc = 0) {
        cnic = c;
        name = n;
        age = a;
        gender = g;
        occupation = occ;
        sector = sect;
        street = str;
        houseNumber = house;
        education = edu;
        income = inc;
        isEmployed = (occupation != "Student" && occupation != "Unemployed" && occupation != "Child");
    }

    void display() {
        cout << "\n--- Citizen Information ---" << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Gender: " << (gender == 'M' ? "Male" : "Female") << endl;
        cout << "Occupation: " << occupation << endl;
        cout << "Education: " << education << endl;
        cout << "Income: Rs. " << income << "/month" << endl;
        cout << "Address: House " << houseNumber << ", " << street << ", " << sector << endl;
        cout << "Employment Status: " << (isEmployed ? "Employed" : "Not Employed") << endl;
        cout << "----------------------------" << endl;
    }
};



// ==================== FAMILY STRUCTURE ====================
struct Family {
    int familyId;
    string familyName;        // usually father's name or family surname
    int memberCount;
    TreeNode* familyTreeRoot; // root of family tree (head of household)

    Family() {
        familyId = 0;
        familyName = "";
        memberCount = 0;
        familyTreeRoot = nullptr;
    }

    Family(int id, string name) {
        familyId = id;
        familyName = name;
        memberCount = 0;
        familyTreeRoot = nullptr;
    }
};


// ==================== HOUSE STRUCTURE ====================
struct House {
    int houseNumber;
    int familyCount;
    Family** families;        // array of families living in this house
    int familyCapacity;
    int totalResidents;

    House() {
        houseNumber = 0;
        familyCount = 0;
        familyCapacity = 5;   // Default: up to 5 families per house
        families = new Family * [familyCapacity];
        for (int i = 0; i < familyCapacity; i++) {
            families[i] = nullptr;
        }
        totalResidents = 0;
    }

    House(int num) {
        houseNumber = num;
        familyCount = 0;
        familyCapacity = 5;
        families = new Family * [familyCapacity];
        for (int i = 0; i < familyCapacity; i++) {
            families[i] = nullptr;
        }
        totalResidents = 0;
    }

    ~House() {
        for (int i = 0; i < familyCount; i++) {
            delete families[i];
        }
        delete[] families;
    }

    bool addFamily(Family* family) {
        if (familyCount < familyCapacity) {
            families[familyCount++] = family;
            return true;
        }
        return false;
    }
};


// ==================== STREET STRUCTURE ====================
struct Street {
    string streetName;
    int houseCount;
    int totalPopulation;
};


// ==================== SECTOR STRUCTURE ====================
struct Sector {
    string sectorName;
    int streetCount;
    int totalHouses;
    int totalPopulation;
};




// 
// ==================== POPULATION & HOUSING SECTOR CLASS ====================
class PopulationSector {
private:
    NaryTree* islamabadHierarchy;    // Islamabad -> Sector -> Street -> House
    HashTable* citizenRegistry;       // for fast CNIC-based citizen lookup 
    HashTable* familyRegistry;        // FamilyID -> Family*
    int totalCitizens;
    int totalFamilies;
    int totalHouses;
    int totalStreets;
    int totalSectors;
    int nextFamilyId;


    // for generating unique IDs
    int generateFamilyId() {
        return ++nextFamilyId;
    }



    //===============================================
    // ========== HELPER FUNCTIONS ==================
    // Find sector node by name - O(n)
    TreeNode* findSectorNode(string sectorName) {
        TreeNode* islamabad = islamabadHierarchy->getRoot();
        if (!islamabad) return nullptr;

        for (int i = 0; i < islamabad->childCount; i++) {
            if (islamabad->children[i]->name == sectorName) {
                return islamabad->children[i];
            }
        }
        return nullptr;
    }

    // Find street node - O(n)
    TreeNode* findStreetNode(string sectorName, string streetName) {
        TreeNode* sector = findSectorNode(sectorName);
        if (!sector) return nullptr;

        for (int i = 0; i < sector->childCount; i++) {
            if (sector->children[i]->name == streetName) {
                return sector->children[i];
            }
        }
        return nullptr;
    }

    // Find house node - O(n)
    TreeNode* findHouseNode(string sectorName, string streetName, int houseNumber) {
        TreeNode* street = findStreetNode(sectorName, streetName);
        if (!street) return nullptr;

        for (int i = 0; i < street->childCount; i++) {
            House* h = (House*)street->children[i]->getData();
            if (h && h->houseNumber == houseNumber) {
                return street->children[i];
            }
        }
        return nullptr;
    }

    // Find family member in family tree - O(n) recursive
    TreeNode* findFamilyMemberNode(TreeNode* node, string cnic) {
        if (!node) return nullptr;

        Citizen* c = (Citizen*)node->getData();
        if (c && c->cnic == cnic) {
            return node;
        }

        for (int i = 0; i < node->childCount; i++) {
            TreeNode* found = findFamilyMemberNode(node->children[i], cnic);
            if (found) return found;
        }

        return nullptr;
    }



public:

    PopulationSector() {
        islamabadHierarchy = new NaryTree();
        citizenRegistry = new HashTable(1000);    // support 1000+ citizens
        familyRegistry = new HashTable(200);      // support 200+ families
        totalCitizens = 0;
        totalFamilies = 0;
        totalHouses = 0;
        totalStreets = 0;
        totalSectors = 0;
        nextFamilyId = 0;

        // Create root node for Islamabad
        TreeNode* islamabad = new TreeNode(0, 50, "Islamabad");
        islamabadHierarchy->setRoot(islamabad);
    }

    ~PopulationSector() {
        // Clean up citizens
        string cnics[1000];
        int count;
        citizenRegistry->getAllKeys(cnics, count);
        for (int i = 0; i < count; i++) {
            Citizen* c = (Citizen*)citizenRegistry->search(cnics[i]);
            if (c) delete c;
        }

        delete islamabadHierarchy;
        delete citizenRegistry;
        delete familyRegistry;
    }



    //===============================================================
    // ==================== HIERARCHY MANAGEMENT ====================

    // Add a sector to Islamabad - O(n)
    /* 1. get root
    *  2. check if sector alr exists
    *  3. create new sector node
    *  4. add to islamabadHierarchy & sector count++
    */
    bool addSector(string sectorName) {
        TreeNode* islamabad = islamabadHierarchy->getRoot();
        if (!islamabad) {
            cout << "Error: Islamabad root not found!" << endl;
            return false;
        }

        // check if sector already exists
        for (int i = 0; i < islamabad->childCount; i++) {
            if (islamabad->children[i]->name == sectorName) {
                cout << "Sector " << sectorName << " already exists!" << endl;
                return false;
            }
        }

        // create new sector node
        int sectorId = totalSectors + 1;
        TreeNode* sector = new TreeNode(sectorId, 30, sectorName);

        Sector* sectorData = new Sector();
        sectorData->sectorName = sectorName;
        sectorData->streetCount = 0;
        sectorData->totalHouses = 0;
        sectorData->totalPopulation = 0;
        sector->setData(sectorData);

        // add to Islamabad
        islamabadHierarchy->addNode(0, sector);
        totalSectors++;

        cout << "Sector " << sectorName << " added successfully!" << endl;
        return true;
    }


    // Add a street to a sector - O(n)
    /* 1. get root
    *  2. find sector
    *  3. if found, check if street exists
    *  4. if it doesn't, create street node
    *  5. add it to sector
    *  6. update sector data (street count++)
    */
    bool addStreet(string sectorName, string streetName) {
        TreeNode* islamabad = islamabadHierarchy->getRoot();
        if (!islamabad) return false;

        // find sector
        TreeNode* sectorNode = nullptr;
        for (int i = 0; i < islamabad->childCount; i++) {
            if (islamabad->children[i]->name == sectorName) {
                sectorNode = islamabad->children[i];
                break;
            }
        }
        if (!sectorNode) {
            cout << "Sector " << sectorName << " not found!" << endl;
            return false;
        }

        // check if street already exists
        for (int i = 0; i < sectorNode->childCount; i++) {
            if (sectorNode->children[i]->name == streetName) {
                cout << "Street " << streetName << " already exists in " << sectorName << "!" << endl;
                return false;
            }
        }

        // create street node
        int streetId = (sectorNode->id * 100) + totalStreets + 1;
        TreeNode* street = new TreeNode(streetId, 50, streetName);

        Street* streetData = new Street();
        streetData->streetName = streetName;
        streetData->houseCount = 0;
        streetData->totalPopulation = 0;
        street->setData(streetData);

        // add to sector
        islamabadHierarchy->addNode(sectorNode->id, street);

        // update sector data
        Sector* sectData = (Sector*)sectorNode->getData();
        if (sectData) {
            sectData->streetCount++;
        }

        totalStreets++;

        cout << "Street " << streetName << " added to " << sectorName << " successfully!" << endl;
        return true;
    }


    // Add a house to a street - O(n)
    /* 1. get root
    *  2. find sector -> street
    *  3. check if house exists, if not then create node
    *  4. add to street
    *  5. update street data and then sector data (increment house no)
    */
    bool addHouse(string sectorName, string streetName, int houseNumber) {
        TreeNode* islamabad = islamabadHierarchy->getRoot();
        if (!islamabad) return false;

        // find sector
        TreeNode* sectorNode = nullptr;
        for (int i = 0; i < islamabad->childCount; i++) {
            if (islamabad->children[i]->name == sectorName) {
                sectorNode = islamabad->children[i];
                break;
            }
        }
        if (!sectorNode) {
            cout << "Sector " << sectorName << " not found!" << endl;
            return false;
        }

        // find street
        TreeNode* streetNode = nullptr;
        for (int i = 0; i < sectorNode->childCount; i++) {
            if (sectorNode->children[i]->name == streetName) {
                streetNode = sectorNode->children[i];
                break;
            }
        }
        if (!streetNode) {
            cout << "Street " << streetName << " not found in " << sectorName << "!" << endl;
            return false;
        }

        // check if house already exists
        for (int i = 0; i < streetNode->childCount; i++) {
            House* h = (House*)streetNode->children[i]->getData();
            if (h && h->houseNumber == houseNumber) {
                cout << "House " << houseNumber << " already exists on " << streetName << "!" << endl;
                return false;
            }
        }

        // create house node
        int houseId = (streetNode->id * 1000) + houseNumber;
        string houseName = "House " + to_string(houseNumber);
        TreeNode* house = new TreeNode(houseId, 10, houseName);

        House* houseData = new House(houseNumber);
        house->setData(houseData);

        // add to street
        islamabadHierarchy->addNode(streetNode->id, house);

        // update street data
        Street* strData = (Street*)streetNode->getData();
        if (strData) {
            strData->houseCount++;
        }

        // update sector data
        Sector* sectData = (Sector*)sectorNode->getData();
        if (sectData) {
            sectData->totalHouses++;
        }

        totalHouses++;

        cout << "House " << houseNumber << " added to " << streetName << ", " << sectorName << " successfully!" << endl;
        return true;
    }




    //============================================================
    // ==================== FAMILY MANAGEMENT ====================

    // Add a family to a house - O(n)
    /* 1. find house node
    *  2. crete new fam
    *  3. add to house
    *  4. store in fam registry
    */
    bool addFamily(string sectorName, string streetName, int houseNumber, string familyName) {
        // find the house node
        TreeNode* houseNode = findHouseNode(sectorName, streetName, houseNumber);
        if (!houseNode) {
            cout << "House not found!" << endl;
            return false;
        }

        House* house = (House*)houseNode->getData();
        if (!house) return false;

        // create new family
        int famId = generateFamilyId();
        Family* family = new Family(famId, familyName);

        // add to house
        if (!house->addFamily(family)) {
            cout << "House is full! Cannot add more families." << endl;
            delete family;
            return false;
        }

        // store in family registry
        string famKey = to_string(famId);
        familyRegistry->insert(famKey, family);

        totalFamilies++;

        cout << "Family '" << familyName << "' (ID: " << famId << ") added to House " << houseNumber << endl;
        return true;
    }




    //=============================================================
    // ==================== CITIZEN MANAGEMENT ====================

    // Register a citizen - O(1) average
    /* 1. check if cnic exists
    *  2. verify house
    *  3. create new citizen
    *  4. add to citizen registry
    *  5. update house phir street phir sector ki population  (increment total population)
    *  6.
    */
    bool registerCitizen(string cnic, string name, int age, char gender, string occupation, string sector, string street,
        int houseNumber, string education = "None", int income = 0) {

        // check if CNIC already exists
        if (citizenRegistry->contains(cnic)) {
            cout << "Error: Citizen with CNIC " << cnic << " already registered!" << endl;
            return false;
        }

        // verify house exists
        TreeNode* houseNode = findHouseNode(sector, street, houseNumber);
        if (!houseNode) {
            cout << "Error: House not found! Please add the house first." << endl;
            return false;
        }

        // create new citizen
        Citizen* citizen = new Citizen(cnic, name, age, gender, occupation, sector, street, houseNumber, education, income);

        // add it to registry
        citizenRegistry->insert(cnic, citizen);

        // update house population
        House* house = (House*)houseNode->getData();
        if (house) {
            house->totalResidents++;
        }

        // update street population
        TreeNode* streetNode = findStreetNode(sector, street);
        if (streetNode) {
            Street* str = (Street*)streetNode->getData();
            if (str)
                str->totalPopulation++;
        }

        // update sector population
        TreeNode* sectorNode = findSectorNode(sector);
        if (sectorNode) {
            Sector* sect = (Sector*)sectorNode->getData();
            if (sect)
                sect->totalPopulation++;
        }

        totalCitizens++;

        cout << "Citizen " << name << " registered successfully!" << endl;
        return true;
    }



    // Add family member with family tree structure - O(1) + O(n) for finding parent
    /* 1. get family
    *  2. parent citizen gets address
    */
    bool addFamilyMember(int familyId, string parentCnic, string cnic, string name, int age, char gender, string occupation, string education = "None", int income = 0) {

        // Get family
        string famKey = to_string(familyId);
        Family* family = (Family*)familyRegistry->search(famKey);
        if (!family) {
            cout << "Family ID " << familyId << " not found!" << endl;
            return false;
        }

        // Get parent citizen to get address
        Citizen* parent = nullptr;
        if (parentCnic != "") {
            parent = (Citizen*)citizenRegistry->search(parentCnic);
            if (!parent) {
                cout << "Parent CNIC " << parentCnic << " not found!" << endl;
                return false;
            }
        }

        // For head of family, get address from first registration
        string sector, street;
        int houseNumber;

        if (parent) {
            sector = parent->sector;
            street = parent->street;
            houseNumber = parent->houseNumber;
        }
        else {
            // This is head of household, will need address
            cout << "Enter sector: ";
            cin >> sector;
            cout << "Enter street: ";
            cin.ignore();
            getline(cin, street);
            cout << "Enter house number: ";
            cin >> houseNumber;
        }

        // Register citizen
        if (!registerCitizen(cnic, name, age, gender, occupation, sector, street, houseNumber, education, income)) {
            return false;
        }

        // Add to family tree structure
        Citizen* newMember = (Citizen*)citizenRegistry->search(cnic);

        if (!family->familyTreeRoot) {
            // This is the first member (head of household)
            family->familyTreeRoot = new TreeNode(family->memberCount + 1, 10, name);
            family->familyTreeRoot->setData(newMember);
        }
        else {
            // Add as child to parent
            TreeNode* parentNode = findFamilyMemberNode(family->familyTreeRoot, parentCnic);
            if (!parentNode) {
                cout << "Parent not found in family tree!" << endl;
                return false;
            }

            TreeNode* memberNode = new TreeNode(family->memberCount + 1, 10, name);
            memberNode->setData(newMember);
            parentNode->addChild(memberNode);
        }

        family->memberCount++;

        cout << "Family member added successfully!" << endl;
        return true;
    }


    // ==================== SEARCH FUNCTIONS ====================

    // fast lookup of citizen by CNIC - O(1) average
    Citizen* searchCitizen(string cnic) {
        Citizen* citizen = (Citizen*)citizenRegistry->search(cnic);

        if (citizen) {
            cout << "\nCitizen found!" << endl;
            citizen->display();
        }
        else {
            cout << "Citizen with CNIC " << cnic << " not found!" << endl;
        }

        return citizen;
    }





    //============================================================
    // ==================== REPORT GENERATION ====================

    // Generate age distribution report - O(n)
    void generateAgeDistributionReport() {

        cout << "\n========== AGE DISTRIBUTION REPORT ==========" << endl;

        int ageGroups[6] = { 0 }; // 0-12, 13-18, 19-30, 31-45, 46-60, 61+
        string groupNames[] = { "0-12 (Children)", "13-18 (Teenagers)",
                              "19-30 (Young Adults)", "31-45 (Adults)",
                              "46-60 (Middle Age)", "61+ (Senior Citizens)" };

        string cnics[1000];
        int count;
        citizenRegistry->getAllKeys(cnics, count);

        for (int i = 0; i < count; i++) {
            Citizen* c = (Citizen*)citizenRegistry->search(cnics[i]);
            if (c) {
                if (c->age <= 12) ageGroups[0]++;
                else if (c->age <= 18) ageGroups[1]++;
                else if (c->age <= 30) ageGroups[2]++;
                else if (c->age <= 45) ageGroups[3]++;
                else if (c->age <= 60) ageGroups[4]++;
                else ageGroups[5]++;
            }
        }

        cout << "Total Population: " << totalCitizens << endl;
        cout << "\nAge Group Distribution:" << endl;
        for (int i = 0; i < 6; i++) {
            double percentage = totalCitizens > 0 ? (ageGroups[i] * 100.0 / totalCitizens) : 0;
            cout << groupNames[i] << ": " << ageGroups[i]
                << " (" << percentage << "%)" << endl;
        }
        cout << "============================================\n" << endl;
    }


    // Generate occupation summary - O(n)
    // counts citizen by occupation
    void generateOccupationSummary() {
        cout << "\n========== OCCUPATION SUMMARY ==========" << endl;

        HashTable occupationCount(50);

        string cnics[1000];
        int count;
        citizenRegistry->getAllKeys(cnics, count);

        for (int i = 0; i < count; i++) {
            Citizen* c = (Citizen*)citizenRegistry->search(cnics[i]);
            if (c) {
                int* currentCount = (int*)occupationCount.search(c->occupation);
                if (currentCount) {
                    (*currentCount)++;
                }
                else {
                    int* newCount = new int(1);
                    occupationCount.insert(c->occupation, newCount);
                }
            }
        }

        cout << "Total Working Population: " << totalCitizens << endl;
        cout << "\nOccupation Breakdown:" << endl;

        string occupations[50];
        int occCount;
        occupationCount.getAllKeys(occupations, occCount);

        for (int i = 0; i < occCount; i++) {
            int* cnt = (int*)occupationCount.search(occupations[i]);
            if (cnt) {
                double percentage = totalCitizens > 0 ? (*cnt * 100.0 / totalCitizens) : 0;
                cout << occupations[i] << ": " << *cnt
                    << " (" << percentage << "%)" << endl;
            }
        }

        // Clean up
        for (int i = 0; i < occCount; i++) {
            int* cnt = (int*)occupationCount.search(occupations[i]);
            if (cnt) delete cnt;
        }

        cout << "========================================\n" << endl;
    }



    // Generate gender ratio report - O(n)
    void generateGenderRatioReport() {
        cout << "\n========== GENDER RATIO REPORT ==========" << endl;

        int maleCount = 0;
        int femaleCount = 0;

        string cnics[1000];
        int count;
        citizenRegistry->getAllKeys(cnics, count);

        for (int i = 0; i < count; i++) {
            Citizen* c = (Citizen*)citizenRegistry->search(cnics[i]);
            if (c) {
                if (c->gender == 'M') maleCount++;
                else femaleCount++;
            }
        }

        cout << "Total Population: " << totalCitizens << endl;
        cout << "Males: " << maleCount << " (" << (totalCitizens > 0 ? maleCount * 100.0 / totalCitizens : 0) << "%)" << endl;
        cout << "Females: " << femaleCount << " (" << (totalCitizens > 0 ? femaleCount * 100.0 / totalCitizens : 0) << "%)" << endl;

        if (femaleCount > 0) {
            double ratio = (double)maleCount / femaleCount;
            cout << "Male to Female Ratio: " << ratio << ":1" << endl;
        }

        cout << "========================================\n" << endl;
    }



    // Generate population density report - O(n)
    void generatePopulationDensityReport() {
        cout << "\n========== POPULATION DENSITY REPORT ==========" << endl;

        TreeNode* islamabad = islamabadHierarchy->getRoot();
        if (!islamabad) return;

        cout << "Total Sectors: " << totalSectors << endl;
        cout << "Total Streets: " << totalStreets << endl;
        cout << "Total Houses: " << totalHouses << endl;
        cout << "Total Families: " << totalFamilies << endl;
        cout << "Total Citizens: " << totalCitizens << endl;

        if (totalHouses > 0) {
            cout << "\nAverage Citizens per House: " << (double)totalCitizens / totalHouses << endl;
        }

        if (totalFamilies > 0) {
            cout << "Average Family Size: " << (double)totalCitizens / totalFamilies << endl;
        }

        cout << "\nSector-wise Population:" << endl;
        for (int i = 0; i < islamabad->childCount; i++) {
            TreeNode* sector = islamabad->children[i];
            Sector* sectData = (Sector*)sector->getData();
            if (sectData) {
                cout << sector->name << ": " << sectData->totalPopulation
                    << " people in " << sectData->totalHouses << " houses" << endl;
            }
        }

        cout << "============================================\n" << endl;
    }



    // Generate comprehensive report - O(n)
    void generateComprehensiveReport() {
        cout << "\n\n";
        cout << "=====================================================" << endl;
        cout << "     POPULATION & HOUSING - COMPREHENSIVE REPORT     " << endl;
        cout << "=====================================================" << endl;

        generateAgeDistributionReport();
        generateGenderRatioReport();
        generateOccupationSummary();
        generatePopulationDensityReport();
    }


    // ==================== DISPLAY FUNCTIONS ====================

    // Display Islamabad hierarchy - O(n)
    void displayIslamabadHierarchy() {
        cout << "\n========== ISLAMABAD HIERARCHY ==========" << endl;
        islamabadHierarchy->printTree();
        cout << "========================================\n" << endl;
    }

    // Display all citizens - O(n)
    void displayAllCitizens() {
        cout << "\n========== ALL REGISTERED CITIZENS ==========" << endl;
        cout << "Total Citizens: " << totalCitizens << endl;

        string cnics[1000];
        int count;
        citizenRegistry->getAllKeys(cnics, count);

        for (int i = 0; i < count; i++) {
            Citizen* c = (Citizen*)citizenRegistry->search(cnics[i]);
            if (c) {
                c->display();
            }
        }

        cout << "=============================================\n" << endl;
    }

    // Display statistics - O(1)
    void displayStatistics() {
        cout << "\n========== STATISTICS ==========" << endl;
        cout << "Total Sectors: " << totalSectors << endl;
        cout << "Total Streets: " << totalStreets << endl;
        cout << "Total Houses: " << totalHouses << endl;
        cout << "Total Families: " << totalFamilies << endl;
        cout << "Total Citizens: " << totalCitizens << endl;
        cout << "================================\n" << endl;
    }




    // ==================== UTILITY FUNCTIONS ====================

    int getTotalCitizens() { return totalCitizens; }
    int getTotalFamilies() { return totalFamilies; }
    int getTotalHouses() { return totalHouses; }
    int getTotalSectors() { return totalSectors; }






    //============================================================
    // ==================== BONUS: HEATMAP LOGIC ==================

    // Generate population heatmap - identifies hotspots - O(n)
    void generatePopulationHeatmap() {
        cout << "\n========== POPULATION HEATMAP ==========" << endl;

        TreeNode* islamabad = islamabadHierarchy->getRoot();
        if (!islamabad || totalCitizens == 0) {
            cout << "No population data available!" << endl;
            return;
        }

        // Calculate average population per sector
        double avgPopulation = (double)totalCitizens / totalSectors;

        cout << "Total Population: " << totalCitizens << endl;
        cout << "Average Population per Sector: " << avgPopulation << endl;
        cout << "\n--- Heatmap by Sector ---" << endl;

        // Analyze each sector and classify as hotspot/moderate/low
        for (int i = 0; i < islamabad->childCount; i++) {
            TreeNode* sector = islamabad->children[i];
            Sector* sectData = (Sector*)sector->getData();

            if (sectData) {
                int pop = sectData->totalPopulation;
                string heatLevel;
                string indicator;

                // Classification logic
                if (pop >= avgPopulation * 1.5) {
                    heatLevel = " HIGH DENSITY (HOTSPOT)";
                    indicator = "[::::::::::::::]"; // Full bar
                }
                else if (pop >= avgPopulation * 0.75) {
                    heatLevel = " MODERATE DENSITY";
                    indicator = "[:::::::        ]"; // Mid bar
                }
                else {
                    heatLevel = " LOW DENSITY";
                    indicator = "[:::           ]"; // Low bar
                }

                cout << "\n" << sector->name << ": " << pop << " people" << endl;
                cout << "  " << indicator << " " << heatLevel << endl;
                cout << "  Houses: " << sectData->totalHouses
                    << " | Density: " << (sectData->totalHouses > 0 ?
                        (double)pop / sectData->totalHouses : 0) << " people/house" << endl;
            }
        }

        // Find top 3 hotspots
        cout << "\n--- TOP 3 POPULATION HOTSPOTS ---" << endl;

        // Simple bubble sort to find top 3
        TreeNode* topSectors[3] = { nullptr, nullptr, nullptr };
        int topPops[3] = { 0, 0, 0 };

        for (int i = 0; i < islamabad->childCount; i++) {
            TreeNode* sector = islamabad->children[i];
            Sector* sectData = (Sector*)sector->getData();

            if (sectData) {
                int pop = sectData->totalPopulation;

                // Check if it should be in top 3
                for (int j = 0; j < 3; j++) {
                    if (pop > topPops[j]) {
                        // Shift others down
                        for (int k = 2; k > j; k--) {
                            topSectors[k] = topSectors[k - 1];
                            topPops[k] = topPops[k - 1];
                        }
                        topSectors[j] = sector;
                        topPops[j] = pop;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            if (topSectors[i]) {
                Sector* sectData = (Sector*)topSectors[i]->getData();
                cout << (i + 1) << ". " << topSectors[i]->name
                    << " - " << topPops[i] << " people";
                if (sectData) {
                    cout << " (" << (sectData->totalHouses > 0 ?
                        (double)topPops[i] / sectData->totalHouses : 0)
                        << " people/house)";
                }
                cout << endl;
            }
        }

        cout << "\n========================================\n" << endl;
    }






    //// Display sector information - O(n)
    //void displaySectorInfo(string sectorName) {
    //    cout << "\n========== SECTOR INFORMATION: " << sectorName << " ==========" << endl;

    //    // Find the sector node
    //    TreeNode* sectorNode = findSectorNode(sectorName);

    //    if (!sectorNode) {
    //        cout << "Sector " << sectorName << " not found!" << endl;
    //        cout << "============================================\n" << endl;
    //        return;
    //    }

    //    // Get sector data
    //    Sector* sectData = (Sector*)sectorNode->getData();

    //    if (sectData) {
    //        cout << "Sector Name: " << sectorName << endl;
    //        cout << "Total Streets: " << sectData->streetCount << endl;
    //        cout << "Total Houses: " << sectData->totalHouses << endl;
    //        cout << "Total Population: " << sectData->totalPopulation << endl;

    //        if (sectData->totalHouses > 0) {
    //            cout << "Average Population per House: "
    //                << (double)sectData->totalPopulation / sectData->totalHouses << endl;
    //        }

    //        // Display streets in this sector
    //        if (sectorNode->childCount > 0) {
    //            cout << "\nStreets in " << sectorName << ":" << endl;
    //            for (int i = 0; i < sectorNode->childCount; i++) {
    //                TreeNode* streetNode = sectorNode->children[i];
    //                Street* streetData = (Street*)streetNode->getData();

    //                if (streetData) {
    //                    cout << "  " << (i + 1) << ". " << streetNode->name
    //                        << " - Houses: " << streetData->houseCount
    //                        << ", Population: " << streetData->totalPopulation << endl;
    //                }
    //            }
    //        }
    //    }
    //    else {
    //        cout << "No data available for sector " << sectorName << endl;
    //    }

    //    cout << "============================================\n" << endl;
    //}





};


