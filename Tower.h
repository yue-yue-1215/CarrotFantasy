#ifndef __TOWER__H__
#define __TOWER__H__
#include "Enemy.h"
#include <vector>
#include "cocos2d.h"
#define MAXlevel 4
using namespace std;

class Tower {  // 防御塔类
private:
    int Type; 
    int tower_level;  
    int coins_to_level_up[MAXlevel]; 
    int damage_per_time[MAXlevel + 1];  
    double attck_range[MAXlevel + 1]; 
    int tower_position_x; 
    int tower_position_y; 
    bool group_damage; 

public:
    Tower() {
        tower_level = 0;
        fill(begin(coins_to_level_up), end(coins_to_level_up), 0);
        fill(begin(damage_per_time), end(damage_per_time), 0);
        fill(begin(attck_range), end(attck_range), 0);
        tower_position_x = -1;
        tower_position_y = -1;
        group_damage = false;
    }
    ~Tower() {}

    // 初始化防御塔属性
    void initial(int type, int input_tower_level, int input_coins_to_level_up[],
        int input_damage_per_time[], double input_attck_range[], bool input_group_damage) {
        Type = type;
        tower_level = input_tower_level;
        copy(input_coins_to_level_up, input_coins_to_level_up + MAXlevel, coins_to_level_up);
        copy(input_damage_per_time, input_damage_per_time + MAXlevel + 1, damage_per_time);
        copy(input_attck_range, input_attck_range + MAXlevel + 1, attck_range);
        group_damage = input_group_damage;
    }

    double getPositionX();  // 获取横坐标
    double getPositionY();  // 获取纵坐标
    bool upgrade(int& gold_coins);  // 升级防御塔
    virtual bool attack(vector<Enemy*>& enemy, int damage_per_time, Enemy*& target);  // 攻击敌人
    void setPosition(int x, int y);  // 设置防御塔位置
    int getType() const;  // 获取防御塔种类
    int getLevel();  // 获取当前等级
    int getDamage();  // 获取当前伤害
    int getAttackRange();  // 获取攻击范围
    bool inRange(Enemy* enemy);  // 检查敌人是否在攻击范围内
    int getUpgradeCost();  // 获取升级所需金币
    Enemy* nearestEnemy(vector<Enemy*>& enemy, int positionx, int positiony);  // 寻找最近的敌人
};
#endif