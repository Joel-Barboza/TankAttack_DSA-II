#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "include/adjacency_matrix.h"

class GameState{

public:
    GameState();
    static int rows;//14
    static int columns;//24
    static AdjacencyMatrix<int>* adjMatrix;

private:


};


#endif // GAME_STATE_H
