#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class PlayerData : public QWidget {
    Q_OBJECT

public:
    explicit PlayerData(QWidget *parent = nullptr);

private:
    QLabel *label;
    void setupFooter();  // Helper function to setup the footer layout
};

#endif // PLAYER_DATA_H
