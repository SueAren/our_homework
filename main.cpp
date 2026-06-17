#include <iostream>
#include <thread>
#include "item.h"
#include "monster.h"
#include "Player.h"
#include "skill.h"

using std::cout;
using std::cin;
using std::string;

bool PlayerFaster(Monster& m,Player& p);
bool arena(Monster& m,Player& p);
bool PlayerAttack(Monster& m,Player& p,double damage);
bool MonsterAttack(Monster& m,Player& p,double damage);
Skill fireball("FireBall",25,20);
Skill blackflame("BlackFlame",30,25);
Skill lighting("Lighting",20,20);
// 名稱、血量、傷害、金幣、速度
Monster Zombie("Zombie",100,15,10,70);
Monster DireWolf("DireWolf",50,20,20,110);

int main(){
    Monster m;
    Player p;
    string n;
    cout << "=========================================================" << endl;
    cout << "【System】: Link Start !!!" << endl;
    cout << "=========================================================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout <<"Enter player name: ";
    cin >> n;
    p.setname(n);
    cout<<"【System】: Welcome "<<p.getName()<<endl;


    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout<<"3"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"2"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"1"<<endl;
    cout << "==================== [ STAGE 1 ] ====================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (!arena(m,p)){
        cout<<"Game Over";
    }else{
        cout << "==================== [ STAGE CLEAR !!! ] ====================" << endl;
    }

    cout << "==================== [ STAGE 2 ] ====================" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (!arena(m,p)){
        cout<<"Game Over";
    }else{
        cout << "==================== [ STAGE CLEAR !!! ] ====================" << endl;
    }


    
    
    
    return 0;
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


bool arena(Monster& m,Player& p){
    int round = 1;
    while (p.isAlive()&&m.isAlive())
    {
        int choice;
        int skillchoice;
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
            if (skillchoice==1){
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
            }else if(skillchoice==2){
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
            }else if(skillchoice==3){
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
            }else if(skillchoice==0){
                continue;
            }
            
                break;
        case 3:
            break;
        }

        round++;
    }

    return (p.isAlive()&&!m.isAlive());
}

bool PlayerFaster(Monster& m,Player& p){
    return(m.getspeed()<p.getspeed());
}
