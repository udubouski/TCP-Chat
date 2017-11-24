#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QtWidgets>
# include <QObject>
# include <QList>

class QTcpServer;
class QTcpSocket;
class ISocketAdapter;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(int nPort, QObject *parent = 0);

public slots:
    void slotNewConnection();
    void slotDisconnect();
    void slotMessage(QString);

protected:
    QTcpServer* m_pTCPServer;
    QList<ISocketAdapter*> m_pClients;

};

#endif // SERVER_H


