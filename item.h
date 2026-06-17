#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;
class Item {
    public:
        Item(string n = "default item", string t = "HP", double e = 20.0, int q = 1) 
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
            cout << "item: " << name << " | type: " << type 
                 << " | effect: " << effectValue << " | quantity: " << quantity << endl;
        }

        bool isAvailable() const { return quantity > 0; }
        double getEffectValue() const { return effectValue; }
        string getName() const { return name; }

    protected:
        string name;
        string type;
        double effectValue;
        int quantity;
};

#endif