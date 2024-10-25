#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsSceneHoverEvent>
#include <include/game_state.h>
#include <include/mainwindow.h>
#include <QDebug>

class Bullet : public QGraphicsEllipseItem {
public:
    Bullet(qreal x, qreal y, qreal width, qreal height, int index = 0, QGraphicsItem* parent = nullptr);
    Bullet* bulletItem;

    int squareId;  // The ID of the square

protected:
    // void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    // void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    // void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};


#endif // BULLET_H
