#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include "limits"
#include "iostream"
#include "include/singly_linked_list.h"
// #include "include/paired_priority_queue.h"
#include "include/struct_int_data_pair.h"

template<typename T>
class AdjacencyMatrix
{
public:
    // Takes nxm as the dimensions of the represented grid
    AdjacencyMatrix(int n, int m);
    //~AdjacencyMatrix();

    void resetAllWeigths();
    // Sets weight of row i, column j node
    void setWeight(int i, int j, int weight);

    void addEdges();

    void printAdjMatrix();

    void setOccupied(int i, int j);

    // void setFree(int i, int j);

    void placeObstacles();

    //SinglyLinkedList<int*>* getList();

    auto* getHead();

    void dijkstra(int src);

    pairNode* findPairInList(SinglyLinkedList<pairNode>& list, int nodeIndex);

    int getNodeWeight(int row, int column);

    void printDistances(SinglyLinkedList<pairNode> &distances);

    int minDistance(SinglyLinkedList<int>* dist, SinglyLinkedList<bool>* sptSet);
    void printPath(int currentNode, SinglyLinkedList<int>*);
    // Saves the index of the previous graph node, path is gotten by recursively checking the previous node until source (-1) is reached
    SinglyLinkedList<int>* previousNode = new SinglyLinkedList<int>();

    SinglyLinkedList<int>* getPathTo(int nodeIndex, SinglyLinkedList<int>* list);
private:
    struct Node {
        int weight;
        Node* right;
        Node* down;
        bool isOccupied;
        int index;
        //std::numeric_limits<int>::max()
        Node(int indx) : weight(0), right(nullptr), down(nullptr), isOccupied(false), index(indx)  {}
    };

    Node* head = nullptr;
    // Square matrix, order is equal to rows times columns of the grid
    int matrixOrder = 0;
    int gridRows = 0;
    int gridColumns = 0;
    int numOfNodes = 0;
    //SinglyLinkedList<Node*>* list = new SinglyLinkedList<int*>();
    //pairNode d = new pairNode();

};

template<typename T>
auto* AdjacencyMatrix<T>::getHead(){
    return this->head;
}

template<typename T>
int AdjacencyMatrix<T>::minDistance(SinglyLinkedList<int>* dist, SinglyLinkedList<bool>* sptSet)
{
    int min = std::numeric_limits<int>::max();
    int min_index = -1;

    for (int v = 0; v < this->matrixOrder; v++) {

        if (sptSet->getValue(v) == false && dist->getValue(v) <= min) {
            min = dist->getValue(v);
            min_index = v;
        }
    }
    return min_index;
}



template<typename T>
void AdjacencyMatrix<T>::dijkstra(int src){
    const int  INT_MAX = std::numeric_limits<int>::max();
    SinglyLinkedList<int>* dist = new SinglyLinkedList<int>();
    SinglyLinkedList<bool>* sptSet = new SinglyLinkedList<bool>();


    for (int i = 0; i < this->matrixOrder; i++){
        dist->insert(INT_MAX);
        sptSet->insert(false);
        this->previousNode->changeValue(i, -1);
    }

    // Distance of source vertex from itself is always 0
    dist->changeValue(src, 0);

    for (int counter = 0; counter < this->matrixOrder; ++counter) {
        int u = minDistance(dist, sptSet);

        if (dist->getValue(u) == INT_MAX) {
            break;
        }

        sptSet->changeValue(u, true);

        for (int v = 0; v < this->matrixOrder; v++) {
            int weight = this->getNodeWeight(u, v);

            if (!sptSet->getValue(v) && weight > 0 && dist->getValue(u) != INT_MAX && dist->getValue(u) + weight < dist->getValue(v)) {
                dist->changeValue(v, dist->getValue(u) + weight);
                this->previousNode->changeValue(v, u);
            }
        }
    }

    // previousNode->print();

    std::cout << "Vertex\t Distance from Source\t Path" << std::endl;
    for (int i = 0; i < this->matrixOrder; i++) {
        std::cout << i << "\t\t" << dist->getValue(i) << "\t\t";
        printPath(i, previousNode);
        std::cout << std::endl;
    }
}

template<typename T>
void AdjacencyMatrix<T>::printPath(int currentNode, SinglyLinkedList<int>* previousNode) {
    if (currentNode == -1)
        return;  // Base case: no previousNode
    printPath(previousNode->getValue(currentNode), previousNode);  // Recursively print the path
    std::cout << currentNode << " ";
}

template<typename T>
SinglyLinkedList<int>* AdjacencyMatrix<T>::getPathTo(int nodeIndex, SinglyLinkedList<int>* list) {
    if (nodeIndex == -1) {
        return list;  // Base case: no previousNode
    }
    list->insert(nodeIndex);
    getPathTo(this->previousNode->getValue(nodeIndex), list);
}


/*// template<typename T>
// SinglyLinkedList<pairNode> AdjacencyMatrix<T>::dijkstra(int src)
// {
//     // Step 1: Create a SinglyLinkedList for distances initialized to infinity
//     SinglyLinkedList<pairNode> distances;
//     PairedPriorityQueue unvisitedNodes;

//     // Step 2: Initialize distances and the priority queue
//     for (int i = 0; i < matrixOrder; ++i) {
//         if (i == src) {
//             distances.insert(pairNode(0, i));  // Distance to source is 0
//             unvisitedNodes.enqueue(pairNode(0, i));  // Enqueue source
//         } else {
//             distances.insert(pairNode(std::numeric_limits<int>::max(), i));  // All other nodes are infinity
//         }
//     }

//     // Step 3: Main loop - process each node
//     while (unvisitedNodes.size > 0) {
//         auto* currentPair = unvisitedNodes.getFront();  // Get the node with the smallest distance
//         //unvisitedNodes.dequeue();  // Remove it from the queue

//         unvisitedNodes.printQueue();

//         printDistances(distances);

//         // Retrieve the node in the adjacency matrix
//         Node* currentNode = getNthNode(currentPair->nodeNum);

//         // Traverse neighbors (right and down in the matrix)
//         Node* neighbor = currentNode->right;
//         int neighborIndex = currentPair->nodeNum + 1;  // Neighbor index (to the right)
//         while (neighbor != nullptr) {
//             int weight = neighbor->weight;
//             std::cout << "Processing neighbor: " << neighborIndex << ", weight: " << weight << "\n";

//             if (weight > 0) {  // Valid edge
//                 pairNode* neighborDistancePair = findPairInList(distances, neighborIndex);
//                 int newDist = currentPair->distance + weight;

//                 // Debug: Print distance comparison
//                 std::cout << "Checking neighbor " << neighborIndex
//                           << ": Current Distance: " << neighborDistancePair->distance
//                           << ", New Distance: " << newDist << "\n";

//                 // If the new distance is shorter, update the distance and enqueue the neighbor
//                 if (newDist < neighborDistancePair->distance) {
//                     // Update distance in the list
//                     neighborDistancePair->distance = newDist;
//                     std::cout << "siuuuu" << "\n";

//                     // Enqueue the neighbor with the new distance
//                     unvisitedNodes.enqueue(pairNode(newDist, neighborIndex));
//                     unvisitedNodes.printQueue();
//                 }
//             }
//             neighbor = neighbor->right;  // Move to the next neighbor
//             neighborIndex++;
//         }
//     }

//     return distances;  // Return the list of shortest distances
// }

// template<typename T>
// void AdjacencyMatrix<T>::printDistances(SinglyLinkedList<pairNode>& distances) {
//     auto* current = distances.getHead();
//     std::cout << "Current distances:\n";
//     while (current != nullptr) {
//         std::cout << "Node: " << current->data.nodeIndex << ", Distance: " << current->data.distance << "\n";
//         current = current->next;
//     }
// }*/

template<typename T>
pairNode* AdjacencyMatrix<T>::findPairInList(SinglyLinkedList<pairNode>& list, int nodeIndex) {
    auto* current = list.getHead();
    while (current != nullptr) {
        if (current->data.nodeIndex == nodeIndex) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;  // Node not found
}

// bool getNodeWithLowestDistance(unvisitedNodes) {

// }


template<typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(int n, int m) {
    if (n <= 0 || m <= 0) {
        std::cerr << "Invalid matrix dimensions!" << std::endl;
        return;
    }
    int index = 0;
    this->head = new Node(index++);
    this->gridRows = n;
    this->gridColumns = m;
    this->matrixOrder = n * m;

    Node* currentColumn = this->head;
    for (int i = 1; i < matrixOrder; ++i) {
        Node* newRight = new Node(index++);
        currentColumn->right = newRight;
        currentColumn = currentColumn->right;
    }

    Node* currentRowStart = this->head;
    Node* previousRowNextColumn = this->head->right;
    for (int i = 1; i < matrixOrder; ++i) {
        Node* newNode = new Node(index++);
        currentRowStart->down = newNode;
        currentRowStart = currentRowStart->down;
        currentColumn = currentRowStart;
        while (previousRowNextColumn != nullptr) {
            Node* newNode = new Node(index++);
            previousRowNextColumn->down = newNode;
            currentColumn->right = newNode;
            currentColumn = currentColumn->right;
            previousRowNextColumn = previousRowNextColumn->right;

        }
        previousRowNextColumn = currentRowStart->right;
    }

    for (int i = 0; i < this->matrixOrder; i++){
        this->previousNode->insert(-1);
    }
}

template<typename T>
void AdjacencyMatrix<T>::printAdjMatrix() {
    Node* currentRowStart = this->head;
    while (currentRowStart != nullptr) {
        Node* currentColumn = currentRowStart;
        while (currentColumn != nullptr) {
            std::cout << currentColumn->weight << " ";
            currentColumn = currentColumn->right;
        }
        std::cout << "\n";
        currentRowStart = currentRowStart->down;
    }
}

template<typename T>
void AdjacencyMatrix<T>::resetAllWeigths() {
    Node* currentRowStart = this->head->down;
    while (currentRowStart != nullptr) {
        Node* currentColumn = currentRowStart;
        while (currentColumn != nullptr) {
            currentColumn->weight = 0;//std::numeric_limits<int>::max();
            currentColumn->isOccupied = false;
            currentColumn = currentColumn->right;
        }
        currentRowStart = currentRowStart->down;
    }
}

template<typename T>
void AdjacencyMatrix<T>::setWeight(int i, int j, int weight)
{
    Node* current = this->head;
    for (int row = 0; row < i; ++row) {
        current = current->down;
    }
    for (int column = 0; column < j; ++column) {
        current = current->right;
    }
    current->weight = weight;
}

template<typename T>
void AdjacencyMatrix<T>::addEdges()
{
    Node* currentRowStart = this->head;
    for (int i = 1; i <= matrixOrder; ++i) {
        Node* currentNode = currentRowStart;
        for (int j = 1; j <= matrixOrder; ++j) {

            if ((i+1==j && j%gridColumns != 1)|| (i-1==j && j%gridColumns != 0)) {
                currentNode->weight = 1;
            }
            if (i+gridColumns == j || (i-gridColumns) == j) {
                currentNode->weight = 1;
            }
            currentNode = currentNode->right;
        }
        currentRowStart = currentRowStart->down;
    }
}

template<typename T>
void AdjacencyMatrix<T>::placeObstacles() {
    int matrixOrder = this->matrixOrder;
    SinglyLinkedList<int>* occupiedCells = new SinglyLinkedList<T>();
    srand(time(0));
    for (int i = 1; i <= this->matrixOrder/10; ++i) {
        int toPlaceObst = rand()%matrixOrder + 1;
        while (occupiedCells->find(toPlaceObst)) {
            toPlaceObst = rand()%matrixOrder + 1;
        }
        occupiedCells->insert(toPlaceObst);
    }

    auto* LinkedLhead = occupiedCells->getHead();
    while (LinkedLhead != nullptr) {
        Node* currentRowElem = this->head;
        Node* currentColumnElem = this->head;
        for (int i = 0; i <= LinkedLhead->data; ++i) {
            currentRowElem = currentRowElem->down;
            currentColumnElem = currentColumnElem->right;
        }
        while (currentRowElem != nullptr) {
            currentRowElem->isOccupied = true;
            currentRowElem->weight = 0;
            currentColumnElem->isOccupied = true;
            currentColumnElem->weight = 0;
            currentRowElem = currentRowElem->right;
            currentColumnElem = currentColumnElem->down;
        }
        LinkedLhead = LinkedLhead->next;
    }
}

// template<typename T>
// SinglyLinkedList<int*>* AdjacencyMatrix<T>::getList() {
//     return this->list;
// }




template<typename T>
int AdjacencyMatrix<T>::getNodeWeight(int row, int column) {
    Node* current = this->head;
    // Move down to the correct row
    for (int i = 0; i < row; ++i) {
        //if (current == nullptr) return 0;  // Out of bounds, return 0 (no edge)
        current = current->down;
    }

    // Move right to the correct column
    for (int j = 0; j < column; ++j) {
        //if (current == nullptr) return 0;  // Out of bounds, return 0 (no edge)

        current = current->right;
    }
    return current->weight;
}

#endif // ADJACENCY_MATRIX_H
