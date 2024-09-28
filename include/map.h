#ifndef MAP_H
#define MAP_H

#include "include/adjacency_matrix.h"
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <include/game_state.h>

class Map : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr, GameState* gameState = nullptr);

private:
    // QGridLayout *gridLayout;
    void createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix);  // Helper function to create the grid
};


#endif // MAP_H
