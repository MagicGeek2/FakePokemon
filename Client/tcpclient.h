#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include<QTableWidget>
#include"pokemon.h"
#include"fightmanager.h"
extern QStringList name_list;
namespace Ui {
class TcpClient;
}

class TcpClient : public QMainWindow        // 主窗口界面
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    void table_show();                                          //初始界面
    void detail_show(QTableWidget* table,QStringList p_list);
    void pet_ser_show();
    void u_update(void);        //用户信息更新  胜率等
    void badge_update(void);    //奖牌信息更新
    void se_pet_out(void);      //决斗赛失败，送出一个精灵。
    ~TcpClient();

protected:
    void init();
    void connectServer();

private slots:
    void fight_end_slot(int flag);

    void on_sendBtn_clicked();

    void displayError(QAbstractSocket::SocketError);

    void on_signBtn_clicked();

    void readMessages();

    void on_table_list_cellPressed(int row, int column);

    void on_back_clicked();

    void on_push_begin_fight_clicked();

    void on_back_ser_clicked();

    void on_PVP_fight_clicked();

    void get_user(QString str);                        //根据combox值获取用户列表

    void get_detail_pet(QString str);                  //根据用户列表当前值，获取精灵信息

    void on_refresh_button_clicked();

    void on_level_fight_clicked();

    void on_table_list_user_cellClicked(int row, int column);

    void on_pushButton_re_clicked();

    void on_table_list_ser_cellClicked(int row, int column);

    void on_table_list_song_cellClicked(int row, int column);

    void on_confirm_clicked();

private:
    Ui::TcpClient *ui;
    QTcpSocket *tcpSocket;
//  ---------在线用户信息---------------
    QString user_name;
    QStringList p_list;                 //宠物信息
    float total_f;                      //总场数
    float win_f;                        //胜利场数
//  --------用户列表信息----------------
    QStringList u_p_list;
    float u_total_f;
    float u_win_f;
//  --------战斗相关-------------------
    Pokemon_Base* pet;
    Pokemon_Base* pet2;

    int fight_flag;                //区别对战类型。  1为升级，2为决斗

    QStringList pet_ser;           //服务器端宠物种类列表。
    FightManager*FM;

    int rand_sel[3];                   //决斗赛失败，随机送出的三只精灵

};

#endif // TCPCLIENT_H
