#ifndef BACKPACK_H
#define BACKPACK_H
#include <vector>


#include "item.h"


using std::cout;
using std::vector;
class Backpack{
    protected:
        int gold;
        vector <Item> inventory;

    public:
        Backpack(int g = 0,vector <Item> c = {}) : gold(g),inventory(c){}
        int getGold(){return gold;}
        int getInventory(){return inventory.size();}


        void addgold(int g){gold += g;}
        void addInventory(Item goods){
            inventory.push_back(goods);
        }




        void showBackpackInfo(){
            cout<<"================================================\n"
                <<"Inventory:\n";
            cout<<"current gold:"<<getGold()<<"\n";
            if (getInventory()>0){
                for (int i = 0;i<getInventory();i++){
                    cout<<i+1<<"."<<inventory[i].getName()<<"\n";
                }
            }
            cout<<"================================================\n";
        }


};







#endif