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
    MainWindow(QWidget *parent = nullptr, int rows = 1, int columns = 1, AdjacencyMatrix<int>* adjMatrix = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Map* map;
    PlayerData* playerData;
};
#endif // MAINWINDOW_H
