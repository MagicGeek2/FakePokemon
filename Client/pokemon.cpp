#include "pokemon.h"
const int Pokemon_Base::Gr_max=15;      // 因为是静态变量所以可以被外部引用
QStringList type_property = {"", "水", "水","草", "圣灵", "圣灵", "草","火", "火" } ;

Pokemon_Base::Pokemon_Base()
{
    this->p_name="";
    this->p_type=T_Attack;       //默认Attack属性
    this->type_num=0;
    this->grade=1;

    this->Hp_max=500;
    this->Atk_max=100;
    this->Def_max=50;
    this->Spe_max=10;
    this->crit_rate_max=0;
    this->dodge_rate_max=0;
    this->exp=0;
    this->exp_thrd=30;
    this->skill_rate[0]=50;
    this->skill_rate[1]=30;
    this->skill_rate[2]=20;
    for(int i=0;i<=NUM;i++)
        this->state[i]=false;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

int Pokemon_Base::UP_GRADE(int t_exp)
{
    this->exp+=t_exp;
    int key=0;
    while(exp>=exp_thrd)
    {
        if(grade<Gr_max)
        {
            key++;
            this->grade++;
            this->ATB_CH();
            exp_thrd+=(30*this->grade);
        }
    }
    return key;
}

void Pokemon_Base::SET_GRADE(int grade)
{
    if(grade>Gr_max)
        grade=Gr_max;

    for(int i=1;i<grade;i++)
    {
        this->grade++;
        this->ATB_CH();
        exp_thrd+=(30*this->grade);
    }
}

GET_DAM Pokemon_Base::GET_HURT(AT_DETAIL atd)
{
    GET_DAM getdam;
    getdam.sk_name=atd.sk_name;
    int d_random = rand()%100+1;       // 闪避机会
    int dam = 0;
    int get_exp=0;

    getdam.is_dead=false;
    getdam.att_ret="NO";
    if(d_random<=dodge_rate)        //躲避
    {
        dam = 0;
        getdam.is_doge="YES";
    }
    else
    {
        getdam.is_doge="NO";

        if(atd.kind==Ex_Arm)
            dam = atd.hurt - (this->Def)/2;
        else if(atd.kind==Gain_DF)
            dam=0;
        else
            dam = atd.hurt - this->Def;

        if((atd.property+1)%4==this->p_property)
           {
            dam*=1.3;
            getdam.att_ret="YES";
           }


        if(dam<0)                   //物防太高
            dam=0;
    }


    if(dam > Hp)
        dam = Hp ;

    qDebug()<<"damage-before hp:"<<this->Hp ;
    Hp -= dam;
    qDebug()<<"damage-after hp:"<<this->Hp ;



    if(this->Hp<=0)
    {
        get_exp = this->grade*10;
        getdam.is_dead=true;
    }

    getdam.get_exp=get_exp;
    getdam.get_hurt=dam;



    QString kind;
    switch (atd.kind) {
    case normalAttack:
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

    qDebug()<<this->p_name<<" 受到攻击 "<<atd.sk_name<<"\t"<<kind<<"\t"<<dam<<"\t血量: "<<this->get_Hp()<<"\t物防:\t"<<Def<<"\t躲避率:\t"<<this->dodge_rate;
    if(get_exp)
        qDebug()<<this->p_name<<" 死亡！";

    return getdam;
}

//void Pokemon_Base::OUT_PUT()
//{
//   qDebug()<<"Atk:\t"<<this->Atk;
//   qDebug()<<"Hp:\t"<<this->Hp;
//   qDebug()<<"Def:\t"<<this->Def;
//   qDebug()<<"Spe:\t"<<this->Spe;
//   qDebug()<<"grade:\t"<<this->grade;
//   qDebug()<<"exp:\t"<<this->exp;
//}

bool Pokemon_Base::get_state(int k)const
{
    return this->state[k];
}
int Pokemon_Base::get_Hp()const
{
    return this->Hp;
}
int Pokemon_Base::get_Spe()const
{
    return this->Spe;
}
int Pokemon_Base::get_Def()const
{
    return this->Def;
}
QString Pokemon_Base::get_name()const
{
    return this->p_name;
}
int Pokemon_Base::get_grade()const
{
    return this->grade;
}
int Pokemon_Base::get_exp()const
{
    return this->exp;
}
int Pokemon_Base::get_typenum()const
{
    return this->type_num;
}
int Pokemon_Base::get_Hp_max()const
{
    return this->Hp_max;
}
void Pokemon_Base::set_exp(int k)
{
    this->exp=k;
}
void Pokemon_Base::set_state(int k,bool s)
{
    this->state[k]=s;
}
void Pokemon_Base::set_name(QString s)
{
    this->p_name=s;
}
void Pokemon_Base::set_Def(int k)
{
    this->Def=k;
}
void Pokemon_Base::set_Hp(int k)
{
    this->Hp=k;
}
void Pokemon_Base::set_crit_rate(int c)
{
    this->crit_rate=c;
}
void Pokemon_Base::set_crit_rate_max(int c)
{
    this->crit_rate=c;
    this->crit_rate_max=c;
}
void Pokemon_Base::set_dodge_rate(int d)
{
    this->dodge_rate=d;
}
void Pokemon_Base::set_dodge_rate_max(int d)
{
    this->dodge_rate_max=d;
    this->dodge_rate=d;
}
int Pokemon_Base::get_crit_rate()const
{
    return this->crit_rate;
}
int Pokemon_Base::get_crit_rate_max()const
{
    return this->crit_rate_max;
}
int Pokemon_Base::get_dodge_rate()const
{
    return this->dodge_rate;
}
int Pokemon_Base::get_dodge_rate_max()const
{
    return this->dodge_rate_max;
}
void Pokemon_Base::refresh()
{
    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;

    for(int i=0;i<NUM;i++)
        this->state[i]=false;

}


//---------------攻击型精灵---------------------------
Pokemon_ATT::Pokemon_ATT()
{
    this->p_type=T_Attack;
    this->Atk_max+=20;
    this->Atk=Atk_max;
}

void Pokemon_ATT::ATB_CH()
{
    this->Atk_max+=20;
    this->Hp_max+=30;
    this->Def_max+=5;
    this->Spe_max+=1;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

//---------------HP精灵---------------------------
Pokemon_HP::Pokemon_HP()
{
    this->p_type=T_Hp;
    this->Hp_max+=60;
    this->Hp=Hp_max;
}
void Pokemon_HP::ATB_CH()
{
    this->Atk_max+=10;
    this->Hp_max+=60;
    this->Def_max+=5;
    this->Spe_max+=1;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;

}
//----------------防御型精灵-----------------------

Pokemon_DEF::Pokemon_DEF()
{
    this->p_type=T_Defence;
    this->Def_max+=10;
    this->Def=Def_max;
}
void Pokemon_DEF::ATB_CH()
{
    this->Atk_max+=10;
    this->Hp_max+=30;
    this->Def_max+=12;
    this->Spe_max+=1;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

//---------------速度型精灵-----------------------
Pokemon_SP::Pokemon_SP()
{
    this->p_type=T_Speed;
    this->Spe_max+=2;
    this->Spe=Spe_max;
}
void Pokemon_SP::ATB_CH()
{
    this->Atk_max+=10;
    this->Hp_max+=30;
    this->Def_max+=5;
    this->Spe_max+=2;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}



//--------------每个精灵的构造函数，攻击函数和data函数--------------------------



Pokemon_T_MGG::Pokemon_T_MGG()
{
    this->type_num=3;
    this->p_name="蘑菇怪";
    p_property=Grass;
    skill.push_back("normalAttack");
    skill.push_back("毒气冲击");
    skill.push_back("光能射线");

}


AT_DETAIL Pokemon_T_MGG::ATTACK(int sk=-1 )
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])     // 20
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])     // 30
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Hit_Fly;
       atd.hurt = (int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
    }
    else if(FS_FLAG)
    {
        atd.kind = normalAttack;
        atd.hurt = (int)(this->Atk*1.2);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;
    qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;

}
QStringList Pokemon_T_MGG::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);

    return list;
}
//-------------------------------------------------------
Pokemon_T_BLS::Pokemon_T_BLS()
{
    this->type_num=2;
    this->p_name="巴鲁斯";
    p_property=Water;
    skill.push_back("normalAttack");
    skill.push_back("泡沫光线");
    skill.push_back("高压水枪");
}
AT_DETAIL Pokemon_T_BLS::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Hit_Fly;
       atd.hurt = (int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
    }
    else if(FS_FLAG)
    {
        atd.kind = normalAttack;
        atd.hurt = (int)(this->Atk*1.2);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_BLS::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;
}

//-------------------------------------------------------
Pokemon_T_LYXX::Pokemon_T_LYXX()
{
    this->type_num=7;
    this->p_name="烈焰猩猩";
    p_property=Fire;
    skill.push_back("normalAttack");
    skill.push_back("火焰车");                //破甲效果
    skill.push_back("烈焰冲撞");                //提升躲避率（无伤害）
}

AT_DETAIL Pokemon_T_LYXX::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_D;
       atd.hurt =(int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_d,true);
       this->dodge_rate+=GAIN;
    }
    else if(FS_FLAG)
    {
        atd.kind = Ex_Arm;
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;
     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_LYXX::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);

    return list;
}
//-------------------------------------------------------
Pokemon_T_BBH::Pokemon_T_BBH()
{
    this->type_num=6;
    this->p_name="布布花";
    p_property=Grass;
    skill.push_back("normalAttack");
    skill.push_back("超级吸取");                //击飞，少量伤害。
    skill.push_back("飞叶风暴");                //物防增益

}
AT_DETAIL Pokemon_T_BBH::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_DF;
       atd.hurt = 0;
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_df,true);
       this->Def=Def*3/2;
    }
    else if(FS_FLAG)
    {
        atd.kind = Hit_Fly;
        atd.hurt = (int)(this->Atk*0.6);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;

      qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}

QStringList Pokemon_T_BBH::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;

}
//-------------------------------------------------------
Pokemon_T_PN::Pokemon_T_PN()
{
    this->type_num=5;
    this->p_name="谱尼";
    p_property=Saint;
    skill.push_back("normalAttack");
    skill.push_back("璨灵圣光");                //吸血技能
    skill.push_back("落芳天华");                //闪避
}
AT_DETAIL Pokemon_T_PN::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_D;
       atd.hurt = (int)(this->Atk*0.6);
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_d,true);
       this->dodge_rate+=GAIN;
    }
    else if(FS_FLAG)
    {
        atd.kind = normalAttack;
        atd.hurt = (int)(this->Atk*0.6);
        atd.sk_name=this->skill[1];
        this->set_Hp(this->get_Hp()*11/10);

    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_PN::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;
}

//-------------------------------------------------------
Pokemon_T_BLG::Pokemon_T_BLG()
{
    this->type_num=1;
    this->p_name="巴拉龟";
    this->set_dodge_rate_max(this->get_dodge_rate_max()+20);//李白自带20%闪避率
    p_property=Water;
    skill.push_back("normalAttack");
    skill.push_back("火箭头槌	");                //提升躲避率
    skill.push_back("光栅炮");                //躲避率加伤害
}

AT_DETAIL Pokemon_T_BLG::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_D;
       atd.hurt = (int)(this->Atk*1.0);
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_d,true);
       this->dodge_rate+=GAIN;
    }
    else if(FS_FLAG)
    {
        atd.kind = Gain_D;
        atd.hurt = (int)(this->Atk*0.8);
        atd.sk_name=this->skill[1];
        this->set_state(is_gain_d,true);
        this->dodge_rate +=GAIN;

    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}

QStringList Pokemon_T_BLG::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);

    return list;
}
//-------------------------------------------------------
Pokemon_T_SGZZ::Pokemon_T_SGZZ()
{
    this->type_num=4;
    this->p_name="圣光之子";
    p_property=Saint;
    skill.push_back("normalAttack");
    skill.push_back("宇宙微茫	");
    skill.push_back("光扬宇宙");
}

AT_DETAIL Pokemon_T_SGZZ::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= normalAttack;
       atd.hurt = (int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
       this->set_Hp(this->get_Hp()+(this->Atk)*0.2);


    }
    else if(FS_FLAG)
    {
        atd.kind = Hit_Fly;
        atd.hurt = (int)(this->Atk*0.8);
        atd.sk_name=this->skill[1];

    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}

QStringList Pokemon_T_SGZZ::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;

}
//-------------------------------------------------------
Pokemon_T_LAS::Pokemon_T_LAS()
{
    this->type_num=8;
    this->p_property=Fire;
    this->p_name="里奥斯";
    skill.push_back("normalAttack");
    skill.push_back("密集火网");
    skill.push_back("烈火燎原");

}
AT_DETAIL Pokemon_T_LAS::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=normalAttack;
    atd.sk_name="";
    atd.is_crit="NO";
    atd.property=p_property;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
        atd.kind = Hit_Fly;
        atd.hurt = (int)(this->Atk*0.6);
        atd.sk_name=this->skill[2];
    }
    else if(FS_FLAG)
    {
        atd.kind= normalAttack;
        atd.hurt = (int)(this->Atk*1.2);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
    }
    atd.is_crit=is_crit ;

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_LAS::data()
{
    QStringList list;
    QString property = type_property[type_num];

    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(property);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;

}
