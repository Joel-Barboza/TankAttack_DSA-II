#include "include/square_items.h"

// Constructor
SquareItem::SquareItem(qreal x, qreal y, qreal width, qreal height, int index, QGraphicsItem* parent)
    : QGraphicsRectItem(x, y, width, height, parent), squareId(index) {
    setAcceptHoverEvents(true);
    setPen(Qt::NoPen);
    setZValue(1);
}

// Mouse press event
void SquareItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(10);
    if (MainWindow::map->timer || GameState::adjMatrix->getIsUnreachable(squareId)) { return; } // Avoid clicking while timer is active

    QPointF scenePos = event->scenePos();
    QGraphicsItem* topItem = this->scene()->itemAt(scenePos, QTransform());

    if (topItem == this) {
        qDebug() << "Square clicked at: " << squareId << "\n";

        if (GameState::pair->getFirst() != nullptr && GameState::pair->getSecond() != nullptr) {
            //GameState::pair->getFirst()->setBrush(QColor("#B4C8C8"));

            GameState::pair->getFirst()->setGraphicsEffect(nullptr);
            GameState::pair->getSecond()->setBrush(QColor("#B4C8C8"));
            //GameState::pair->clear();
            GameState::removeDrawnPath();
        }

        GameState::selectEndPoint(this, squareId);

        if (GameState::pair->getFirst() != nullptr && GameState::pair->getSecond() == nullptr && !GameState::adjMatrix->getIsUnreachable(squareId)) {
            setBrush(QColor("#339033"));
        } else if (GameState::pair->getFirst() != nullptr && GameState::pair->getSecond() != nullptr && !GameState::adjMatrix->getIsUnreachable(squareId)) {
            GameState::pair->getFirst()->setGraphicsEffect(nullptr);
            GameState::adjMatrix->dijkstra(GameState::pair->getFirst()->getNodeIndexPos());
            SinglyLinkedList<int>* path = GameState::adjMatrix->getPathTo(squareId);
            path->print();

            int startPointX = GameState::pair->getFirst()->getTopLeftX()+25;
            int startPointY = GameState::pair->getFirst()->getTopLeftY()+25;
            MainWindow::map->drawPath(path, startPointX, startPointY);
            setBrush(QColor("#903333"));
        }
    }
    QGraphicsRectItem::mousePressEvent(event);
}

// Hover enter event
void SquareItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    setZValue(5);
    QPen pen(QColor("#902c2c"), 2);  // Thicker pen on hover
    pen.setCosmetic(true);  // Make the pen thickness constant regardless of zoom level
    setPen(pen);
    QGraphicsRectItem::hoverEnterEvent(event);
}

// Hover leave event
void SquareItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    setZValue(1);
    setPen(Qt::NoPen);
    QGraphicsRectItem::hoverLeaveEvent(event);
}
