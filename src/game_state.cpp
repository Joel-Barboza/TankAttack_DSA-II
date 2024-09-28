#include <include/game_state.h>

GameState::GameState()
{
    adjMatrix->addEdges();
    adjMatrix->placeObstacles();
}
