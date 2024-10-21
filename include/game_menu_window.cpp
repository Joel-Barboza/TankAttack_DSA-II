#include "game_menu_window.h"
#include "include/mainwindow.h"
#include "how_to_play_window.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>


game_menu_window::game_menu_window(QWidget *parent) : QWidget(parent) {

    // Crear un layout vertical
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setAlignment(Qt::AlignCenter);

    // Crear una etiqueta para la imagen de fondo
    QLabel *backgroundLabel = new QLabel(this);
    // Ruta de direccion de la imagen de fondo
    backgroundLabel->setPixmap(QPixmap(":/fondo del menu/fondo del juego.jpeg"));
    backgroundLabel->setScaledContents(true);
    layout->addWidget(backgroundLabel);

    // Crea label para el titulo del jugao
    QLabel *title_game = new QLabel("Tank Attack", backgroundLabel);
    title_game->setStyleSheet("font-size: 70px; font-weight: bold; color: #216106;");
    title_game->move(300, 15);
    title_game->setParent(backgroundLabel);    

    // Crea boton de Start
    button1 = new QPushButton("Start", backgroundLabel);
    button1->setFixedSize(150, 50);
    button1->move(425,170);


    // Cera boton de How to paly?
    button2 = new QPushButton("How to play?", backgroundLabel);
    button2->setFixedSize(150,50);
    button2->move(425,300);


    // Estilo de los botones
    button1->setStyleSheet("QPushButton{"
                           "background-color: #1c91ec;" //Color de fondo
                           "color: white;"                // Color del texto
                           "border: 2px solid #4CAF50;"  // Borde
                           "border-radius: 10px;"         // Bordes redondeados
                           "padding: 10px;"
                           "font-size: 16px;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: #45a049;"   // Color al pasar el mouse
                           "}"
                           "QPushButton:pressed {"
                           "background-color: #888888;"    // Color al presionar
                           "}");

    button2->setStyleSheet("QPushButton{"
                            "background-color: #1c91ec;" //Color de fondo
                            "color: white;"                // Color del texto
                            "border: 2px solid #4CAF50;"  // Borde
                            "border-radius: 10px;"         // Bordes redondeados
                            "padding: 10px;"
                            "font-size: 16px;"
                            "}"
                            "QPushButton:hover {"
                            "background-color: #45a049;"   // Color al pasar el mouse
                            "}"
                            "QPushButton:pressed {"
                            "background-color: #888888;"    // Color al presionar
                            "}");


    setLayout(layout);

    // Conectar la señal de los botones al slot
    connect(button1, &QPushButton::clicked, this, &game_menu_window::onButtonClick);
    connect(button2, &QPushButton::clicked, this, &game_menu_window::onButtonClick);
}

game_menu_window::~game_menu_window(){
    //delete ui;
}

void game_menu_window::onButtonClick(){
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    qDebug() << "Se hizo click en el boton";

    if (senderButton == button1){
        qDebug() << "Abriendo el juego...";
        //Crea e inicia MainWindow
        GameState* gameState = new GameState();
        MainWindow *mainWindow = new MainWindow(nullptr, gameState);
        mainWindow->setFixedSize(1200, 800);
        mainWindow->show();
        this->close();
    }


    else if (senderButton == button2){
        qDebug() << "Abriendo el How to play...";
        HowToPlayWindow *howToPlayWindow = new HowToPlayWindow(this);
        howToPlayWindow->setFixedSize(1000,600);
        howToPlayWindow->show();
        this->hide();
    }

    qDebug() << "Se abrio y se cerro la ventana bien";
}
