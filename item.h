#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

const string HEALTH_POINT = "healthPoint";
const string ATTACK_POWER = "attackPower";
const string MAGIC_POINT = "magicPoint";
const string SPEED = "speed";


class Item {
    public:
        Item(string n = "default item", string t = HEALTH_POINT, double e = 20.0, int q = 1) 
            : name(n), type(t), effectValue(e), quantity(q) {}
        virtual ~Item() = default;
        virtual void use(Player& playerReference) {cout<<"114514";}

        void showInfo() const {
            cout<<"==============================\n"
                <<"|item: " << name <<endl
                <<"|type: " << type <<endl 
                <<"|effect: " << effectValue <<endl
                <<"|quantity: " << quantity << endl
                <<"==============================\n";
        }

        bool isAvailable() const { return quantity > 0; }
        double getEffectValue() const { return effectValue; }
        string getName() const { return name;}
        string getType() const { return type;}
        int getQuantity() const { return quantity;}

    protected:
        string name;
        string type;
        double effectValue;
        int quantity;
};

#endif
