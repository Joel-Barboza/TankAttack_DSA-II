#ifndef SQUARE_ITEMS_H
#define SQUARE_ITEMS_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsSceneHoverEvent>
#include <include/game_state.h>
#include <include/mainwindow.h>

class SquareItem : public QGraphicsRectItem {
public:
    SquareItem(qreal x, qreal y, qreal width, qreal height, int index = 0, QGraphicsItem* parent = nullptr);

    int squareId;  // The ID of the square

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};
// class SquareItem : public QGraphicsRectItem {
// public:
//     SquareItem(qreal x, qreal y, qreal width, qreal height,  int index = 0, QGraphicsItem* parent = nullptr)
//         : QGraphicsRectItem(x, y, width, height, parent){
//         setAcceptHoverEvents(true);
//         setPen(Qt::NoPen);
//         this->setZValue(1);
//         squareId = index;
//     }
//     int squareId;



// protected:
//     void mousePressEvent(QGraphicsSceneMouseEvent* event) override {

//         this->setZValue(10);
//         // QPointF cursorPos = event->pos();
//         // QRectF bounds = this->boundingRect();
//         if (MainWindow::map->timer) {
//             return
//         }
//         QPointF scenePos = event->scenePos();
//         QGraphicsItem* topItem = this->scene()->itemAt(scenePos, QTransform());

//         if (topItem == this) {
//         qDebug() << "Square clicked at: " << squareId << "\n";
//         if (GameState::pair->getSize() == 2 && !GameState::adjMatrix->getIsOccupied(squareId)) {
//             GameState::pair->getHead()->data->setBrush(QColor("#B4C8C8"));
//             GameState::pair->getHead()->next->data->setBrush(QColor("#B4C8C8"));
//             GameState::removeDrawnPath();
//         }
//         GameState::startEndNodePair(this, squareId);
//         if (GameState::pair->getSize() == 1 && !GameState::adjMatrix->getIsOccupied(squareId)) {
//             // GameState::removeDrawnPath();
//             this->setBrush(QColor("#339033"));
//         } else if (GameState::pair->getSize() == 2 && !GameState::adjMatrix->getIsOccupied(squareId)) {
//             // GameState::removeDrawnPath();
//             GameState::adjMatrix->dijkstra(GameState::pair->getHead()->data->squareId);
//             SinglyLinkedList<int>* path = GameState::adjMatrix->getPathTo(squareId);
//             path->print();

//             int startPointX = GameState::pair->getHead()->data->boundingRect().center().rx();
//             int startPointY = GameState::pair->getHead()->data->boundingRect().center().ry();

//             MainWindow::map->drawPath(path, startPointX, startPointY);


//             this->setBrush(QColor("#903333"));
//         }
//         }
//         QGraphicsRectItem::mousePressEvent(event);
//     }
//     void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override {
//         this->setZValue(5);
//         // QPen pen(QColor("#902c2c"), 1);
//         // pen.setCapStyle(Qt::RoundCap);
//         // setPen(pen);
//         QPen pen(QColor("#902c2c"), 2);  // Thicker pen on hover
//         pen.setCosmetic(true);  // Make the pen thickness constant regardless of zoom level
//         setPen(pen);
//         QGraphicsRectItem::hoverEnterEvent(event);
//     }

//     void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override {
//         this->setZValue(1);
//         setPen(Qt::NoPen);
//         QGraphicsRectItem::hoverLeaveEvent(event);
//     }

// // private:
// //     int xCoord = 0;
// //     int yCoord = 0;
// };

#endif // SQUARE_ITEMS_H
