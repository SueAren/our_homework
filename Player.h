#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Player{
    public:
        Player():name("Unkown"),hp(100),attackPower(5),mp(100),speed(100),gold(0){}//預設數值
        Player(string n,double h,double a,double m,double s,int g):name("Unkown"),hp(h),attackPower(a),mp(m),speed(s),gold(g){}
        string getName(){return name;}
        void sethp(double h){hp = h;}
        void setpower(double p){attackPower = p;}
        void setmp(double m){mp = m;}
        void setname(string n){name = n;}

        double gethp()const{return hp;}
        double getattackpower()const{return attackPower;}
        double getmp()const{return mp;}
        int getspeed()const{return speed;}
        int getgold()const{return gold;}

        void takeDamage(double damage) {
            hp -= damage;
            if (hp < 0) hp = 0; 
        }

        void showInfo() const {
            cout << "Player Name: " << name << " \t| Hp: " << hp << " \t| Atk: " << attackPower << " \t| Spd: " << speed <<" \t| Gold: " << gold << endl;
        }

        bool isAlive() const { return hp > 0; }

        void addgold(int g){gold += g;}
        

    protected:
        std::string name;
        double hp;
        double attackPower;
        double mp;//法力值
        int speed;
        int gold;
};

#endif