#include "include/mainwindow.h"
#include "include/adjacency_matrix.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    int rows = 20;
    int columns = 28;
    AdjacencyMatrix<int>* graph = new AdjacencyMatrix<int>(rows,columns);


    graph->placeObstacles();

    //graph->printAdjMatrix();
    QApplication a(argc, argv);
    MainWindow w(nullptr, rows, columns, graph);
    w.show();
    return a.exec();
}
