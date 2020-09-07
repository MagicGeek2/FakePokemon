#include "socketthread.h"
#include<QTime>


int readcount=0;
QSemaphore mutex(1),wrt(1);

QStringList name_list={"","巴拉龟","巴鲁斯","蘑菇怪","圣光之子","谱尼","布布花","烈焰猩猩","里奥斯"};
socketthread::socketthread(qintptr p, QStringList *online_user):ptr(p),user(online_user)   // 列表user 是server_m 中的online_user, 同一时间只能有一个thread进行修改
{
    qDebug()<<"建立新线程，p="<<p;     //QThread构造函数依然在旧线程
    socket=new socket_m(this->ptr);     // 创建新的socket, 绑定descriptor
    myname="";  // 等待用户输入到来
    // disconnected 和 readyRead 是TcpSocket类中的signal
    connect(socket,SIGNAL(disconnected()),this,SLOT(onDisconnect()));   // 断开连接
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));       // 收到新消息
    sql.threadOpen();   // 每个线程都要打开database
}
socketthread::~socketthread()
{
    socket->abort();
    delete socket;
}
bool socketthread::checkSignIn(QString name,QString password)
{
    bool ret=sql.loguser(name,password);
    return ret;
}

bool socketthread::checkSignUp(QString name, QString password, QString pet)
{
    bool ret=sql.signup(name,password,pet);
    return ret;
}

void socketthread::onReadyRead()    // thread 中可能执行的动作之一
{
    qDebug()<<"线程"<<ptr<<"收到消息";
    QString data=socket->readAll();
    QStringList list=data.split("#");   // 信息用#分隔
    bool ret=0;
    QString sendData=list[0];
    if(list[0]=="z")     //注册
    {
        ret=checkSignUp(list[1],list[2],list[3]);
        if(ret)
            sendData+="#true";
        else
            sendData+="#false";

    }
    else if(list[0]=="d")  //登录
    {
        if(user->indexOf(list[1])==-1)  // 在用户列表中没有找到
        {
            ret=checkSignIn(list[1],list[2]);
            if(ret)
                sendData+="#true";
            else
                sendData+="#false";

            if(list[0]=="d"&&ret)
            {
                QStringList ulist=sql.get_data(list[1]);
                // 登录成功之后，从数据库中获取该用户数据，发送给client端
                for(int i=0;i<ulist.size();i++)
                {
                    sendData+="#";
                    sendData+=ulist[i];
                }
                myname=list[1];             //登录成功，在线用户列表中添加某用户。
                wrt.acquire();  // 同一时间只能有一个thread修改user (server_m 中的QStringList online_user , 被所有的thread共享)
                user->append(myname);
                wrt.release();
            }
        }
        else
            sendData+="#reload";         //重复登陆

    }
    else if(list[0]=="a")               //请求所有用户
    {
        QStringList ulist=sql.get_user_list();
        sendData+="#";

        for(int i=0;i<ulist.size();i++)
        {
            sendData+=ulist[i];
            sendData+="*";
        }
    }
    /*
    为什么在这里设置mutex
    同时有writer和reader访问online_user
    writer先到，那writer拿到wrt权限，reader只能等待，否则可能读到错误的数据
    reader先到，reader拿到wrt权限，writer只能等待，不能在此期间写入数据，否则可能造成reader读取的数据错误
    reader可能有很多(readers), 必须确保其中一个reader拿到wrt, 所有的readers才能安全读取online_user
    不如就确保第一个reader拿到wrt。按照这样的思路，可以设法让reader顺序进行作业。可以设置互斥访问达到目的。
    mutex本身就是互斥锁的意思。
    如果这里没有mutex, 可能有两个reader同时进入下面程序，令readcount=2， 结果没有一个reader拿到wrt权限
    */
    else if(list[0]=="o")           //在线用户
    {
        //读取在线用户列表
        mutex.acquire();            //互斥访问
        readcount++;
        if(readcount == 1)
            wrt.acquire();
        mutex.release();

        QStringList ulist=*user;    //读操作
        sendData+="#";
        for(int i=0;i<ulist.size();i++)
        {
            sendData+=ulist[i];
            sendData+="*";
        }
        mutex.acquire();            //读者减一
        readcount--;
        if(readcount==0)            //若此为最后一个读者，则释放写信号量
            wrt.release();
        mutex.release();
    }
    else if(list[0]=="detail")                  //某用户的详细数据
    {
        QStringList ulist=sql.get_data(list[1]);
        for(int i=0;i<ulist.size();i++)
        {
            sendData+="#";
            sendData+=ulist[i];
        }

    }
    else if(list[0]=="rand_p")
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        sendData+="#";
        for(int i=0;i<15;i++){      //发给客户端15个随机精灵号
            int r=qrand()%8+1;
            sendData.append(QString::number(r)+"*");
        }

    }
    else if(list[0]=="result")
    {
        sql.result_refresh(list,myname);

    }
    else
        return;


    socket->write(sendData.toLatin1());     // socket 回消息
    socket->waitForBytesWritten();  // 等到socket将消息发送出去之后，函数才返回，否则阻塞，默认时间为30s. 保证安全性和正确性。

    if((list[0]=="d"&&ret==false)||list[0]=="z")    // 注册，或者登录不成功
     {
        socket->abort();    // 终止socket
        this->quit();   // 退出thread
     }


}
void socketthread::onDisconnect()    // thread 中可能执行的动作之一
{
    user->removeOne(myname);
    qDebug()<<"线程 p="<<this->ptr<<" 结束";
    this->quit();
}

void socketthread::run()    //
{
    qDebug()<<"开始新线程";
    this->exec();
}
