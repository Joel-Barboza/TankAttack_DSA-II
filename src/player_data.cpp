#include "include/player_data.h"
#include "include/game_state.h"

// Constructor for the PlayerData class
PlayerData::PlayerData(QWidget *parent) : QWidget(parent) {
    setupFooter();
}

void PlayerData::spendPlayer1PwrUp()
{
    PowerUp* pwrUp = GameState::player1->powerUpQueue->getFront().value_or(nullptr);
    if (pwrUp->getPowerUpType() != PowerUp::DoubleTurn) {
        GameState::player1->activatedPowerUp->insert(pwrUp);
    }
    delete pwrUp->getPowerUpImg();
    GameState::player1->powerUpQueue->dequeue();
}

void PlayerData::spendPlayer2PwrUp()
{
    PowerUp* pwrUp = GameState::player2->powerUpQueue->getFront().value_or(nullptr);
    if (pwrUp->getPowerUpType() != PowerUp::DoubleTurn) {
        GameState::player2->activatedPowerUp->insert(pwrUp);
    }
    delete pwrUp->getPowerUpImg();
    GameState::player2->powerUpQueue->dequeue();

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
    QLabel* p2Name = new QLabel("Juan");

    QLabel* p1PoweUp1 = new QLabel();
    QLabel* p2PoweUp1 = new QLabel();

    p1Layout->addWidget(p1Name, 0, 3, 1, 5);
    auto* currentTank = GameState::player1->tankList->getHead();
    int index = 0;
    while (currentTank != nullptr) {
        p1Layout->addWidget(currentTank->data->getTankImgPlyrData(), 1, index++);
        p1Layout->addWidget(currentTank->data->getTankPercentagePlyrData(), 1, index++);
        currentTank = currentTank->next;
    }


    p1Layout->addWidget(p1PoweUp1, 2, 0);



    p2Layout->addWidget(p2Name, 0, 3, 1, 5);

    currentTank = GameState::player2->tankList->getHead();
    index = 0;
    while (currentTank != nullptr) {
        p2Layout->addWidget(currentTank->data->getTankImgPlyrData(), 1, index++);
        p2Layout->addWidget(currentTank->data->getTankPercentagePlyrData(), 1, index++);
        currentTank = currentTank->next;
    }

    p2Layout->addWidget(p2PoweUp1, 2, 0);

    this->setLayout(layout);

}

