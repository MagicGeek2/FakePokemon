#include "fightmanager.h"
#include "ui_fightmanager.h"

int timer=0;

FightManager::FightManager(Pokemon_Base* _p1,Pokemon_Base * _p2) :
    ui(new Ui::FightManager),p1(_p1),p2(_p2)
{
     ui->setupUi(this);
     srand((unsigned)time(NULL));
     updataTimer.start(800);
     connect(&updataTimer,SIGNAL(timeout()),this,SLOT(Fight()));
     connect(&resultTimer,SIGNAL(timeout()),this,SLOT(Fight_Result()));
     resultTimer.setSingleShot(true);
}
void FightManager::ShackWindow(QLabel *lb)      // 实现窗口抖动效果
{
     QPropertyAnimation *pAnimation = new QPropertyAnimation(lb, "pos");

     pAnimation->setDuration(500);
//     pAnimation->setLoopCount(2);
     pAnimation->setKeyValueAt(0, QPoint( lb->pos().x() - 3,  lb->pos().y() - 3));
     pAnimation->setKeyValueAt(0.1, QPoint( lb->pos().x() + 3, lb->pos().y() + 3));
     pAnimation->setKeyValueAt(0.2, QPoint( lb->pos().x() - 3, lb->pos().y() + 3));
     pAnimation->setKeyValueAt(0.3, QPoint( lb->pos().x() + 3, lb->pos().y() - 3));
     pAnimation->setKeyValueAt(0.4, QPoint( lb->pos().x() - 3, lb->pos().y() - 3));
     pAnimation->setKeyValueAt(0.5, QPoint( lb->pos().x() + 3, lb->pos().y() + 3));
     pAnimation->setKeyValueAt(0.6, QPoint( lb->pos().x() - 3, lb->pos().y() + 3));
     pAnimation->setKeyValueAt(0.7, QPoint( lb->pos().x() + 3, lb->pos().y() - 3));
     pAnimation->setKeyValueAt(0.8, QPoint( lb->pos().x() - 3, lb->pos().y() - 3));
     pAnimation->setKeyValueAt(0.9, QPoint( lb->pos().x() + 3, lb->pos().y() + 3));
     pAnimation->setKeyValueAt(1, QPoint( lb->pos().x(), lb->pos().y()));
     pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}
FightManager::~FightManager()
{
    delete ui;
}
void FightManager::Print(void)          // 显示精灵的图片和血条. 只在战斗开始的时候使用
{
    int typenum1,typenum2;
    typenum1=p1->get_typenum();
    typenum2=p2->get_typenum();

    int w1 = ui->AT_pic->width();
    int h1 = ui->AT_pic->height();
    int w2 = ui->DE_pic->width();
    int h2 = ui->DE_pic->height();

    switch(typenum1)     // 选定对应的类，加载图片
    {
    case 1:
        pix.load(":/pictures/img/BLG.jpg");
        break;
    case 2:
        pix.load(":/pictures/img/BLS.jpg");
        break;
    case 3:
        pix.load(":/pictures/img/MGG.jpg");
        break;
    case 4:
        pix.load(":/pictures/img/SGZZ.jpg");
        break;
    case 5:
        pix.load(":/pictures/img/PN.jpg");
        break;
    case 6:
        pix.load(":/pictures/img/BBH.jpg");
        break;
    case 7:
        pix.load(":/pictures/img/LYXX.jpg");
        break;
    case 8:
        pix.load(":/pictures/img/LAS.jpg");
        break;
    default:
        break;

    }
    switch(typenum2)     // 选定对应的类，加载图片
    {
    case 1:
        pix2.load(":/pictures/img/BLG.jpg");
        break;
    case 2:
        pix2.load(":/pictures/img/BLS.jpg");
        break;
    case 3:
        pix2.load(":/pictures/img/MGG.jpg");
        break;
    case 4:
        pix2.load(":/pictures/img/SGZZ.jpg");
        break;
    case 5:
        pix2.load(":/pictures/img/PN.jpg");
        break;
    case 6:
        pix2.load(":/pictures/img/BBH.jpg");
        break;
    case 7:
        pix2.load(":/pictures/img/LYXX.jpg");
        break;
    case 8:
        pix2.load(":/pictures/img/LAS.jpg");
        break;
    default:
        break;

    }

    //  在progress bar 的 styleSheet中修改progress bar 的颜色，字体等等
    ui->AT_pic->setPixmap(pix.scaled(w1,h1,Qt::KeepAspectRatio));
    ui->DE_pic->setPixmap(pix2.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->hp1->setMaximum(p1->get_Hp_max());
    ui->hp2->setMaximum(p2->get_Hp_max());
    ui->hp1->setValue(p1->get_Hp());
    ui->hp2->setValue(p2->get_Hp());
}
void FightManager::Fight(void)
{
    int up_grade_num=0;
    int k;                  //判定谁是被攻击者
    AT_DETAIL atd;  // 攻击的详细信息
    GET_DAM get,get2;   // 攻击的详细信息
    bool fight_flag=true;

    // 攻击间隔     12 - 1/5*speed
    interval1 = p1->get_Spe()*(-1)/5+12;
    interval2 = p2->get_Spe()*(-1)/5+12;

    for(;p1->get_Hp()>0&&p2->get_Hp()>0&&fight_flag;timer=timer+1)
    {

        if(timer%interval1==0&&timer%interval2!=0)      // 只有p1攻击
        {

            fight_flag=false;
            if(p1->get_state(c_state)==false)      //p1处于非控制状态
            {
                this->atker=p1;
                this->defer=p2;
                k=2;
                atd = this->atker->ATTACK();
                get = this->defer->GET_HURT(atd);

                Fight_Out1(atd);
                Fight_Out2(get,k);
                if(atd.kind == Hit_Fly)         //控制处理
                    this->defer->set_state(c_state,true);


                if(defer->get_state(is_gain_d))  //躲避增益处理
                {
                    defer->set_state(is_gain_d,false);
                    defer->set_dodge_rate(defer->get_dodge_rate()-GAIN);
                }

                if(defer->get_state(is_gain_df)) //物防增益处理
                {
                    defer->set_state(is_gain_df,false);
                    defer->set_Def(defer->get_Def()*2/3);

                }
                if(atker->get_state(is_gain_c))  //暴击增益处理
                {
                    atker->set_state(is_gain_c,false);
                    atker->set_crit_rate(atker->get_crit_rate()-GAIN);
                }

                if(get.get_exp)     // 本次击败了敌方精灵，获得经验
                {
                    up_grade_num=this->atker->UP_GRADE(get.get_exp);
                    if(up_grade_num)        // 本次获得经验，升级
                       {
                        qDebug()<<this->atker->get_name()<<" 等级提升 "<<up_grade_num;
                        ui->text_fight->append(atker->get_name()+"等级提升: "+QString::number(up_grade_num));
                       }
                }
            }
            else if(p1->get_state(c_state))
            {
                p1->set_state(c_state,false);         //解除控制状态， 无法进行攻击
            }
        }
        else if(timer%interval2==0&&timer%interval1!=0) // 只有p2攻击
        {
            fight_flag=false;

            if(p2->get_state(c_state)==false)
            {
                this->atker=p2;
                this->defer=p1;
                k=1;
                atd = this->atker->ATTACK();
                get = this->defer->GET_HURT(atd);

                Fight_Out1(atd);
                Fight_Out2(get,k);

                if(atd.kind == Hit_Fly)         //控制处理
                    this->defer->set_state(c_state,true);


                if(defer->get_state(is_gain_d))  //躲避增益处理
                {
                    defer->set_state(is_gain_d,false);
                    defer->set_dodge_rate(defer->get_dodge_rate()-GAIN);
                }

                if(defer->get_state(is_gain_df)) //物防增益处理
                {
                    defer->set_state(is_gain_df,false);
                    defer->set_Def(defer->get_Def()*2/3);


                }
                if(atker->get_state(is_gain_c))  //暴击增益处理
                {
                    atker->set_state(is_gain_c,false);
                    atker->set_crit_rate(atker->get_crit_rate()-GAIN);
                }
            }
            else if(p2->get_state(c_state))
            {
                p2->set_state(c_state,false);         //屏蔽一次攻击，解除控制状态
            }
        }
        else if(timer%interval2==0&&timer%interval1==0)  //有机会同时攻击
        {

            fight_flag=false;

            ui->text_fight->append("同时发动攻击，互相伤害啊！");

            qDebug()<<"同时攻击";
            int flag=0;         //flag=1 两者状态相同(同时被控制或者同时行动)
            if(p1->get_state(c_state)==false&&p2->get_state(c_state)==false)
            {
                flag=1;         //特殊处理 两精灵互殴。同时攻击同时受到伤害
                atker=p1;
                defer=p2;
                k=2;
                atd = atker->ATTACK();
                get = defer->GET_HURT(atd);

                Fight_Out1(atd);

                if(atd.kind == Hit_Fly)         //控制处理
                    this->defer->set_state(c_state,true);


                if(defer->get_state(is_gain_d))  //躲避增益处理
                {
                    defer->set_state(is_gain_d,false);
                    defer->set_dodge_rate(defer->get_dodge_rate()-GAIN);
                }

                if(defer->get_state(is_gain_df)) //物防增益处理
                {
                    defer->set_state(is_gain_df,false);
                    defer->set_Def(defer->get_Def()*2/3);


                }
                if(atker->get_state(is_gain_c))  //暴击增益处理
                {
                    atker->set_state(is_gain_c,false);
                    atker->set_crit_rate(atker->get_crit_rate()-GAIN);
                }


                atker=p2;
                defer=p1;
                k=1;
                atd = atker->ATTACK();
                get2 = defer->GET_HURT(atd);

                Fight_Out1(atd);

                if(atd.kind == Hit_Fly)         //控制处理
                    this->defer->set_state(c_state,true);


                if(defer->get_state(is_gain_d))  //躲避增益处理
                {
                    defer->set_state(is_gain_d,false);
                    defer->set_dodge_rate(defer->get_dodge_rate()-GAIN);
                }

                if(defer->get_state(is_gain_df)) //物防增益处理
                {
                    defer->set_state(is_gain_df,false);
                    defer->set_Def(defer->get_Def()*2/3);


                }
                if(atker->get_state(is_gain_c))  //暴击增益处理
                {
                    atker->set_state(is_gain_c,false);
                    atker->set_crit_rate(atker->get_crit_rate()-GAIN);
                }

                if(get.get_exp)
                {
                    up_grade_num=p1->UP_GRADE(get.get_exp);
                    if(up_grade_num)
                    {
                        qDebug()<<p1->get_name()<<" 等级提升 "<<up_grade_num;
                        ui->text_fight->append(p1->get_name()+"等级提升: "+QString::number(up_grade_num));
                    }

                }
                if(get2.get_exp)
                {
                    up_grade_num=p2->UP_GRADE(get2.get_exp);
                    if(up_grade_num)
                    {
                        qDebug()<<p2->get_name()<<" 等级提升 "<<up_grade_num;
                        ui->text_fight->append(p2->get_name()+"等级提升: "+QString::number(up_grade_num));
                    }
                }


                Fight_Out2(get,2);
                Fight_Out2(get2,1);

            }
            else if(p1->get_state(c_state)==true&&p2->get_state(c_state)==false)
            {
                this->atker=p2;
                this->defer=p1;
                p1->set_state(c_state,false);
                k=1;
            }
            else if(p2->get_state(c_state)==true&&p1->get_state(c_state)==false)
            {
                this->atker=p1;
                this->defer=p2;
                p2->set_state(c_state,false);
                k=2;
            }
            else
            {
                flag=1;
                p1->set_state(c_state,false);
                p2->set_state(c_state,false);
            }

            if(flag==0)
            {
                atd = this->atker->ATTACK();
                get = this->defer->GET_HURT(atd);

                Fight_Out1(atd);
                Fight_Out2(get,k);

                if(atd.kind == Hit_Fly)         //控制处理
                    this->defer->set_state(c_state,true);


                if(defer->get_state(is_gain_d))  //躲避增益处理
                {
                    defer->set_state(is_gain_d,false);
                    defer->set_dodge_rate(defer->get_dodge_rate()-GAIN);
                }

                if(defer->get_state(is_gain_df)) //物防增益处理
                {
                    defer->set_state(is_gain_df,false);
                    defer->set_Def(defer->get_Def()*2/3);


                }
                if(atker->get_state(is_gain_c))  //暴击增益处理
                {
                    atker->set_state(is_gain_c,false);
                    atker->set_crit_rate(atker->get_crit_rate()-GAIN);
                }

                if(get.get_exp)
                {
                    up_grade_num=this->atker->UP_GRADE(get.get_exp);
                    if(up_grade_num)
                    {
                        qDebug()<<p1->get_name()<<" 等级提升 "<<up_grade_num;
                         ui->text_fight->append(p1->get_name()+"等级提升: "+QString::number(up_grade_num));
                    }
                }
            }
        }
    }    
}

void FightManager::Fight_Out1(AT_DETAIL atd)      // 发动攻击时处理函数。显示本次攻击的详细信息
{

    QString kind;
    switch (atd.kind) {
    case  normalAttack:
        kind="普通攻击";
        break;
    case Hit_Fly:
        kind="击飞眩晕";
        break;
    case Ex_Arm:
        kind="破甲攻击";
        break;
    case Gain_D:
        kind="闪避增益";
        break;
    case Gain_C:
        kind="暴击增益";
        break;
    case Gain_DF:
        kind="物防增益";
        break;
    default:
        break;
    }

    ui->text_fight->append(atker->get_name()+" 发动攻击 "+atd.sk_name+"\t"+kind+"\t"+"暴击:"+atd.is_crit);
}

void FightManager::Fight_Out2(GET_DAM dam, int k)       // 受到攻击时的处理函数
{

    if(k==1)
        ShackWindow(ui->AT_pic);
    else
        ShackWindow(ui->DE_pic);

    int now_hp=0;
    int next_hp=0;


    //  显示受到伤害的详细信息， 并且做结算

    // 两段代码逻辑上并无不同
    if(k==2)                        //p2被攻击
    {

        //  p2收到攻击处理

        ui->text_fight->append(p2->get_name()+" 受到攻击 "+dam.sk_name+"\t伤害:"+QString::number(dam.get_hurt)+"\t属性克制:"+dam.att_ret+"\t躲避:"+dam.is_doge);
        now_hp=ui->hp2->value();
        next_hp=now_hp-dam.get_hurt;
        if(next_hp<0)
            next_hp=0;
        while(now_hp!=next_hp)
        {
            ui->hp2->setValue(now_hp-1);
            now_hp=ui->hp2->value();
        }

        if(p2->get_Hp()==0)
        {
           ui->text_fight->append(p2->get_name()+" 死亡");
            updataTimer.stop();
            resultTimer.start(1000);
        }
    }
    else if(k==1)
    {

         //  p1收到攻击处理

        ui->text_fight->append(p1->get_name()+" 受到攻击 "+dam.sk_name+"\t伤害:"+QString::number(dam.get_hurt)+"\t属性克制:"+dam.att_ret+"\t躲避:"+dam.is_doge);
        now_hp=ui->hp1->value();
        next_hp=now_hp-dam.get_hurt;
        if(next_hp<0)
            next_hp=0;

        while(now_hp!=next_hp)
        {
            ui->hp1->setValue(now_hp-1);
            now_hp=ui->hp1->value();
        }

        if(p1->get_Hp()==0)
        {
           ui->text_fight->append(p1->get_name()+" 死亡");
            updataTimer.stop();
            resultTimer.start(1000);
        }
    }

}

void FightManager::on_repeat_fight_clicked()
{
    p1->refresh();
    p2->refresh();
    timer=0;
    this->Print();
    p1->set_Hp(p1->get_Hp_max());
    p2->set_Hp(p2->get_Hp_max());
    ui->text_fight->clear();
    updataTimer.start(800);
}

void FightManager::on_back_clicked()
{
    //关闭
    p1->refresh();
    p2->refresh();
    this->close();
}
void FightManager::Fight_Result()       // 战斗结束
{
    if(p1->get_Hp()==0&&p2->get_Hp()==0)
    {
        QMessageBox::warning(this,"信息提示","同归于尽!",QMessageBox::Ok);
        emit fight_end_sig(2);
    }
    else if(p1->get_Hp()==0&&p2->get_Hp()!=0)
    {
        QMessageBox::warning(this,"信息提示","你挂了!",QMessageBox::Ok);
        emit fight_end_sig(0);
        p1->refresh();
        p2->refresh();
        this->close();
    }
    else if(p1->get_Hp()!=0&&p2->get_Hp()==0)
    {
        QMessageBox::information(this,"信息提示","你赢了!",QMessageBox::Ok);
         emit fight_end_sig(1);
    }
}
