#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "Client.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=0);

private:
    QLineEdit* m_pClientName;
    QLineEdit* m_pIpv4Adress;
    QLineEdit* m_pPort;
    QRadioButton* m_pCreateServer;
    QRadioButton* m_pConnectServer;

    QAction* m_pCreate;
    QAction* m_pConnect;
    QAction* m_pOk;
    QAction* m_pExit;

    Client* m_pClient;

    void createWidget();
    void createActions();
    void createConnections();

private slots:
    void createClientConnection();

};
#endif // MAINWINDOW_H
