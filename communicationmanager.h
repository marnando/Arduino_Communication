#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>

class CommunicationManager : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationManager(){}

    virtual bool IsConnected(){return false;}


signals:
    virtual void receivedLine(QString string);

public slots:
    virtual bool connectTo(QString port){return false;}
    virtual void disconnect(){}
    virtual void send(QString string){}

private:


};

#endif // COMMUNICATIONMANAGER_H
