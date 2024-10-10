#include <include/map.h>
#include <QWidget>
#include <include/adjacency_matrix.h>
#include <QGraphicsRectItem>
#include <include/square_items.h>
#include <include/game_state.h>
#include <QTimer>
#include <include/tank.h>


Map::Map(QWidget *parent) {
    createGrid(GameState::rows, GameState::columns, GameState::adjMatrix);
    Tank* yellowTank = new Tank(Tank::YellowTank, this);
    yellowTank->setPos(100, 100);
    this->addItem(yellowTank);
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

QGraphicsLineItem* Map::createLine(int x1, int y1, int x2, int y2) {
    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
    line->setZValue(4);
    this->addItem(line);
    return line;
}

void Map::drawPath(SinglyLinkedList<int>* list, int startX, int startY){
    auto* current = list->getHead();
    int previousX = startX;
    int previousY = startY;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (current->next != nullptr) {

            QPen pen(QColor("#2c2c90"), 3);
            pen.setStyle(Qt::DashLine);
            if (current->data == current->next->data - 1) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX+50, previousY);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                previousX += 50;
            } else if (current->data == current->next->data + 1) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX-50, previousY);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                previousX -= 50;
            } else if (current->data == current->next->data + GameState::columns) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX, previousY-50);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                previousY -= 50;
            } else if (current->data == current->next->data - GameState::columns) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX, previousY+50);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                previousY += 50;
            }
            current = current->next;
        } else {
            timer->stop();
            timer->deleteLater();
        }
    });

    timer->start(50);
};
