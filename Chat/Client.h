#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QTcpSocket>

class ISocketAdapter;

class Client: public QDialog
{
    Q_OBJECT

public:
    Client(const QString& strHost, int nPort, const QString& strClient, QWidget *parent=0);

private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtMessage;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;
    QString m_strClientName;

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );


public slots:
    void on_message(QString text);
    void on_send();

protected:
    ISocketAdapter *m_pSock;
};

#endif // CLIENT_H
