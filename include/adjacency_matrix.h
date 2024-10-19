#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include "limits"
#include "iostream"
#include "include/singly_linked_list.h"
#include "include/tank.h"



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

    void setOccupiedByTank(int nodeIndex);

    void setFreeOfTanks(int nodeIndex);

    void placeObstacles(SinglyLinkedList<Tank*>* player1TankList, SinglyLinkedList<Tank*>* player2TankList);

    auto* getHead();

    void dijkstra(int src);

    int getNodeWeight(int row, int column);

    int minDistance(SinglyLinkedList<int>* dist, SinglyLinkedList<bool>* sptSet);
    void printPath(int currentNode, SinglyLinkedList<int>*);
    // Saves the index of the previous graph node, path is gotten by recursively checking the previous node until source (-1) is reached
    SinglyLinkedList<int>* previousNode = new SinglyLinkedList<int>();

    SinglyLinkedList<int>* getPathTo(int nodeIndex);

    bool getIsUnreachable(int nodeIndex);

    bool getHasTank();
private:
    struct Node {
        int weight;
        Node* right;
        Node* down;
        bool isUnreachable;
        bool isTank;
        int index;
        //std::numeric_limits<int>::max()
        Node(int indx) : weight(0), right(nullptr), down(nullptr), isUnreachable(false), index(indx)  {}
    };

    Node* head = nullptr;
    // Square matrix, order is equal to rows times columns of the grid
    int matrixOrder = 0;
    int gridRows = 0;
    int gridColumns = 0;
    int numOfNodes = 0;

};

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
    const int  MAX_INT_VALUE = std::numeric_limits<int>::max();
    SinglyLinkedList<int>* dist = new SinglyLinkedList<int>();
    SinglyLinkedList<bool>* sptSet = new SinglyLinkedList<bool>();


    for (int i = 0; i < this->matrixOrder; i++){
        dist->insert(MAX_INT_VALUE);
        sptSet->insert(false);
        this->previousNode->changeValue(i, -1);
    }

    // Distance of source vertex from itself is always 0
    dist->changeValue(src, 0);

    for (int counter = 0; counter < this->matrixOrder; ++counter) {
        int u = minDistance(dist, sptSet);

        if (dist->getValue(u) == MAX_INT_VALUE) {
            break;
        }

        sptSet->changeValue(u, true);

        for (int v = 0; v < this->matrixOrder; v++) {
            int weight = this->getNodeWeight(u, v);

            if (!sptSet->getValue(v) && weight > 0 && dist->getValue(u) != MAX_INT_VALUE && dist->getValue(u) + weight < dist->getValue(v)) {
                dist->changeValue(v, dist->getValue(u) + weight);
                this->previousNode->changeValue(v, u);
            }
        }
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
SinglyLinkedList<int>* AdjacencyMatrix<T>::getPathTo(int nodeIndex) {
    SinglyLinkedList<int>* list = new SinglyLinkedList<int>();
    auto* current = this->previousNode->getHead();
    for (int i = 0; i < nodeIndex; ++i) {
        current = current->next;
    }
    int index = nodeIndex;
    while (this->previousNode->getValue(index) != -1) {
        list->insertFirst(index);
        index = this->previousNode->getValue(index);
    }
    list->insertFirst(index);
    return list;
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
void AdjacencyMatrix<T>::setOccupiedByTank(int nodeIndex)
{
    Node* currentRowElem = this->head;
    Node* currentColumnElem = this->head;
    for (int i = 0; i < nodeIndex; ++i) {
        currentRowElem = currentRowElem->down;
        currentColumnElem = currentColumnElem->right;
    }
    while (currentRowElem != nullptr) {
        currentRowElem->isTank = true;
        currentColumnElem->isTank = true;
        currentColumnElem->weight = 0;
        currentRowElem->isUnreachable = true;
        currentColumnElem->isUnreachable = true;
        currentRowElem = currentRowElem->right;
        currentColumnElem = currentColumnElem->down;
    }
}

template<typename T>
void AdjacencyMatrix<T>::setFreeOfTanks(int nodeIndex)
{
    Node* currentRowElem = this->head;
    Node* currentColumnElem = this->head;
    for (int i = 0; i < nodeIndex; ++i) {
        currentRowElem = currentRowElem->down;
        currentColumnElem = currentColumnElem->right;
    }
    while (currentRowElem != nullptr) {
        currentRowElem->isTank = false;
        currentColumnElem->isTank = false;
        currentColumnElem->weight = currentRowElem->weight;
        currentRowElem->isUnreachable = false;
        currentColumnElem->isUnreachable = false;
        currentRowElem = currentRowElem->right;
        currentColumnElem = currentColumnElem->down;
    }
}

template<typename T>
void AdjacencyMatrix<T>::resetAllWeigths() {
    Node* currentRowStart = this->head->down;
    while (currentRowStart != nullptr) {
        Node* currentColumn = currentRowStart;
        while (currentColumn != nullptr) {
            currentColumn->weight = 0;//std::numeric_limits<int>::max();
            currentColumn->isUnreachable = false;
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
void AdjacencyMatrix<T>::placeObstacles(SinglyLinkedList<Tank*>* player1TankList, SinglyLinkedList<Tank*>* player2TankList) {
    int matrixOrder = this->matrixOrder;
    SinglyLinkedList<int>* occupiedCells = new SinglyLinkedList<T>();
    auto* p1Current = player1TankList->getHead();
    auto* p2Current = player2TankList->getHead();

    while (p1Current != nullptr) {
        occupiedCells->insert(p1Current->data->getNodeIndexPos());
        occupiedCells->insert(p2Current->data->getNodeIndexPos());
        p1Current = p1Current->next;
        p2Current = p2Current->next;
    }

    srand(time(0));
    for (int i = 0; i <= this->matrixOrder/10; ++i) {
        int toPlaceObst = rand()%matrixOrder + 1;
        while (occupiedCells->find(toPlaceObst)) {
            toPlaceObst = rand()%matrixOrder + 1;
        }
        occupiedCells->insert(toPlaceObst);
    }

    auto* LinkedLhead = occupiedCells->getHead();
    int counter = 0;
    while (LinkedLhead != nullptr) {
        Node* currentRowElem = this->head;
        Node* currentColumnElem = this->head;
        for (int i = 0; i < LinkedLhead->data; ++i) {
            currentRowElem = currentRowElem->down;
            currentColumnElem = currentColumnElem->right;
        }
        while (currentRowElem != nullptr) {
            if (counter < 8) {
                currentRowElem->isTank = true;
                currentColumnElem->isTank = true;
                currentColumnElem->weight = 0;
            } else {
                currentRowElem->weight = 0;
                currentColumnElem->weight = 0;

            }
            currentRowElem->isUnreachable = true;
            currentColumnElem->isUnreachable = true;
            currentRowElem = currentRowElem->right;
            currentColumnElem = currentColumnElem->down;
        }
        ++counter;
        LinkedLhead = LinkedLhead->next;
    }
}





template<typename T>
int AdjacencyMatrix<T>::getNodeWeight(int row, int column) {
    Node* current = this->head;
    for (int i = 0; i < row; ++i) {
        current = current->down;
    }

    for (int j = 0; j < column; ++j) {
        current = current->right;
    }
    return current->weight;
}

template<typename T>
bool AdjacencyMatrix<T>::getIsUnreachable(int nodeIndex) {
    Node* current = this->head;
    for (int i = 0; i < nodeIndex/this->matrixOrder; ++i) {
        current = current->down;
    }
    for (int j = 0; j < nodeIndex%this->matrixOrder; ++j) {
        current = current->right;
    }
    return current->isUnreachable;
}

#endif // ADJACENCY_MATRIX_H
