#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/game_state.h"
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

    // Inicializa el contador
    , secondsElapsed(0)
    , timer(new QTimer(this))

    // Variable donde se guarda el ganador
    , winningPlayer("Jugador 1")

{
    ui->setupUi(this);


    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);


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

    // Crea un Label para el cronometro
    timerLabel = new QLabel("00:00");
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("background-color: lightblue; font-size: 24px; font-weight: bold; border: none;");
    layout->addWidget(timerLabel);


    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    centralWidget->layout()->setContentsMargins(0, 0, 0, 0);

    setFixedSize(1200, 1000);

    // Configura el QTimer para el cronometro
    //QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    timer->start(1000); // Actualiza cada segundo

}
void MainWindow::updateTimer() {
    secondsElapsed++;
    int minutes = secondsElapsed / 60;
    int seconds = secondsElapsed % 60;
    timerLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));

    // Tiempo termina a los 5min
    if (secondsElapsed >= 300){
        timer->stop();
        qDebug() << "Termino el tiempo";
        this->setEnabled(false);
        qDebug() << "Termino el juego";

        QString message = QString("El ganador es:  %1!").arg(winningPlayer);
        QMessageBox::information(this, "Fin de la partida", message);
    }

}


Map* MainWindow::map = nullptr;

MainWindow::~MainWindow()
{
    delete ui;
}
