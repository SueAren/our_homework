#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Player{
    public:
        Player():name("Unkown"),hp(20),attackPower(5),mp(100){}//預設數值
        Player(string n,double h,double a,double m):name("Unkown"),hp(h),attackPower(a),mp(m){}//預設數值
        string getname(){return name;}
        void sethp(double h){hp = h;}
        void setpower(double p){attackPower = p;}
        void setmp(double m){mp = m;}
        virtual double gethp()const{return hp;}
        virtual double getattack()const{return attackPower;}
        virtual double getmp()const{return mp;}
    protected:
        std::string name;
        double hp;
        double attackPower;
        double mp;//法力值
};

#endif