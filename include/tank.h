#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <include/map.h>
#include <QDir>


class Tank: public QGraphicsPixmapItem {
public:
    enum TankType {
        RedTank,
        BlueTank,
        YellowTank,
        LightBlueTank
    };

    Tank(TankType type, Map* parent) : QGraphicsPixmapItem(nullptr) {
        switch (type) {
        case RedTank:
            setPixmap(QPixmap("../../images/red_tank.png").scaled(50, 50, Qt::KeepAspectRatio));
            break;
        case BlueTank:
            setPixmap(QPixmap("../../images/blue_tank.png").scaled(50, 50, Qt::KeepAspectRatio));
            break;
        case YellowTank:
            setPixmap(QPixmap("../../images/yellow_tank.png").scaled(50, 50, Qt::KeepAspectRatio));
            break;
        case LightBlueTank:
            setPixmap(QPixmap("../../images/yellow_tank.png").scaled(50, 50, Qt::KeepAspectRatio));
            break;
        }

        setZValue(100);

    }

    int getHealth() const { return health; }

private:
    int health = 100;

};

#endif // TANK_H
