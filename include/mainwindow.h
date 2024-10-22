#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/map.h>
#include <include/player_data.h>
#include <include/adjacency_matrix.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static Map* map;

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    PlayerData* playerData;
};
#endif // MAINWINDOW_H
