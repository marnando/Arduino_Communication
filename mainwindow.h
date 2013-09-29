#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionSerialPort_Settings_triggered();

private:
    Ui::MainWindow *ui;
    Arduino arduino;

};

#endif // MAINWINDOW_H
