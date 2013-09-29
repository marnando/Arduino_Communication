#include "serialportsettingsdialog.h"
#include "ui_serialportsettingsdialog.h"

SerialPortSettingsDialog::SerialPortSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortSettingsDialog)
{
    ui->setupUi(this);
   // manager = parent;
    QStringList baudrates;
    baudrates<<"1200"<<"2400"<<"9600"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600"<<"115200";
    ui->BaudRateBox->addItems(baudrates);
    QStringList flowcontrols;
    flowcontrols<<"NoFlowControl"<<"HardwareControl"<<"SoftwareControl";
    ui->FlowControlBox->addItems(flowcontrols);
    QStringList parity;
    parity<<"NoParity"<<"EvenParity"<<"OddParity"<<"SpaceParity"<<"MarkParity";
    ui->ParityBox->addItems(parity);
}

SerialPortSettingsDialog::~SerialPortSettingsDialog()
{
    delete ui;
}

void SerialPortSettingsDialog::on_DefaultSettingsButton_clicked()
{
    ui->BaudRateBox->setCurrentIndex(8);
    ui->FlowControlBox->setCurrentIndex(0);
    ui->checkBox->setChecked(false);
    ui->BreakSpinBox->setValue(0);
    ui->ParityBox->setCurrentIndex(0);
}

void SerialPortSettingsDialog::on_DialogButton_accepted()
{
   emit changeBaudRate(ui->BaudRateBox->currentText().toInt());
   emit changeFlowControl(QSerialPort::FlowControl(ui->FlowControlBox->currentIndex()));
   emit changeParity(QSerialPort::Parity(ui->ParityBox->currentIndex()));
   if(ui->checkBox->isChecked()){emit changeBreak(ui->BreakSpinBox->value(),true);}
}

void SerialPortSettingsDialog::on_DialogButton_rejected()
{
    return;
}

void SerialPortSettingsDialog::on_checkBox_toggled(bool checked)
{
    ui->BreakSpinBox->setEnabled(checked);
}
