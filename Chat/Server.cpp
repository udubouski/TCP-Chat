#include "Server.h"
#include "ServerSocketAdapter.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

Server::Server(int nPort, QObject *parent) : QObject(parent)
{
     m_pTCPServer = new QTcpServer(this);
     connect(m_pTCPServer, SIGNAL(newConnection()), SLOT(slotNewConnection()));

    if (false == m_pTCPServer->listen(QHostAddress::Any, nPort))
    {
        m_pTCPServer->close();
        throw m_pTCPServer->errorString();
    }
}

void Server::slotNewConnection()
{
      QTcpSocket* pClientSock = m_pTCPServer->nextPendingConnection();
      ISocketAdapter *pSockHandle = new ServerSocketAdapter(pClientSock);

      m_pClients.push_back(pSockHandle);

      pSockHandle->sendString("Client connected");

      connect(pSockHandle, SIGNAL(disconnected()), SLOT(slotDisconnect()));
      connect(pSockHandle, SIGNAL(message(QString)), SLOT(slotMessage(QString)));
}

void Server::slotDisconnect()
{
      ISocketAdapter* pClient = static_cast<ServerSocketAdapter*>(sender());
      m_pClients.removeOne(pClient);
      delete pClient;
}

void Server::slotMessage(QString msg)
{
      foreach (ISocketAdapter *sock, m_pClients)
        sock->sendString(msg);
}



