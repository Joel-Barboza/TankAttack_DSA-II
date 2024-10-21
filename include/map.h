#ifndef MAP_H
#define MAP_H

//#include "include/adjacency_matrix.h"
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

template<typename T>
class AdjacencyMatrix;

template<typename T>
class SinglyLinkedList;

template<typename T, typename U>
class DataPair;


class Map : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    void drawPath(SinglyLinkedList<int>* list, int startX, int startY);
    QTimer* timer = nullptr;

    void moveTank(SinglyLinkedList<DataPair<QPoint, QPoint>*>* pointList);
    void moveTankToNeighbor(QPoint startPoint, QPoint endPoint);
private:
    // QGridLayout *gridLayout;
    void createGrid(int numRows, int numCols, AdjacencyMatrix<int>* adjMatrix);  // Helper function to create the grid
    QGraphicsLineItem* createLine(int x1, int y1, int x2, int y2);
};


#endif // MAP_H
