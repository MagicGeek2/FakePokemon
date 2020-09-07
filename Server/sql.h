#ifndef MYSQL_H
#define MYSQL_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QCoreApplication>

class MySql
{
public:
    MySql();
    ~MySql();
    void open();                                                //打开数据库
    void threadOpen() ;
    void close();                                               //关闭数据库
    void createtable();                                         //创建table
    bool loguser(QString name,QString password);                //登录检查
    bool signup(QString name,QString password,QString pet);     //注册检查
    void delete_user(QString name);                             //删除某一用户
    QStringList get_data(QString name);                         //获取某一用户详细信息
    QStringList get_user_list();                                //获取用户列表
    void result_refresh(QStringList list, QString name);        //战斗后数据更新
private:
    QSqlQuery *query;
    QSqlDatabase db;
};

#endif // MYSQL_H
