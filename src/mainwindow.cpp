#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/game_state.h"
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>



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
    this->installEventFilter(this);


    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(3);


    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);



    map = new Map(this);
    map->setBackgroundBrush(QColor(0x9BB6C4)); // #9BB6C4

    statusBar()->hide();


    view->setScene(map);


    view->setFixedSize(1212, 900);


    layout->addWidget(view);


    playerData = new PlayerData(this);

    playerData->setStyleSheet("background-color: lightblue;");
    playerData->setContentsMargins(0,0,0,0);

    layout->addWidget(playerData);

    // Crea un Label para el cronometro
    timerLabel = new QLabel("00:00");
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("background-color: lightblue; font-size: 24px; font-weight: bold; color: black;");
    timerLabel->setContentsMargins(0,0,0,0);
    layout->addWidget(timerLabel);


    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    centralWidget->layout()->setContentsMargins(0, 0, 0, 0);

    setFixedSize(1205, 1000);

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

    if (secondsElapsed%30 == 0 && 0 < secondsElapsed  && secondsElapsed != 300 ) {
        int p1QueueSize = GameState::player1->powerUpQueue->getSize();
        int p2QueueSize = GameState::player2->powerUpQueue->getSize();
        if (p1QueueSize < 8) {
            PowerUp* p1PowerUp = new PowerUp();
            GameState::player1->powerUpQueue->enqueue(p1PowerUp);
            playerData->p1Layout->addWidget(p1PowerUp->getPowerUpImg(), 2, p1QueueSize);
        }

        if (p2QueueSize < 8) {
            PowerUp* p2PowerUp = new PowerUp();
            GameState::player2->powerUpQueue->enqueue(p2PowerUp);
            playerData->p2Layout->addWidget(p2PowerUp->getPowerUpImg(), 2, p2QueueSize);
        }
    }

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
bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Shift) {
            if (map->currentTurn == map->Turn::Player1) {
                qDebug() << "Shift key pressed!";
                // PowerUp* nextPowerUp = GameState::player1->powerUpQueue->getFront().value_or(nullptr);
                // if (!nextPowerUp) return true;
                // // GameState::player1->activatedPowerUp->insert(nextPowerUp);
                // if (nextPowerUp->getPowerUpType() == PowerUp::DoubleTurn) {
                //     map->hasExtraTurn = true;
                // } else {
                //     map->endTurn();
                // }
                // playerData->spendPlayer1PwrUp();
            } else if (map->currentTurn == map->Turn::Player2) {
                qDebug() << "Shift key pressed!";
                // PowerUp* nextPowerUp = GameState::player2->powerUpQueue->getFront().value_or(nullptr);
                // if (!nextPowerUp) return true;
                // // GameState::player2->activatedPowerUp->insert(nextPowerUp);
                // if (nextPowerUp->getPowerUpType() == PowerUp::DoubleTurn) {
                //     map->hasExtraTurn = true;
                // } else {
                //     map->endTurn();
                // }
                // playerData->spendPlayer2PwrUp();
            }
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


Map* MainWindow::map = nullptr;

MainWindow::~MainWindow()
{
    this->removeEventFilter(this);
    delete ui;
}
