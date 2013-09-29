#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include "serialcommunicationmanager.h"
#include "serialportconnectioncontrols.h"
#include <QTimer>

static int ArduinoVersion = 1;

class Arduino : public QObject
{
    Q_OBJECT
public:
    explicit Arduino(QObject *parent = 0);
    void openSettingsWindow(){ComManager.openSettingsWindow();}
    void flush();

    void setLed1(bool value);
    void setLed2(bool value);

signals:
    void receivedLine(QString string);
    void sentLine(QString string);
    void AutoconnectIsSetTo(bool value);
    void successfullyConnectedTo(QString port);
    void disconnecteToPort();
    void PinChanged(int pin,bool value);

public slots:
    bool connectTo(QString port);
    void disconnect()               {ComManager.disconnect();}
    void send(QString string);
    void setAutoconnect(bool value);
    void VerificationTimeout();
    void timerTimeout(){qDebug()<<"VerificationTimer Timeout";}

private:
    void verifyVersion();

    SerialCommunicationManager ComManager;
    QTimer verificationTimeoutTimer;

private slots:
    void _receiveLine(QString string);
    void _sentLine(QString string){emit sentLine(string);}
    void _successfullyConnectedTo(QString port){emit successfullyConnectedTo(port);verifyVersion();}
    void _disconnectedToPort(){emit disconnecteToPort();}

};

//static void connectWithControls(Arduino &arduino, serialportconnectioncontrols *controls);

#endif // ARDUINO_H
