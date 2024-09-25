#include "include/player_data.h"

// Constructor for the PlayerData class
PlayerData::PlayerData(QWidget *parent) : QWidget(parent) {
    setupFooter();
}

// Function to create the footer layout
void PlayerData::setupFooter() {
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    label = new QLabel("Player Data: Add controls or information here.");
    layout->addWidget(label);

    container->setStyleSheet("background-color: lightblue;");

    setLayout(layout);

}
