#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QtWidgets>

class QTcpServer;
class QTcpSocket;
class QString;

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(int nPort, QWidget* pwgt = 0);
    QString getMessage() {return m_strMesg;}
private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;
    QString m_strMesg;

    void sendToClient(QTcpSocket* pSocket, const QString& str);

public slots:
    void slotNewConnection();
    void slotReadClient   ();

};

#endif // SERVER_H
