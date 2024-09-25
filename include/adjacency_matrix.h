#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include "limits"
#include "iostream"

template<typename T>
class AdjacencyMatrix
{
public:
    // Takes nxm as the dimensions of the represented grid
    AdjacencyMatrix(int n, int m);
    //~AdjacencyMatrix();

    void resetAllWeigths();
    // Sets weight of row i, column j node
    // void setWeight(int i, int j);

    void printAdjMatrix();

    void setOccupied(int i, int j);

    // void setFree(int i, int j);

    // void placeObstacles();


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

// template<typename T>
// void AdjacencyMatrix<T>::setOccupied(int i, int j) {
//     if (i >= this->gridRows || j >= this->gridColumns ) {
//         std::cerr << "Invalid matrix element!" << std::endl;
//         return;
//     }
//     Node* current = this->head;

//     for (int row = 0; row < i; ++row) {
//         current = current->down;
//     }

//     for (int column = 0; column < j; ++column) {
//         current = current->right;
//     }

//     current->isOccupied = true;
// }

// template<typename T>
// void AdjacencyMatrix<T>::setOccupied(int i, int j) {
//     if (i >= this->gridRows || j >= this->gridColumns ) {
//         std::cerr << "Invalid matrix element!" << std::endl;
//         return;
//     }
//     Node* current = this->head;

//     for (int row = 0; row < i; ++row) {
//         current = current->down;
//     }

//     for (int column = 0; column < j; ++column) {
//         current = current->right;
//     }

//     current->isOccupied = true;
// }

#endif // ADJACENCY_MATRIX_H
