#include "include/how_to_play_window.h"
#include "game_menu_window.h"
#include "include/mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>



HowToPlayWindow::HowToPlayWindow(game_menu_window *menuWindow, QWidget *parent)
    : QWidget(parent), menuWindow(menuWindow) {
    // Titulo a la ventana
    setWindowTitle("How to Play?");


    // Crea el layout principal
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);


    // Crear una etiqueta para la imagen de fondo
    QLabel *backgroundLabel = new QLabel(this);
    // Ruta de direccion de la imagen de fondo
    backgroundLabel->setPixmap(QPixmap(":/fondo del menu/fondo del juego.jpeg"));
    backgroundLabel->setScaledContents(true);
    //layout->addWidget(backgroundLabel);

    // Crea un ScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea {background: transparent; border: none; }");
    scrollArea->setFixedSize(400,250);
    scrollArea->setParent(backgroundLabel);
    scrollArea->move(300,125);


    // Crea label para el titulo del jugao
    QLabel *title_game = new QLabel("How to Play?", backgroundLabel);
    title_game->setStyleSheet("font-size: 70px; font-weight: bold; color: #216106;");
    title_game->move(290, 15);
    title_game->setParent(backgroundLabel);

    // Agrega el contenido adicional aquí (puedes incluir instrucciones, imágenes, etc.)
    QLabel *instructionsLabel = new QLabel("-------------------------------   Tank Attack!   -------------------------------"
                                           "\n\n"
                                           "Es un juego de modalidad multijugador que permite\n"
                                           "que 2 personas juegen un 1 vs 1 mediante turnos."
                                           "\n\n"
                                           "- El tiempo de cada partida es de 5 minutos como máximo."
                                           "\n\n"
                                           "- Por turno solo se puede hacer una de estas tres cosas:"
                                           "\n"
                                           "      1) Moverse ----------------> CLICK IZQUIERDO"
                                           "\n"
                                           "      2) Disparar ----------------> CLICK DERECHO"
                                           "\n"
                                           "      3) Usar un Powe-up  ---> SHIFT"
                                           "\n\n"
                                           "- Cada jugador tiene 4 tanques 2 de cada color, los colres son: \n"
                                           "Rojo y Azul para el Jugador 1\n"
                                           "Amarillo y Celeste"
                                           "para el Jugador 2"
                                           "\n\n"
                                           "- Para disparar se debe seleccionar el tanque que va a dispa"
                                           "rar y hace CLICK DERECHO donde se quiere disparar."
                                           "\n\n"
                                           "- Las balas le hacen un 25% de daño a los tanques Azules y Celestes.\n"
                                           "- Las balas le hacen un 50% de daño a los tanques Rojos y Amarillos."
                                           "\n\n"
                                           "¡ATENCIÓN, HAY FUEGO ALIADO, TENGAN CUIDADO DONDE APUNTAN!"
                                           "\n\n"
                                           "- En el juego hay Power-ups, estos se consumen con SHIFT en un"
                                           " turno y se aplican en el siguiente turno, los Power-ups son:\n"
                                           "      1) Doble turno"
                                           "\n"
                                           "      2) Precisión de movimiento"
                                           "\n"
                                           "      3) Precisión de ataque"
                                           "\n"
                                           "      4) Poder de ataque"
                                           "\n\n"
                                           "\n\n"
                                           "                    ¡AHORA SI, A DISFRUTAR DEL JUEGO!"
                                           "\n\n"
                                           "\n\n"
                                           "\n\n");
    instructionsLabel->setStyleSheet("background-color: transparent; color: black;");
    instructionsLabel->setWordWrap(true); // Permite el ajuste de texto
    //layout->addWidget(instructionsLabel);

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

    scrollArea->setWidget(instructionsLabel);

    layout->addWidget(backgroundLabel);


    setLayout(layout);
}

void HowToPlayWindow::onBackButtonClick( ){
    // Cierra la ventana actual
    qDebug() << "Regresando al menú principal";
    this->close();
    menuWindow->show();
}
