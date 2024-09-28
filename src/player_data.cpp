#include "include/player_data.h"

// Constructor for the PlayerData class
PlayerData::PlayerData(QWidget *parent) : QWidget(parent) {
    setupFooter();
}

// Function to create the footer layout
void PlayerData::setupFooter() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setFixedSize(1200, 100);
    layout->setContentsMargins(0,0,0,0);

    infoLabel = new QLabel("player info", this);
    layout->addWidget(infoLabel);

    this->setStyleSheet("background-color: lightblue;");
    this->setLayout(layout);

}
