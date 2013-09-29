#include "serialcommunicationmanager.h"
#include "communicationmanager.h"
#include "serialportsettingsdialog.h"

SerialCommunicationManager::SerialCommunicationManager()
{
    connect(&serialPort,SIGNAL(readyRead()),this,SLOT(dataAvailable()));
    connect(&serialPort,SIGNAL(error(QSerialPort::SerialPortError)),this,SLOT(ErrorHandler(QSerialPort::SerialPortError)));
    connect(&autoConnectionTimer,SIGNAL(timeout()),this,SLOT(autoconnect()));
    tryToAutoconnect = false;

    //dialog signals
    connect(&dialog,SIGNAL(changeBaudRate(QSerialPort::BaudRate)),this,SLOT(changeBaudRate(QSerialPort::BaudRate)));
    connect(&dialog,SIGNAL(changeBreak(int,bool)),this,SLOT(changeBreak(int,bool)));
    connect(&dialog,SIGNAL(changeFlowControl(QSerialPort::FlowControl)),this,SLOT(changeFlowControl(QSerialPort::FlowControl)));
    connect(&dialog,SIGNAL(changeParity(QSerialPort::Parity)),this,SLOT(changeParity(QSerialPort::Parity)));

    autoConnectionTimer.setInterval(5000);

    //dialog controls
//    connect(&dialog,SIGNAL(successfullyConnectedTo(QString)),this,SLOT(setConnectedPort(QString)));
//    connect(this,SIGNAL(Connect(QString)),&dialog,SLOT(connectTo(QString)));
//    connect(this,SIGNAL(Disconnect()),&dialog,SLOT(disconnect()));
//    connect(this,SIGNAL(AutoconnectChanged(bool)),&dialog,SLOT(setAutoconnect(bool)));
//    connect(&dialog,SIGNAL(disconnecteToPort()),this,SLOT(setDisconnected()));
}

SerialCommunicationManager::~SerialCommunicationManager()
{
    disconnect();
}

void SerialCommunicationManager::openSettingsWindow()
{
    dialog.show();
}

bool SerialCommunicationManager::connectTo(QString port,QSerialPort::BaudRate baud)
{
    serialPort.setPortName(port);
    serialPort.setBaudRate(baud);
    serialPort.clearError();
    if(serialPort.open(QIODevice::ReadWrite))
    {
        serialPort.clear();
        portName = port;
        qDebug()<<"connected to: "<<port;
        emit successfullyConnectedTo(port);
        if(autoConnectionTimer.isActive())
        {
            autoConnectionTimer.stop();
        }
        return true;
    }
    return false;
}

void SerialCommunicationManager::setAutoconnect(bool value)
{
    tryToAutoconnect = value;
    emit AutoconnectionIsSet(value);
    if(value){autoconnect();}
    if(!serialPort.isOpen())
    {
        autoConnectionTimer.start();
    }
}

void SerialCommunicationManager::dataAvailable()
{
    qDebug()<<"dataAvailable triggered |canReadLine is:"<<serialPort.canReadLine();
    if(serialPort.canReadLine())
    {
        QString tmp = serialPort.readLine(1000);
        qDebug()<<"received: "<<tmp;
        emit receivedLine(tmp);
    }
}

void SerialCommunicationManager::ErrorHandler(QSerialPort::SerialPortError error)
{
    switch(error)
    {
    case QSerialPort::NoError:
        return;
        break;
    case QSerialPort::DeviceNotFoundError:
        break;
    case QSerialPort::PermissionError:
        QMessageBox::warning(0,"title","Warning: Could not connect: Permission Error!!"
                             "Are you sure that you have write permission and no other Program is using this port?",QMessageBox::Ok	,QMessageBox::NoButton);
        break;
    case QSerialPort::OpenError:
        break;
    case QSerialPort::ParityError:
        break;
    case QSerialPort::FramingError:
        QMessageBox::warning(0,"title","Warning: Probably the baud rates doesn´t match!",QMessageBox::Ok	,QMessageBox::NoButton);
        break;
    case QSerialPort::BreakConditionError:
        break;
    case QSerialPort::WriteError:
        qDebug()<<"Serial Port WriteError!!";
        disconnect();
        break;
    case QSerialPort::ReadError:
        qDebug()<<"Serial Port ReadError!!";
        disconnect();
        break;
    case QSerialPort::ResourceError:
        qDebug()<<"Serial Port ResourceError!!";
        //disconnect();
        break;
    case QSerialPort::UnsupportedOperationError:
        break;
    case QSerialPort::UnknownError:
        break;
    default:
        break;
    }
    qDebug()<<"Serial Port error: Number "<<error;
    //serialPort.clearError();
}

void SerialCommunicationManager::disconnect()
{
    serialPort.flush();
    serialPort.close();
    portName.clear();
    emit disconnectedToPort();
    qDebug()<<"disconnected";
    if(tryToAutoconnect)
    {
        autoConnectionTimer.start();
    }
}

void SerialCommunicationManager::send(QString string)
{
    string.append('\n');
    serialPort.write(string.toStdString().c_str());
    string.chop(1);
    qDebug()<<"sending: "<<string;
    emit sentLine(string);
}


bool SerialCommunicationManager::autoconnect()
{
    QList <QSerialPortInfo>arduino;
    QSerialPortInfo info;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if(info.description() == "USB Serial Port" && info.manufacturer() == "FTDI" && !info.isBusy())
        {
            arduino.append(info);
        }
    }
    if(arduino.size()>1)
    {
        qWarning()<<"Warning: You tried to autoconnect, but there are more than one Arduino";
    }
    else if(arduino.size() == 1)
    {
        qDebug()<<"try to autoconnect to: "<<arduino.at(0).portName();
        qDebug()<<"error status: "<<serialPort.error();
        connectTo(arduino.at(0).portName());
    }
}

bool SerialCommunicationManager::flush()
{
    serialPort.clear();
    //serialPort.clearError();
    //serialPort.close();
    serialPort.flush();
}


/*
Location: \\.\COM3
Description: USB Serial Port
Manufacturer: FTDI
Vendor Identifier: 403
Product Identifier: 6001
Busy: No
*/
