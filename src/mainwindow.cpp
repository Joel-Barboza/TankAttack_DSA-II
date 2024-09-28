#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/game_state.h"



MainWindow::MainWindow(QWidget *parent, GameState* gameState)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout;


    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    map = new Map(this, gameState);
    map->setBackgroundBrush(QColor("gray"));

    statusBar()->hide();


    view->setScene(map);


    view->setFixedSize(1200, 900);


    layout->addWidget(view);


    playerData = new PlayerData(this);

    playerData->setStyleSheet("background-color: lightblue;");
    playerData->setContentsMargins(0,0,0,0);

    layout->addWidget(playerData);


    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    centralWidget->layout()->setContentsMargins(0, 0, 0, 0);

    setFixedSize(1200, 1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}
