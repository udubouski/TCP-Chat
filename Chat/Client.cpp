#include "Client.h"

Client::Client(const QString& strHost, int nPort, const QString& strClientName, QWidget* parent) : QDialog(parent), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));

    m_strClientName=strClientName;
    m_ptxtMessage = new QTextEdit;
    m_ptxtMessage->setReadOnly(true);
    m_ptxtInput = new QLineEdit;
    connect(m_ptxtInput, SIGNAL(returnPressed()), this, SLOT(slotSendToServer()));

    QPushButton* pButnSend = new QPushButton(tr("Send"));
    QPushButton* pButnExit = new QPushButton(tr("Exit"));
    connect(pButnSend, SIGNAL(clicked()), SLOT(slotSendToServer()));

    connect(pButnSend,SIGNAL(clicked()), this, SLOT(sendToServer()));
    connect(pButnExit,SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* phbxButtons = new QHBoxLayout;
    phbxButtons->addWidget(pButnSend);
    phbxButtons->addWidget(pButnExit);

    QVBoxLayout* pvbxMain = new QVBoxLayout;
    pvbxMain->addWidget(m_ptxtMessage);
    pvbxMain->addWidget(m_ptxtInput);
    pvbxMain->addLayout(phbxButtons);
    setLayout(pvbxMain);

    connect(pButnSend,SIGNAL(clicked()),this,SLOT(Message()));
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        m_ptxtMessage->append(m_strClientName + ":" + m_strMessage);
        //m_ptxtMessage->append(time.toString() + " " + str);
        m_nNextBlockSize = 0;
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    m_ptxtMessage->append(strError);
}

void Client::slotSendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    m_ptxtInput->setText("");
}

void Client::slotConnected()
{
    m_ptxtMessage->append("Received the connected() signal");
}


