#ifndef SERVERSOCKETADAPTER_H
#define SERVERSOCKETADAPTER_H

# include "socketadapter.h"

class ServerSocketAdapter : public SocketAdapter
{
    Q_OBJECT

public:
    explicit ServerSocketAdapter(QTcpSocket* pSock, QObject *parent = 0);

};

#endif // SERVERSOCKETADAPTER_H
