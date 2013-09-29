#include "arduino.h"

Arduino::Arduino(QObject *parent) :
    QObject(parent)
{
    connect(&ComManager,SIGNAL(receivedLine(QString)),this,SLOT(_receiveLine(QString)));
    connect(&ComManager,SIGNAL(successfullyConnectedTo(QString)),this,SLOT(_successfullyConnectedTo(QString)));
    connect(&ComManager,SIGNAL(sentLine(QString)),this,SLOT(_sentLine(QString)));
    connect(&ComManager,SIGNAL(disconnectedToPort()),this,SLOT(_disconnectedToPort()));

    verificationTimeoutTimer.setSingleShot(true);
    verificationTimeoutTimer.setInterval(3000);
    connect(&verificationTimeoutTimer,SIGNAL(timeout()),this,SLOT(timerTimeout()));
    connect(&verificationTimeoutTimer,SIGNAL(timeout()),this,SLOT(VerificationTimeout()));
}

void Arduino::flush()
{
    ComManager.flush();
}

void Arduino::setAutoconnect(bool value)
{
    ComManager.setAutoconnect(value);
    emit AutoconnectIsSetTo(value);
}

bool Arduino::connectTo(QString port)
{
    bool tmp = ComManager.connectTo(port);
    return tmp;
}

void Arduino::send(QString string)
{
    if(ComManager.IsConnected())
    {
        ComManager.send(string);
    }
    else
    {
        qDebug()<<"Warning: Try to send but port is not connected!!";
    }
}

void Arduino::verifyVersion()
{
    verificationTimeoutTimer.start();
    ComManager.flush();
    ComManager.send("I");
}

void Arduino::VerificationTimeout()
{
    verificationTimeoutTimer.stop();
    qDebug()<<"VerificationTimeout on port: "<<ComManager.getPortName();
    disconnect();
}


/////////////////////////////////////////////////////////////////////////////////////////////

void Arduino::_receiveLine(QString string)
{
    string.chop(1);
    qDebug()<<"received: "<<string;
    emit receivedLine(string);
    if(string.startsWith("F"))
    {

    }
    else if(string.startsWith("ID:"))
    {
        if(string.compare("ID:" + ArduinoVersion))
        {
            verificationTimeoutTimer.stop();
            qDebug()<<"successfully veryfied!!";
        }
    }
}


void Arduino::setLed1(bool value)
{
    QString tmp;
    tmp.append("F1 ");
    tmp.append(value);
    ComManager.send(tmp);
}
