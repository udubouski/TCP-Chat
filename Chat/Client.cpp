#include "Client.h"
#include "ClientSocketAdapter.h"

Client::Client(const QString& strHost, int nPort, const QString& strClientName, QWidget* parent) : QDialog(parent)
{
    m_pSock = new ClientSocketAdapter(this);
    connect(m_pSock, SIGNAL(message(QString)), SLOT(slotMessage(QString)));

    m_strClientName=strClientName;
    m_ptxtMessage = new QTextEdit;
    m_ptxtMessage->setReadOnly(true);
    m_ptxtInput = new QLineEdit;

    QPushButton* pButnSend = new QPushButton(tr("Send"));
    QPushButton* pButnExit = new QPushButton(tr("Exit"));
    connect(pButnSend, SIGNAL(clicked()), SLOT(slotSend()));
    connect(pButnExit,SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* phbxButtons = new QHBoxLayout;
    phbxButtons->addWidget(pButnSend);
    phbxButtons->addWidget(pButnExit);

    QVBoxLayout* pvbxMain = new QVBoxLayout;
    pvbxMain->addWidget(m_ptxtMessage);
    pvbxMain->addWidget(m_ptxtInput);
    pvbxMain->addLayout(phbxButtons);
    setLayout(pvbxMain);
    setWindowTitle("Chat. Client - " + m_strClientName);
}

void Client::slotMessage(QString text)
{
    m_ptxtMessage->setHtml(m_ptxtMessage->toHtml() + text + "<br>");
}

void Client::slotSend()
{
    QTime currTime = QTime::currentTime();
    QString strTime = currTime.toString();
    m_pSock->sendString(strTime + " - " + m_strClientName + " : " + m_ptxtInput->text());
    m_ptxtInput->clear();
}

