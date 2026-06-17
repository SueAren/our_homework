#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>

using namespace std;

class Monster {
    public:
        Monster(string n = "slime", double h = 50.0, double a = 50.0, int r = 15,int s = 80) 
            : name(n), hp(h), attackPower(a), rewardGold(r),speed(s) {}

        double getattackpower() const {
            return attackPower;
        }

        int getspeed()const{return speed;}
        double gethp()const{return hp;}
        int dropgold()const{return rewardGold;}

        void takeDamage(double damage) {
            hp -= damage;
            if (hp < 0) hp = 0; 
        }

        bool isAlive() const { return hp > 0; }

        void showInfo() const {
            cout << "Enemy Name: " << name << " \t| Hp: " << hp << " \t| Atk: " << attackPower << " \t| Spd: " << speed << endl;
        }
        
        string getName() const { return name; }

    protected:
        string name;
        double hp;
        double attackPower;
        int rewardGold;
        int speed;
};

#endif