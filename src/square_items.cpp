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
    if (event->button() == Qt::LeftButton) {

        if (MainWindow::map->timer || GameState::adjMatrix->getIsUnreachable(squareId)) { return; } // Avoid clicking while timer is active

        QPointF scenePos = event->scenePos();
        QGraphicsItem* topItem = this->scene()->itemAt(scenePos, QTransform());

        if (topItem == this) {
            qDebug() << "Square left clicked at: " << squareId << "\n";

            if (GameState::pair->getFirst() != nullptr && GameState::pair->getSecond() != nullptr) {
                //GameState::pair->getFirst()->setBrush(QColor(0xB4C8C8));

                GameState::pair->getFirst()->setGraphicsEffect(nullptr);
                GameState::pair->getSecond()->setBrush(QColor(0xB4C8C8)); // #B4C8C8
                //GameState::pair->clear();
                GameState::removeDrawnPath();
            }

            GameState::selectEndPoint(this, squareId);


            if (GameState::pair->getFirst() != nullptr && GameState::pair->getSecond() == nullptr && !GameState::adjMatrix->getIsUnreachable(squareId)) {
                setBrush(QColor(0x339033));
            } else if (GameState::pair->getFirst() != nullptr && GameState::pair->getSecond() != nullptr && !GameState::adjMatrix->getIsUnreachable(squareId)) {
                GameState::pair->getFirst()->setGraphicsEffect(nullptr);

                if (GameState::pair->getFirst()->getTankType() == Tank::BlueTank || GameState::pair->getFirst()->getTankType() == Tank::LightBlueTank) {

                    GameState::adjMatrix->bfs(GameState::pair->getFirst()->getNodeIndexPos());

                } else if (GameState::pair->getFirst()->getTankType() == Tank::YellowTank || GameState::pair->getFirst()->getTankType() == Tank::RedTank) {

                    GameState::adjMatrix->dijkstra(GameState::pair->getFirst()->getNodeIndexPos());

                }
                SinglyLinkedList<int>* path = GameState::adjMatrix->getPathTo(squareId);
                path->print();
                if (path->getSize() == 1) return;

                int startPointX = GameState::pair->getFirst()->getTopLeftX()+25;
                int startPointY = GameState::pair->getFirst()->getTopLeftY()+25;
                MainWindow::map->drawPath(path, startPointX, startPointY);
                setBrush(QColor(0x903333));
            }
        }
        QGraphicsRectItem::mousePressEvent(event);
    } else if (event->button() == Qt::RightButton){
        qDebug() << "Square right clicked at: " << squareId << "\n";
        MainWindow::map->shootBullet(this->boundingRect().topLeft());
    }
}
// int startPointX = GameState::pair->getFirst()->getTopLeftX()+25;
// int startPointY = GameState::pair->getFirst()->getTopLeftY()+25;
// int endPointX = GameState::pair->getSecond()->boundingRect().topLeft().rx()+25;
// int endPointY = GameState::pair->getSecond()->boundingRect().topLeft().ry()+25;
// QGraphicsLineItem* line = MainWindow::map->createLine(startPointX, startPointY, endPointX, endPointY);
// QPen pen(QColor(0x2c2c99"), 50);
// pen.setCapStyle(Qt::RoundCap);
// line->setPen(pen);
// QPainterPath lineShape = line->shape();
// QList<QGraphicsItem*> itemsUnderLine = scene()->items(line->mapToScene(lineShape));

// QList<QGraphicsRectItem*> rectItemsUnderLine;
// for (QGraphicsItem* item : itemsUnderLine) {
//     // Check if the item is a QGraphicsRectItem
//     if (auto* rectItem = dynamic_cast<QGraphicsRectItem*>(item)) {
//         // rectItemsUnderLine.append(rectItem);
//         // QColor translucentColor = QColor(Qt::red);
//         // //translucentColor.setAlpha(128);  // Set the transparency (128 is 50% transparent)
//         // QBrush highlightBrush(translucentColor);

//         // Apply the translucent brush
//         //rectItem->setBrush(highlightBrush);
//         //rectItem->setHighlight(rectItem, QColor(Qt::red));
//         QGraphicsRectItem* overlayItem = new QGraphicsRectItem(rectItem->boundingRect());
//         QColor overlayColor(255, 0, 0, 50); // Red with 100 alpha (transparency)
//         overlayItem->setBrush(QBrush(overlayColor));
//         overlayItem->setPen(Qt::NoPen); // Remove border
//         overlayItem->setZValue(1000); // Ensure it's above the original item

//         MainWindow::map->addItem(overlayItem);
//         MainWindow::map->moveTankToNeighbor(QPoint(GameState::pair->getFirst()->getTopLeftX()+25, GameState::pair->getFirst()->getTopLeftY()+25),
//                                             GameState::pair->getSecond()->boundingRect().center().toPoint());
//         //rectItem->setBrush(QColor(255,34,255,50));
//     }
// }
// // for () {

// // }
// pen.setWidth(1);

// Hover enter event
void SquareItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    setZValue(5);
    QPen pen(QColor(0x902c2c), 2);  // Thicker pen on hover
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
