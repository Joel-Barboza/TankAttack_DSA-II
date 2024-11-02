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
    QGridLayout* p1Layout = nullptr;
    QGridLayout* p2Layout = nullptr;

private:
    QLabel *infoLabel;
    QPushButton *powerUpButton;
    void setupFooter();
};

#endif // PLAYER_DATA_H
