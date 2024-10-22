#include "include/how_to_play_window.h"
#include "game_menu_window.h"
#include "include/mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>



HowToPlayWindow::HowToPlayWindow(game_menu_window *menuWindow, QWidget *parent)
    : QWidget(parent), menuWindow(menuWindow) {
    // Titulo a la ventana
    setWindowTitle("How to Play?");


    // Crea el layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);

    // Crear una etiqueta para la imagen de fondo
    QLabel *backgroundLabel = new QLabel(this);
    // Ruta de direccion de la imagen de fondo
    backgroundLabel->setPixmap(QPixmap(":/fondo del menu/fondo del juego.jpeg"));
    backgroundLabel->setScaledContents(true);
    layout->addWidget(backgroundLabel);

    // Crea label para el titulo del jugao
    QLabel *title_game = new QLabel("How to Play?", backgroundLabel);
    title_game->setStyleSheet("font-size: 70px; font-weight: bold; color: #216106;");
    title_game->move(290, 15);
    title_game->setParent(backgroundLabel);

    // Boton para devolverse al main menu
    backButton = new QPushButton("Back",this);
    backButton->setFixedSize(75, 40);
    backButton->move(25, 25);


    backButton->setStyleSheet("QPushButton{"
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

    // Conectar la señal del boton al slot
    connect(backButton, &QPushButton::clicked, this, &HowToPlayWindow::onBackButtonClick);

    setLayout(layout);
}

void HowToPlayWindow::onBackButtonClick( ){
    // Cierra la ventana actual
    qDebug() << "Regresando al menú principal";
    this->close();
    menuWindow->show();
}
