#ifndef __TOWER__H__
#define __TOWER__H__
#include "Enemy.h"
#include <vector>
#include "cocos2d.h"
#define MAXlevel 4
using namespace std;

class Tower {  // ��������
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

    // ��ʼ������������
    void initial(int type, int input_tower_level, int input_coins_to_level_up[],
        int input_damage_per_time[], double input_attck_range[], bool input_group_damage) {
        Type = type;
        tower_level = input_tower_level;
        copy(input_coins_to_level_up, input_coins_to_level_up + MAXlevel, coins_to_level_up);
        copy(input_damage_per_time, input_damage_per_time + MAXlevel + 1, damage_per_time);
        copy(input_attck_range, input_attck_range + MAXlevel + 1, attck_range);
        group_damage = input_group_damage;
    }

    double getPositionX();  // ��ȡ������
    double getPositionY();  // ��ȡ������
    bool upgrade(int& gold_coins);  // ����������
    virtual bool attack(vector<Enemy*>& enemy, int damage_per_time, Enemy*& target);  // ��������
    void setPosition(int x, int y);  // ���÷�����λ��
    int getType() const;  // ��ȡ����������
    int getLevel();  // ��ȡ��ǰ�ȼ�
    int getDamage();  // ��ȡ��ǰ�˺�
    int getAttackRange();  // ��ȡ������Χ
    bool inRange(Enemy* enemy);  // �������Ƿ��ڹ�����Χ��
    int getUpgradeCost();  // ��ȡ����������
    Enemy* nearestEnemy(vector<Enemy*>& enemy, int positionx, int positiony);  // Ѱ������ĵ���
};
#endif