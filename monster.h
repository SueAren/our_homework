#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>

using namespace std;

class Monster {
    public:
        Monster(string n = "slime", double h = 50.0, double a = 10.0, int r = 15) 
            : name(n), hp(h), attackPower(a), rewardGold(r) {}

        double attack() const {
            cout << "【" << name << "】attack! Deal " << attackPower << "damage" << endl;
            return attackPower;
        }

        void takeDamage(double damage) {
            hp -= damage;
            if (hp < 0) hp = 0; 
            cout << "【" << name << "】take " << damage << " damage! (left hp: " << hp << ")" << endl;
        }

        bool isAlive() const { return hp > 0; }

        void showInfo() const {
            cout << "enemy name: " << name << " | hp: " << hp 
                 << " | atk: " << attackPower << endl;
        }
        
        string getName() const { return name; }

    protected:
        string name;
        double hp;
        double attackPower;
        int rewardGold;
};

#endif