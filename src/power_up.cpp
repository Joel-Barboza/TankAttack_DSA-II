#include "../include/power_up.h"
#include "QPixmap"

#include <include/customlabel.h>

PowerUp::PowerUp()  : QGraphicsPixmapItem(nullptr) {

    int random = 0;
    //srand(time(0));
    random = rand()%4;


    QPixmap* pwrUpImg = nullptr;
    switch (random) {
    case 0:
        pwrUpImg = new QPixmap("../../images/plus_two_pwrUp.png");
        powerUpType = DoubleTurn;
        break;
    case 1:
        pwrUpImg = new QPixmap("../../images/move_acc_pwrUp.png");
        powerUpType = MovementAcc;
        break;
    case 2:
        pwrUpImg = new QPixmap("../../images/atk_acc_pwrUp.png");
        powerUpType = AttackAcc;
        break;
    case 3:
        pwrUpImg = new QPixmap("../../images/atk_power_pwrUp.png");
        powerUpType = AttackPower;
        break;
    }

    if (pwrUpImg) {
        *pwrUpImg = pwrUpImg->scaled(25, 25, Qt::KeepAspectRatio);
        setPixmap(*pwrUpImg);
    }



    setZValue(100);

    setTransformOriginPoint(boundingRect().center());

    powerUpImg = new CustomLabel(this);
    powerUpImg->setPixmap(*pwrUpImg);
    powerUpImg->setContentsMargins(0, 0, 0, 0);
    powerUpImg->setStyleSheet("padding: 0px; border: 1px solid black;");
};

PowerUp::PowerUpType PowerUp::getPowerUpType() const {  return powerUpType; }

CustomLabel *PowerUp::getPowerUpImg() const
{
    return powerUpImg;
}


