#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include<QThread>
#include<QTcpSocket>
#include<QWidget>
#include<QSemaphore>
#include"sql.h"
#include"socket_m.h"

//读者、写者问题 信号量解决
extern int readcount;
extern QSemaphore mutex,wrt;

class socketthread:public QThread
{
    Q_OBJECT
public:
    explicit socketthread(qintptr p, QStringList *online_user);
    ~socketthread();
    bool checkSignIn(QString name,QString passward);
    bool checkSignUp(QString name,QString passward,QString pet);
protected:
     virtual void run();
private slots:
    void onReadyRead();
    void onDisconnect();
private:
     qintptr ptr;           //socketDescriptor
     QStringList *user;     //在线用户列表
     socket_m *socket;      //socket. 一个新的thread管理一个新的socket
     QString myname;        //该线程对应用户的用户名
     MySql sql;             //数据库

};

#endif // SOCKETTHREAD_H
