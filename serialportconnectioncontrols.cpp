#include "serialportconnectioncontrols.h"
#include "ui_serialportconnectioncontrols.h"

serialportconnectioncontrols::serialportconnectioncontrols(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialportconnectioncontrols)
{
    ui->setupUi(this);
    connected = false;
    QList <QSerialPortInfo> ports = portInfo.availablePorts();
    QSerialPortInfo tmp;
    for(int i=0;i<ports.size();i++)
    {
        tmp = ports.at(i);
        ui->PortBox->addItem(tmp.portName());
    }
    autoconnect = true;
}

void serialportconnectioncontrols::setConnectedPort(QString portName)
{
    connected = true;
    ui->PortBox->setCurrentText(portName);
    checkButtonLogic();
}

void serialportconnectioncontrols::setDisconnected()
{
    connected = false;
    checkButtonLogic();
}

void serialportconnectioncontrols::setAutoconnected(bool value)
{
    autoconnect = value;
    checkButtonLogic();
}

void serialportconnectioncontrols::on_AutoConnectButton_toggled(bool checked)
{
    autoconnect = checked;
    emit AutoconnectChanged(checked);
    checkButtonLogic();
}

void serialportconnectioncontrols::on_ConnectButton_clicked(bool checked)
{
    if(checked){emit Connect(ui->PortBox->currentText());}
    else{emit Disconnect();}
    checkButtonLogic();
}

void serialportconnectioncontrols::checkButtonLogic()
{
    if(autoconnect && connected)
    {
        ui->ConnectButton->setEnabled(false);
        ui->PortBox->setEnabled(false);
        ui->AutoConnectButton->setEnabled(true);
    }
    else if(!autoconnect && connected)
    {
        ui->ConnectButton->setEnabled(true);
        ui->PortBox->setEnabled(false);
        ui->AutoConnectButton->setEnabled(false);
    }
    else if(autoconnect && !connected)
    {
        ui->ConnectButton->setEnabled(false);
        ui->PortBox->setEnabled(false);
        ui->AutoConnectButton->setEnabled(true);
    }
    else if(!autoconnect && !connected)
    {
        ui->ConnectButton->setEnabled(true);
        ui->PortBox->setEnabled(true);
        ui->AutoConnectButton->setEnabled(true);
    }

    ui->AutoConnectButton->setChecked(autoconnect);
    ui->ConnectButton->setChecked(connected);
    (connected)?ui->ConnectButton->setText("Disconnect"):ui->ConnectButton->setText("Connect");
}
