#ifndef SERIALPORTSETTINGSDIALOG_H
#define SERIALPORTSETTINGSDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore>
#include <QStringList>
#include <QMetaEnum>


namespace Ui {
class SerialPortSettingsDialog;
}

class SerialPortSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortSettingsDialog(QWidget *parent=0);
    ~SerialPortSettingsDialog();

signals:
    void changeBaudRate(int baud);
    void changeFlowControl(QSerialPort::FlowControl flow);
    void changeBreak(int millis,bool enable = true);
    void changeParity(QSerialPort::Parity parity);

private slots:
    void on_DialogButton_accepted();

    void on_DialogButton_rejected();

    void on_DefaultSettingsButton_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::SerialPortSettingsDialog *ui;

    friend class SerialCommunicationManager;
};

#endif // SERIALPORTSETTINGSDIALOG_H


