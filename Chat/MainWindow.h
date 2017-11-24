#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QNetworkInterface>
#include "Client.h"
#include "Server.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);

private:
    QVBoxLayout* m_pMainLayout;
    QVBoxLayout* m_pUpLayout;
    QVBoxLayout* m_pDownLayout;

    QRadioButton* m_pCreateServer;
    QRadioButton* m_pConnectServer;

    QLineEdit* m_pPort;
    QLineEdit* m_pIpv4Adress;
    QLineEdit* m_pClientName;

    QLabel* m_plPort;
    QLabel* m_plIpAdr;
    QLabel* m_plClientName;

    QPushButton* m_pButOk;
    QPushButton* m_pButExit;

    Client* m_pClient;
    Server* m_pServer;

    QString m_Message;

    void createWidget();
    void createConnections();
    void createPortInput();
    void createIpv4Input();
    void hideDownLayout();
    void showDownLayout();
    QString localIP();

private slots:
    void createInputForNewServer();
    void createInputForExistingServer();
    void createClientConnection();

};
#endif // MAINWINDOW_H


