#ifndef HOW_TO_PLAY_WINDOW_H
#define HOW_TO_PLAY_WINDOW_H

#include "game_menu_window.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class HowToPlayWindow : public QWidget {
    Q_OBJECT

public:
    explicit HowToPlayWindow(game_menu_window *menuWindow, QWidget *parent = nullptr);

private slots:
    void onBackButtonClick();

private:
    QPushButton *backButton;
    game_menu_window *menuWindow;

};


#endif // HOW_TO_PLAY_WINDOW_H
