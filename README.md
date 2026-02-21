# 🏙️ Smart City — Data Structures Project

A Smart City simulation system built in **C++** that models real-world urban infrastructure using core data structures. The system handles city navigation, traffic management, emergency services, and resource/utility management — all powered by efficient data structure implementations.

---

## 🌆 About the Project

This project simulates a smart city environment where various city systems interact with each other. From finding the shortest route across the city to dispatching emergency services and managing utilities, every feature is backed by an appropriate data structure chosen for optimal performance.

---

## ✨ Features

- 🗺️ **City Navigation & Routing** — Find shortest paths between city locations using graph traversal algorithms
- 🚦 **Traffic Management** — Monitor and manage traffic flow across city roads and intersections
- 🚨 **Emergency Services** — Dispatch ambulances, fire trucks, and police using priority-based systems
- ⚡ **Resource & Utility Management** — Track and allocate city resources like power, water, and waste

---

## 🛠️ Data Structures Used

| Data Structure | Use Case |
|---|---|
| **Graph** | City road network, routing between locations |
| **AVL / BST Tree** | Sorted lookup of city records and locations |
| **Heap (Priority Queue)** | Emergency dispatch prioritization |
| **Hash Table** | Fast lookup of city resources and utilities |
| **Queue / Stack** | Traffic flow simulation, request processing |
| **Linked List** | Dynamic management of city entities |

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/Alina-Ansarii/Smart-City.git
   ```
2. Open the project in **Visual Studio** or compile via terminal:
   ```bash
   g++ -o SmartCity main.cpp -std=c++17
   ./SmartCity
   ```

---

## 📁 Project Structure

```
Smart-City/
├── main.cpp               # Entry point
├── graph.h/.cpp           # City road network (Graph)
├── avl.h/.cpp             # AVL / BST Tree implementation
├── heap.h/.cpp            # Priority queue for emergency services
├── hashtable.h/.cpp       # Hash table for resource management
├── queue.h/.cpp           # Queue/Stack for traffic simulation
├── linkedlist.h/.cpp      # Linked list utilities
└── README.md              # Project documentation
```

> File names may vary — update this to match your actual structure.

---

## 👥 Authors

- **Alina Ansari** — [GitHub](https://github.com/Alina-Ansarii)

---

## 📚 Course

**Data Structures (DS)**  
3rd Semester — FAST NUCES

---

## 📄 License

This project was developed for academic purposes.
