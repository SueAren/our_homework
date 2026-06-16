#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Player{
    public:
        Player():name("Unkown"),hp(100),attackPower(5),mp(100){}//預設數值
        string getname(){return name;}
        void sethp(double h){hp = h;}
        void setpower(double p){attackPower = p;}
        void setmp(double m){mp = m;}
        double gethp()const{return hp;}
        double getattackpower()const{return attackPower;}
        double getmp()const{return mp;}
    protected:
        std::string name;
        double hp;
        double attackPower;
        double mp;//法力值
};

#endif