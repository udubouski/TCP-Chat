#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QTcpSocket>
#include <Server.h>

class Client: public QDialog
{
    Q_OBJECT

public:
    Client(const QString& strHost, int nPort, const QString& strClient, QWidget *parent=0);
    void answerMessage(const QString& str) {m_strMessage=str;}
private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtMessage;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;
    QString m_strClientName;
    QString m_strMessage;

signals:
    void sendMessage();
public slots:
    void Message() {emit sendMessage();}
private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );

};
#endif // CLIENT_H
