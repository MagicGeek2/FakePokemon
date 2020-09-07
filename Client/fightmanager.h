#ifndef FIGHTMANAGER_H
#define FIGHTMANAGER_H
#include "pokemon.h"
#include <QMainWindow>
#include  <QPixmap>
#include <synchapi.h>
#include <QTimer>
#include<QMessageBox>
#include<QPropertyAnimation>
extern int timer;


namespace Ui {
class FightManager;
}

class FightManager : public QMainWindow
{
    Q_OBJECT
public:
    explicit FightManager(Pokemon_Base* _p1,Pokemon_Base * _p2);
    void Print(void);
    ~FightManager();
public slots:
    void Fight(void);
    void Fight_Out1(AT_DETAIL atd);
    void Fight_Out2(GET_DAM dam, int k);
    void Fight_Result(void);
    void ShackWindow(QLabel* lb);
private slots:
    void on_repeat_fight_clicked();

    void on_back_clicked();


signals:
    void fight_end_sig(int flag);
    void back_clicked(void);

private:
    QTimer updataTimer,resultTimer;
    Ui::FightManager *ui;
    Pokemon_Base* atker,*defer,*p1,*p2;
    QPixmap pix,pix2;
    int interval1,interval2;
};

#endif // FIGHTMANAGER_H
