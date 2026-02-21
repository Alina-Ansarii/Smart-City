#pragma once
#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
#include "HashTable.h"
#include "MinHeap.h"
using namespace std;




////////////////  COMMERCIAL MODULE  //////////////////
//
//CommercialSector
//|---Graph (mallGraph)
//|   |---Stores mall locations as nodes
//|   |--- Edges represent distances between malls
//|
//|---HashTable (mallRegistry)
//|   |---Key : Mall name(string)
//|   |---Value : Mall * pointer
//|
//|--- IntHashTable (mallIdRegistry)
//|  |--- Key : Mall ID(int)
//|   |--- Value : Mall * pointer
//|
//|--- HashTable (productGlobal)
//|   |--- Key : Product name(string)
//|   |--- Value : Product * pointer
//|
//|--- HashTable (categoryProducts)
//|--- Key : Category name(string)
//|---Value : Linked list of Product* pointers




// ==================== PRODUCT STRUCTURE ====================
// note: products are stored in multiple pleaces (mall, global, category) -> same product ptr used everywhere
struct Product {
    int productId;
    string name;
    string category;        // Electronics, Clothing, Food, Books, etc.
    double price;
    string brand;
    int stock;
    string mallName;        // Which mall sells this product

    Product() {
        productId = 0;
        name = "";
        category = "";
        price = 0.0;
        brand = "";
        stock = 0;
        mallName = "";
    }

    Product(int id, string n, string cat, double p, string b, int s, string mall) {
        productId = id;
        name = n;
        category = cat;
        price = p;
        brand = b;
        stock = s;
        mallName = mall;
    }

    void display() {
        cout << "Product ID: " << productId << endl;
        cout << "Name: " << name << endl;
        cout << "Category: " << category << endl;
        cout << "Price: Rs. " << price << endl;
        cout << "Brand: " << brand << endl;
        cout << "Stock: " << stock << " units" << endl;
        cout << "Available at: " << mallName << endl;
        cout << "-----------------------------------" << endl;
    }
};


// ==================== MALL STRUCTURE ====================
struct Mall {
    int mallId;
    string name;
    string location;        // Sector/area name
    double latitude;
    double longitude;
    int totalShops;
    string openingHours;
    HashTable* products;    // Products available in this mall (product name -> Product*)

    Mall() {
        mallId = 0;
        name = "";
        location = "";
        latitude = 0.0;
        longitude = 0.0;
        totalShops = 0;
        openingHours = "";
        products = new HashTable(200);  // Each mall can have up to 200 products
    }

    Mall(int id, string n, string loc, double lat, double lon, int shops, string hours) {
        mallId = id;
        name = n;
        location = loc;
        latitude = lat;
        longitude = lon;
        totalShops = shops;
        openingHours = hours;
        products = new HashTable(200);
    }

    ~Mall() {
        // Clean up products, only delete one here
        string keys[200];
        int count;
        products->getAllKeys(keys, count);
        for (int i = 0; i < count; i++) {
            Product* p = (Product*)products->search(keys[i]);
            if (p) delete p;
        }
        delete products;
    }

    void display() {
        cout << "\n========================================" << endl;
        cout << "Mall ID: " << mallId << endl;
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Total Shops: " << totalShops << endl;
        cout << "Opening Hours: " << openingHours << endl;
        cout << "Total Products: " << products->getSize() << endl;
        cout << "========================================\n" << endl;
    }
};




////////// MAIN CLASS //////////////
// ==================== COMMERCIAL SECTOR CLASS ====================
class CommercialSector {
private:
    Graph* mallGraph;                    // Graph for mall locations and connectivity
    HashTable* mallRegistry;             // Mall lookup by name (mallName -> Mall*)
    IntHashTable* mallIdRegistry;        // Mall lookup by ID (mallId -> Mall*)
    HashTable* productGlobal;            // Global product search (productName -> Product*)
    HashTable* categoryProducts;         // Category-based search (category -> linked list of products)
    int mallCount;
    int productCount;

    // Structure for category product list
    struct ProductNode {
        Product* product;
        ProductNode* next;

        ProductNode(Product* p) {
            product = p;
            next = nullptr;
        }
    };

public:

    CommercialSector() {
        mallGraph = new Graph(100);      // Up to 100 malls
        mallRegistry = new HashTable(100);
        mallIdRegistry = new IntHashTable(100);
        productGlobal = new HashTable(500);  // Up to 500 unique products
        categoryProducts = new HashTable(50); // Product categories
        mallCount = 0;
        productCount = 0;
    }

    ~CommercialSector() {
        // Clean up malls
        string keys[100];
        int count;
        mallRegistry->getAllKeys(keys, count);
        for (int i = 0; i < count; i++) {
            Mall* m = (Mall*)mallRegistry->search(keys[i]);
            if (m) delete m;
        }

        // Clean up category lists
        string catKeys[50];
        int catCount;
        categoryProducts->getAllKeys(catKeys, catCount);
        for (int i = 0; i < catCount; i++) {
            ProductNode* head = (ProductNode*)categoryProducts->search(catKeys[i]);
            while (head) {
                ProductNode* temp = head;
                head = head->next;
                delete temp;  // don't delete product, it's owned by mall
            }
        }

        delete mallGraph;
        delete mallRegistry;
        delete mallIdRegistry;
        delete productGlobal;
        delete categoryProducts;
    }



    // ==================== MALL REGISTRATION ====================

    // Register a new shopping mall - O(1)
    /* 1. check if mall exists
    *  2. create new mall
    *  3. add to graph and hash tables
    */
    bool registerMall(int mallId, string name, string location, double latitude,
        double longitude, int totalShops, string openingHours) {

        // Check if mall already exists
        if (mallRegistry->contains(name)) {
            cout << "Error: Mall with name '" << name << "' already exists!" << endl;
            return false;
        }

        if (mallIdRegistry->contains(mallId)) {
            cout << "Error: Mall with ID " << mallId << " already exists!" << endl;
            return false;
        }

        // Create new mall
        Mall* newMall = new Mall(mallId, name, location, latitude, longitude, totalShops, openingHours);

        // Add to graph for location-based queries
        int graphIndex = mallGraph->addNode(newMall);
        if (graphIndex == -1) {
            cout << "Error: Graph capacity full!" << endl;
            delete newMall;
            return false;
        }

        // Add to hash tables for quick lookup
        mallRegistry->insert(name, newMall);
        mallIdRegistry->insert(mallId, newMall);

        mallCount++;

        cout << "Successfully registered mall: " << name << endl;
        return true;
    }


    // Connect two malls with distance - O(1)
    /* 1.
    */
    bool connectMalls(string mall1Name, string mall2Name, double distance) {
        Mall* m1 = (Mall*)mallRegistry->search(mall1Name);
        Mall* m2 = (Mall*)mallRegistry->search(mall2Name);

        if (!m1 || !m2) {
            cout << "Error: One or both malls not found!" << endl;
            return false;
        }

        int index1 = mallGraph->findNodeIndex(m1);
        int index2 = mallGraph->findNodeIndex(m2);

        if (index1 == -1 || index2 == -1) {
            cout << "Error: Mall not found in graph!" << endl;
            return false;
        }

        // Add bidirectional edge
        mallGraph->addEdge(index1, index2, distance);
        mallGraph->addEdge(index2, index1, distance);

        cout << "Connected " << mall1Name << " and " << mall2Name << " with distance " << distance << " km" << endl;
        return true;
    }



    // ==================== PRODUCT MANAGEMENT ====================

    // Add product to a specific mall - O(1) average
    /* 1. if mall exits, creat product
    *  2. add to malls hash table
    *  3. add to global product registry
    *  4. add to category based search
    */
    bool addProduct(string mallName, int productId, string productName,
        string category, double price, string brand, int stock) {

        Mall* mall = (Mall*)mallRegistry->search(mallName);
        if (!mall) {
            cout << "Error: Mall '" << mallName << "' not found!" << endl;
            return false;
        }

        // Create new product
        Product* newProduct = new Product(productId, productName, category, price, brand, stock, mallName);

        // Add to mall's product hash table
        mall->products->insert(productName, newProduct);

        // Add to global product registry
        productGlobal->insert(productName, newProduct);

        // Add to category-based search
        addToCategory(category, newProduct);

        productCount++;
        cout << "Added product '" << productName << "' to " << mallName << endl;
        return true;
    }


    // Add product to category list - O(1)
    void addToCategory(string category, Product* product) {
        ProductNode* existingList = (ProductNode*)categoryProducts->search(category);

        // create new node
        ProductNode* newNode = new ProductNode(product);

        if (existingList == nullptr) {
            categoryProducts->insert(category, newNode);      // first product in this category
        }
        else {
            // Add to front of list
            newNode->next = existingList;
            categoryProducts->update(category, newNode);
        }
    }



    // ==================== SEARCH FUNCTIONS ====================

    // Search product by name across all malls - O(1) average
    Product* searchProductByName(string productName) {
        Product* product = (Product*)productGlobal->search(productName);

        if (product) {
            cout << "\nProduct found:" << endl;
            product->display();
            return product;
        }
        else {
            cout << "Product '" << productName << "' not found in any mall." << endl;
            return nullptr;
        }
    }


    // Search products by category - O(n) where n is products in category
    void searchProductsByCategory(string category) {
        cout << "\n========== Products in category: " << category << " ==========" << endl;

        ProductNode* current = (ProductNode*)categoryProducts->search(category);

        if (!current) {
            cout << "No products found in category: " << category << endl;
            return;
        }

        int count = 0;
        while (current) {
            cout << "\n[" << (++count) << "]" << endl;
            current->product->display();
            current = current->next;
        }

        cout << "Total products in " << category << ": " << count << endl;
    }


    // Search products in a specific mall - O(n) where n is products in mall
    void searchProductsInMall(string mallName) {
        Mall* mall = (Mall*)mallRegistry->search(mallName);

        if (!mall) {
            cout << "Mall '" << mallName << "' not found!" << endl;
            return;
        }

        cout << "\n========== Products in " << mallName << " ==========" << endl;

        string productNames[200];
        int count;
        mall->products->getAllKeys(productNames, count);

        if (count == 0) {
            cout << "No products available in this mall." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            Product* p = (Product*)mall->products->search(productNames[i]);
            if (p) {
                cout << "\n[" << (i + 1) << "]" << endl;
                p->display();
            }
        }

        cout << "Total products: " << count << endl;
    }

    // Get mall by name - O(1)
    Mall* getMall(string mallName) {
        return (Mall*)mallRegistry->search(mallName);
    }

    // Get mall by ID - O(1)
    Mall* getMallById(int mallId) {
        return (Mall*)mallIdRegistry->search(mallId);
    }




    // ==================== NEAREST MALL FINDING ====================

    // Find nearest mall to a given location - O(n) where n is number of malls
    Mall* findNearestMall(double userLat, double userLon) {
        cout << "\nFinding nearest mall to location (" << userLat
            << ", " << userLon << ")..." << endl;

        if (mallCount == 0) {
            cout << "No malls registered!" << endl;
            return nullptr;
        }

        Mall* nearestMall = nullptr;
        double minDistance = 999999.0;

        // Check all malls
        string mallNames[100];
        int count;
        mallRegistry->getAllKeys(mallNames, count);

        for (int i = 0; i < count; i++) {
            Mall* mall = (Mall*)mallRegistry->search(mallNames[i]);
            if (mall) {
                double dist = Graph::calculateDistance(userLat, userLon,
                    mall->latitude, mall->longitude);

                if (dist < minDistance) {
                    minDistance = dist;
                    nearestMall = mall;
                }
            }
        }

        if (nearestMall) {
            cout << "Nearest mall: " << nearestMall->name << endl;
            cout << "Distance: " << minDistance << " km" << endl;
            nearestMall->display();
        }

        return nearestMall;
    }

    // Find shortest path between two malls - O(E log V)
    void findShortestPathBetweenMalls(string sourceMall, string destMall) {
        Mall* m1 = (Mall*)mallRegistry->search(sourceMall);
        Mall* m2 = (Mall*)mallRegistry->search(destMall);

        if (!m1 || !m2) {
            cout << "One or both malls not found!" << endl;
            return;
        }

        int sourceIndex = mallGraph->findNodeIndex(m1);
        int destIndex = mallGraph->findNodeIndex(m2);

        if (sourceIndex == -1 || destIndex == -1) {
            cout << "Mall not found in graph!" << endl;
            return;
        }

        double totalDistance;
        int* path = mallGraph->dijkstra(sourceIndex, destIndex, &totalDistance);

        if (!path) {
            cout << "No path found between " << sourceMall << " and " << destMall << endl;
            return;
        }

        int pathLength = path[0];

        cout << "\n========== Shortest Path ==========" << endl;
        cout << "From: " << sourceMall << endl;
        cout << "To: " << destMall << endl;
        cout << "Total Distance: " << totalDistance << " km" << endl;
        cout << "Path: ";

        for (int i = 1; i <= pathLength; i++) {
            Mall* mall = (Mall*)mallGraph->getNodeData(path[i]);
            if (mall) {
                cout << mall->name;
                if (i < pathLength) cout << " -> ";
            }
        }
        cout << endl;

        delete[] path;
    }


    // Get top N nearest malls using priority queue - O(n log n)
    void getTopNearestMalls(double userLat, double userLon, int topN) {
        cout << "\nFinding top " << topN << " nearest malls..." << endl;

        PriorityQueue nearestMalls(100);

        // Add all malls to priority queue with distance as priority
        string mallNames[100];
        int count;
        mallRegistry->getAllKeys(mallNames, count);

        for (int i = 0; i < count; i++) {
            Mall* mall = (Mall*)mallRegistry->search(mallNames[i]);
            if (mall) {
                double dist = Graph::calculateDistance(userLat, userLon,
                    mall->latitude, mall->longitude);

                // Priority is distance in meters (lower = closer)
                int priority = (int)(dist * 1000);
                nearestMalls.insert(priority, mall);
            }
        }

        cout << "\n========== Top " << topN << " Nearest Malls ==========" << endl;

        int displayed = 0;
        while (!nearestMalls.isEmpty() && displayed < topN) {
            int distance;
            void* data;

            if (nearestMalls.extractMin(&data, &distance)) {
                Mall* mall = (Mall*)data;
                cout << "\n[" << (displayed + 1) << "] " << mall->name << endl;
                cout << "    Location: " << mall->location << endl;
                cout << "    Distance: " << (distance / 1000.0) << " km" << endl;
                displayed++;
            }
        }
    }




    // ==================== DISPLAY FUNCTIONS ====================

    // Display all registered malls - O(n)
    void displayAllMalls() {
        cout << "\n========== All Registered Malls ==========" << endl;
        cout << "Total Malls: " << mallCount << endl;

        string mallNames[100];
        int count;
        mallRegistry->getAllKeys(mallNames, count);

        for (int i = 0; i < count; i++) {
            Mall* mall = (Mall*)mallRegistry->search(mallNames[i]);
            if (mall) {
                mall->display();
            }
        }
    }

    // Display all categories - O(n)
    void displayAllCategories() {
        cout << "\n========== Available Product Categories ==========" << endl;

        string categories[50];
        int count;
        categoryProducts->getAllKeys(categories, count);

        if (count == 0) {
            cout << "No categories available." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            ProductNode* current = (ProductNode*)categoryProducts->search(categories[i]);
            int productCount = 0;
            while (current) {
                productCount++;
                current = current->next;
            }

            cout << "[" << (i + 1) << "] " << categories[i]
                << " - " << productCount << " products" << endl;
        }
    }

    // Display statistics - O(n)
    void displayStatistics() {
        cout << "\n========== Commercial Sector Statistics ==========" << endl;
        cout << "Total Malls: " << mallCount << endl;
        cout << "Total Products: " << productCount << endl;

        string categories[50];
        int catCount;
        categoryProducts->getAllKeys(categories, catCount);
        cout << "Total Categories: " << catCount << endl;

        // Calculate average products per mall
        if (mallCount > 0) {
            cout << "Average Products per Mall: " << (productCount / mallCount) << endl;
        }

        // Find mall with most products
        string mallNames[100];
        int mallCnt;
        mallRegistry->getAllKeys(mallNames, mallCnt);

        int maxProducts = 0;
        string maxMall = "";

        for (int i = 0; i < mallCnt; i++) {
            Mall* mall = (Mall*)mallRegistry->search(mallNames[i]);
            if (mall && mall->products->getSize() > maxProducts) {
                maxProducts = mall->products->getSize();
                maxMall = mall->name;
            }
        }

        if (maxMall != "") {
            cout << "Mall with Most Products: " << maxMall
                << " (" << maxProducts << " products)" << endl;
        }

        cout << "========================================\n" << endl;
    }




    // ==================== UTILITY FUNCTIONS ====================

    // Get total number of malls - O(1)
    int getTotalMalls() {
        return mallCount;
    }

    // Get total number of products - O(1)
    int getTotalProducts() {
        return productCount;
    }

    // Check if mall exists - O(1)
    bool mallExists(string mallName) {
        return mallRegistry->contains(mallName);
    }

    // Check if product exists - O(1)
    bool productExists(string productName) {
        return productGlobal->contains(productName);
    }
};





