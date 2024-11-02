#include "include/player_data.h"
#include "include/game_state.h"

// Constructor for the PlayerData class
PlayerData::PlayerData(QWidget *parent) : QWidget(parent) {
    setupFooter();
}

// Function to create the footer layout
void PlayerData::setupFooter() {
    setFixedSize(1212, 125);
    setStyleSheet("background-color: lightblue;");

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);

    QWidget* player1Data = new QWidget();
    QWidget* player2Data = new QWidget();
    layout->addWidget(player1Data, 0, 0);
    layout->addWidget(player2Data, 0, 1);

    p1Layout = new QGridLayout(player1Data);
    p1Layout->setSpacing(0);
    p2Layout = new QGridLayout(player2Data);
    p2Layout->setSpacing(0);


    QLabel* p1Name = new QLabel("Roberto");
    QLabel* p2Name = new QLabel("Roberto");

    QPixmap* tankRed = new QPixmap("../../images/red_tank.png");
    *tankRed = tankRed->scaled(25, 25, Qt::KeepAspectRatio);

    QPixmap* tankBlue = new QPixmap("../../images/blue_tank.png");
    *tankBlue = tankBlue->scaled(25, 25, Qt::KeepAspectRatio);

    QPixmap* tankYellow = new QPixmap("../../images/yellow_tank.png");
    *tankYellow = tankYellow->scaled(25, 25, Qt::KeepAspectRatio);

    QPixmap* tankLightBlue = new QPixmap("../../images/lightblue_tank.png");
    *tankLightBlue = tankLightBlue->scaled(25, 25, Qt::KeepAspectRatio);

    // QLabel* p1TankRed1 = new QLabel();
    // //p1TankRed1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    // p1TankRed1->setPixmap(*tankRed);
    // p1TankRed1->setContentsMargins(0, 0, 0, 0);
    // p1TankRed1->setStyleSheet("padding: 0px; border: 1px solid black; border-right: 0px");
    // QLabel* p1TankRed1Percent = new QLabel("75%");
    // p1TankRed1Percent->setContentsMargins(0, 0, 0, 0);
    // p1TankRed1Percent->setStyleSheet("padding: 0px; border: 1px solid black; border-left: 0px; color: black;");

    // QLabel* p1TankRed2 = new QLabel();
    // p1TankRed2->setPixmap(*tankRed);
    // QLabel* p1TankRed2Percent = new QLabel("75%");

    // QLabel* p1TankBlue1 = new QLabel();
    // p1TankBlue1->setPixmap(*tankBlue);
    // QLabel* p1TankBlue1Percent = new QLabel("75%");

    // QLabel* p1TankBlue2 = new QLabel();
    // p1TankBlue2->setPixmap(*tankBlue);
    // QLabel* p1TankBlue2Percent = new QLabel("75%");

    // QLabel* p1PoweUp1 = new QLabel();
    // p1PoweUp1->setPixmap(*tankRed);



    // QLabel* p2TankYellow1 = new QLabel();
    // p2TankYellow1->setPixmap(*tankYellow);
    // QLabel* p2TankYellow1Percent = new QLabel("75%");

    // QLabel* p2TankYellow2 = new QLabel();
    // p2TankYellow2->setPixmap(*tankYellow);
    // QLabel* p2TankYellow2Percent = new QLabel("75%");

    // QLabel* p2TankLightBlue1 = new QLabel();
    // p2TankLightBlue1->setPixmap(*tankLightBlue);
    // QLabel* p2TankLightBlue1Percent = new QLabel("75%");

    // QLabel* p2TankLightBlue2 = new QLabel();
    // p2TankLightBlue2->setPixmap(*tankLightBlue);
    // QLabel* p2TankLightBlue2Percent = new QLabel("75%");

    QLabel* p2PoweUp1 = new QLabel();
    p2PoweUp1->setPixmap(*tankYellow);

    // p1PwrUp1->setRect(0,0,5,5);


    // QLabel* p1TankLabel2 = new QLabel;

    p1Layout->addWidget(p1Name, 0, 3, 1, 5);
    auto* currentTank = GameState::player1->tankList->getHead();
    int index = 0;
    while (currentTank != nullptr) {
        p1Layout->addWidget(currentTank->data->getTankImgPlyrData(), 1, index++);
        p1Layout->addWidget(currentTank->data->getTankPercentagePlyrData(), 1, index++);
        currentTank = currentTank->next;
    }

    // p1Layout->addWidget(p1TankRed2, 1, 2);
    // p1Layout->addWidget(p1TankRed2Percent, 1, 3);

    // p1Layout->addWidget(p1TankBlue1, 1, 4);
    // p1Layout->addWidget(p1TankBlue1Percent, 1, 5);

    // p1Layout->addWidget(p1TankBlue2, 1, 6);
    // p1Layout->addWidget(p1TankBlue2Percent, 1, 7);

    //p1Layout->addWidget(p1PoweUp1, 2, 0);



    p2Layout->addWidget(p2Name, 0, 3, 1, 5);

    currentTank = GameState::player2->tankList->getHead();
    index = 0;
    while (currentTank != nullptr) {
        p2Layout->addWidget(currentTank->data->getTankImgPlyrData(), 1, index++);
        p2Layout->addWidget(currentTank->data->getTankPercentagePlyrData(), 1, index++);
        currentTank = currentTank->next;
    }

    // p2Layout->addWidget(p2TankYellow1, 1, 0);
    // p2Layout->addWidget(p2TankYellow1Percent, 1, 1);

    // p2Layout->addWidget(p2TankYellow2, 1, 2);
    // p2Layout->addWidget(p2TankYellow2Percent, 1, 3);

    // p2Layout->addWidget(p2TankLightBlue1, 1, 4);
    // p2Layout->addWidget(p2TankLightBlue1Percent, 1, 5);

    // p2Layout->addWidget(p2TankLightBlue2, 1, 6);
    // p2Layout->addWidget(p2TankLightBlue2Percent, 1, 7);

    p2Layout->addWidget(p2PoweUp1, 2, 0);





    this->setLayout(layout);

}



// // Add buttons in a 3x3 grid
// for (int row = 0; row < 3; ++row) {
//     for (int col = 0; col < 3; ++col) {
//         QString buttonText = QString::number(row * 3 + col + 1);
//         QPushButton *button = new QPushButton(buttonText);

//         // Add button to the grid layout at the specified row and column
//     }
// }

// QVBoxLayout* layout = new QVBoxLayout(this);
// this->setFixedSize(1212, 100);

// infoLabel = new QLabel("player info", this);
// layout->addWidget(infoLabel);

// this->setStyleSheet("background-color: lightblue;");
