
#include "communicationmanager.h"

CommunicationManager::CommunicationManager()
{

}

bool CommunicationManager::connectTo(QString port)
{
    return false;
}

void CommunicationManager::disconnect()
{

}

void CommunicationManager::send(QString string)
{

}

bool CommunicationManager::getIsConnected() const
{
    return isConnected;
}

void CommunicationManager::setIsConnected(bool value)
{
    isConnected = value;
}
