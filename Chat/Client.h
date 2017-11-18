#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QTcpSocket>

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

private slots:
    void sendToServer();

};
#endif // CLIENT_H
