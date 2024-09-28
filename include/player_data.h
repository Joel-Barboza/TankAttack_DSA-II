#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsScene>
#include <QPushButton>

class PlayerData : public QWidget {
    Q_OBJECT

public:
    explicit PlayerData(QWidget *parent = nullptr);

private:
    QLabel *infoLabel;          // To show player information
    QPushButton *powerUpButton; // To represent a power-up button
    void setupFooter();  // Helper function to setup the footer layout
};

#endif // PLAYER_DATA_H
