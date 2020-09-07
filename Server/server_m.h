#ifndef SERVER_M_H
#define SERVER_M_H


#include<QObject>
#include<QTcpServer>
#include<QWidget>
#include"sql.h"

class server_m:public QTcpServer  // 继承QTcpServer类
{
    Q_OBJECT
private:
    MySql sql;                           //数据库
    QStringList *online_user;           //在线用户列表
public:
    server_m();
    ~server_m();

private:
    virtual void incomingConnection(qintptr socketDescriptor);  // QTcpServer类中的虚函数，有新的tcp连接时触发。在server_m类中重写
};

#endif // SERVER_M_H
