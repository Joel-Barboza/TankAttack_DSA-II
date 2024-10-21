#include "include/mainwindow.h"
#include "include/adjacency_matrix.h"
#include "include/game_menu_window.h"
#include <QApplication>
#include <include/game_state.h>

int main(int argc, char *argv[])
{

    //GameState* gameState = new GameState();

    //gameState->adjMatrix->printAdjMatrix();

    QApplication a(argc, argv);

    //MainWindow mainWindow(nullptr, gameState); //  rows, columns, graph
    //mainWindow.setFixedSize(1200, 800);
    //mainWindow.show();

    // Crear e iniciar la ventana de menú del juego
    game_menu_window gameMenuWindow(nullptr);
    gameMenuWindow.setFixedSize(1000, 600);  // Ajusta el tamaño según necesites
    gameMenuWindow.show();  // Mostrar la nueva ventana


    return a.exec();
}
