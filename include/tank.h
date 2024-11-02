#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <include/map.h>
#include <QDir>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <include/customlabel.h>


class Tank: public QGraphicsPixmapItem {
public:
    enum TankType {
        RedTank,
        BlueTank,
        YellowTank,
        LightBlueTank
    };

    enum Player {
        Player1,
        Player2
    };

    Tank(TankType type, Player owner, Map* parent);

    int getHealth();
    TankType getTankType();

    Player getOwner();

    int getNodeIndexPos();
    void setNodeIndexPos(int nodeIndex);
    int getTopLeftX();
    void setTopLeftX(int xCoord);
    int getTopLeftY();
    void setTopLeftY(int yCoord);
    void setGridPosition(int row, int column);

    void rotateNorth();
    void rotateSouth();
    void rotateEast();
    void rotateWest();
    void setCenteredPos(int x, int y);
    void instaKill();
    void reduceHealth();
    CustomLabel* getTankImgPlyrData();

    CustomLabel* getTankPercentagePlyrData();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    int health = 100;
    TankType tankType;
    Player owner;
    int nodeIndexPos;
    int topLeftX;
    int topLeftY;
    CustomLabel* tankImgPlyrData = nullptr;
    CustomLabel* tankPercentagePlyrData = nullptr;

};



#endif // TANK_H
