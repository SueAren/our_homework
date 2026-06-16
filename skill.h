#ifndef SKILL_H
#define SKILL_H
#include <iostream>
#include <string>

using namespace std;

class Skill {
    public:
        Skill(string n = "預設技能", double d = 10.0, double m = 5.0) 
            : name(n), damage(d), mpCost(m) {}

        void use() const {
            cout << "施放了技能【" << name << "】！消耗了 " << mpCost << " 點魔力。" << endl;
        }

        void showInfo() const {
            cout << "技能名稱: " << name << " | 傷害: " << damage << " | 魔力消耗: " << mpCost << endl;
        }

        double getDamage() const { return damage; }
        double getMpCost() const { return mpCost; }
        string getName() const { return name; }

    protected:
        string name;
        double damage;
        double mpCost;
};

#endif