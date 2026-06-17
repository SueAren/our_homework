#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

class Item {
    public:
        Item(string n = "預設物品", string t = "HP", double e = 20.0, int q = 1) 
            : name(n), type(t), effectValue(e), quantity(q) {}

        void use() {
            if (isAvailable()) {
                cout << "使用了物品【" << name << "】！" << endl;
                quantity--; 
            } else {
                cout << "【" << name << "】數量不足，無法使用！" << endl;
            }
        }

        void showInfo() const {
            cout << "物品名稱: " << name << " | 類型: " << type 
                 << " | 效果數值: " << effectValue << " | 數量: " << quantity << endl;
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