#include <iostream>
#include <thread>
#include <fstream>
#include "item.h"
#include "monster.h"
#include "Player.h"
#include "skill.h"
#include "backpack.h"
#include "character.h"

using namespace std;

Player* createPlayer(string n);

void PrintOutImage(ifstream &image);
void PrintOutStory(ifstream &story);
bool PlayerFaster(Monster& m,Player& p);
bool arena(Monster& m,Player& p,Backpack& b);
bool PlayerAttack(Monster& m,Player& p,double damage);
bool MonsterAttack(Monster& m,Player& p,double damage);
ifstream dragonImage("images\\dragon.txt");
ifstream titleImage("images\\title.txt");
ifstream championImage("images\\champion.txt");
ifstream direwolfImage("images\\direwolf.txt");
ifstream skeletonImage("images\\skeleton.txt");
ifstream slimeImage("images\\slime.txt");
ifstream zombieImage("images\\zombie.txt");

ifstream openingStory("story\\opening.txt");
ifstream winStory("story\\win.txt");
ifstream loseStory("story\\lose.txt");

Consumable apple("apple",HEALTH_POINT,15,1);
Consumable magicWine("magicWine",MAGIC_POINT,20,2);
Equipment diamond_sword("diamond_sword",ATTACK_POWER,15,1);
Consumable poison("poison",HEALTH_POINT,-20,1);
Equipment UltimateInvinciblePowerBoots("Ultimate Invincible Power Boots",SPEED,50,1);

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
    PrintOutImage(dragonImage);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintOutImage(titleImage);
    PrintOutStory(openingStory);
    cout << "=========================================================" << endl;
    cout << "【System】: Link Start !!!" << endl;
    cout << "=========================================================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout <<"Enter player name: ";
    cin >> n;
    cout<<"【System】: Welcome "<< n <<endl;

    Player* p = createPlayer(n);
    p->setname(n);

    b.addInventory(new Consumable(apple));
    b.addInventory(new Consumable(magicWine));
    b.addInventory(new Equipment(diamond_sword));
    b.addInventory(new Consumable(poison));
    b.addInventory(new Equipment(UltimateInvinciblePowerBoots));

    cout<<"3"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"2"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"1"<<endl;
    cout << "==================== [ STAGE 1 ] ====================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintOutImage(slimeImage);
    if (!arena(Slime,*p,b)){
        cout<<"Game Over"<<endl;
        PrintOutImage(skeletonImage);
        PrintOutStory(loseStory);
        return 0;
    }else{
        cout << "==================== [ STAGE CLEAR !!! ] ====================" << endl;
    }

    cout << "==================== [ STAGE 2 ] ====================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintOutImage(zombieImage);
    if (!arena(Zombie,*p,b)){
        cout<<"Game Over"<<endl;
        PrintOutImage(skeletonImage);
        PrintOutStory(loseStory);
        return 0;
    }else{
        cout << "==================== [ STAGE CLEAR !!! ] ====================" << endl;
    }

    cout << "==================== [ STAGE 3 ] ====================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintOutImage(direwolfImage);
    if (!arena(DireWolf,*p,b)){
        cout<<"Game Over"<<endl;
        PrintOutImage(skeletonImage);
        PrintOutStory(loseStory);
        return 0;
    }else{
        cout << "==================== [ Youwin !!! ] ====================" << endl;
        PrintOutImage(championImage);
        PrintOutStory(winStory);
    }

  
    delete p;
    return 0;
}

void PrintOutImage(ifstream &image){
    string content;
    if(image.is_open()){
        while(getline(image,content)){
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
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
        cout <<"1. Normal Attack \n" <<"2. Skill\n"<<"3. Use Item\n"<<endl;
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
                if (fireball.getcurrentcd()>0){
                    cout<<"Skills in cooldown!"<<endl;
                    continue;
                }

                fireball.setcooldown();
                p.costmp(20);
                if (PlayerFaster(m,p)){
                    if(PlayerAttack(m,p,fireball.getDamage())){
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
                        break;
                    }
                }
                break;
            case 2:
                if (blackflame.getcurrentcd()>0){
                    cout<<"Skills in cooldown!"<<endl;
                    continue;
                }

                blackflame.setcooldown();
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
                if (lighting.getcurrentcd()>0){
                    cout<<"Skills in cooldown!"<<endl;
                    continue;
                }

                lighting.setcooldown();
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
                b.showBackpackInfo();
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
    return(m.getspeed()<p.getspeed());
}
