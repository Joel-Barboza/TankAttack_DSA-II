#ifndef POWER_UP_H
#define POWER_UP_H

#include <QGraphicsPixmapItem>
#include "include/customlabel.h"


class PowerUp : public QGraphicsPixmapItem  {
public:
    enum PowerUpType {
        DoubleTurn,
        MovementAcc,
        AttackAcc,
        AttackPower
    };
    PowerUp();
    PowerUpType getPowerUpType() const;

    CustomLabel *getPowerUpImg() const;

private:
    PowerUpType powerUpType;

    CustomLabel* powerUpImg = nullptr;

};

#endif // POWER_UP_H
