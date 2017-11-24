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
    QString m_strClientName;

public slots:
    void slotMessage(QString text);
    void slotSend();

protected:
    ISocketAdapter *m_pSock;
};

#endif // CLIENT_H
