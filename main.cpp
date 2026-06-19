#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include "item.h"
#include "monster.h"
#include "Player.h"
#include "skill.h"
#include "backpack.h"
#include "character.h"
#include "achievement.h"

using namespace std;

Player* createPlayer(string n);

void PrintOutImage(ifstream &image);
void PrintOutStory(ifstream &story);
bool PlayerFaster(Monster& m,Player& p);
bool arena(Monster& m,Player& p,Backpack& b);
bool PlayerAttack(Monster& m,Player& p,double damage);
bool MonsterAttack(Monster& m,Player& p,double damage);

const string SAVE_FILE = "savegame.txt";
void saveGame(Player* p,const string& playerClass,Backpack& b,int stage);
bool loadGame(Player*& p,string& playerClass,Backpack& b,int& stage);
bool saveFileExists();

//開啟ascii圖片
ifstream dragonImage("images\\dragon.txt");
ifstream titleImage("images\\title.txt");
ifstream championImage("images\\champion.txt");
ifstream direwolfImage("images\\direwolf.txt");
ifstream skeletonImage("images\\skeleton.txt");
ifstream slimeImage("images\\slime.txt");
ifstream zombieImage("images\\zombie.txt");

//開啟前後故事
ifstream openingStory("story\\opening.txt");
ifstream winStory("story\\win.txt");
ifstream loseStory("story\\lose.txt");

//定義消耗品與裝備
Consumable apple("apple",HEALTH_POINT,15,1);
Consumable magicWine("magicWine",MAGIC_POINT,20,2);
Equipment diamond_sword("diamond_sword",ATTACK_POWER,15,1);
Consumable cake("cake",HEALTH_POINT,-20,1);
Equipment UltimateInvinciblePowerBoots("Ultimate Invincible Power Boots",SPEED,50,1);

Achievement startAchi("The beginning of a legend");
Achievement cakeAchi("The cake is a lie");
Achievement winAchi("The End?");
Achievement fastAchi("Faster and faster");
Achievement fireballAchi("Burning with desire");

//名稱、傷害、mp、cd
Skill fireball("FireBall",25,20,3);
Skill blackflame("BlackFlame",30,25,4);
Skill lighting("Lighting",20,20,3);
// 名稱、血量、傷害、金幣、速度
Monster Zombie("Zombie",100,15,10,70);
Monster DireWolf("DireWolf",50,20,20,110);
Monster Slime;

int main(){

    Backpack b;
    string n;
    Player* p = nullptr;
    string playerClass;
    int startStage = 1;

    PrintOutImage(dragonImage);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintOutImage(titleImage);

    // ===== 主選單：新遊戲 / 讀取存檔 =====
    int menuChoice = 0;
    if(saveFileExists()){
        cout << "1. New Game\n2. Load Game\nEnter your choice: ";
        cin >> menuChoice;
        cin.ignore();
    }else{
        menuChoice = 1;
    }

    if(menuChoice == 2 && loadGame(p,playerClass,b,startStage)){
        // 讀檔成功，p / b / startStage 都已經設好
    }else{
        // ===== 新遊戲流程 =====
        PrintOutStory(openingStory);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout << "=========================================================" << endl;
        cout << "【System】: Link Start !!!" << endl;
        cout << "=========================================================" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout <<"Enter player name: ";
        cin >> n;
        cout<<"【System】: Welcome "<< n <<"\n"<<endl;
        startAchi.unlockAchievement();

        p = createPlayer(n);
        p->setname(n);

        // 紀錄職業字串，存檔用
        if(dynamic_cast<Knight*>(p)) playerClass = "Knight";
        else if(dynamic_cast<Mage*>(p)) playerClass = "Mage";
        else playerClass = "Monk";

        b.addInventory(new Consumable(apple));
        b.addInventory(new Consumable(magicWine));
        b.addInventory(new Equipment(diamond_sword));
        b.addInventory(new Consumable(cake));
        b.addInventory(new Equipment(UltimateInvinciblePowerBoots));

        startStage = 1;
    }

    cout<<"\n3"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"2"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"1\n"<<endl;

    // ===== STAGE 1 : Slime =====
    if(startStage <= 1){
        cout << "==================== [ STAGE 1 ] ====================" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        PrintOutImage(slimeImage);
        if (!arena(Slime,*p,b)){
            cout<<"Game Over"<<endl;
            PrintOutImage(skeletonImage);
            PrintOutStory(loseStory);
            delete p;
            return 0;
        }else{
            cout << "==================== [ STAGE CLEAR !!! ] ====================" << endl;
        }

        cout << "Save your progress? (1 = Yes, 0 = No): ";
        int saveChoice; cin >> saveChoice;
        if(saveChoice == 1) saveGame(p,playerClass,b,2);
    }

    // ===== STAGE 2 : Zombie =====
    if(startStage <= 2){
        cout << "==================== [ STAGE 2 ] ====================" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        PrintOutImage(zombieImage);
        if (!arena(Zombie,*p,b)){
            cout<<"Game Over"<<endl;
            PrintOutImage(skeletonImage);
            PrintOutStory(loseStory);
            delete p;
            return 0;
        }else{
            cout << "==================== [ STAGE CLEAR !!! ] ====================" << endl;
        }

        cout << "Save your progress? (1 = Yes, 0 = No): ";
        int saveChoice; cin >> saveChoice;
        if(saveChoice == 1) saveGame(p,playerClass,b,3);
    }

    // ===== STAGE 3 : DireWolf =====
    cout << "==================== [ STAGE 3 ] ====================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintOutImage(direwolfImage);
    if (!arena(DireWolf,*p,b)){
        cout<<"Game Over"<<endl;
        PrintOutImage(skeletonImage);
        PrintOutStory(loseStory);
        delete p;
        return 0;
    }else{
        cout << "==================== [ Youwin !!! ] ====================" << endl;
        PrintOutImage(championImage);
        PrintOutStory(winStory);
        winAchi.unlockAchievement();
    }

  
    delete p;
    return 0;
}

void PrintOutImage(ifstream &image){
    string content;
    if(image.is_open()){
        while(getline(image,content)){
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            cout<< content <<endl;
        }
    }

}
void PrintOutStory(ifstream &story){
    string content;
    if(story.is_open()){
        while(getline(story,content)){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            cout<< content <<endl;
        }
    }

}

bool saveFileExists(){
    ifstream f(SAVE_FILE);
    return f.good();
}

// 存檔格式（每行一個欄位）：
// playerClass
// name
// hp atk mp speed gold
// stage
// itemCount
// 每個item一行： isEquipment name type effectValue quantity
void saveGame(Player* p,const string& playerClass,Backpack& b,int stage){
    ofstream out(SAVE_FILE);
    if(!out.is_open()){
        cout<<"【System】: Save failed! Could not open file.\n";
        return;
    }

    out << playerClass << "\n";
    out << p->getName() << "\n";
    out << p->gethp() << " " << p->getattackpower() << " " << p->getmp() << " " << p->getspeed() << " " << p->getgold() << "\n";
    out << stage << "\n";

    out << b.getInventorySize() << "\n";
    for(int i = 0;i<b.getInventorySize();i++){
        Item& it = b.getSpecifyItem(i);
        bool isEquip = (dynamic_cast<Equipment*>(&it) != nullptr);
        // 用 | 分隔避免名字裡有空格時出問題
        out << isEquip << "|" << it.getName() << "|" << it.getType() << "|" << it.getEffectValue() << "|" << it.getQuantity() << "\n";
    }

    out.close();
    cout<<"【System】: Game saved!\n";
}

bool loadGame(Player*& p,string& playerClass,Backpack& b,int& stage){
    ifstream in(SAVE_FILE);
    if(!in.is_open()){
        cout<<"【System】: No save file found.\n";
        return false;
    }

    string name;
    double hp,atk,mp,spd;
    int gold;

    getline(in,playerClass);
    getline(in,name);

    in >> hp >> atk >> mp >> spd >> gold;
    in >> stage;
    in.ignore(); // 吃掉換行字元

    int itemCount;
    in >> itemCount;
    in.ignore();

    // 依職業字串重建玩家物件
    if(playerClass == "Knight"){
        p = new Knight(name);
    }else if(playerClass == "Mage"){
        p = new Mage(name);
    }else{
        p = new Monk(name);
    }
    p->setname(name);
    p->sethp(hp);
    p->setpower(atk);
    p->setmp(mp);
    p->setspeed((int)spd);
    p->addgold(gold - p->getgold()); // 修正金幣到存檔數值

    // 清空目前背包，重建道具（main() 會保證讀檔時傳入全新的 Backpack）

    for(int i = 0;i<itemCount;i++){
        string line;
        getline(in,line);
        stringstream ss(line);
        string token;
        bool isEquip; string itemName; string itemType; double effectValue; int quantity;

        getline(ss,token,'|'); isEquip = (token == "1");
        getline(ss,itemName,'|');
        getline(ss,itemType,'|');
        getline(ss,token,'|'); effectValue = stod(token);
        getline(ss,token,'|'); quantity = stoi(token);

        if(isEquip){
            b.addInventory(new Equipment(itemName,itemType,effectValue,quantity));
        }else{
            b.addInventory(new Consumable(itemName,itemType,effectValue,quantity));
        }
    }

    in.close();
    cout<<"【System】: Save loaded! Welcome back, "<<name<<".\n";
    return true;
}

Player* createPlayer(string n){
    int classchoice;
    cout << "Choose your class：" << endl;
    cout << "1. Knight (Medium Hp、Hight attack)" << endl;
    cout << "2. Mage   (Low Hp、Hight attack)" << endl;
    cout << "3. Monk  (Hight HP、Medium attack)" << endl;
    cin >> classchoice;
    cin.ignore();

    if(classchoice == 1){
        return new Knight(n);
    }else if(classchoice == 2){
        return new Mage(n);
    }else if(classchoice == 3){
        return new Monk(n);
    }

    cout <<"Defult set knight"<<endl;
    return new Knight(n);
}

bool PlayerAttack(Monster& m,Player& p,double damage){
    m.takeDamage(damage);
    cout << "【" << m.getName() << "】take " << damage << " damage! (left hp: " << m.gethp() << ")" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (!m.isAlive()){ 
        p.addgold(m.dropgold());
        cout <<"Succesfully defeat " << m.getName()<<endl;
        cout<<m.getName()<<" Drop " <<m.dropgold()<<" gold"<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"You have "<<p.getgold()<<" Gold"<<endl;
    }
    return !m.isAlive();
}


bool MonsterAttack(Monster& m,Player& p,double damage){
     p.takeDamage(m.getattackpower());
    cout << "【" << p.getName() << "】take " << m.getattackpower() << " damage! (left hp: " << p.gethp() << ")" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (!p.isAlive()){
        cout<<"Defeat!!!"<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return !p.isAlive();
}


bool arena(Monster& m,Player& p,Backpack& b){
    int round = 1;
    while (p.isAlive()&&m.isAlive())
    {
        int choice;
        int skillchoice;
        int itemchoice;
        int checkItemOrUseItem;
        cout <<round<<" Round start!"<<endl;
        p.showInfo();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        m.showInfo();
        cout <<"====================="<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout <<"1. Normal Attack \n" <<"2. Skill\n"<<"3. Use Item\n"<<endl;
        cout <<"Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (PlayerFaster(m,p)){
                    if(PlayerAttack(m,p,p.getattackpower())){
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                }else{
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(PlayerAttack(m,p,p.getattackpower())){
                        break;
                    }
                }
            
            break;
        case 2:
            cout <<"====================="<<endl;
            cout<<"1.";
            fireball.showInfo();
            cout<<"2.";
            blackflame.showInfo();
            cout<<"3.";
            lighting.showInfo();
            cout<<"0.RETURN!"<<endl;
            cout <<"====================="<<endl;

            cin >> skillchoice;
            switch (skillchoice)
            {
            case 1:
                cout <<"\n";
                if (fireball.getcurrentcd()>0){
                    cout<<"Skills in cooldown!"<<endl;
                    continue;
                }

                fireball.setcooldown();
                cout <<"【"<<p.getName()<<"】";
                fireball.use();
                p.costmp(20);
                if (PlayerFaster(m,p)){
                    if(PlayerAttack(m,p,fireball.getDamage())){
                        fireballAchi.unlockAchievement();
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                }else{
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(PlayerAttack(m,p,fireball.getDamage())){
                        fireballAchi.unlockAchievement();
                        break;
                    }
                }
                break;
            case 2:
                cout <<"\n";
                if (blackflame.getcurrentcd()>0){
                    cout<<"Skills in cooldown!"<<endl;
                    continue;
                }

                blackflame.setcooldown();
                cout <<"【"<<p.getName()<<"】";
                blackflame.use();
                p.costmp(25);
                if (PlayerFaster(m,p)){
                    if(PlayerAttack(m,p,blackflame.getDamage())){
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                }else{
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(PlayerAttack(m,p,blackflame.getDamage())){
                        break;
                    }
                }
                break;
            case 3:
                cout <<"\n";
                if (lighting.getcurrentcd()>0){
                    cout<<"Skills in cooldown!"<<endl;
                    continue;
                }

                lighting.setcooldown();
                cout <<"【"<<p.getName()<<"】";
                lighting.use();
                p.costmp(20);
                if (PlayerFaster(m,p)){
                    if(PlayerAttack(m,p,lighting.getDamage())){
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                }else{
                    if(MonsterAttack(m,p,m.getattackpower())){
                        return false;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(PlayerAttack(m,p,lighting.getDamage())){
                        break;
                    }
                }
                break;
            case 0:
                continue;
                break;
            }
            
                break;
        case 3:
            bool backToActChoice = false;
            do
            {
                b.showBackpackInfo(p.getgold());
                cout<<"choose item that you want to check/use (0 for return):";
                cin>>itemchoice;
                if (itemchoice == 0){
                    backToActChoice = true;
                    break;
                }
                cout<<"check item's info (0)/use item(1) :";
                cin>>checkItemOrUseItem;
                switch (checkItemOrUseItem){
                case 0:
                    b.getSpecifyItem(itemchoice-1).showInfo();
                    break;
                case 1:
                    b.getSpecifyItem(itemchoice-1).use(p);
                    if (b.getSpecifyItem(itemchoice-1).getName() == "cake"){
                        cakeAchi.unlockAchievement();
                    }
                    b.removeInventory();
                    break;
                default:
                    break;
                }
                std::this_thread::sleep_for(std::chrono::seconds(2));
            } while (checkItemOrUseItem == 0);
            if(backToActChoice){
                continue;
            }

            if(MonsterAttack(m,p,m.getattackpower())){
                return false;
            }

            break;
        }

        round++;
        p.addmp();
        fireball.countcooldown();
        blackflame.countcooldown();
        lighting.countcooldown();
    }

    return (p.isAlive()&&!m.isAlive());
}

bool PlayerFaster(Monster& m,Player& p){
    if (m.getspeed()<p.getspeed() && m.getName() == "DireWolf"){
        fastAchi.unlockAchievement();
    }
    return(m.getspeed()<p.getspeed());
}
