#include <include/map.h>
#include <QWidget>
#include <include/adjacency_matrix.h>
#include <QGraphicsRectItem>
#include <include/square_items.h>
#include <include/game_state.h>
#include <QTimer>
#include <QDebug>
#include <include/tank.h>
#include <include/bullet.h>


Map::Map(QWidget *parent) {
    createGrid(GameState::rows, GameState::columns, GameState::adjMatrix);

    auto* p1Current = GameState::player1->tankList->getHead();
    auto* p2Current = GameState::player2->tankList->getHead();
    while (p1Current != nullptr) {

        this->addItem(p1Current->data);
        this->addItem(p2Current->data);

        p1Current = p1Current->next;
        p2Current = p2Current->next;
    }
}


void Map::createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix) {
    int squareSize = 50;
    QRectF sceneRect = this->sceneRect();
    qDebug()<< sceneRect.width()/*<< << << */<< "\n";

    // Initialize the walls and add them to the scene
    topWall = new QGraphicsRectItem(0, 0, 1210, 5);
    bottomWall = new QGraphicsRectItem(0, 705, 1210, 5);
    leftWall = new QGraphicsRectItem(0, 5, 5, 700);
    rightWall = new QGraphicsRectItem(1205, 5, 5, 700);
    topWall->setBrush(QColor(0x50C005)); // #50C005
    bottomWall->setBrush(QColor(0x50C005));
    leftWall->setBrush(QColor(0x50C005));
    rightWall->setBrush(QColor(0x50C005));
    topWall->setZValue(5);// #90F545
    bottomWall->setZValue(5);
    leftWall->setZValue(5);
    rightWall->setZValue(5);
    topWall->setPen(Qt::NoPen);
    bottomWall->setPen(Qt::NoPen);
    leftWall->setPen(Qt::NoPen);
    rightWall->setPen(Qt::NoPen);


    this->addItem(topWall);
    this->addItem(bottomWall);
    this->addItem(leftWall);
    this->addItem(rightWall);
    auto* currentListNode = adjMatrix->getHead();
    int i = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            SquareItem *square = new SquareItem(squareSize * col+5, squareSize * row+5, squareSize, squareSize, i++);

            square->setAcceptHoverEvents(true);
            if ((currentListNode->weight == 0 && currentListNode->isUnreachable && !currentListNode->isTank) || (col == 0 && row == 0)) {
                square->setBrush(QColor(0x90F545));
                square->setAcceptHoverEvents(false);
                GameState::obstacleList->insert(square);


            } else {
                square->setBrush(QColor(0xB4C8C8));
            }
            this->addItem(square);
            currentListNode->weight = 0;
            currentListNode = currentListNode->down;
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

            QPen pen(QColor(0x2c2c99), 5);
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
                pointsToStraightLine->setFirst(QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(QPoint(previousX-50, previousY));
                previousX -= 50;
            } else if (current->data == current->next->data + GameState::columns) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX, previousY-50);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                pointsToStraightLine->setFirst(QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(QPoint(previousX, previousY-50));
                previousY -= 50;
            } else if (current->data == current->next->data - GameState::columns) {
                QGraphicsLineItem* newLine = createLine(previousX, previousY, previousX, previousY+50);
                newLine->setPen(pen);
                GameState::pathLinesList->insert(newLine);
                pointsToStraightLine->setFirst(QPoint(previousX, previousY));
                pointsToStraightLine->setSecond(QPoint(previousX, previousY+50));
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
                //delete pathLinesListNode->data;

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
            GameState::pair->getSecond()->setBrush(QColor(0xB4C8C8));
            GameState::pair->clear();

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
            //tank->collidesWithItem(GameState::adjMatrix->occupiedCells->getHead()->data);

        } else {
            if (!timer) return;
            timer->stop();
            timer->deleteLater();
            timer = nullptr;
        }
    });

    timer->start(5);
};


void Map::shootBullet(QPointF endPoint) {
    auto* shootingTank = GameState::pair->getFirst();
    if (shootingTank == nullptr) return;

    shootingTank->setGraphicsEffect(nullptr);
    Bullet* bullet = new Bullet(shootingTank->getTopLeftX()+20, shootingTank->getTopLeftY()+23, 10, 10);
    addItem(bullet);

    qreal deltaX = endPoint.rx()- shootingTank->getTopLeftX() +1;
    qreal deltaY = endPoint.ry() - shootingTank->getTopLeftY() +1;

    qreal angleRadians = qAtan2(deltaY, deltaX);
    qreal angleDegrees = qRadiansToDegrees(angleRadians);
    shootingTank->setRotation(angleDegrees+90);
    //qDebug() << qRadiansToDegrees(angleRadians) << "\n";


    timer = new QTimer(this);
    int bounceCount = 0;
    QGraphicsItem* previousCollide = shootingTank;
    bool bulletOutOfTank = false;
    connect(timer, &QTimer::timeout, this, [=]() mutable {

        QList<QGraphicsItem*> collidingItemsList = bullet->collidingItems();
        for (auto* item : collidingItemsList) {
            if (!bulletOutOfTank) {
                if (!collidingItemsList.contains(shootingTank)) {
                    bulletOutOfTank = true;
                }
            }
            if (((GameState::player2->tankList->find(dynamic_cast<Tank*>(item)) && GameState::player1->tankList->find(shootingTank))||      // shoots player 1, no damage for his own tank
                 (GameState::player1->tankList->find(dynamic_cast<Tank*>(item)) && GameState::player2->tankList->find(shootingTank))) ||    // shoots player 2, no damage for his own tank
                (bulletOutOfTank && item == shootingTank)                                                                               // can shoot itself
                ) {
                shootingTank->rotateNorth();
                dynamic_cast<Tank*>(item)->reduceHealth();
                timer->stop();
                timer->deleteLater();
                delete bullet;
                timer = nullptr;
                GameState::pair->clear();
                return;
            }
            if (item != previousCollide &&
                (GameState::obstacleList->find(dynamic_cast<SquareItem*>(item)) ||
                item == this->bottomWall || item == this->topWall || item == this->rightWall || item == this->leftWall)
                ) {

                QRectF bulletRect = bullet->boundingRect().translated(bullet->pos());
                QRectF itemRect = item->boundingRect().translated(item->pos());

                qreal leftDist = bulletRect.right() - itemRect.left();
                qreal rightDist = itemRect.right() - bulletRect.left();
                qreal topDist = bulletRect.bottom() - itemRect.top();
                qreal bottomDist = itemRect.bottom() - bulletRect.top();

                if ((leftDist < rightDist && leftDist < topDist && leftDist < bottomDist) ||    // Hit on the left side
                    (rightDist < leftDist && rightDist < topDist && rightDist < bottomDist) ){  // Hit on the right side
                    angleRadians = M_PI - angleRadians;
                }
                else if ((topDist < bottomDist && topDist < leftDist && topDist < rightDist) ||         // Hit on the top side
                         (bottomDist < topDist && bottomDist < leftDist && bottomDist < rightDist)){    // Hit on the bottom side
                    angleRadians = -angleRadians;
                }

                previousCollide = item;
                bounceCount++;

                if (bounceCount >= 3) {
                    timer->stop();
                    timer->deleteLater();
                    delete bullet;
                    timer = nullptr;
                    shootingTank->rotateNorth();
                    GameState::pair->clear();
                    return;
                }
            }else {
                qreal dx = qCos(angleRadians) * 2;
                qreal dy = qSin(angleRadians) * 2;
                bullet->setPos(bullet->x() + dx, bullet->y() + dy);

            }
        }
    });

    timer->start(5);

}
qreal Map::getAngleBetweenPoints(QPointF p1, QPointF p2) {
    qreal deltaX = p2.x() - p1.x();
    qreal deltaY = p2.y() - p1.y();

    qreal angleRadians = qAtan2(deltaY, deltaX);

    qreal angleDegrees = qRadiansToDegrees(angleRadians);

    return angleDegrees;
}
