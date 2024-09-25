#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/adjacency_matrix.h"



MainWindow::MainWindow(QWidget *parent, int rows, int columns, AdjacencyMatrix<int>* adjMatrix)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QVBoxLayout* layout = new QVBoxLayout;

    map = new Map(this, rows, columns, adjMatrix);
    playerData = new PlayerData(this);


    layout->addWidget(map);
    layout->addWidget(playerData);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
