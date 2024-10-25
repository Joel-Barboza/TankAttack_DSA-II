#include <include/game_state.h>

GameState::GameState()
{
    // AdjacencyMatrix<int>* sf = new AdjacencyMatrix<int>(3,4);
    // for (int i = 0; i < sf->getMatrixOrder(); ++i) {
    //     sf->addEdgesToNeighbor(i);
    // }
    // sf->printAdjMatrix();

    for (int i = 0; i < adjMatrix->getMatrixOrder(); ++i) {
        adjMatrix->addEdgesToNeighbor(i);
    }
    initializeTanks();
    adjMatrix->placeObstacles(player1TankList, player2TankList);
    adjMatrix->bfs(0);

}

int GameState::rows = 14;
int GameState::columns = 24;

// int GameState::rows = 10;
// int GameState::columns = 10;

DataPair<Tank*, SquareItem*>* GameState::pair = new DataPair<Tank*, SquareItem*>();
// SinglyLinkedList<SquareItem*>* GameState::pair = new SinglyLinkedList<SquareItem*>();

AdjacencyMatrix<int>* GameState::adjMatrix  = new AdjacencyMatrix<int>(rows,columns);

SinglyLinkedList<QGraphicsLineItem*>* GameState::pathLinesList = new SinglyLinkedList<QGraphicsLineItem*>();

SinglyLinkedList<Tank*>* GameState::player1TankList = new SinglyLinkedList<Tank*>();
SinglyLinkedList<Tank*>* GameState::player2TankList = new SinglyLinkedList<Tank*>();

SinglyLinkedList<SquareItem*>* GameState::obstacleList = new SinglyLinkedList<SquareItem*>();

void GameState::removeDrawnPath() {
    auto* current = pathLinesList->getHead();
    while (current != nullptr) {
        delete current->data;
        current = current->next;
    }
    pathLinesList->clear();
}

//Map* GameState::map = new Map(this);

// void GameState::startEndNodePair(SquareItem* square, int squareId) {

//     if (adjMatrix->getIsUnreachable(squareId)) return;

//     if (pair->getFirst() != nullptr && pair->getSecond() != nullptr) {
//         pair->clear();
//     }
//     // if () {
//     // }
//     //     pair->insert(square);

// }

void GameState::selectTank(Tank* tank, int squareId) {
    removeDrawnPath();
    if (tank != pair->getFirst()){
        pair->setFirst(tank);
    }
    }

void GameState::selectEndPoint(SquareItem* square, int squareId) {
    qDebug() << "Square left clicked at: " << pair->getSecond() << "\n";
    if (pair->getFirst() == nullptr) return;

    if (square != pair->getSecond()){
        pair->setSecond(square);
    }
}

void GameState::initializeTanks() {

    //--------------------------------------
    //           Player 1
    //--------------------------------------
    Tank* frontLineBlue = new Tank(Tank::BlueTank, MainWindow::map);
    frontLineBlue->setGridPosition(2, 3);
    player1TankList->insert(frontLineBlue);

    Tank* backLineRed = new Tank(Tank::RedTank, MainWindow::map);
    backLineRed->setGridPosition(4, 1);
    player1TankList->insert(backLineRed);

    Tank* backLineBlue = new Tank(Tank::BlueTank, MainWindow::map);
    backLineBlue->setGridPosition(9, 1);
    player1TankList->insert(backLineBlue);

    Tank* frontLineRed = new Tank(Tank::RedTank, MainWindow::map);
    frontLineRed->setGridPosition(11, 3);
    player1TankList->insert(frontLineRed);


    //--------------------------------------
    //           Player 2
    //--------------------------------------
    Tank* frontLineLightBlue = new Tank(Tank::LightBlueTank, MainWindow::map);
    frontLineLightBlue->setGridPosition(2, 20);
    player2TankList->insert(frontLineLightBlue);

    Tank* backLineYellow = new Tank(Tank::YellowTank, MainWindow::map);
    backLineYellow->setGridPosition(4, 22);
    player2TankList->insert(backLineYellow);

    Tank* backLineLightBlue = new Tank(Tank::LightBlueTank, MainWindow::map);
    backLineLightBlue->setGridPosition(9, 22);
    player2TankList->insert(backLineLightBlue);

    Tank* frontLineYellow = new Tank(Tank::YellowTank, MainWindow::map);
    frontLineYellow->setGridPosition(11, 20);
    player2TankList->insert(frontLineYellow);


}
