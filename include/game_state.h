#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "include/adjacency_matrix.h"

class GameState{

public:
    GameState();
    int rows = 4;//14
    int columns = 4;//24
    AdjacencyMatrix<int>* adjMatrix = new AdjacencyMatrix<int>(rows,columns);

private:


};


#endif // GAME_STATE_H
