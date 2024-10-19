#include <include/map.h>
#include <QWidget>
#include <include/adjacency_matrix.h>
#include <QGraphicsRectItem>
#include <include/square_items.h>
#include <include/game_state.h>
#include <QTimer>
#include <QDebug>
#include <include/tank.h>


Map::Map(QWidget *parent) {
    createGrid(GameState::rows, GameState::columns, GameState::adjMatrix);

    auto* p1Current = GameState::player1TankList->getHead();
    auto* p2Current = GameState::player2TankList->getHead();
    while (p1Current != nullptr) {

        this->addItem(p1Current->data);
        this->addItem(p2Current->data);

        p1Current = p1Current->next;
        p2Current = p2Current->next;
    }
}


void Map::createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix) {
    int squareSize = 50;
    auto* currentListNode = adjMatrix->getHead();
    int i = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            SquareItem *square = new SquareItem(squareSize * col, squareSize * row, squareSize, squareSize, i++);

            square->setAcceptHoverEvents(true);
            if (currentListNode->weight == 0 && currentListNode->isUnreachable && !currentListNode->isTank) {
                square->setBrush(QColor("#90F545"));
                square->setAcceptHoverEvents(false);


            } else {
                square->setBrush(QColor("#B4C8C8"));
            }
            this->addItem(square);
            currentListNode = currentListNode->right;
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

    if (timer) return;

    SinglyLinkedList<DataPair<QPoint, QPoint>*>* pointList = new SinglyLinkedList<DataPair<QPoint, QPoint>*>();
    auto* current = list->getHead();
    int previousX = startX;
    int previousY = startY;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (current->next != nullptr) {

            QPen pen(QColor("#2c2c99"), 5);
            pen.setStyle(Qt::DashLine);
            DataPair<QPoint, QPoint>* pointsToStraightLine = new DataPair<QPoint, QPoint>();
            if (current->data == current->next->data - 1) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX+50, previousY);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                pointsToStraightLine->setFirst(QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(QPoint(previousX+50, previousY));
                previousX += 50;
            } else if (current->data == current->next->data + 1) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX-50, previousY);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                pointsToStraightLine->setFirst(*new QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(*new QPoint(previousX-50, previousY));
                previousX -= 50;
            } else if (current->data == current->next->data + GameState::columns) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX, previousY-50);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                pointsToStraightLine->setFirst(*new QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(*new QPoint(previousX, previousY-50));
                previousY -= 50;
            } else if (current->data == current->next->data - GameState::columns) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX, previousY+50);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                pointsToStraightLine->setFirst(*new QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(*new QPoint(previousX, previousY+50));
                previousY += 50;
            }
            pointList->insert(pointsToStraightLine);
            current = current->next;
        } else {
            timer->stop();
            timer->deleteLater();
            timer = nullptr;
            moveTank(pointList);
        }
    });

    timer->start(20);
};


void Map::moveTank(SinglyLinkedList<DataPair<QPoint, QPoint>*>* pointList){
    auto* current = pointList->getHead();
    Tank* tank= GameState::pair->getFirst();
    auto* pathLinesListNode = GameState::pathLinesList->getHead();
    QTimer* timer2 = new QTimer(this);

    connect(timer2, &QTimer::timeout, this, [=]() mutable {
        if (current != nullptr) {
            if (!timer) {
                moveTankToNeighbor(current->data->getFirst(), current->data->getSecond());
                delete pathLinesListNode->data;

                current = current->next;
                pathLinesListNode = pathLinesListNode->next;
            }

        } else {
            timer2->stop();
            timer2->deleteLater();
            timer2 = nullptr;
            GameState::adjMatrix->setFreeOfTanks(tank->getNodeIndexPos());
            tank->setGridPosition(GameState::pair->getSecond()->squareId/GameState::columns, GameState::pair->getSecond()->squareId%GameState::columns);
            GameState::adjMatrix->setOccupiedByTank(tank->getNodeIndexPos());
            GameState::pathLinesList->clear();

        }

    });

    timer2->start(00);
};

void Map::moveTankToNeighbor(QPoint startPoint, QPoint endPoint){
    Tank* tank= GameState::pair->getFirst();
    timer = new QTimer(this);
    if (startPoint.rx() < endPoint.rx() &&
        startPoint.ry() == endPoint.ry()) {
        tank->rotateEast();

    } else if (startPoint.rx() > endPoint.rx() &&
               startPoint.ry() == endPoint.ry()
               ) {
        tank->rotateWest();

    } else if (startPoint.rx() == endPoint.rx() &&
               startPoint.ry() < endPoint.ry()
               ) {
        tank->rotateSouth();

    } else if (startPoint.rx() == endPoint.rx() &&
               startPoint.ry() > endPoint.ry()
               ) {
        tank->rotateNorth();

    }
    int startX = startPoint.rx();
    int startY = startPoint.ry();
    int xDir = (endPoint.rx()-startPoint.rx())/50;
    int yDir = (endPoint.ry()-startPoint.ry())/50;
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (startX != endPoint.rx() || startY != endPoint.ry()) {
            startX = startX+xDir*2;
            startY = startY+yDir*2;
            tank->setCenteredPos(startX, startY);

        } else {
            timer->stop();
            timer->deleteLater();
            timer = nullptr;
        }
    });

    timer->start(5);
};
