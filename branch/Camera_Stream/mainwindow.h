#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    int keyDelayTimer;

private slots:
    void on_switchStreamButton_clicked();
    void on_upDirButton_clicked(bool);
    void on_leftDirButton_clicked(bool);
    void on_downDirButton_clicked(bool);
    void on_rightDirButton_clicked(bool);

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *myScene;
    void change_x_freq(int);
    void change_y_freq(int);

    int x_freq;
    int y_freq;

    static int freq_array[13];
};

#endif // MAINWINDOW_H
