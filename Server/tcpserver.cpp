#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "sql.h"

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    this->server=new server_m;
}

TcpServer::~TcpServer()
{
    delete ui;
    delete server;
}


void TcpServer::on_startBtn_clicked()
{
    // 点击按钮之后，服务器开始监听
    if(!server->listen(QHostAddress::Any,8000))
    {
        // 端口被占用，服务器未能正常启动
        qDebug()<<server->errorString();
        return;
    }
    else
    {
         qDebug()<<"开启服务器";
         ui->startBtn->setEnabled(false);
    }
}


