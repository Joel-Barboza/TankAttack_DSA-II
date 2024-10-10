#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/game_state.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout;


    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);



    map = new Map(this);
    map->setBackgroundBrush(QColor("blue"));

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

Map* MainWindow::map = nullptr;

MainWindow::~MainWindow()
{
    delete ui;
}
