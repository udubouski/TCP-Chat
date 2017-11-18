#include "Client.h"

Client::Client(const QString& strHost, int nPort,const QString& strClientName, QWidget* parent) : QDialog(parent), m_nNextBlockSize(0)
{
    /*m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );

    m_ptxtInfo  = new QTextEdit;
    m_ptxtInput = new QLineEdit;

    connect(m_ptxtInput, SIGNAL(returnPressed()),
            this,        SLOT(slotSendToServer())
           );
    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);*/

    m_ptxtMessage = new QTextEdit;
    m_ptxtMessage->setReadOnly(true);
    m_ptxtInput = new QLineEdit;

    QPushButton* pButnSend = new QPushButton(tr("Send"));
    QPushButton* pButnExit = new QPushButton(tr("Exit"));

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

    m_ptxtMessage->append(strHost);
    m_ptxtMessage->append(n);
    m_ptxtMessage->append(strClientName);
}

void Client::sendToServer()
{

}

