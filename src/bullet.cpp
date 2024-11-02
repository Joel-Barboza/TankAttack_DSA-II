#include "include/bullet.h"


Bullet::Bullet(qreal x, qreal y, qreal width, qreal height, int index, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, width, height, parent), squareId(index) {

    setPen(Qt::NoPen);
    setZValue(10000);

    setBrush(QColor(0x119933));

    setTransformOriginPoint(boundingRect().center());
    //setRotation(-90);
    bulletItem = this;
}
