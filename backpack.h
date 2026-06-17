#ifndef BACKPACK_H
#define BACKPACK_H
#include <iostream>
#include <vector>
#include <algorithm>


#include "consumable.h"


using std::cout;
using std::vector;
class Backpack{
    protected:
        int gold;
        vector <Item*> inventory;

    public:
        Backpack(int g = 0,vector <Item*> c = {}) : gold(g),inventory(c){}
        ~Backpack(){
            for(Item* item : inventory){
                delete item;
            }
            inventory.clear();
        }
        int getGold(){return gold;}
        int getInventorySize(){return inventory.size();}


        void addgold(int g){gold += g;}

        void addInventory(Item* goods){
            inventory.push_back(goods);
        }
        void removeInventory(){
            for (auto it = inventory.begin(); it != inventory.end(); ){
                if (!(*it)->isAvailable()){
                    delete *it;
                    it = inventory.erase(it);
                }
                else{
                    ++it;
                }
            }
        }


        Item& getSpecifyItem(int location){
            return *inventory[location];
        }

        void showBackpackInfo(){
            cout<<"================================================\n"
                <<"Inventory:\n";
            cout<<"current gold:"<<getGold()<<"\n";
            if (getInventorySize()>0){
                for (int i = 0;i<getInventorySize();i++){
                    cout<<i+1<<"."<<inventory[i]->getName()<<"\n";
                }
            }
            cout<<"================================================\n";
        }


};







#endif