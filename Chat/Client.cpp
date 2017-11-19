#include "Client.h"

Client::Client(const QString& strHost, int nPort,const QString& strClientName, QWidget* parent) : QDialog(parent), m_nNextBlockSize(0)
{
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
    m_ptxtMessage->append(QString::number(nPort));
    m_ptxtMessage->append(strClientName);
}



void Client::sendToServer()
{

}

