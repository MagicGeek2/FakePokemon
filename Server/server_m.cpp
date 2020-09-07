#include "server_m.h"
#include"socket_m.h"
#include"socketthread.h"
#include<QMessageBox>
server_m::server_m()
{
    // 启动服务器，就是启动数据库，并向数据库中写入table ; 如果已经存在table则不会进行此操作
    sql.open();            // 创建并启动数据库
    sql.createtable();    //table user 只创建一次
    online_user=new QStringList;    // 在线用户列表

}
server_m::~server_m()
{
     sql.close();
}
void server_m::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"有新的连接";
    socketthread * thread=new socketthread(socketDescriptor,online_user);

    thread->start();    // thread开始运行. 可能收到新消息 或者 断开连接
}
