#include "include/tank.h"
#include "include/game_state.h"
#include "include/mainwindow.h"
#include "include/square_items.h"

#include <QGraphicsColorizeEffect>

Tank::Tank(TankType type, Player owner, Map* parent) : QGraphicsPixmapItem(nullptr), tankType(type), owner(owner) {
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

    //p1TankRed1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    tankImgPlyrData = new CustomLabel(this);
    tankImgPlyrData->setPixmap(tankImage->scaled(25, 25, Qt::KeepAspectRatio));
    tankImgPlyrData->setContentsMargins(0, 0, 0, 0);
    tankImgPlyrData->setStyleSheet("padding: 0px; border: 1px solid black; border-right: 0px");
    tankPercentagePlyrData = new CustomLabel(QString::number(health) + "%", this);
    tankPercentagePlyrData->setContentsMargins(0, 0, 0, 0);
    tankPercentagePlyrData->setStyleSheet("padding: 0px; border: 1px solid black; border-left: 0px; color: black;");
}

int Tank::getHealth() { return health; }

Tank::TankType Tank::getTankType() { return tankType; }

Tank::Player Tank::getOwner(){
    return owner;
}

int Tank::getNodeIndexPos() { return nodeIndexPos; }

void Tank::setNodeIndexPos(int nodeIndex) { this->nodeIndexPos = nodeIndex; }

void Tank::setTopLeftX(int xCoord){ this->topLeftX = xCoord; }

int Tank::getTopLeftX(){ return topLeftX; }

void Tank::setTopLeftY(int yCoord){ this->topLeftY = yCoord; }

int Tank::getTopLeftY(){ return topLeftY; }

void Tank::setGridPosition(int row, int column)
{
    int xCoord = column*50+5;
    int yCoord = row*50+5;
    setPos(xCoord, yCoord);
    setTopLeftX(xCoord);
    setTopLeftY(yCoord);
    setNodeIndexPos((xCoord-5)/50 + GameState::columns*(yCoord-5)/50);

}


void Tank::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(10);
    if (MainWindow::map->timer) return; // Avoid clicking while timer is active
    qDebug() << "jdfjalsdfj" << "\n";


    QPointF scenePos = event->scenePos();
    QGraphicsItem* topItem = this->scene()->itemAt(scenePos, QTransform());

    if (GameState::pair->getFirst() != nullptr) {
        GameState::pair->getFirst()->setGraphicsEffect(nullptr);
        //GameState::removeDrawnPath();
    }
    if (GameState::pair->getSecond() != nullptr) {
        GameState::pair->getSecond()->setBrush(QColor(0xB4C8C8));
    }
    if (topItem == this) {
        qDebug() << "Tank clicked at: " << nodeIndexPos << "\n";

        auto* colorEffect = new QGraphicsColorizeEffect();
        colorEffect->setColor(Qt::red);
        setGraphicsEffect(colorEffect);
        GameState::selectTank(this, nodeIndexPos);
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}

CustomLabel* Tank::getTankPercentagePlyrData() {
    return tankPercentagePlyrData;
}

CustomLabel* Tank::getTankImgPlyrData() {
    return tankImgPlyrData;
};

void Tank::rotateNorth(){
    setRotation(0);
}

void Tank::rotateSouth(){
    setRotation(180);
}


void Tank::rotateEast(){
    setRotation(90);
}


void Tank::rotateWest(){
    setRotation(-90);
}

void Tank::setCenteredPos(int x, int y) {
    QRectF bounds = this->boundingRect();
    int newX = x - bounds.width() / 2;
    int newY = y - bounds.height() / 2;
    this->setPos(newX, newY);
}

void Tank::instaKill()
{
    this->health = 0;
    auto* colorEffect1 = new QGraphicsColorizeEffect();
    auto* colorEffect2 = new QGraphicsColorizeEffect();
    colorEffect1->setColor(Qt::red);
    colorEffect2->setColor(Qt::red);
    if (SinglyLinkedList<Tank*>::Node* foundTank = GameState::player1->tankList->find(this)) {
        foundTank->data->tankPercentagePlyrData->setGraphicsEffect(colorEffect1);
        foundTank->data->tankImgPlyrData->setGraphicsEffect(colorEffect2);
        foundTank->data->tankPercentagePlyrData->setTankReference(nullptr);
        foundTank->data->tankImgPlyrData->setTankReference(nullptr);
        GameState::player1->tankList->remove(this);
        GameState::adjMatrix->setFreeOfTanks(nodeIndexPos);
    }
    if (SinglyLinkedList<Tank*>::Node* foundTank = GameState::player2->tankList->find(this)) {
        foundTank->data->tankPercentagePlyrData->setGraphicsEffect(colorEffect1);
        foundTank->data->tankImgPlyrData->setGraphicsEffect(colorEffect2);
        foundTank->data->tankPercentagePlyrData->setTankReference(nullptr);
        foundTank->data->tankImgPlyrData->setTankReference(nullptr);
        GameState::player2->tankList->remove(this);
        GameState::adjMatrix->setFreeOfTanks(nodeIndexPos);
    }
    delete this;
}

void Tank::reduceHealth()
{
    if (tankType == BlueTank || tankType == LightBlueTank) {
        health -= 25;
        tankPercentagePlyrData->setText(QString::number(health) + "%");
        if (health <= 0){
            instaKill();
        }
    } else if (tankType == YellowTank || tankType == RedTank) {
        health -= 50;
        tankPercentagePlyrData->setText(QString::number(health) + "%");
        if (health <= 0){
            instaKill();
        }
    }
}




