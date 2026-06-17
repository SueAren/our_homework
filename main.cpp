#include <iostream>
#include "item.h"
#include "monster.h"
#include "Player.h"
#include "skill.h"

using std::cout;
using std::cin;
using std::string;

bool PlayerFaster(Monster m,Player p);
bool arena(Monster m,Player p);

int main(){
    Monster m;
    Player p;

    if (!arena(m,p)){
        cout<<"Defeat!!!"<<endl;
    }
    cout << "win!"<<endl;
}

bool arena(Monster m,Player p){
    int round = 1;
    while (p.isAlive()&&m.isAlive())
    {
        int choice;
        cout <<round<<" Round start!"<<endl;
        p.showInfo();
        m.showInfo();
        cout <<"====================="<<endl;
        cout <<"1. Normal Attack \n" <<"2. Skill\n"<<"3. Use Item\n"<<endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (PlayerFaster(m,p)){
                m.takeDamage(p.getattackpower());
                cout << "【" << m.getName() << "】take " << p.getattackpower() << " damage! (left hp: " << m.gethp() << ")" << endl;
                if (!m.isAlive()){ 
                    p.addgold(m.dropgold());
                    cout <<"Succesfully defeat " << m.getName()<<endl;
                    cout<<m.getName()<<"Drop " <<m.dropgold()<<endl;
                    cout<<"You have "<<p.getgold()<<" Gold"<<endl;
                    return true;
                }
                
                p.takeDamage(m.getattackpower());
                cout << "【" << p.getName() << "】take " << m.getattackpower() << " damage! (left hp: " << p.gethp() << ")" << endl;
                if (!p.isAlive()){
                    return false;
                }
            }else{
                p.takeDamage(m.getattackpower());
                cout << "【" << p.getName() << "】take " << m.getattackpower() << " damage! (left hp: " << p.gethp() << ")" << endl;
                if (!p.isAlive()){
                    return false;
                }
                m.takeDamage(p.getattackpower());
                cout << "【" << m.getName() << "】take " << p.getattackpower() << " damage! (left hp: " << m.gethp() << ")" << endl;
                if (!m.isAlive()){
                    p.addgold(m.dropgold());
                    cout <<"Succesfully defeat " << m.getName()<<endl;
                    cout<<m.getName()<<"Drop " <<m.dropgold()<<endl;
                    cout<<"You have "<<p.getgold()<<" Gold"<<endl;   
                    return true;
                }
            }
            break;
        case 2:
            
                break;
        case 3:
            
                break;
                }
            round++;
        
        cout <<"====================="<<endl;
    
    }

}

bool PlayerFaster(Monster m,Player p){
    return(m.getspeed()<p.getspeed());
}

//cout << "【" << name << "】take " << damage << " damage! (left hp: " << hp << ")" << endl;