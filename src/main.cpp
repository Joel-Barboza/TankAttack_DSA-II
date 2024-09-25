#include "include/mainwindow.h"
#include "include/adjacency_matrix.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    AdjacencyMatrix<int>* siuuu = new AdjacencyMatrix<int>(3,4);
    siuuu->printAdjMatrix();
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
