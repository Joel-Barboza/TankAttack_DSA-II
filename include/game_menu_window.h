#ifndef GAME_MENU_WINDOW_H
#define GAME_MENU_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class game_menu_window: public QWidget
{
    Q_OBJECT

public:
    game_menu_window(QWidget *parent = nullptr);
    ~game_menu_window();

private slots:
    void onButtonClick();

private:
    QPushButton *button1;
    QPushButton *button2;

};

#endif // GAME_MENU_WINDOW_H
