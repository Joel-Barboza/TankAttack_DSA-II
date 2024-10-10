#include "include/mainwindow.h"
#include "include/adjacency_matrix.h"
#include <QApplication>
#include <include/game_state.h>

int main(int argc, char *argv[])
{

    GameState* gameState = new GameState();

    //gameState->adjMatrix->printAdjMatrix();
    QApplication a(argc, argv);
    MainWindow mainWindow(nullptr);
    mainWindow.setFixedSize(1200, 800);
    mainWindow.show();
    return a.exec();
}
