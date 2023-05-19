#include "Drawing_sword.h"
/*
Các biến khai báo thêm cần nhớ: eventarr: Con trỏ lưu các sự kiện.
*/
//BEGIN implementation of addition function
int Stoi(string s){
    int i = 0;
    while (true){
        if (s[i] == '\n' || s[i] == '\r')
            break;
        i++;
    }
    int num = 0, pos = 0;
    for (int j = i - 1; j > -1; j--){
        num += (s[pos]-'0')*pow(10,j);
        pos++;
    }
    return num;
}
bool checkPrime(int HP){
    if (HP == 0 || HP == 1)
    return false;
    for (int i = 2; i < HP; i++)
        if (HP%i == 0)
            return false;
    return true;
}    

//END implementation of addition function
/* * * BEGIN implementation of class BaseBag * * */
bool Antidote:: canUse (BaseKnight *knight){
    if (knight->getIntoxication() == 1){
        if (knight->getBag()->getFirstPos(ANTIDOTE)!=-1)
            return true;
    }
    return false;  
}
void Antidote:: use (BaseKnight *knight){
    if (knight->getKnightType() == DRAGON)
        return;
    else{
        knight->setIntoxication(false);
        knight->setAntidote(-1);
        int pos = knight->getBag()->getFirstPos(ANTIDOTE);
        knight->getBag()->remove(pos);
    }
}
bool PhoenixDownI:: canUse(BaseKnight *knight){
    if (knight->getHp() < 0 && knight->getPhoenixDownI() > 0){
        return true;
    }
    return false;
}
void PhoenixDownI:: use(BaseKnight * knight){
    knight->setHp(knight->getmaxHp());
    knight->setPhoenixDownI(-1);
    int pos = knight->getBag()->getFirstPos(PHOENIXDOWNI);
    knight->getBag()->remove(pos);
}
bool PhoenixDownII:: canUse(BaseKnight *knight){
    if (knight->getHp() < (int)(knight->getmaxHp()/4) && knight->getPhoenixDownII() > 0){
        return true;
    }
    return false;
}
void PhoenixDownII:: use(BaseKnight * knight){
    knight->setHp(knight->getmaxHp());
    knight->setPhoenixDownI(-1);
    int pos = knight->getBag()->getFirstPos(PHOENIXDOWNII);
    knight->getBag()->remove(pos);
}       
bool PhoenixDownIII:: canUse(BaseKnight *knight){
    if (knight->getHp() < (int)(knight->getmaxHp()/3) && knight->getPhoenixDownIII() > 0){
        return true;
    }
    return false;
}
void PhoenixDownIII:: use(BaseKnight * knight){
    if (knight->getHp() <= 0)
        knight->setHp((int)(knight->getmaxHp()/3));
    else
        knight->setHp(knight->getHp() + (int)(knight->getmaxHp()/4));
    knight->setPhoenixDownIII(-1);
    int pos = knight->getBag()->getFirstPos(PHOENIXDOWNIII);
    knight->getBag()->remove(pos);
}
bool PhoenixDownIV:: canUse(BaseKnight *knight){
    if (knight->getHp() < (int)(knight->getmaxHp()/2) && knight->getPhoenixDownIV() > 0){
        return true;
    }
    return false;
}
void PhoenixDownIV:: use(BaseKnight * knight){
    if (knight->getHp() <= 0)
        knight->setHp((int)(knight->getmaxHp()/2));
    else
        knight->setHp((knight->getHp() + (int)knight->getmaxHp()/5));
    knight->setPhoenixDownIV(-1);
    int pos = knight->getBag()->getFirstPos(PHOENIXDOWNIV);
    knight->getBag()->remove(pos);
}        
BaseBag::BaseBag(BaseKnight *knight){
    head = nullptr;
    this->knight = knight;
}
BaseBag::BaseBag(){
    head = nullptr;
}
bool BaseBag::insertFirst(BaseItem *item){
    if (knight->getBag()->getnumberofItem() < knight->getBag()->maxcarryItem){
        insert(item->Item);
        return true;
    }
    else return false;
}
int BaseBag::getmaxcarryItem(){
    return maxcarryItem;
}
void BaseBag:: remove(int pos){
    BaseItem *DelBag;
    DelBag = head;
    numberofItem--;
    if (pos == 0){
        head = DelBag->next;
        DelBag->next = nullptr;
        delete DelBag->next;
        return;
    }
    for (int i = 0 ; i < pos - 1; i++)
        DelBag = DelBag->next;
    if (DelBag->next->next == nullptr)//Nếu xóa ở vị trí cuối
        {
            DelBag->next = nullptr;
            return;
        }
    BaseItem *temp;
    temp = DelBag->next;
    DelBag->next = temp->next;
    temp->next = nullptr;
    delete temp->next;
    return;
}
void BaseBag:: setmaxcarryItem(int max){
    maxcarryItem = max;
}
void BaseBag:: insert(ItemType itemtype){
    if (numberofItem == maxcarryItem)
        return;//Nếu túi đã đầy không nhận thêm
    BaseItem *newBag;
        switch (itemtype){
            case 0:{
                newBag = new Antidote;
                knight->setAntidote(1);
                newBag->next = nullptr;
                break;
            }
            case 1:{
                newBag = new PhoenixDownI;
                knight->setPhoenixDownI(1);
                newBag->next = nullptr;
                break;
            }
            case 2:{
                newBag = new PhoenixDownII;
                knight->setPhoenixDownII(1);
                newBag->next = nullptr;
                break;
            }
            case 3:{
                newBag = new PhoenixDownIII;
                knight->setPhoenixDownIII(1);
                newBag->next = nullptr;
                break;
            }
            case 4:{
                newBag = new PhoenixDownIV;
                knight->setPhoenixDownIV(1);
                newBag->next = nullptr;
                break;
            }
        }
    if (numberofItem == 0)
        head = newBag;
    else{
            newBag->next = head;
            head = newBag;
        }
    numberofItem++;
}
int BaseBag:: getnumberofItem(){
            return numberofItem;
        }
BaseItem *BaseBag:: get(ItemType itemType){
            BaseItem *temp;
            temp = knight->getBag()->head;
            while (temp->next != nullptr){
                if (temp->Item == itemType)
                    break;
                else
                    temp = temp->next;
            }
            if (temp->Item == itemType)
                return temp;
            return NULL;
        }
int BaseBag::getFirstPos(ItemType itemtype){
    if (head == nullptr)
        return -1;
    BaseItem *temp;
    int pos = 0;
    temp = head;
    while (temp->next != nullptr){
        if (temp->Item == itemtype)
            break;
        temp = temp->next;
        pos++;
    }
    if (temp->Item == itemtype)
        return pos;
    else
        return -1;
}
void BaseBag:: swap(int pos){
    BaseItem *SwapBag = head, *FirstBag = head;
    for (int i = 0; i < pos; i++)
        SwapBag = SwapBag->next;
    ItemType temp;
    temp = FirstBag->Item;
    FirstBag->Item = SwapBag->Item;
    SwapBag->Item = temp;
}
string BaseBag:: toString() const{
    if (head == nullptr)
        return "";
    BaseItem *temp = head;
    string s = "";
    s = s + "Bag[count=" + to_string(numberofItem) + ";";
    for (int i = 1; i <= numberofItem; i++){
        switch (temp->Item){
            case 0:
                s += "Antidote";
                break;
            case 1:
                s += "PhoenixI";
                break;
            case 2:
                s += "PhoenixII";
                break;
            case 3:
                s += "PhoenixIII";
                break;
            case 4:
                s += "PhoenixIV";
                break;
            }
        if (i == numberofItem)
            s += "]";
        else
            s += ",";
        temp = temp->next;
        }
        if (numberofItem==0)
            s+="]";
    return s;
}

PaladinBag::PaladinBag(BaseKnight *knight, int PhoenixDownI, int Antidote):BaseBag(knight){
    this->maxcarryItem = -1;
    if (PhoenixDownI > 0){
        for (int i = 0; i < PhoenixDownI; i++){
            ItemType type = PHOENIXDOWNI;
            insert(type);
        }
    }
    if (Antidote > 0){
        for (int i = 0; i < Antidote; i++){
            ItemType type = ANTIDOTE;
            insert(type);
        }
    }
}
string PaladinBag::toString()const{
    BaseItem *temp = head;
    string s = "";
    s = s + "Bag[count=" + to_string(this->numberofItem) + ";";
    for (int i = 1; i <= this->numberofItem; i++){
        switch (temp->Item){
            case 0:
                s += "Antidote";
                break;
            case 1:
                s += "PhoenixI";
                break;
            case 2:
                s += "PhoenixII";
                break;
            case 3:
                s += "PhoenixIII";
                break;
            case 4:
                s += "PhoenixIV";
                break;
            }
        if (i == this->numberofItem)
            s += "]";
        else
            s += ",";
        temp = temp->next;
        }
        if (this->numberofItem==0)
            s+="]";
    return s;
}
LancelotBag::LancelotBag(BaseKnight *knight, int PhoenixDownI, int Antidote):BaseBag(knight){
    this->maxcarryItem = 16;
    if (PhoenixDownI > 0 && this->numberofItem < this->maxcarryItem){
        for (int i = 0; i < PhoenixDownI; i++){
            if (this->numberofItem == this->maxcarryItem)
                break;
            ItemType type = PHOENIXDOWNI;
            insert(type);
        }
    }
    if (Antidote > 0 && this->numberofItem < maxcarryItem){
        for (int i = 0; i < Antidote; i++){
            if( this->numberofItem == this->maxcarryItem)
                break;
            ItemType type = ANTIDOTE;
            insert(type);
        }
    }
}
string LancelotBag::toString()const{
    BaseItem *temp = head;
    string s = "";
    s = s + "Bag[count=" + to_string(this->numberofItem) + ";";
    for (int i = 1; i <= this->numberofItem; i++){
        switch (temp->Item){
            case 0:
                s += "Antidote";
                break;
            case 1:
                s += "PhoenixI";
                break;
            case 2:
                s += "PhoenixII";
                break;
            case 3:
                s += "PhoenixIII";
                break;
            case 4:
                s += "PhoenixIV";
                break;
            }
        if (i == this->numberofItem)
            s += "]";
        else
            s += ",";
        temp = temp->next;
        }
        if (this->numberofItem==0)
            s+="]";
    return s;
}
DragonBag::DragonBag(BaseKnight *knight, int PhoenixDownI):BaseBag(knight){
    this->maxcarryItem = 14;
    if (PhoenixDownI > 0 && this->numberofItem < this->maxcarryItem)
    for (int i = 0; i <PhoenixDownI; i++){
        ItemType type = PHOENIXDOWNI;
        insert(type);
        if( this->numberofItem == this->maxcarryItem)
            break;
    }
}
string DragonBag::toString()const{
    BaseItem *temp = head;
    string s = "";
    s = s + "Bag[count=" + to_string(this->numberofItem) + ";";
    for (int i = 1; i <= this->numberofItem; i++){
        switch (temp->Item){
            case 0:
                s += "Antidote";
                break;
            case 1:
                s += "PhoenixI";
                break;
            case 2:
                s += "PhoenixII";
                break;
            case 3:
                s += "PhoenixIII";
                break;
            case 4:
                s += "PhoenixIV";
                break;
            }
        if (i == this->numberofItem)
            s += "]";
        else
            s += ",";
        temp = temp->next;
        }
        if (this->numberofItem == 0)
            s+="]";
    return s;
}
NormalBag::NormalBag(BaseKnight *knight, int PhoenixDownI, int Antidote):BaseBag(knight){
    this->maxcarryItem = 19;
    if (PhoenixDownI > 0 && this->numberofItem < this->maxcarryItem){
        for (int i = 0; i < PhoenixDownI; i++){
            if (this->numberofItem == this->maxcarryItem)
                break;
            ItemType type = PHOENIXDOWNI;
            insert(type);
        }
    }
    if (Antidote > 0 && this->numberofItem < this->maxcarryItem){
        for (int i = 0; i < Antidote; i++){
            if (this->numberofItem == this->maxcarryItem)
                break;
            ItemType type = ANTIDOTE;
            insert(type);
        }
    }
}
string NormalBag::toString()const{
    BaseItem *temp = head;
    string s = "";
    s = s + "Bag[count=" + to_string(this->numberofItem) + ";";
    for (int i = 1; i <= this->numberofItem; i++){
        switch (temp->Item){
            case 0:
                s += "Antidote";
                break;
            case 1:
                s += "PhoenixI";
                break;
            case 2:
                s += "PhoenixII";
                break;
            case 3:
                s += "PhoenixIII";
                break;
            case 4:
                s += "PhoenixIV";
                break;
            }
        if (i != this->numberofItem)
            s += ",";
        temp = temp->next;
        }
    s+="]";
    return s;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight *BaseKnight:: create( int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight *knight = new BaseKnight;
    knight->hp = maxhp;
    knight->gil = gil;
    knight->id = id;
    knight->level = level;
    knight->maxhp = maxhp;;
    knight->PhoenixDownI = phoenixdownI;
    knight->Antidote = antidote;
    knight->setknightType();
    knight->setBag(knight, phoenixdownI, antidote);
    return knight;
}
void BaseKnight::setBag(BaseKnight *knight, int PhoenixDownI, int Antidote){
    switch(knightType){
        case 0:
        {
            bag = new PaladinBag(knight, PhoenixDownI, Antidote);
            break;
        }
        case 1:
        {
            bag = new LancelotBag(knight, PhoenixDownI, Antidote);
            break;
        }
        case 2:
        {
            bag = new DragonBag(knight, PhoenixDownI);
            break;
        }
        case 3:
        {
            bag = new NormalBag(knight, PhoenixDownI, Antidote);
            break;
        }
        }
}
BaseKnight::~BaseKnight(){
    delete bag;
}
void BaseKnight::setknightType(){
    if (checkPrime(maxhp)){
        knightType = PALADIN;
    }
    else if (maxhp == 888){
        knightType = LANCELOT;
    }
    else if (maxhp>99 && maxhp < 1000){
        int a = maxhp/100, c = maxhp%10, b = (maxhp%100)/10;
        if (pow(a,2)+pow(b,2)==pow(c,2)||pow(a,2)+pow(c,2)==pow(b,2)||pow(c,2)+pow(b,2)==pow(a,2)) 
            knightType = DRAGON;    
        else
            knightType = NORMAL;
    }
    else   
        knightType = NORMAL;
}
BaseBag * BaseKnight::getBag(){
    return bag;
}
void BaseKnight:: setAntidote(int Antidote){
    this->Antidote += Antidote;
}
int BaseKnight:: getAntidote(){
    return Antidote;
}
void BaseKnight:: setPhoenixDownI(int PhoenixDownI){
    this->PhoenixDownI += PhoenixDownI;
}
int BaseKnight:: getPhoenixDownI(){
    return PhoenixDownI;
}
void BaseKnight:: setPhoenixDownII(int PhoenixDownII){
    this->PhoenixDownII += PhoenixDownII;
}
int BaseKnight:: getPhoenixDownII(){
    return PhoenixDownII;
}
void BaseKnight:: setPhoenixDownIII(int PhoenixDownIII){
    this->PhoenixDownIII += PhoenixDownIII;
}
int BaseKnight:: getPhoenixDownIII(){
    return PhoenixDownIII;
}
void BaseKnight:: setPhoenixDownIV(int PhoenixDownIV){
    this->PhoenixDownIV += PhoenixDownIV;
}
int BaseKnight:: getPhoenixDownIV(){
    return PhoenixDownIV;
}
int BaseKnight:: getHp(){
    return this->hp;  
}
void BaseKnight:: setHp(int hp){
    this->hp = hp;
}
void BaseKnight:: setId(int id){
    this->id = id;
}
void BaseKnight:: setmaxHp(int maxhp){
    this->maxhp = maxhp;
}
int BaseKnight:: getId(){
    return id;
}
int BaseKnight:: getmaxHp(){
    return maxhp;
}
int BaseKnight:: getLevel(){
    return level;
}
void BaseKnight:: setLevel(int level){
    this->level = level;
}
int BaseKnight:: getKnightType(){
    return knightType;
}
bool BaseKnight:: getIntoxication(){
    return intoxication;
}
void BaseKnight:: setIntoxication(bool status){
    this->intoxication = status;
}
void BaseKnight:: setGil(int gil){
    this->gil = gil;
}
int BaseKnight:: getGil(){
    return gil;
}
string BaseKnight:: toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code but the format output must be the same
    string s = "";
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString() + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string &file_armyknights){
    fstream read;
    read.open(file_armyknights,ios::in);
    read >> numberofKnights;
    isFighting = numberofKnights - 1;
    knightlist = new BaseKnight *[numberofKnights];
    for (int i = 0; i < numberofKnights; i++){
        string type[4] = {"PALADIN","LANCELOT","DRAGON","NORMAL"};
        int ID, MAXHP, LEVEL, GIL, ANTIDOTE, PHOENIXDOWNI;
        string temp;
        ID = i + 1;
        read >> MAXHP >> LEVEL >> PHOENIXDOWNI >> GIL >> ANTIDOTE;//Đọc các thông tin từ file để ghi vào thông tin cho từng hiệp sĩ trong file
        knightlist[i] = knightlist[i]->create(ID, MAXHP, LEVEL, GIL, ANTIDOTE, PHOENIXDOWNI);
    }
}
ArmyKnights::~ArmyKnights(){
    delete[] knightlist;
}
bool ArmyKnights:: fight(BaseOpponent * opponent){
    int hpbefore = knightlist[isFighting]->getHp();
    if(opponent->getOpponentType() == 0)//Nếu mã sự kiện là từ 1 đến 5 sẽ làm như dưới  
        {
            if (knightlist[isFighting]->getLevel() >=  opponent->getLevelO() || knightlist[isFighting]->getKnightType() == PALADIN || knightlist[isFighting]->getKnightType() == LANCELOT){
                if (knightlist[isFighting]->getGil() < 999)
                    knightlist[isFighting]->setGil(knightlist[isFighting]->getGil() + opponent->getGil());//Nếu chiến thắng số gil của hiệp sĩ sẽ tăng lên theo mô tả đề
                if (knightlist[isFighting]->getGil() > 999){
                    int remainGil = knightlist[isFighting]->getGil() - 999;
                    knightlist[isFighting] -> setGil(999);
                    int passing = isFighting - 1;
                    if (passing > -1)
                        while (remainGil != 0){
                            if (knightlist[passing]->getGil() < 999)
                                {
                                    if(remainGil <= 999 - knightlist[passing]->getGil()){
                                        knightlist[passing]->setGil(knightlist[passing]->getGil()+ remainGil);
                                        break;
                                    }
                                    else{
                                        remainGil -= (999 - knightlist[passing]->getGil());
                                        knightlist[passing]->setGil(999);
                                        passing--;
                                        if (passing == -1)
                                            break;
                                    }
                                }
                        }
                }
            }
            else{
                    int hpafter = knightlist[isFighting]->getHp() - opponent->getBaseDamage()*(opponent->getLevelO()-knightlist[isFighting]->getLevel());//Nếu thua điều chỉnh lại máu 
                    knightlist[isFighting]->setHp(hpafter);
                }
        }
    if (opponent->getOpponentType() == 1){//Đối với sự kiện TornBery
            if (knightlist[isFighting]->getLevel() >= opponent->getLevelO()){
                //Đang mổ tả đánh nhau tornbery, chưa làm gì hết, nhớ mô tả lại class tornbery
                if (knightlist[isFighting]->getLevel()<10)
                    knightlist[isFighting]->setLevel(knightlist[isFighting]->getLevel() + 1);
            }
            else{//Đã thua TornBery và có antidote
            if (knightlist[isFighting]->getKnightType() != DRAGON){
                knightlist[isFighting]->setIntoxication(true);
                if (knightlist[isFighting]->getAntidote() > 0){
                    Antidote *antidote = new Antidote;
                    if (antidote->canUse(knightlist[isFighting])){
                        int pos = knightlist[isFighting]->getBag()->getFirstPos(ANTIDOTE);
                        knightlist[isFighting]->getBag()->swap(pos);
                        antidote->use(knightlist[isFighting]);
                    }
                    delete antidote;
                }
                else{//Trường hợp đã thua TornBery và không có antidote
                    int temp = knightlist[isFighting]->getBag()->getnumberofItem();
                    for (int i = 0; i < 3; i++){
                        if (i == temp)
                            break;
                        knightlist[isFighting]->getBag()->remove(0);
                    }
                    knightlist[isFighting]->setHp(knightlist[isFighting]->getHp() - 10);
                    knightlist[isFighting]->setIntoxication(false);
                }
                }
            }
        }
    if (opponent->getOpponentType() == 2){
            if (knightlist[isFighting]->getLevel() >= opponent->getLevelO()){
                int gil_receiving = knightlist[isFighting]->getGil();
                int receiving = isFighting;
                while (gil_receiving > 0){
                    if (receiving == -1){
                        break;
                    }
                    if (knightlist[receiving]->getGil() + gil_receiving >= 999){
                        knightlist[receiving]->setGil(999);
                        gil_receiving -= (999-knightlist[receiving]->getGil());
                        --receiving;
                    }
                    else{
                        knightlist[receiving]->setGil(knightlist[receiving]->getGil() + gil_receiving);
                        gil_receiving = 0;
                    }
                }
            }
            else{
                if (knightlist[isFighting]->getKnightType() != PALADIN)
                    knightlist[isFighting]->setGil((int)(knightlist[isFighting]->getGil()/2));
            }
        }
    if (opponent->getOpponentType() == 3){
            if ((knightlist[isFighting]->getGil() >= 50 || knightlist[isFighting]->getKnightType() == PALADIN )&& knightlist[isFighting]->getHp() < (int)(knightlist[isFighting]->getmaxHp()/3)){//Nếu máu của hiệp sĩ đang thấp hơn 1/3 máu tối đa và số tiền lớn hoặc bằng 50 gil, hiệp sĩ sẽ được tăng 1/5 số máu tối đa
                if (knightlist[isFighting]->getKnightType() != PALADIN)
                    knightlist[isFighting]->setGil(knightlist[isFighting]->getGil() - 50);
                knightlist[isFighting]->setHp(knightlist[isFighting]->getHp() + (int)(knightlist[isFighting]->getmaxHp()/5));
            }
        }
    if (opponent->getOpponentType() == 4)//Gặp sự kiện vườn sầu riêng máu hiệp sĩ sẽ được tăng về maxhp
            {knightlist[isFighting]->setHp(knightlist[isFighting]->getmaxHp());
            }
    if (opponent->getOpponentType() == 5){
            if (OmegaWeapon == 0){
                if (knightlist[isFighting]->getKnightType() == DRAGON || knightlist[isFighting]->getLevel() == 10){
                        setOmegaWeapon();
                        knightlist[isFighting]->setLevel(10);
                        knightlist[isFighting]->setGil(999);
                    }
                else{
                    setOmegaWeapon();
                    knightlist[isFighting]->setHp(0);
                }
            }
        }
    if (opponent->getOpponentType() == 6){
            if (Hades == 0){
                Hades = 1;
                if (knightlist[isFighting]->getKnightType() == PALADIN && knightlist[isFighting]->getLevel() >= 8|| knightlist[isFighting]->getLevel() == 10){
                    if (!PaladinShield)
                        PaladinShield = 1;
                }
                else
                    knightlist[isFighting]->setHp(0);
            }
        }
    if (opponent->getOpponentType() == 15){//Gặp Ultimecia
            if (ExcaliburSword){
                return true;
            }
            else if (LancelotSpear == 1 && PaladinShield == 1 && GuinevereHair == 1){
                int firstFighting = isFighting;
                while (isFighting != -1){
                    if (knightlist[isFighting]->getKnightType() != NORMAL){
                        float knightBaseDamage;
                        if (knightlist[isFighting]->getKnightType() == DRAGON)
                            knightBaseDamage = 0.075;
                        else if (knightlist[isFighting]->getKnightType() == LANCELOT)
                            knightBaseDamage = 0.05;
                        else    
                            knightBaseDamage = 0.06;
                        opponent->fightingUltimecia((int)(knightlist[isFighting]->getHp()*knightlist[isFighting]->getLevel()*knightBaseDamage));
                        if (opponent->getHpultimecia() <= 0)
                            return true;
                        else
                            knightlist[isFighting] = nullptr;
                    }
                    --isFighting;
                }
                if (isFighting == -1){
                    for (int i = 0; i <= firstFighting; i++)
                        knightlist[i] = nullptr;
                    return false;
                }
                else{
                    while(knightlist[firstFighting]==nullptr)
                        firstFighting--;
                    isFighting = firstFighting;
                }
            }
            else {
                for (int i = isFighting; i > -1; i--)
                    knightlist[i] = nullptr;
                return false;
            }
        }
    if (opponent->getOpponentType() == 8){
        ItemType item;
        item = PHOENIXDOWNII;
        if (knightlist[isFighting]->getBag()->getnumberofItem() < knightlist[isFighting]->getBag()->getmaxcarryItem() || knightlist[isFighting]->getBag()->getmaxcarryItem() == -1)
            knightlist[isFighting]->getBag()->insert(item);
        else{
            int passing = isFighting - 1;
            BaseItem *item = new PhoenixDownII;
            if (passing > -1)
                while(true){
                    if (knightlist[passing]->getBag()->insertFirst(item))
                        break;
                    passing--;
                    if (passing == -1)
                        break;
                }
        }
    }
    if (opponent->getOpponentType() == 9){
        ItemType item;
        item = PHOENIXDOWNIII;
        if (knightlist[isFighting]->getBag()->getnumberofItem() < knightlist[isFighting]->getBag()->getmaxcarryItem() || knightlist[isFighting]->getBag()->getmaxcarryItem() == -1)
            knightlist[isFighting]->getBag()->insert(item);
        else{
            int passing = isFighting - 1;
            BaseItem *item = new PhoenixDownIII;
            if (passing > -1)
                while(true){
                    if (knightlist[passing]->getBag()->insertFirst(item))
                        break;
                    passing--;
                    if (passing == -1)
                        break;
                }
        }
    }
    if (opponent->getOpponentType() == 10){
        ItemType item;
        item = PHOENIXDOWNIV;
        if (knightlist[isFighting]->getBag()->getnumberofItem() < knightlist[isFighting]->getBag()->getmaxcarryItem() || knightlist[isFighting]->getBag()->getmaxcarryItem() == -1)
            knightlist[isFighting]->getBag()->insert(item);
        else{
            int passing = isFighting - 1;
            BaseItem *item = new PhoenixDownIV;
            if (passing > -1)
                while(true){
                    if (knightlist[passing]->getBag()->insertFirst(item))
                        break;
                    passing--;
                    if (passing == -1)
                        break;
                }
        }
    }
    if (opponent->getOpponentType() == 11)//Gặp nhặt paladinshield
    {
        if (!PaladinShield)
            PaladinShield = 1;
    }
    if (opponent->getOpponentType() == 12)//Gặp nhặt lancelotspear
    {
        if (!LancelotSpear)
            LancelotSpear = 1;
    }
    if (opponent->getOpponentType() == 13)//Gặp nhặt guineverehair
    {
        if (!GuinevereHair)
            GuinevereHair = 1;
    }
    if (opponent->getOpponentType() == 14)//Gặp nhặt excalibursword
    {
        if (PaladinShield | LancelotSpear | GuinevereHair)
            ExcaliburSword = 1;
    }
    if (knightlist[isFighting]->getHp() < hpbefore && isFighting != -1){
            BaseBag *tempbag = knightlist[isFighting]->getBag();
            int minpos = -1;
            ItemType type;
            if (minpos == -1 || minpos > tempbag->getFirstPos(PHOENIXDOWNI) && minpos >= 0 && tempbag->getFirstPos(PHOENIXDOWNI) >=0){
                PhoenixDownI temp;
                if (temp.canUse(knightlist[isFighting])){
                    type = PHOENIXDOWNI;   
                    minpos = knightlist[isFighting]->getBag()->getFirstPos(PHOENIXDOWNI);
                }
            }
            if (minpos == -1 || minpos > tempbag->getFirstPos(PHOENIXDOWNII) && minpos >= 0 && tempbag->getFirstPos(PHOENIXDOWNII) >=0){
                PhoenixDownII temp;
                if (temp.canUse(knightlist[isFighting])){
                    type = PHOENIXDOWNII;   
                    minpos = knightlist[isFighting]->getBag()->getFirstPos(PHOENIXDOWNII);
                }
            }
            if (minpos == -1 || minpos > tempbag->getFirstPos(PHOENIXDOWNIII) && minpos >= 0 && tempbag->getFirstPos(PHOENIXDOWNIII) >=0){
                PhoenixDownIII temp;
                if (temp.canUse(knightlist[isFighting])){
                    type = PHOENIXDOWNIII;   
                    minpos = knightlist[isFighting]->getBag()->getFirstPos(PHOENIXDOWNIII);
                }
            }
            if (minpos == -1 || minpos > tempbag->getFirstPos(PHOENIXDOWNIV) && minpos >= 0 && tempbag->getFirstPos(PHOENIXDOWNIV) >=0){
                PhoenixDownIV temp;
                if (temp.canUse(knightlist[isFighting])){
                    type = PHOENIXDOWNIV;   
                    minpos = knightlist[isFighting]->getBag()->getFirstPos(PHOENIXDOWNIV);
                }
            }
            if (minpos != -1){
                BaseItem *phoenix;
                switch (type){
                case 1:
                    {
                        phoenix = new PhoenixDownI;
                        break;
                    }
                case 2:
                    {
                        phoenix = new PhoenixDownII;
                        break;
                    }
                case 3:
                    {
                        phoenix = new PhoenixDownIII;
                        break;
                    }
                case 4:
                    {
                        phoenix = new PhoenixDownIV;
                        break;
                    }
                } 
                if (phoenix->canUse(knightlist[isFighting])){
                    int pos = knightlist[isFighting]->getBag()->getFirstPos(phoenix->Item);
                    knightlist[isFighting]->getBag()->swap(pos);
                    phoenix->use(knightlist[isFighting]);
                }
                delete phoenix;
            }
            else if (knightlist[isFighting]->getHp() <= 0){
                if (knightlist[isFighting]->getGil() >= 100){
                    knightlist[isFighting]->setGil(knightlist[isFighting]->getGil()-100);
                    knightlist[isFighting]->setHp((int)(knightlist[isFighting]->getmaxHp()/2));
                }
                else{
                    knightlist[isFighting] = nullptr;
                    --isFighting;
                }
            }
        }
    if (count() == 0){  
        return 0;
    }          
        return 1;      
}
bool ArmyKnights:: adventure(Events *events){//Code sau định dạng phương thức trang 10
    int eventId;
    isFighting = numberofKnights - 1;
    for (int i = 0; i < events->count();i++){
        eventId = events->get(i);
            switch (eventId){
                case 1:{
                    MadBear *opponent = new MadBear(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    } 
                    delete opponent;
                    break; 
                }
                case 2:{
                    Bandit *opponent = new Bandit(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    } 
                    delete opponent;
                    break; 
                }
                case 3:{
                    LordLupin *opponent = new LordLupin(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    } 
                    delete opponent;
                    break;
                }
                case 4:{
                    Elf *opponent = new Elf(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    }   
                    delete opponent;
                    break;
                }
                case 5:{
                    Troll *opponent = new Troll(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    }  
                    delete opponent;
                    break;
                }
                case 6:{
                    Tornbery *opponent = new Tornbery(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    }  
                    delete opponent;
                    break;
                }
                case 7:{
                    QueenOfCards *opponent = new QueenOfCards(i);
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    }  
                    delete opponent;
                    break;
                }
                case 8:{
                    NinaDeRings *opponent = new NinaDeRings;
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    } 
                    delete opponent;
                    break;
                }
                case 9:{
                    DurianGarden *opponent = new DurianGarden;
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    }  
                    delete opponent;
                    break;
                }
                case 10:{
                    Omega_Weapon *opponent = new Omega_Weapon;
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    }  
                    delete opponent;
                    break;
                }
                case 11:{
                    HaDes *opponent = new HaDes;
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    } 
                    delete opponent;
                    break;
                }
                case 112:{
                    PhoenixdownII *opponent = new PhoenixdownII;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 113:{
                    PhoenixdownIII *opponent = new PhoenixdownIII;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 114:{
                    PhoenixdownIV *opponent = new PhoenixdownIV;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 95:{
                    Paladinshield *opponent = new Paladinshield;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 96:{
                    Lancelotspear *opponent = new Lancelotspear;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 97:{
                    Guineverehair *opponent = new Guineverehair;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 98:{
                    Excalibursword *opponent = new Excalibursword;
                    fight(opponent);
                    delete opponent;
                    break;
                }
                case 99:{
                    Ultimecia *opponent = new Ultimecia;
                    if(!fight(opponent)){
                        printInfo();
                        return false; 
                    } 
                    delete opponent;
                    break;
                }
            }
        printInfo();
        if (knightlist[0] == nullptr){
                delete knightlist[0];
                for (int i = 1 ; i < numberofKnights; i++){
                    knightlist[i] = nullptr;
                }
                return false;
            }
    }
    return true;
}
int ArmyKnights:: count() const{
    int count = 0;
    for (int i = 0; i < numberofKnights; i++){
    if (knightlist[i] != nullptr)
        count++;
    }
    return count;
}
BaseKnight* ArmyKnights:: lastKnight() const{
    if(knightlist[0] == nullptr)
        return NULL;
    else 
        return knightlist[isFighting];// Nên xem lại
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: "<< count();
    if (count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

bool ArmyKnights::hasExcaliburSword() const{
    return ExcaliburSword;
}

bool ArmyKnights::hasPaladinShield() const{
    return PaladinShield;
}

bool ArmyKnights::hasGuinevereHair() const{
    return GuinevereHair;
}

bool ArmyKnights::hasLancelotSpear() const{
    return LancelotSpear;
}

void ArmyKnights::setOmegaWeapon(){
    OmegaWeapon = true;
}

void ArmyKnights::setPaladinShield(){
    PaladinShield = true;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class BaseOpponent * * */
BaseOpponent::BaseOpponent(BaseKnight *knight){
    this->knight = knight;
}

int BaseOpponent::getLevelO(){
    return levelO;
}

int BaseOpponent::getGil(){
    return gil;
}

int BaseOpponent:: getBaseDamage(){
    return baseDamage;
}

int BaseOpponent::getOpponentType(){
    return type;
}
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure(){
    delete events;
    delete armyKnights;
}
void KnightAdventure::loadArmyKnights(const string &file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string &file_events){
    events = new Events(file_events);
}
void KnightAdventure::run(){
    armyKnights->printResult(armyKnights->adventure(events));
}
/* * * END implementation of class KnightAdventure * * */
Events::Events(const string &file_events){
    fstream inforofevent;
    inforofevent.open(file_events, ios::in);
    inforofevent>>Count;
    eventarr = new int[Count];//Tạo một mảng động để lưu trữ các mã sự kiện
    for (int i = 0; i < Count; i++){
        inforofevent >> eventarr[i];
    }
}
int Events:: count() const{
    return Count;
}
int Events:: get(int i) const{
    return eventarr[i];
}
Events::~ Events(){
    delete[] eventarr;
}