#ifndef SQUARE_ITEMS_H
#define SQUARE_ITEMS_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsSceneHoverEvent>
#include <include/game_state.h>

class SquareItem : public QGraphicsRectItem {
public:
    SquareItem(qreal x, qreal y, qreal width, qreal height,  int index = 0, QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(x, y, width, height, parent){
        setAcceptHoverEvents(true);
        setPen(Qt::NoPen);
        this->setZValue(1);
        setAcceptHoverEvents(true);
        squareId = index;

    }
    int squareId;



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        qDebug() << "Square clicked at: " << squareId << "\n";
        GameState::adjMatrix->dijkstra(squareId);/*
        SinglyLinkedList<int>* sf = GameState::adjMatrix->printPath(0, new SinglyLinkedList<int>);
        sf->print();*/
        QGraphicsRectItem::mousePressEvent(event);
    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override {
        this->setZValue(2);
        QPen pen(QColor("#902c2c"), 1);
        pen.setCapStyle(Qt::RoundCap);
        setPen(pen);
        QGraphicsRectItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override {
        this->setZValue(1);
        setPen(Qt::NoPen);
        QGraphicsRectItem::hoverEnterEvent(event);
    }

// private:
//     int xCoord = 0;
//     int yCoord = 0;
};

#endif // SQUARE_ITEMS_H
