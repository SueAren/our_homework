#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
#include "Player.h"

using std::string;

class Knight:public Player{
    public:
        Knight(string n):Player(n,115,15,40,100,0){}
};

class Mage:public Player{
    public:
        Mage(string n):Player(n,70,20,150,70,0){}
        void addmp(){mp +=15;}
};

class Monk:public Player{
    public:
        Monk(string n):Player(n,200,10,100,90,0){}
};


#endif