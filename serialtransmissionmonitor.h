#ifndef SERIALTRANSMISSIONMONITOR_H
#define SERIALTRANSMISSIONMONITOR_H

#include <QWidget>
#include <QtCore>

namespace Ui {
class serialtransmissionmonitor;
}

class serialtransmissionmonitor : public QWidget
{
    Q_OBJECT

public:
    explicit serialtransmissionmonitor(QWidget *parent = 0);
    ~serialtransmissionmonitor();

public slots:
    void addToRXbrowser(QString string);
    void addToTXbrowser(QString string);
private:
    Ui::serialtransmissionmonitor *ui;

//    QStringList Rxlist,Txlist;
//    QAbstractItemModel *Rxmodel,*Txmodel;
};

#endif // SERIALTRANSMISSIONMONITOR_H
