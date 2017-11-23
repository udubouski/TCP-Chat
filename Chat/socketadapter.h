#ifndef SOCKETADAPTER_H
#define SOCKETADAPTER_H

# include "isocketadapter.h"

class QTcpSocket;

class SocketAdapter : public ISocketAdapter
{
    Q_OBJECT
public:
    SocketAdapter(QObject *parent, QTcpSocket *pSock = 0);
    virtual ~SocketAdapter();
    virtual void sendString(const QString& str);

protected slots:
    void on_readyRead();
    void on_disconnected();

protected:
    QTcpSocket *m_ptcpSocket;
    qint16 m_msgSize;

};

#endif // SOCKETADAPTER_H
