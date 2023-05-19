#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "Drawing_sword_main.h"

// #define DEBUG

enum ItemType {ANTIDOTE = 0,PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII,PHOENIXDOWNIV};

class BaseItem;
class BaseKnight;
class BaseBag {
protected:
        BaseKnight *knight;
        BaseItem *head;
        int maxcarryItem;
        int numberofItem = 0;
public:
    BaseBag(BaseKnight *knight);
    BaseBag();
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    BaseBag *getBag();
    void swap(int pos);
    void remove(int pos);
    void insert(ItemType itemtype);
    int getFirstPos(ItemType itemtype);
    int getmaxcarryItem();
    void setmaxcarryItem(int maxcarryitem);
    int getnumberofItem();
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int hp = 0, id = 0, maxhp = 0, level = 0, gil, Antidote = 0, PhoenixDownI = 0, PhoenixDownII = 0, PhoenixDownIII = 0, PhoenixDownIV = 0;
    bool intoxication = false;
    BaseBag * bag;
    KnightType knightType;
public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~BaseKnight();
    void setknightType();
    BaseBag *getBag();
    void setAntidote(int Antidote);
    int getAntidote();
    void setBag(BaseKnight *knight, int PhoenixDownI, int Antidote);
    void setPhoenixDownI(int PhoenixDownI);
    int getPhoenixDownI();
    void setPhoenixDownII(int PhoenixDownII);
    int getPhoenixDownII();
    void setPhoenixDownIII(int PhoenixDownIII);
    int getPhoenixDownIII();
    void setPhoenixDownIV(int PhoenixDownIV);
    int getPhoenixDownIV();
    string toString() const;
    int getKnightType();
    int getHp();
    void setHp(int hp);
    int getId();
    void setId(int id);
    void setmaxHp(int maxhp);
    int getmaxHp();
    int getLevel();
    void setLevel(int level);
    bool getIntoxication();
    void setIntoxication(bool status);
    void setGil(int gil);
    int getGil();
};
class Events;
class BaseItem{
        public:
        ItemType Item;
        BaseItem *next;
        virtual bool canUse ( BaseKnight *knight ) = 0;
        virtual void use ( BaseKnight * knight ) = 0;
};
class Antidote: public BaseItem{
    public:
    Antidote(){
        Item = ANTIDOTE;
    };
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownI: public BaseItem{
    public:
    PhoenixDownI(){
        Item = PHOENIXDOWNI;
    };
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownII: public BaseItem{
    public:
    PhoenixDownII(){
        Item = PHOENIXDOWNII;
    };
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIII: public BaseItem{
    public:
    PhoenixDownIII(){
        Item = PHOENIXDOWNIII;
    };
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIV: public BaseItem{
    public:
    PhoenixDownIV(){
        Item = PHOENIXDOWNIV;
    };
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PaladinBag: public BaseBag{
    public:
    PaladinBag(BaseKnight *knight, int PhoenixDownI, int Antidote);
    virtual string toString()const;
};
class DragonBag: public BaseBag{
    public:
    DragonBag(BaseKnight *knight, int PhoenixDownI);
    virtual string toString()const;
};
class LancelotBag: public BaseBag{
    public:
    LancelotBag(BaseKnight *knight, int PhoenixDownI, int Antidote);
    virtual string toString()const;
};
class NormalBag: public BaseBag{
    public:
    NormalBag(BaseKnight *knight, int PhoenixDownI, int Antidote);
    virtual string toString()const;
};
enum opponent_type {normal = 0, tornbery, queenofcards, ninadering, duriangarden, omegaweapon, hades, phoenixdownI ,phoenixdownII, phoenixdownIII, phoenixdownIV, paladin, lancelot, guinevere, excalibur, ultimecia};
class BaseOpponent{
    protected:
    BaseKnight *knight;
    int levelO, baseDamage, gil, hpUltimecia = 5000;
    opponent_type type;
    public:
    BaseOpponent(BaseKnight *knight);
    int getLevelO();
    int getGil();
    int getBaseDamage();
    int getOpponentType();
    void fightingUltimecia(int damage){
        hpUltimecia -= damage;
    }
    int getHpultimecia(){
        return hpUltimecia;
    }
};
class MadBear: public BaseOpponent{
    public:
        MadBear(int eventnum):BaseOpponent(knight){
            baseDamage = 10;
            levelO = (eventnum + 1)%10 + 1;
            gil = 100;
            type = normal;
        };
};
class Bandit: public BaseOpponent{
    public:
        Bandit(int eventnum):BaseOpponent(knight){
            baseDamage = 15;
            levelO = (eventnum + 2)%10 + 1;
            gil = 150;
            type = normal;
        };
};
class LordLupin: public BaseOpponent{
    public:
        LordLupin(int eventnum):BaseOpponent(knight){
            baseDamage = 45;
            levelO = (eventnum + 3)%10 + 1;
            gil = 450;
            type = normal;
        };
};
class Elf: public BaseOpponent{
    public:
        Elf(int eventnum):BaseOpponent(knight){
            baseDamage = 75;
            levelO = (eventnum + 4)%10 + 1;
            gil = 750;
            type = normal;
        };
};
class Troll: public BaseOpponent{
    public:
        Troll(int eventnum):BaseOpponent(knight){
            baseDamage = 95;
            levelO = (eventnum + 5)%10 + 1;
            gil = 800;
            type = normal;
        };
};
class Tornbery: public BaseOpponent{
    public:
        Tornbery(int eventnum):BaseOpponent(knight){
            levelO = (eventnum + 6)%10 + 1;
            type = tornbery;
        }
};
class QueenOfCards: public BaseOpponent{
    public:
    QueenOfCards(int eventnum):BaseOpponent(knight){
        levelO = (eventnum + 7)%10 + 1;
        type = queenofcards;
    }
};
class NinaDeRings: public BaseOpponent{
    public:
        NinaDeRings():BaseOpponent(knight){
            type = ninadering;
        }
};
class DurianGarden: public BaseOpponent{
    public:
        DurianGarden():BaseOpponent(knight){
            type = duriangarden;
        }
};
class Omega_Weapon: public BaseOpponent{
    public:
        Omega_Weapon():BaseOpponent(knight){
            type = omegaweapon;
        }
};
class HaDes: public BaseOpponent{
    public:
        HaDes():BaseOpponent(knight){
        type = hades;
    }
};
class Ultimecia: public BaseOpponent{
    public:
        Ultimecia():BaseOpponent(knight){
            type = ultimecia;
        }
};
class PhoenixdownII: public BaseOpponent{
    public:
        PhoenixdownII():BaseOpponent(knight){
            type = phoenixdownII;
        }
};
class PhoenixdownIII: public BaseOpponent{
    public:
        PhoenixdownIII():BaseOpponent(knight){
            type = phoenixdownIII;
        }
};
class PhoenixdownIV: public BaseOpponent{
    public:
        PhoenixdownIV():BaseOpponent(knight){
            type = phoenixdownIV;
        }
};
class Lancelotspear: public BaseOpponent{
    public:
        Lancelotspear():BaseOpponent(knight){
            type = lancelot;
        }
};
class Paladinshield: public BaseOpponent{
    public:
        Paladinshield():BaseOpponent(knight){
            type = paladin;
        }
};
class Guineverehair: public BaseOpponent{
    public:
        Guineverehair():BaseOpponent(knight){
            type = guinevere;
        }
};
class Excalibursword: public BaseOpponent{
    public:
        Excalibursword():BaseOpponent(knight){
            type = excalibur;
        }
};
class NormalKnight: public BaseKnight{};
class DragonKnight: public BaseKnight{};
class LancelotKnight: public BaseKnight{};
class PaladinKnight: public BaseKnight{};
class ArmyKnights{
private:
    BaseKnight **knightlist;
    int numberofKnights = 0, isFighting;
    bool ExcaliburSword = false, LancelotSpear = false, PaladinShield = false, GuinevereHair = false, OmegaWeapon = false, Hades = false;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    bool getOmegaWeapon() const;
    void setPaladinShield();
    void setOmegaWeapon();
    void printInfo() const;
    void printResult(bool win) const;
};


class Events{//Định nghĩa class Events
    private:
        int Count = 5;
        int *eventarr;
    public:
        Events(const string &file_events);
        int count() const;
        int get(int i) const;
        ~ Events();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); 

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__