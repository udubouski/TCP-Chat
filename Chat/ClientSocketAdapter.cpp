#include "ClientSocketAdapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>

ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent){
    m_ptcpSocket->connectToHost("localhost",1024);
}

