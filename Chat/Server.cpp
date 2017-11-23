/*#include "Server.h"

Server::Server(int nPort, QWidget* pwgt) : QWidget(pwgt), m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0, "Server Error", "Unable to start the server:"+ m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }

    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void Server::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();

    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Server Response: Connected!");
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime   time;
        QString str;
        in >> time >> str;

        QString strMessage = time.toString() + " " + "Client has sent - " + str;


        m_nNextBlockSize = 0;

        sendToClient(pClientSocket, "Server Response: Received \"" + str + "\"");
    }
}

void Server::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}*/

#include "Server.h"
#include "serversocketadapter.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

Server::Server(int nPort, QObject *parent) : QObject(parent)
{
     m_ptcpServer = new QTcpServer(this);
     connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(on_newConnection()));

    if (false == m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        m_ptcpServer->close();
        throw m_ptcpServer->errorString();
    }
}

void Server::on_newConnection()
{
      QTextStream(stdout) << "new connection" << endl;

      QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
      ISocketAdapter *pSockHandle = new ServerSocketAdapter(pclientSock);

      m_clients.push_back(pSockHandle);

      pSockHandle->sendString("connect");

      connect(pSockHandle, SIGNAL(disconnected()), SLOT(on_disconnected()));
      connect(pSockHandle, SIGNAL(message(QString)), SLOT(on_message(QString)));
}

void Server::on_disconnected()
{
      QTextStream(stdout) << "client disconnected" << endl;
      ISocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
      m_clients.removeOne(client);
      delete client;
}

void Server::on_message(QString msg)
{
      foreach (ISocketAdapter *sock, m_clients)
        sock->sendString(msg);
}



