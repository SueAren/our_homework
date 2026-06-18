#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <string>
#include "item.h"

using std::cout;

class Equipment : public Item {
    protected:

    public:
        Equipment(string n = "default item", string t = HEALTH_POINT, double e = 20.0, int q = 1):Item(n,t,e,q){}
        ~Equipment () = default;
        void use(Player& playerReference) override{
            if(type == HEALTH_POINT){
                playerReference.sethp(playerReference.gethp()+getEffectValue());
                cout<<playerReference.getName()<<" uses "<<getName()<<"!!!!!"<<" and recover for "<<getEffectValue()<<" hp!!!"<<endl;
            }
            else if(type == ATTACK_POWER){
                playerReference.setpower(playerReference.getattackpower()+getEffectValue());
                cout<<playerReference.getName()<<" uses "<<getName()<<"!!!!!"<<" and strengthen for "<<getEffectValue()<<" atk!!!"<<endl;
            }
            else if (type == MAGIC_POINT){
                playerReference.setmp(playerReference.getmp()+getEffectValue());
                cout<<playerReference.getName()<<" uses "<<getName()<<"!!!!!"<<" and recover for "<<getEffectValue()<<" mp!!!"<<endl;
            }
            else if (type == SPEED){
                playerReference.setspeed(playerReference.getspeed()+getEffectValue());
                cout<<playerReference.getName()<<" uses "<<getName()<<"!!!!!"<<" and strengthen for "<<getEffectValue()<<" speed!!!"<<endl;
            }
            quantity --;
        }



};




#endif