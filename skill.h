#ifndef SKILL_H
#define SKILL_H
#include <iostream>
#include <string>

using namespace std;

class Skill {
    public:
        Skill(string n = "default skill", double d = 10.0, double m = 5.0) 
            : name(n), damage(d), mpCost(m) {}

        void use() const {
            cout << "use skill【" << name << "】！cost " << mpCost << " mp" << endl;
        }

        void showInfo() const {
            cout << "skill: " << name << " | damage: " << damage << " | mpcost: " << mpCost << endl;
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