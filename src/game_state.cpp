#include <include/game_state.h>

GameState::GameState()
{

    adjMatrix->addEdges();
    adjMatrix->placeObstacles();
    //initializeTanks();
    std::cout << "\nRunning Dijkstra's algorithm from node 0..." << std::endl;
    adjMatrix->dijkstra(0);

}

int GameState::rows = 14;
int GameState::columns = 24;

// int GameState::rows = 3;
// int GameState::columns = 4;

SinglyLinkedList<SquareItem*>* GameState::pair = new SinglyLinkedList<SquareItem*>();

AdjacencyMatrix<int>* GameState::adjMatrix  = new AdjacencyMatrix<int>(rows,columns);

SinglyLinkedList<QGraphicsLineItem*>* GameState::pathLinesList = new SinglyLinkedList<QGraphicsLineItem*>();

SinglyLinkedList<Tank*>* GameState::player1TankList = new SinglyLinkedList<Tank*>();
SinglyLinkedList<Tank*>* GameState::player2TankList = new SinglyLinkedList<Tank*>();



void GameState::removeDrawnPath() {
    auto* current = pathLinesList->getHead();
    while (current != nullptr) {
        delete current->data;
        current = current->next;
    }
    pathLinesList->clear();
}

//Map* GameState::map = new Map(this);

void GameState::startEndNodePair(SquareItem* square, int squareId) {

    if (!adjMatrix->getIsOccupied(squareId)){
        if (pair->getSize() == 2) {
            pair->clear();
        }
        pair->insert(square);

    }

}

void GameState::initializeTanks() {

    // player1TankList->insert(new Tank(Tank::YellowTank, MainWindow::map));
}
