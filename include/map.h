#ifndef MAP_H
#define MAP_H

#include "include/adjacency_matrix.h"
#include <QWidget>
#include <QGridLayout>
class Map : public QWidget {
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr, int rows = 1, int columns = 1, AdjacencyMatrix<int>* adjMatrix = nullptr);

private:
    QGridLayout *gridLayout;
    void createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix);  // Helper function to create the grid
};


#endif // MAP_H
