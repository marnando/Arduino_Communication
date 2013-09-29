#ifndef SERIALPORTCONNECTIONCONTROLS_H
#define SERIALPORTCONNECTIONCONTROLS_H

#include <QWidget>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore>

namespace Ui {
class serialportconnectioncontrols;
}

class serialportconnectioncontrols : public QWidget
{
    Q_OBJECT

public:
    explicit serialportconnectioncontrols(QWidget *parent = 0);
    ~serialportconnectioncontrols(){delete ui;}

    bool isAutoconnect(){return autoconnect;}

public slots:
    void setConnectedPort(QString portName);
    void setDisconnected();
    void setAutoconnected(bool value);

signals:
    void AutoconnectChanged(bool autoconnect);
    void Connect(QString portName);
    void Disconnect();


private slots:

    void on_AutoConnectButton_toggled(bool checked);

    void on_ConnectButton_clicked(bool checked);

private:
    Ui::serialportconnectioncontrols *ui;
    bool autoconnect;
    QSerialPortInfo portInfo;
    QStringList entryList;
    bool connected;

    void checkButtonLogic();
};


#endif // SERIALPORTCONNECTIONCONTROLS_H
