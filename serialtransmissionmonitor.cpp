#include "serialtransmissionmonitor.h"
#include "ui_serialtransmissionmonitor.h"

serialtransmissionmonitor::serialtransmissionmonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialtransmissionmonitor)
{
    ui->setupUi(this);
//    Rxmodel = new QStringListModel(Rxlist);
//    Txmodel = new QStringListModel(Txlist);
//    ui->RXlistView->setModel(Rxmodel);
//    ui->TXlistView->setModel(Txmodel);
}

serialtransmissionmonitor::~serialtransmissionmonitor()
{
    delete ui;
}

void serialtransmissionmonitor::addToRXbrowser(QString string)
{
    ui->RXlistWidget->addItem(string);
    //Rxlist.append(string);
    //if(Rxlist.size() > 100){Rxlist.pop_front();}

}

void serialtransmissionmonitor::addToTXbrowser(QString string)
{
    ui->TXlistWidget->addItem(string);
    //Txlist.append(string);
    //if(Txlist.size() > 100){Txlist.pop_front();}
    //ui->TXlistView->setModel(Txmodel);
    //Txmodel->dataChanged();
}
