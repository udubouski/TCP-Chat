#ifndef CLIENTSOCKETADAPTER_H
#define CLIENTSOCKETADAPTER_H

# include "socketadapter.h"

class ClientSocketAdapter : public SocketAdapter
{
    Q_OBJECT

public:
  explicit ClientSocketAdapter(QObject *parent);

};

#endif // CLIENTSOCKETADAPTER_H
