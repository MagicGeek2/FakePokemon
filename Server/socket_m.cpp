#include "socket_m.h"
#include<QByteArray>
#include<QDataStream>
socket_m::socket_m(qintptr p)
{
    this->setSocketDescriptor(p);  // 设置该socket的描述符
    this->connect(this,SIGNAL(disconnected()),this,SLOT(on_discon()));    // 有客户端断开连接就发送信息

}


void socket_m::on_discon()
{
    qDebug()<<"有一个客户端断开！";
}
