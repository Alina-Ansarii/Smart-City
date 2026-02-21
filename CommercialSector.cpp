//#pragma once
//#include <iostream>
//#include <string>
//#include "Graph.h"
//#include "HashTable.h"
//#include "MinHeap.h"
//#include "CommercialSector.h"
//using namespace std;
//
//
//void printMenu() {
//    cout << "\n======================================================" << endl;
//    cout << "           COMMERCIAL SECTOR - SMART CITY" << endl;
//    cout << "======================================================" << endl;
//    cout << "1.  Register a Mall" << endl;
//    cout << "2.  Connect Two Malls" << endl;
//    cout << "3.  Add Product to Mall" << endl;
//    cout << "4.  Search Product by Name" << endl;
//    cout << "5.  Search Products by Category" << endl;
//    cout << "6.  View Products in a Mall" << endl;
//    cout << "7.  Find Nearest Mall to Location" << endl;
//    cout << "8.  Find Top N Nearest Malls" << endl;
//    cout << "9.  Find Shortest Path Between Malls" << endl;
//    cout << "10. Display All Malls" << endl;
//    cout << "11. Display All Categories" << endl;
//    cout << "12. Display Statistics" << endl;
//    cout << "13. Load Sample Data" << endl;
//    cout << "0.  Exit" << endl;
//    cout << "======================================================" << endl;
//    cout << "Enter your choice: ";
//}
//
//// Load sample data for testing
//void loadSampleData(CommercialSector& sector) {
//    cout << "\nLoading sample data..." << endl;
//
//    // Register malls with realistic Islamabad locations
//    sector.registerMall(1, "Centaurus Mall", "F-8", 33.708, 73.041, 200, "10:00 AM - 10:00 PM");
//    sector.registerMall(2, "The Centaurus", "Blue Area", 33.720, 73.065, 150, "10:00 AM - 11:00 PM");
//    sector.registerMall(3, "Giga Mall", "DHA Phase 2", 33.540, 73.130, 180, "11:00 AM - 11:00 PM");
//    sector.registerMall(4, "Safa Gold Mall", "F-7", 33.721, 73.052, 120, "10:00 AM - 9:00 PM");
//    sector.registerMall(5, "Jinnah Super Market", "F-7", 33.725, 73.055, 100, "9:00 AM - 10:00 PM");
//
//    // Connect malls with distances (in km)
//    sector.connectMalls("Centaurus Mall", "The Centaurus", 2.5);
//    sector.connectMalls("Centaurus Mall", "Safa Gold Mall", 1.8);
//    sector.connectMalls("The Centaurus", "Safa Gold Mall", 1.2);
//    sector.connectMalls("Safa Gold Mall", "Jinnah Super Market", 0.5);
//    sector.connectMalls("Centaurus Mall", "Giga Mall", 12.5);
//    sector.connectMalls("The Centaurus", "Giga Mall", 14.0);
//
//    // Add Electronics products
//    sector.addProduct("Centaurus Mall", 1001, "Samsung Galaxy S23", "Electronics", 189999, "Samsung", 25);
//    sector.addProduct("Centaurus Mall", 1002, "iPhone 15 Pro", "Electronics", 429999, "Apple", 15);
//    sector.addProduct("Giga Mall", 1003, "Dell Laptop XPS 15", "Electronics", 299999, "Dell", 10);
//    sector.addProduct("The Centaurus", 1004, "Sony PlayStation 5", "Electronics", 149999, "Sony", 20);
//    sector.addProduct("Safa Gold Mall", 1005, "Apple MacBook Pro", "Electronics", 549999, "Apple", 8);
//
//    // Add Clothing products
//    sector.addProduct("Centaurus Mall", 2001, "Levi's Jeans", "Clothing", 8999, "Levi's", 50);
//    sector.addProduct("Jinnah Super Market", 2002, "Nike T-Shirt", "Clothing", 3500, "Nike", 100);
//    sector.addProduct("The Centaurus", 2003, "Adidas Sneakers", "Clothing", 12999, "Adidas", 40);
//    sector.addProduct("Giga Mall", 2004, "Zara Dress", "Clothing", 7500, "Zara", 30);
//
//    // Add Food products
//    sector.addProduct("Centaurus Mall", 3001, "Nestle Coffee", "Food", 450, "Nestle", 200);
//    sector.addProduct("Jinnah Super Market", 3002, "Shan Biryani Masala", "Food", 120, "Shan", 500);
//    sector.addProduct("Safa Gold Mall", 3003, "Tapal Tea", "Food", 350, "Tapal", 300);
//    sector.addProduct("The Centaurus", 3004, "Olpers Milk", "Food", 280, "Olpers", 150);
//
//    // Add Books
//    sector.addProduct("Centaurus Mall", 4001, "The Alchemist", "Books", 1200, "Paulo Coelho", 20);
//    sector.addProduct("Safa Gold Mall", 4002, "Atomic Habits", "Books", 1500, "James Clear", 15);
//    sector.addProduct("The Centaurus", 4003, "Rich Dad Poor Dad", "Books", 900, "Robert Kiyosaki", 25);
//
//    // Add Furniture
//    sector.addProduct("Giga Mall", 5001, "Office Chair", "Furniture", 15000, "IKEA", 12);
//    sector.addProduct("Giga Mall", 5002, "Dining Table Set", "Furniture", 85000, "HomeStyle", 5);
//    sector.addProduct("Centaurus Mall", 5003, "Sofa 3-Seater", "Furniture", 120000, "Interwood", 8);
//
//    cout << "\nSample data loaded successfully!" << endl;
//    cout << "- 5 Malls registered" << endl;
//    cout << "- 20 Products added" << endl;
//    cout << "- 5 Categories created" << endl;
//}
//
//int main() {
//    CommercialSector commercialSector;
//    int choice;
//
//    do {
//        printMenu();
//        cin >> choice;
//        cin.ignore(); // Clear newline from buffer
//
//        switch (choice) {
//        case 1: {
//            // Register a Mall
//            int mallId;
//            string name, location, hours;
//            double lat, lon;
//            int shops;
//
//            cout << "\n--- Register New Mall ---" << endl;
//            cout << "Enter Mall ID: ";
//            cin >> mallId;
//            cin.ignore();
//
//            cout << "Enter Mall Name: ";
//            getline(cin, name);
//
//            cout << "Enter Location (Sector): ";
//            getline(cin, location);
//
//            cout << "Enter Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Longitude: ";
//            cin >> lon;
//
//            cout << "Enter Total Shops: ";
//            cin >> shops;
//            cin.ignore();
//
//            cout << "Enter Opening Hours (e.g., 10:00 AM - 10:00 PM): ";
//            getline(cin, hours);
//
//            commercialSector.registerMall(mallId, name, location, lat, lon, shops, hours);
//            break;
//        }
//
//        case 2: {
//            // Connect Two Malls
//            string mall1, mall2;
//            double distance;
//
//            cout << "\n--- Connect Two Malls ---" << endl;
//            cout << "Enter First Mall Name: ";
//            getline(cin, mall1);
//
//            cout << "Enter Second Mall Name: ";
//            getline(cin, mall2);
//
//            cout << "Enter Distance (km): ";
//            cin >> distance;
//
//            commercialSector.connectMalls(mall1, mall2, distance);
//            break;
//        }
//
//        case 3: {
//            // Add Product to Mall
//            string mallName, productName, category, brand;
//            int productId, stock;
//            double price;
//
//            cout << "\n--- Add Product to Mall ---" << endl;
//            cout << "Enter Mall Name: ";
//            getline(cin, mallName);
//
//            cout << "Enter Product ID: ";
//            cin >> productId;
//            cin.ignore();
//
//            cout << "Enter Product Name: ";
//            getline(cin, productName);
//
//            cout << "Enter Category: ";
//            getline(cin, category);
//
//            cout << "Enter Price (Rs.): ";
//            cin >> price;
//            cin.ignore();
//
//            cout << "Enter Brand: ";
//            getline(cin, brand);
//
//            cout << "Enter Stock: ";
//            cin >> stock;
//
//            commercialSector.addProduct(mallName, productId, productName,
//                category, price, brand, stock);
//            break;
//        }
//
//        case 4: {
//            // Search Product by Name
//            string productName;
//
//            cout << "\n--- Search Product by Name ---" << endl;
//            cout << "Enter Product Name: ";
//            getline(cin, productName);
//
//            commercialSector.searchProductByName(productName);
//            break;
//        }
//
//        case 5: {
//            // Search Products by Category
//            string category;
//
//            cout << "\n--- Search Products by Category ---" << endl;
//            cout << "Enter Category: ";
//            getline(cin, category);
//
//            commercialSector.searchProductsByCategory(category);
//            break;
//        }
//
//        case 6: {
//            // View Products in a Mall
//            string mallName;
//
//            cout << "\n--- View Products in Mall ---" << endl;
//            cout << "Enter Mall Name: ";
//            getline(cin, mallName);
//
//            commercialSector.searchProductsInMall(mallName);
//            break;
//        }
//
//        case 7: {
//            // Find Nearest Mall
//            double lat, lon;
//
//            cout << "\n--- Find Nearest Mall ---" << endl;
//            cout << "Enter Your Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Your Longitude: ";
//            cin >> lon;
//
//            commercialSector.findNearestMall(lat, lon);
//            break;
//        }
//
//        case 8: {
//            // Find Top N Nearest Malls
//            double lat, lon;
//            int n;
//
//            cout << "\n--- Find Top N Nearest Malls ---" << endl;
//            cout << "Enter Your Latitude: ";
//            cin >> lat;
//
//            cout << "Enter Your Longitude: ";
//            cin >> lon;
//
//            cout << "Enter Number of Malls (N): ";
//            cin >> n;
//
//            commercialSector.getTopNearestMalls(lat, lon, n);
//            break;
//        }
//
//        case 9: {
//            // Find Shortest Path Between Malls
//            string source, dest;
//
//            cout << "\n--- Find Shortest Path Between Malls ---" << endl;
//            cout << "Enter Source Mall Name: ";
//            getline(cin, source);
//
//            cout << "Enter Destination Mall Name: ";
//            getline(cin, dest);
//
//            commercialSector.findShortestPathBetweenMalls(source, dest);
//            break;
//        }
//
//        case 10: {
//            // Display All Malls
//            commercialSector.displayAllMalls();
//            break;
//        }
//
//        case 11: {
//            // Display All Categories
//            commercialSector.displayAllCategories();
//            break;
//        }
//
//        case 12: {
//            // Display Statistics
//            commercialSector.displayStatistics();
//            break;
//        }
//
//        case 13: {
//            // Load Sample Data
//            loadSampleData(commercialSector);
//            break;
//        }
//
//        case 0: {
//            cout << "\nExiting Commercial Sector Module..." << endl;
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
//            cin.ignore();
//            cin.get();
//        }
//
//    } while (choice != 0);
//
//    return 0;
//}
//
//// ==================== ADDITIONAL TEST FUNCTIONS ====================
//
//// Test function for automated testing
//void runAutomatedTests() {
//    cout << "\n========== RUNNING AUTOMATED TESTS ==========" << endl;
//
//    CommercialSector sector;
//
//    // Test 1: Register Malls
//    cout << "\nTest 1: Registering Malls..." << endl;
//    sector.registerMall(1, "Test Mall 1", "G-10", 33.684, 73.025, 100, "10-10");
//    sector.registerMall(2, "Test Mall 2", "F-8", 33.709, 73.037, 150, "9-11");
//
//    // Test 2: Add Products
//    cout << "\nTest 2: Adding Products..." << endl;
//    sector.addProduct("Test Mall 1", 1, "Product A", "Category1", 1000, "Brand A", 50);
//    sector.addProduct("Test Mall 1", 2, "Product B", "Category1", 2000, "Brand B", 30);
//    sector.addProduct("Test Mall 2", 3, "Product C", "Category2", 1500, "Brand C", 40);
//
//    // Test 3: Search by Name
//    cout << "\nTest 3: Searching Product by Name..." << endl;
//    sector.searchProductByName("Product A");
//
//    // Test 4: Search by Category
//    cout << "\nTest 4: Searching by Category..." << endl;
//    sector.searchProductsByCategory("Category1");
//
//    // Test 5: Find Nearest Mall
//    cout << "\nTest 5: Finding Nearest Mall..." << endl;
//    sector.findNearestMall(33.700, 73.030);
//
//    // Test 6: Statistics
//    cout << "\nTest 6: Displaying Statistics..." << endl;
//    sector.displayStatistics();
//
//    cout << "\n========== ALL TESTS COMPLETED ==========" << endl;
//}
//
//// Example usage scenarios
//void demonstrateUseCases() {
//    cout << "\n========== USE CASE DEMONSTRATIONS ==========" << endl;
//
//    CommercialSector sector;
//
//    // Use Case 1: Customer looking for specific product
//    cout << "\n--- Use Case 1: Customer searching for iPhone ---" << endl;
//    loadSampleData(sector);
//    sector.searchProductByName("iPhone 15 Pro");
//
//    // Use Case 2: Customer wants to see all electronics
//    cout << "\n--- Use Case 2: Browse all Electronics ---" << endl;
//    sector.searchProductsByCategory("Electronics");
//
//    // Use Case 3: Customer at specific location wants nearest mall
//    cout << "\n--- Use Case 3: Find nearest mall from G-9 ---" << endl;
//    sector.findNearestMall(33.700, 73.030);
//
//    // Use Case 4: Compare products in specific mall
//    cout << "\n--- Use Case 4: What's available in Centaurus Mall? ---" << endl;
//    sector.searchProductsInMall("Centaurus Mall");
//
//    // Use Case 5: Planning route between malls
//    cout << "\n--- Use Case 5: Route from Centaurus to Giga Mall ---" << endl;
//    sector.findShortestPathBetweenMalls("Centaurus Mall", "Giga Mall");
//}