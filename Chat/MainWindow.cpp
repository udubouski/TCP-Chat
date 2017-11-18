#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QDialog(parent)
{
    createWidget();
}

void MainWindow::createWidget()
{
    m_pCreateServer = new QRadioButton(tr("Create server"));
    m_pConnectServer = new QRadioButton(tr("Connect server"));
    QHBoxLayout* phbxServer = new QHBoxLayout;
    phbxServer->addWidget(m_pCreateServer);
    phbxServer->addWidget(m_pConnectServer);

    QLabel* plIpAdr = new QLabel(tr("Ipv4 adress:"));
    m_pIpv4Adress = new QLineEdit;
    QHBoxLayout* phbxIpAdr = new QHBoxLayout;
    phbxIpAdr->addWidget(plIpAdr);
    phbxIpAdr->addWidget(m_pIpv4Adress);

    QLabel* plPort = new QLabel(tr("Port:"));
    m_pPort = new QLineEdit;
    QHBoxLayout* phbxPort= new QHBoxLayout;
    phbxPort->addWidget(plPort);
    phbxPort->addWidget(m_pPort);

    QLabel* plClientName = new QLabel(tr("Client name:"));
    m_pClientName = new QLineEdit;
    QHBoxLayout* phbxClientName= new QHBoxLayout;
    phbxClientName->addWidget(plClientName);
    phbxClientName->addWidget(m_pClientName);

    QPushButton* pButOk = new QPushButton(tr("Ok"));
    QPushButton* pButExit = new QPushButton(tr("Exit"));
    connect(pButOk,SIGNAL(clicked()), this, SLOT(createClientConnection()));
    connect(pButOk,SIGNAL(clicked()), this, SLOT(hide()));
    connect(pButExit,SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* phbxButn= new QHBoxLayout;
    phbxButn->addWidget(pButOk);
    phbxButn->addWidget(pButExit);

    QVBoxLayout* pAdr = new QVBoxLayout;
    pAdr->addLayout(phbxServer);
    pAdr->addLayout(phbxIpAdr);
    pAdr->addLayout(phbxPort);
    pAdr->addLayout(phbxClientName);
    pAdr->addLayout(phbxButn);
    setLayout(pAdr);
}

void MainWindow::createActions()
{
    /*
    m_pCreate = new QAction(tr("Create"),this);
    m_pConnect = new QAction(tr("Connect"),this);
    m_pOk = new QAction(tr("Ok"),this);
    m_pExit = new QAction(tr("Exit"),this);*/
}

void MainWindow::createConnections()
{

}

void MainWindow::createClientConnection()
{
    QString sIpv4 = m_pIpv4Adress->text();
    qint64 iPort = m_pPort->text().toInt();
    QString strClientName = m_pClientName->text();

    m_pClient = new Client(sIpv4,iPort,strClientName,this);
    m_pClient->show();
}
