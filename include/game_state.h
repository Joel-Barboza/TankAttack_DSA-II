#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "include/adjacency_matrix.h"
#include "QGraphicsLineItem"
#include <include/mainwindow.h>
class SquareItem;
class Map;
class Tank;

class GameState{

public:

    GameState();
    static int rows;//14
    static int columns;//24
    static AdjacencyMatrix<int>* adjMatrix;
    static void startEndNodePair(SquareItem* square, int squareId);
    static SinglyLinkedList<SquareItem*>* pair;
    static SinglyLinkedList<QGraphicsLineItem*>* pathLinesList;
    static void removeDrawnPath();
    static SinglyLinkedList<Tank*>* player1TankList;
    static SinglyLinkedList<Tank*>* player2TankList;
private:
    void initializeTanks();



};


#endif // GAME_STATE_H
