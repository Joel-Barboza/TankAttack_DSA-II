#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "include/adjacency_matrix.h"
#include "QGraphicsLineItem"
#include <include/mainwindow.h>
#include <include/tank.h>
#include <include/data_pair.h>
class SquareItem;
class Map;

class GameState{

public:

    GameState();
    static int rows;//14
    static int columns;//24
    static AdjacencyMatrix<int>* adjMatrix;
    static void startEndNodePair(SquareItem* square, int squareId);
    static DataPair<Tank*, SquareItem*>* pair;
    //static SinglyLinkedList<SquareItem*>* pair;
    static SinglyLinkedList<QGraphicsLineItem*>* pathLinesList;
    static void removeDrawnPath();
    static SinglyLinkedList<Tank*>* player1TankList;
    static SinglyLinkedList<Tank*>* player2TankList;
    static void selectTank(Tank *square, int squareId);
    static void selectEndPoint(SquareItem *square, int squareId);
private:
    void initializeTanks();



};


#endif // GAME_STATE_H
