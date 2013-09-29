#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "serialcommunicationmanager.h"
#include "serialtransmissionmonitor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //controls
    connect(&arduino,SIGNAL(successfullyConnectedTo(QString)),ui->widget,SLOT(setConnectedPort(QString)));
    connect(ui->widget,SIGNAL(Connect(QString)),&arduino,SLOT(connectTo(QString)));
    connect(ui->widget,SIGNAL(Disconnect()),&arduino,SLOT(disconnect()));
    connect(ui->widget,SIGNAL(AutoconnectChanged(bool)),&arduino,SLOT(setAutoconnect(bool)));
    connect(&arduino,SIGNAL(disconnecteToPort()),ui->widget,SLOT(setDisconnected()));

    connect(&arduino,SIGNAL(sentLine(QString)),ui->widget_2,SLOT(addToTXbrowser(QString)));
    connect(&arduino,SIGNAL(receivedLine(QString)),ui->widget_2,SLOT(addToRXbrowser(QString)));
    //arduino.setAutoconnect(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    arduino.send("hi");
}

void MainWindow::on_actionSerialPort_Settings_triggered()
{
    arduino.openSettingsWindow();
}
