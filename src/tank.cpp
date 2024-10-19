#include "include/tank.h"
#include "include/game_state.h"
#include "include/mainwindow.h"
#include "include/square_items.h"

#include <QGraphicsColorizeEffect>

Tank::Tank(TankType type, Map* parent) : QGraphicsPixmapItem(nullptr), tankType(type) {
    QPixmap* tankImage = nullptr;
    switch (type) {
    case RedTank:
        tankImage = new QPixmap("../../images/red_tank.png");
        break;
    case BlueTank:
        tankImage = new QPixmap("../../images/blue_tank.png");
        break;
    case YellowTank:
        tankImage = new QPixmap("../../images/yellow_tank.png");
        break;
    case LightBlueTank:
        tankImage = new QPixmap("../../images/lightblue_tank.png");
        break;
    }

    if (tankImage) {
        *tankImage = tankImage->scaled(50, 50, Qt::KeepAspectRatio);
        setPixmap(*tankImage);
    }



    setZValue(100);

    setTransformOriginPoint(boundingRect().center());
    //setTransformOriginPoint(QPoint(getTopLeftX()+25, getTopLeftY()+25));
}

int Tank::getHealth() { return health; }

Tank::TankType Tank::getTankType() { return tankType; }


int Tank::getNodeIndexPos() { return nodeIndexPos; }

void Tank::setNodeIndexPos(int nodeIndex) { this->nodeIndexPos = nodeIndex; }

void Tank::setTopLeftX(int xCoord){ this->topLeftX = xCoord; }

int Tank::getTopLeftX(){ return topLeftX; }

void Tank::setTopLeftY(int yCoord){ this->topLeftY = yCoord; }

int Tank::getTopLeftY(){ return topLeftY; }

void Tank::setGridPosition(int row, int column)
{
    int xCoord = column*50;
    int yCoord = row*50;
    setPos(xCoord, yCoord);
    setTopLeftX(xCoord);
    setTopLeftY(yCoord);
    setNodeIndexPos(xCoord/50 + GameState::columns*yCoord/50);

}


void Tank::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(10);
    if (MainWindow::map->timer) {
        return;  // Avoid clicking while timer is active
    }

    QPointF scenePos = event->scenePos();
    QGraphicsItem* topItem = this->scene()->itemAt(scenePos, QTransform());

    if (GameState::pair->getFirst() != nullptr) {
        GameState::pair->getFirst()->setGraphicsEffect(nullptr);
        GameState::removeDrawnPath();
    }
    if (GameState::pair->getSecond() != nullptr) {
        GameState::pair->getSecond()->setBrush(QColor("#B4C8C8"));
    }
    if (topItem == this) {
        qDebug() << "Tank clicked at: " << nodeIndexPos << "\n";

        auto* colorEffect = new QGraphicsColorizeEffect();
        colorEffect->setColor(Qt::red);
        setGraphicsEffect(colorEffect);

        GameState::selectTank(this, nodeIndexPos);
    }
    // qDebug() << "1: " << boundingRect().topLeft() << "\n";
    // rotateEast();
    // qDebug() << "2: " << boundingRect().topLeft() << "\n";
    // setPos(getTopLeftX(), getTopLeftY());
    QGraphicsPixmapItem::mousePressEvent(event);
};

void Tank::rotateNorth(){
    setRotation(0);
    // setPos(getTopLeftX(), getTopLeftY());
}

void Tank::rotateSouth(){
    setRotation(180);
    // setPos(getTopLeftX()+50, getTopLeftY()+50);
}


void Tank::rotateEast(){
    setRotation(90);
    // setPos(getTopLeftX()+50, getTopLeftY());
    //setTopLeftX(getTopLeftX()+50);
}


void Tank::rotateWest(){

    setRotation(-90);
    // setPos(getTopLeftX(), getTopLeftY()-50);
}

void Tank::setCenteredPos(int x, int y) {
    // Get the bounding rectangle of the Tank (QGraphicsPixmapItem)
    QRectF bounds = this->boundingRect();

    // Calculate the new top-left position such that the center is at (x, y)
    int newX = x - bounds.width() / 2;
    int newY = y - bounds.height() / 2;

    // Set the position of the tank with the adjusted coordinates
    this->setPos(newX, newY);
}




