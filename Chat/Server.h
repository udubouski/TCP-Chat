#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QtWidgets>

/*class QTcpServer;
class QTcpSocket;
class QString;

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(int nPort, QWidget* pwgt = 0);

private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str);

public slots:
    void slotNewConnection();
    void slotReadClient   ();

};*/

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
    void on_newConnection();
    void on_disconnected();
    void on_message(QString);

protected:
  QTcpServer* m_ptcpServer;
  QList<ISocketAdapter*> m_clients;

};

#endif // SERVER_H


