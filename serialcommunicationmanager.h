#ifndef SERIALCOMMUNICATIONMANAGER_H
#define SERIALCOMMUNICATIONMANAGER_H

#include "communicationmanager.h"
#include "QtSerialPort/QSerialPort"
#include "QtSerialPort/QSerialPortInfo"
#include "serialportsettingsdialog.h"
#include <QtCore>
#include <QMessageBox>

class SerialCommunicationManager : public CommunicationManager
{
    Q_OBJECT

public:
    SerialCommunicationManager();
    ~SerialCommunicationManager();

    bool IsConnected(){return serialPort.isOpen();}

    QString getPortName(){return portName;}
    void openSettingsWindow();

signals:
    void receivedLine(QString string);
    void sentLine(QString string);
    void successfullyConnectedTo(QString portName);
    void disconnectedToPort();
    void AutoconnectionIsSet(bool value);

public slots:
    void disconnect();
    void send(QString string);
    bool connectTo(QString port, QSerialPort::BaudRate baud = QSerialPort::Baud115200);
    void setAutoconnect(bool value);
    bool autoconnect();
    bool flush();

private slots:
    void dataAvailable();
    void ErrorHandler(QSerialPort::SerialPortError error);

    void changeBaudRate(int baud){serialPort.setBaudRate(baud);}
    void changeFlowControl(QSerialPort::FlowControl flow){serialPort.setFlowControl(flow);}
    void changeBreak(int millis,bool enable = true){serialPort.setBreakEnabled(enable);serialPort.sendBreak(millis);}
    void changeParity(QSerialPort::Parity parity){serialPort.setParity(parity);}

private:
    bool tryToAutoconnect;
    QSerialPort serialPort;
    QString portName;
    QMutex mutex;
    QTimer autoConnectionTimer;

    SerialPortSettingsDialog dialog;

};

#endif // SERIALCOMMUNICATIONMANAGER_H
