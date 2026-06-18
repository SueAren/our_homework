#ifndef SKILL_H
#define SKILL_H
#include <iostream>
#include <string>

using namespace std;

class Skill {
    public:
        Skill(string n = "default skill", double d = 10.0, double m = 5.0, int c = 2) 
            : name(n), damage(d), mpCost(m), cooldown(c) {}

        void use() const {
            cout << " use skill【" << name << "】！cost " << mpCost << " mp" << " |Cause "<<damage<<" damage\n"<<endl;
        }

        void showInfo() const {
            cout << "skill: " << name << " | damage: " << damage << " | mpcost: " << mpCost;
            if(currentcooldown>0){
                cout << "| cooldown: " << currentcooldown<< endl;
            }else{
                cout <<"\n";
            }
        }

        double getDamage() const { return damage; }
        double getMpCost() const { return mpCost; }
        string getName() const { return name; }

        int getcurrentcd()const{return currentcooldown;}
        void setcooldown(){ currentcooldown = cooldown;}
        void countcooldown(){currentcooldown--;}

    protected:
        string name;
        double damage;
        double mpCost;
        int cooldown;
        int currentcooldown;
};

#endif