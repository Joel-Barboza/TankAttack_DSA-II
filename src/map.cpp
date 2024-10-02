#include "include/map.h"
#include <QWidget>
#include "include/adjacency_matrix.h"
#include "QGraphicsRectItem"
#include "include/square_items.h"
#include "include/game_state.h"

Map::Map(QWidget *parent, GameState* gameState) {

    createGrid(gameState->rows, gameState->columns, gameState->adjMatrix);
}


void Map::createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix) {
    int squareSize = 50;
    auto* currentListNode = adjMatrix->getHead();
    int i = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            SquareItem *square = new SquareItem(squareSize * col, squareSize * row, squareSize, squareSize, i++);

            square->setAcceptHoverEvents(true);
            if (currentListNode->weight == 0 && currentListNode->isOccupied) {
                square->setBrush(QColor("#90F545"));
                square->setAcceptHoverEvents(false);


            } else {
                square->setBrush(QColor("#B4C8C8"));
            }
            this->addItem(square);
            currentListNode = currentListNode->right;
            //if (currentListNode->next != nullptr) {
            //}
        }
    }
}
