#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H
#include <iostream>
#include <string>

using std::cout;
using std::string;

class Achievement{
    private:
        string description;
        bool is_unlock;
    public:
        Achievement(string d = ""):description(d),is_unlock(false){}

        void unlockAchievement(){
            if (!is_unlock){
                cout<<"【System】: unlock an achievement \""<<description<<"\" ,congratulations!\n";
                is_unlock = true;
            }
        }


};


#endif