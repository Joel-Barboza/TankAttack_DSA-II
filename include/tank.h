#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <include/map.h>
#include <QDir>
#include <QGraphicsSceneMouseEvent>


class Tank: public QGraphicsPixmapItem {
public:
    enum TankType {
        RedTank,
        BlueTank,
        YellowTank,
        LightBlueTank
    };

    Tank(TankType type, Map* parent);

    int getHealth();
    TankType getTankType();
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
private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    int health = 100;
    TankType tankType;
    int nodeIndexPos;
    int topLeftX;
    int topLeftY;

};



#endif // TANK_H
