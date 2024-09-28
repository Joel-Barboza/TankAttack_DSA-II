#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

//#include "limits"
#include "iostream"
#include "include/singly_linked_list.h"

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

    SinglyLinkedList<int*>* getList();


private:
    struct Node {
        int weight;
        Node* right;
        Node* down;
        bool isOccupied;
        //std::numeric_limits<int>::max()
        Node() : weight(0), right(nullptr), down(nullptr), isOccupied(false)  {}
    };

    Node* head = nullptr;
    // Square matrix, order is equal to rows times columns of the grid
    int matrixOrder = 0;
    int gridRows = 0;
    int gridColumns = 0;
    SinglyLinkedList<int*>* list = new SinglyLinkedList<int*>();

};

template<typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(int n, int m) {
    if (n <= 0 || m <= 0) {
        std::cerr << "Invalid matrix dimensions!" << std::endl;
        return;
    }
    this->head = new Node();
    this->gridRows = n;
    this->gridColumns = m;
    this->matrixOrder = n * m;

    Node* currentColumn = this->head;
    for (int i = 1; i < matrixOrder; ++i) {
        Node* newRight = new Node();
        currentColumn->right = newRight;
        currentColumn = currentColumn->right;
        this->list->insert(&newRight->weight);
    }

    Node* currentRowStart = this->head;
    Node* previousRowNextColumn = this->head->right;
    for (int i = 1; i <= matrixOrder; ++i) {
            Node* newNode = new Node();
            currentRowStart->down = newNode;
            currentRowStart = currentRowStart->down;
            currentColumn = currentRowStart;
            while (previousRowNextColumn != nullptr) {
                Node* newNode = new Node();
                previousRowNextColumn->down = newNode;
                currentColumn->right = newNode;
                previousRowNextColumn->down = newNode;
                currentColumn = currentColumn->right;
                previousRowNextColumn = previousRowNextColumn->right;

            }
            previousRowNextColumn = currentRowStart->right;
    }
}

template<typename T>
void AdjacencyMatrix<T>::printAdjMatrix() {
    Node* currentRowStart = this->head->down;
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
    Node* currentRowStart = this->head->down;
    for (int i = 0; i < matrixOrder; ++i) {
        Node* currentColumn = currentRowStart;
        for (int j = 0; j < matrixOrder; ++j) {
            if (((i+1) == j&& j%gridColumns!=0) || ((i-1) == j && i%gridColumns!=0)) {
                currentColumn->weight = 1;
            }
            if (i+gridColumns == j || (i-gridColumns) == j) {
                currentColumn->weight = 1;
            }
            // std::cout << currentColumn->weight << " ";
            currentColumn = currentColumn->right;
        }
        // std::cout << "\n";
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

    auto* LinkedLhead =occupiedCells->getHead();
    while (LinkedLhead != nullptr) {
        Node* currentRowElem = this->head;
        Node* currentColumnElem = this->head;
        for (int i = 0; i < LinkedLhead->data; ++i) {
            currentRowElem = currentRowElem->down;
            currentColumnElem = currentColumnElem->right;
        }
        while (currentRowElem != nullptr) {
            currentRowElem->isOccupied = true;
            currentRowElem->weight = -1;
            currentColumnElem->isOccupied = true;
            currentColumnElem->weight = -1;
            currentRowElem = currentRowElem->right;
            currentColumnElem = currentColumnElem->down;
        }
        LinkedLhead = LinkedLhead->next;
    }
}

template<typename T>
SinglyLinkedList<int*>* AdjacencyMatrix<T>::getList() {
    return this->list;
}



#endif // ADJACENCY_MATRIX_H
