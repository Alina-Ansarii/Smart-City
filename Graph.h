#pragma once
#pragma once
#pragma once
#include <iostream>
using namespace std;



class Graph {
protected:
    struct Edge {
        int destIndex;      // Index of destination node
        double weight;      // Distance/weight
        Edge* next;         // Next edge in list

        Edge(int dest, double w) {
            destIndex = dest;
            weight = w;
            next = nullptr;
        }
    };

    struct EdgeList {
        Edge* head;

        EdgeList() { head = nullptr; }

        ~EdgeList() {
            Edge* current = head;
            while (current != nullptr) {
                Edge* next = current->next;
                delete current;
                current = next;
            }
        }

        void append(Edge* edge) {
            if (head == nullptr) {
                head = edge;
            }
            else {
                Edge* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = edge;
            }
        }
    };

    struct GraphNode {
        void* data;         // Generic pointer to ANY object
        EdgeList* edges;    // Adjacency list

        GraphNode() {
            data = nullptr;
            edges = new EdgeList();
        }

        ~GraphNode() {
            delete edges;
            // Don't delete data - we don't own it!
        }
    };

    GraphNode** nodes;      // Array of nodes
    int nodeCount;
    int capacity;

public:
    Graph(int cap = 100) {
        capacity = cap;
        nodes = new GraphNode * [capacity];
        nodeCount = 0;
    }

    virtual ~Graph() {
        for (int i = 0; i < nodeCount; i++) {
            delete nodes[i];
        }
        delete[] nodes;
    }

    // COMMON FUNCTION: Add a node - O(1)
    int addNode(void* data) {
        if (nodeCount >= capacity) {
            return -1;  // Graph full
        }

        GraphNode* newNode = new GraphNode();
        newNode->data = data;

        nodes[nodeCount] = newNode;
        return nodeCount++;  // Return index of new node
    }

    // COMMON FUNCTION: Add an edge - O(1)
    bool addEdge(int sourceIndex, int destIndex, double weight) {
        if (sourceIndex < 0 || sourceIndex >= nodeCount ||
            destIndex < 0 || destIndex >= nodeCount) {
            return false;
        }

        Edge* edge = new Edge(destIndex, weight);
        nodes[sourceIndex]->edges->append(edge);
        return true;
    }

    // COMMON FUNCTION: Get node count - O(1)
    int getNodeCount() {
        return nodeCount;
    }

    // COMMON FUNCTION: Get node data - O(1)
    void* getNodeData(int index) {
        if (index < 0 || index >= nodeCount) {
            return nullptr;
        }
        return nodes[index]->data;
    }

    // COMMON FUNCTION: Find node index by data pointer - O(n)
    int findNodeIndex(void* data) {
        for (int i = 0; i < nodeCount; i++) {
            if (nodes[i]->data == data) {
                return i;
            }
        }
        return -1;
    }

    // COMMON FUNCTION: Get edges for a node - O(1)
    EdgeList* getEdges(int nodeIndex) {
        if (nodeIndex < 0 || nodeIndex >= nodeCount) {
            return nullptr;
        }
        return nodes[nodeIndex]->edges;
    }

    // COMMON FUNCTION: Dijkstra's shortest path - O(E log V)
    int* dijkstra(int startIndex, int endIndex, double* totalDistance) {
        // Implementation of Dijkstra's algorithm
        // Returns array of node indices representing path
        // Sets totalDistance to the total path weight

        if (startIndex < 0 || startIndex >= nodeCount ||
            endIndex < 0 || endIndex >= nodeCount) {
            return nullptr;
        }

        // Arrays for Dijkstra
        double* distances = new double[nodeCount];
        int* previous = new int[nodeCount];
        bool* visited = new bool[nodeCount];

        // Initialize
        for (int i = 0; i < nodeCount; i++) {
            distances[i] = 999999.0;  // Infinity
            previous[i] = -1;
            visited[i] = false;
        }
        distances[startIndex] = 0;

        // Dijkstra's algorithm
        for (int count = 0; count < nodeCount; count++) {
            // Find minimum distance unvisited node
            int minIndex = -1;
            double minDist = 999999.0;

            for (int i = 0; i < nodeCount; i++) {
                if (!visited[i] && distances[i] < minDist) {
                    minDist = distances[i];
                    minIndex = i;
                }
            }

            if (minIndex == -1) break;  // No path exists

            visited[minIndex] = true;

            // Update distances for neighbors
            Edge* edge = nodes[minIndex]->edges->head;
            while (edge != nullptr) {
                int neighbor = edge->destIndex;
                double newDist = distances[minIndex] + edge->weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    previous[neighbor] = minIndex;
                }
                edge = edge->next;
            }
        }

        // Reconstruct path
        if (distances[endIndex] == 999999.0) {
            // No path found
            delete[] distances;
            delete[] previous;
            delete[] visited;
            return nullptr;
        }

        // Count path length
        int pathLength = 0;
        int current = endIndex;
        while (current != -1) {
            pathLength++;
            current = previous[current];
        }

        // Build path array
        int* path = new int[pathLength + 1];  // +1 for length
        path[0] = pathLength;  // First element is path length

        current = endIndex;
        for (int i = pathLength; i >= 1; i--) {
            path[i] = current;
            current = previous[current];
        }

        *totalDistance = distances[endIndex];

        delete[] distances;
        delete[] previous;
        delete[] visited;

        return path;
    }

    // COMMON FUNCTION: Calculate Euclidean distance - O(1)
    static double calculateDistance(double lat1, double lon1,
        double lat2, double lon2) {
        double dx = lat2 - lat1;
        double dy = lon2 - lon1;
        return sqrt(dx * dx + dy * dy);
    }
};