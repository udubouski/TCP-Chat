#include "serversocketadapter.h"
#include <QTcpSocket>

ServerSocketAdapter::ServerSocketAdapter(QTcpSocket* pSock, QObject *parent) : SocketAdapter(parent, pSock) {}
