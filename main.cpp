#include <iostream>
#include <string>
// 引入你自己寫的標頭檔
#include "Player.h"
#include "Skill.h"
#include "Item.h"
#include "Monster.h"

using namespace std;

int main() {
    // 初始化物件
    Player player;
    Monster monster("哥布林戰士", 60.0, 12.0, 30);
    Skill fireball("火球術", 35.0, 15.0);   
    Item potion("回復藥水", "HP", 30.0, 3); 

    cout << "=== 戰鬥開始！ ===" << endl;
    cout << "遭遇了【" << monster.getName() << "】！\n" << endl;

    // 回合制戰鬥迴圈
    while (player.gethp() > 0 && monster.isAlive()) {
        cout << "-----------------------------------" << endl;
        cout << "[玩家] " << player.getname() << " | HP: " << player.gethp() << " | MP: " << player.getmp() << endl;
        monster.showInfo();
        cout << "-----------------------------------" << endl;
        
        cout << "請選擇行動：\n1. 普通攻擊\n2. 使用技能\n3. 使用物品\n輸入數字選項: ";
        int choice;
        cin >> choice;
        cout << "\n";

        if (choice == 1) {
            cout << "【玩家回合】\n" << player.getname() << " 發動了普通攻擊！" << endl;
            monster.takeDamage(player.getattackpower());
        } 
        else if (choice == 2) {
            cout << "【玩家回合】" << endl;
            if (player.getmp() >= fireball.getMpCost()) {
                fireball.use();
                player.setmp(player.getmp() - fireball.getMpCost());
                monster.takeDamage(fireball.getDamage());
            } else {
                cout << "魔力不足，無法施放技能！" << endl;
                continue; 
            }
        } 
        else if (choice == 3) {
            cout << "【玩家回合】" << endl;
            if (potion.isAvailable()) {
                potion.use();
                player.sethp(player.gethp() + potion.getEffectValue());
                cout << player.getname() << " 恢復了 " << potion.getEffectValue() << " 點 HP！" << endl;
            } else {
                cout << "物品數量不足！" << endl;
                continue; 
            }
        } 
        else {
            cout << "無效選擇，請重新輸入。" << endl;
            continue; 
        }

        // 檢查怪物是否死亡
        if (!monster.isAlive()) {
            cout << "\n🌟 戰鬥勝利！擊敗了【" << monster.getName() << "】！ 🌟" << endl;
            break;
        }

        // 怪物回合
        cout << "\n【怪物回合】" << endl;
        double dmg = monster.attack();
        player.sethp(player.gethp() - dmg);

        // 檢查玩家是否死亡
        if (player.gethp() <= 0) {
            cout << "\n💀 玩家血量歸零，遊戲結束... 💀" << endl;
            break;
        }
        cout << endl;
    }

    return 0;
}