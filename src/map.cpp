#include "include/map.h"
#include <QWidget>
#include "include/adjacency_matrix.h"

// Helper function to create squares
QWidget* createSquare(int size, QString bgColor) {
    QWidget* square = new QWidget();
    square->setFixedSize(size, size);
    square->setStyleSheet(bgColor);
    return square;
}

// Constructor for the Map class
Map::Map(QWidget *parent, int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix) : QWidget(parent) {

    gridLayout = new QGridLayout(this);
    gridLayout->setHorizontalSpacing(1);
    gridLayout->setVerticalSpacing(1);
    setStyleSheet("background-color: blue;margin:0;");
    createGrid(numRows, numCols, adjMatrix);
}


void Map::createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix) {
    int squareSize = 30;
    auto* currentListNode = adjMatrix->getList()->getHead();
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (*currentListNode->data == -1) {
                QWidget* square = createSquare(squareSize, "background-color: sand;");
                gridLayout->addWidget(square, row, col);

            } else {
                QWidget* square = createSquare(squareSize, "background-color: grey;");
                gridLayout->addWidget(square, row, col);
            }
            if (currentListNode->next != nullptr) {
                currentListNode = currentListNode->next;
            }
        }
    }
}
