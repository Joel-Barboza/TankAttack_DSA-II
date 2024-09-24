#ifndef ADYACENCY_MATRIX_H
#define ADYACENCY_MATRIX_H

#include "limits"

template<typename T>
class AdjacencyMatrix
{
public:
    // Takes nxm as the dimensions of the represented grid
    AdjacencyMatrix(int n /*s*/, int m);
    ~AdjacencyMatrix();

    void resetAllWeigths();
    // Sets weight of row i, column j node
    void setWeight(int i, int j);

    void setOccupied(int i, int j);

    void setFree(int i, int j);

    void placeObstacles();


private:
    struct Node {
        T weight;
        Node* right;
        Node* down;
        bool isOccupied;
        Node() : weight(std::numeric_limits<int>::max()), right(nullptr), down(nullptr), isOccupied(false)  {}
    };

    Node* head = nullptr;
    // Square matrix, order is equal to rows times columns of the grid
    int matrixOrder;
    int gridRows, gridColums = 0;
};

#endif // ADYACENCY_MATRIX_H
