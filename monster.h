#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>

using namespace std;

class Monster {
    public:
        Monster(string n = "史萊姆", double h = 50.0, double a = 10.0, int r = 15) 
            : name(n), hp(h), attackPower(a), rewardGold(r) {}

        double attack() const {
            cout << "怪物【" << name << "】發起了攻擊！造成了 " << attackPower << " 點傷害。" << endl;
            return attackPower;
        }

        void takeDamage(double damage) {
            hp -= damage;
            if (hp < 0) hp = 0; 
            cout << "怪物【" << name << "】受到了 " << damage << " 點傷害！(剩餘血量: " << hp << ")" << endl;
        }

        bool isAlive() const { return hp > 0; }

        void showInfo() const {
            cout << "怪物名稱: " << name << " | 血量: " << hp 
                 << " | 攻擊力: " << attackPower << endl;
        }
        
        string getName() const { return name; }

    protected:
        string name;
        double hp;
        double attackPower;
        int rewardGold;
};

#endif