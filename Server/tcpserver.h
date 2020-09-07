#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTimer>
#include"server_m.h"
namespace Ui {
class TcpServer;
}

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

private slots:
    void on_startBtn_clicked();

private:
    Ui::TcpServer *ui;
    server_m* server;
};

#endif // TCPSERVER_H
