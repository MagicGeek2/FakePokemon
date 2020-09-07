#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <QDebug>
using namespace std;

extern QStringList type_property ;

const int GAIN=30;
const int NUM=5;
const int c_state=0;         //是否处于控制状态
const int is_gain_c=1;      //是否处于暴击增益状态
const int is_gain_d=2;      //是否处于躲避增益状态
const int is_gain_df=3;     //是否处于防御增益状态

enum PokemonType        // 四种精灵类型
{
    T_Attack, //high attack
    T_Hp,	//high HP
    T_Defence, //high defence
    T_Speed	//high speed
};

enum ATK_KIND       // 每次攻击可能带有的属性
{
    normalAttack,       //普通攻击
    Hit_Fly,         //击飞技能（控制）
    Ex_Arm,          //破甲
    Gain_D,           //闪避率增益技能
    Gain_C,            //暴击率增益技能
    Gain_DF             //防御增益技能

};

enum PO_PROPERTY
{
    Water,
    Fire,
    Grass,
    Saint

    /*
     * 属性克制
     水->火
     火->草
     草->圣灵
     圣灵->冰
     */
};
struct AT_DETAIL     // 攻击操作的详细信息
{
    int hurt;
    ATK_KIND kind;
    QString sk_name;
    QString is_crit;
    PO_PROPERTY property;

};

struct GET_DAM       // 受到攻击操作的详细信息
{
    QString sk_name;
    int get_exp;
    QString att_ret;       //是否属性克制
    QString is_doge;       //是否躲避
    int get_hurt;       //伤害值
    bool is_dead;       //是否死亡

};


class Pokemon_Base
{
protected:
    QString p_name;
    PokemonType p_type;
    int type_num;           //宠物类型编号  1-8；
    float Atk;              //攻击力
    int Hp;                 //血量
    int Def;                //防御力
    int Spe;                //敏捷度（敏捷度越高，攻击间隔越小）
    int grade;              //等级
    int crit_rate;          //暴击率      0-100
    int dodge_rate;         //闪避率      0-100
    int exp;                //经验值
    int exp_thrd;           //下一级升级阈值
    int skill_rate[3];      //技能释放概率（包含normalAttack在内一共3个技能）

    //浮动属性
    float Atk_max;
    int Hp_max;                 //最大生命值
    int Def_max;
    int Spe_max;
    int crit_rate_max;
    int dodge_rate_max;

    const static int Gr_max;    //最大等级
    PO_PROPERTY p_property;     //属性
    bool state[NUM];         //状态数组

public:

    Pokemon_Base ();
    QString get_name()const;
    int get_typenum()const;
    int get_Hp()const;
    int get_Hp_max()const;
    int get_Spe()const;
    int get_Def()const;
    int get_grade()const;
    int get_exp()const;
    int get_crit_rate()const;
    int get_crit_rate_max()const;
    int get_dodge_rate()const;
    int get_dodge_rate_max() const;
    bool get_state(int k)const;
    void set_exp(int k);
    void set_state(int k,bool s);
    void set_Def(int);
    void set_Hp(int);
    void set_dodge_rate(int);
    void set_crit_rate(int);
    void set_crit_rate_max(int);
    void set_dodge_rate_max(int);
    void set_name(QString);
    void refresh();     // 精灵回复满状态
    GET_DAM GET_HURT (AT_DETAIL atd);     //受到伤害，处理
    int UP_GRADE (int t_exp);        //升级函数   判断是否升级  若可升级，修改grade以及exp_thrd   返回值为提升的等级数
    void SET_GRADE (int grade);       //设置初始等级
    void OUT_PUT(void);


    virtual void ATB_CH ()=0;       //属性改变（升级后）
    virtual AT_DETAIL ATTACK (int sk=-1)=0;       //攻击函数
    virtual QStringList data()=0;


};

//---------------四种精灵类别----------------------

// 同种类的精灵属性提升相同
class Pokemon_ATT:public Pokemon_Base
{

public:
    Pokemon_ATT ();
    virtual void ATB_CH ();

};

class Pokemon_HP:public Pokemon_Base
{
public:
    Pokemon_HP ();
    virtual void ATB_CH ();

};
class Pokemon_DEF:public Pokemon_Base
{
public:
    Pokemon_DEF();
    virtual void ATB_CH ();
};
class Pokemon_SP:public Pokemon_Base
{
public:
    Pokemon_SP();
    virtual void ATB_CH ();
};

//--------------具体精灵---------------------

// 每只精灵的攻击和具体数据都是不同的

class Pokemon_T_MGG:public Pokemon_ATT
{
private:
    vector<QString> skill;
public:
    Pokemon_T_MGG();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();

};

class Pokemon_T_BLS:public Pokemon_ATT
{
private:
    vector<QString> skill;

public:
    Pokemon_T_BLS();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_LYXX:public Pokemon_SP
{
private:
    vector<QString> skill;
public:
    Pokemon_T_LYXX();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_BBH:public Pokemon_DEF
{
private:
    vector<QString> skill;
public:
    Pokemon_T_BBH();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_PN:public Pokemon_HP
{
private:
    vector<QString> skill;
public:
    Pokemon_T_PN();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_BLG:public Pokemon_ATT
{
private:
    vector<QString> skill;
public:
    Pokemon_T_BLG();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_SGZZ:public Pokemon_ATT
{
private:
    vector<QString> skill;
public:
    Pokemon_T_SGZZ();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_LAS:public Pokemon_SP
{
private:
    vector<QString> skill;
public:
    Pokemon_T_LAS();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};
#endif // POKEMON_H
