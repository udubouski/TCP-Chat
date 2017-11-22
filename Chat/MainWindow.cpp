#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QDialog(parent)
{
    createWidget();
    createConnections();
}

void MainWindow::createWidget()
{
    m_pMainLayout = new QVBoxLayout;
    m_pUpLayout = new QVBoxLayout;
    m_pDownLayout = new QVBoxLayout;

    m_pCreateServer = new QRadioButton(tr("Create server"));
    m_pConnectServer = new QRadioButton(tr("Connect server"));

    QHBoxLayout* phbxServer = new QHBoxLayout;
    phbxServer->addWidget(m_pCreateServer);
    phbxServer->addWidget(m_pConnectServer);

    m_plClientName = new QLabel(tr("Client name:"));
    m_pClientName = new QLineEdit;
    QHBoxLayout* phbxClientName= new QHBoxLayout;
    phbxClientName->addWidget(m_plClientName);
    phbxClientName->addWidget(m_pClientName);

    m_pButOk = new QPushButton(tr("Ok"));
    m_pButExit = new QPushButton(tr("Exit"));
    QHBoxLayout* phbxButn= new QHBoxLayout;
    phbxButn->addWidget(m_pButOk);
    phbxButn->addWidget(m_pButExit);

    hideDownLayout();
    m_pDownLayout->addLayout(phbxClientName);
    m_pDownLayout->addLayout(phbxButn);
    m_pMainLayout->addLayout(phbxServer);

    m_pMainLayout->addLayout(m_pUpLayout);
    m_pMainLayout->addLayout(m_pDownLayout);
    setLayout(m_pMainLayout);
}

void MainWindow::createConnections()
{
    connect(m_pCreateServer,SIGNAL(clicked()),this,SLOT(createInputForNewServer()));
    connect(m_pConnectServer,SIGNAL(clicked()),this,SLOT(createInputForExistingServer()));
    connect(m_pButOk,SIGNAL(clicked()), this, SLOT(createConnection()));
    connect(m_pButOk,SIGNAL(clicked()), this, SLOT(hide()));
    connect(m_pButExit,SIGNAL(clicked()), this, SLOT(close()));
}

void MainWindow::createInputForNewServer()
{
    showDownLayout();
    if (m_plPort && m_pPort)
    {
        if (m_plIpAdr && m_pIpv4Adress)
        {
            delete m_plIpAdr;
            delete m_pIpv4Adress;
            m_plIpAdr=0;
            m_pIpv4Adress=0;
        }
    }
    else createPortInput();
}

void MainWindow::createInputForExistingServer()
{
    showDownLayout();
    if (m_plPort && m_pPort)
    {
        if (m_plIpAdr && m_pIpv4Adress) {}
        else createIpv4Input();
    }
    else
    {
        createPortInput();
        createIpv4Input();
    }
}

void MainWindow::createPortInput()
{
    m_plPort = new QLabel(tr("Port:"));
    m_pPort = new QLineEdit;
    QHBoxLayout* phbxPort= new QHBoxLayout;
    phbxPort->addWidget(m_plPort);
    phbxPort->addWidget(m_pPort);
    m_pUpLayout->addLayout(phbxPort);
}

void MainWindow::createIpv4Input()
{
    m_plIpAdr = new QLabel(tr("Ipv4 adress:"));
    m_pIpv4Adress = new QLineEdit;
    QHBoxLayout* phbxIpAdr = new QHBoxLayout;
    phbxIpAdr->addWidget(m_plIpAdr);
    phbxIpAdr->addWidget(m_pIpv4Adress);
    m_pUpLayout->addLayout(phbxIpAdr);
}

void MainWindow::hideDownLayout()
{
    m_plClientName->hide();
    m_pClientName->hide();
    m_pButOk->hide();
    m_pButExit->hide();
}

void MainWindow::showDownLayout()
{
    m_plClientName->show();
    m_pClientName->show();
    m_pButOk->show();
    m_pButExit->show();
}

void MainWindow::createConnection()
{
    qint64 iPort = m_pPort->text().toInt();
    QString strClientName = m_pClientName->text();
    QString sIpv4;

    if (m_pCreateServer->isChecked())
    {
        m_pServer = new Server(iPort);
        sIpv4 = localIP();
    }
    else sIpv4 = m_pIpv4Adress->text();

    m_pClient = new Client(sIpv4,iPort,strClientName);
    m_pClient->show();

}

QString MainWindow::localIP()
{
    QString locIP;
    QList<QHostAddress> addr = QNetworkInterface::allAddresses();
    locIP = addr.first().toString();
    return locIP;
}

