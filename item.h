#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

const string CONSUMABLE = "consumable";
const string EQUIPMENT = "equipment";
class Item {
    public:
        Item(string n = "default item", string t = CONSUMABLE, double e = 20.0, int q = 1) 
            : name(n), type(t), effectValue(e), quantity(q) {}

        void use() {
            if (isAvailable()) {
                cout << "use item【" << name << "】!" << endl;
                quantity--; 
            } else {
                cout << "【" << name << "】not enough!" << endl;
            }
        }

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

    protected:
        string name;
        string type;
        double effectValue;
        int quantity;
};

#endif