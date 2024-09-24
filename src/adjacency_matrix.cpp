#include "include/adjacency_matrix.h"
#include "limits"


template<typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(int n, int m) {
    this->gridRows = n;
    this->gridColums = m;
    this->matrixOrder = n*m;
    head = new Node();
    head->down = new Node();

    Node* currentColumn = head;
    for (int i = 1; i < n*m - 1; ++i) {
        Node* newRight = new Node();

        currentColumn->right = newRight;
        currentColumn = currentColumn->right;
    }

    currentColumn = head;
    Node* currentRowStart = head->down;
    for (int i = 1; i < this->matrixOrder - 1; ++i) {
        for (int j = 1; j < this->matrixOrder; ++j) {
            Node* newDown = new Node();
            currentRowStart->down = newDown;
            currentColumn = currentColumn->right;
        }
        currentRowStart = currentRowStart->down;
    }
}

template<typename T>
void AdjacencyMatrix<T>::resetAllWeigths() {
    Node* currentColumn = head;
    Node* currentRowStart = head;
    for (int i = 1; i < this->matrixOrder; ++i) {
        for (int j = 1; j < this->matrixOrder; ++j) {
            currentColumn->weight = std::numeric_limits<int>::max();
            currentColumn->isOccupied = false;
            currentColumn = currentColumn->right;
        }
        currentRowStart = currentRowStart->down;
    }
}

/*-----------------------------------------------------
 *             in process
------------------------------------------------------*/
template<typename T>
void AdjacencyMatrix<T>::placeObstacles() {
    for (int i = 0; i < this->matrixOrder/8; ++i) {
        int randI = rand(this->gridRows);
        int randJ = rand(this->gridColums);


    }
}



template<typename T>
void AdjacencyMatrix<T>::setWeight(int i, int j) {

}

template<typename T>
void AdjacencyMatrix<T>::setOccupied(int i, int j) {

}

template<typename T>
void AdjacencyMatrix<T>::setFree(int i, int j) {

}



// template<typename T>


// template<typename T>

// template<typename T>
