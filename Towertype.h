#ifndef __TOWER__KIND__H__
#define __TOWER__KIND__H__
#include "Tower.h"
#include <vector>
using namespace std;

// 塔0的升级属性
extern int tower0_upgrade_coins[MAXlevel + 1]; // 塔0各等级升级所需金币
extern int tower0_attack[MAXlevel + 1];       // 塔0各等级攻击力
extern double tower0_attack_range[MAXlevel + 1]; // 塔0各等级攻击范围

// 塔1的升级属性
extern int tower1_upgrade_coins[MAXlevel + 1]; // 塔1各等级升级所需金币
extern int tower1_attack[MAXlevel + 1];       // 塔1各等级攻击力
extern double tower1_attack_range[MAXlevel + 1]; // 塔1各等级攻击范围

// 塔2的升级属性
extern int tower2_upgrade_coins[MAXlevel + 1]; // 塔2各等级升级所需金币
extern int tower2_attack[MAXlevel + 1];       // 塔2各等级攻击力
extern double tower2_attack_range[MAXlevel + 1]; // 塔2各等级攻击范围

// 塔3的升级属性
extern int tower3_upgrade_coins[MAXlevel + 1]; // 塔3各等级升级所需金币
extern int tower3_attack[MAXlevel + 1];       // 塔3各等级攻击力
extern double tower3_attack_range[MAXlevel + 1]; // 塔3各等级攻击范围

// 塔0类，继承自CTower
class Tower0 : public Tower
{
public:
    Tower0();
    virtual ~Tower0();
};

// 塔1类，继承自CTower
class Tower1 : public Tower
{
public:
    Tower1();
    virtual ~Tower1();
};

// 塔2类，继承自CTower
class Tower2 : public Tower
{
public:
    Tower2();
    virtual ~Tower2();
};

// 塔3类，继承自CTower
class Tower3 : public Tower
{
public:
    Tower3();
    virtual ~Tower3();

    // 重写攻击方法
    bool attack(vector<Enemy*>& enemy, int damage_per_time, Enemy*& target) override
    {
        if (!enemy.empty())
        {
            // 存储在攻击范围内的怪物
            vector<Enemy*> enemiesInRange;
            // 查找在攻击范围内的怪物
            for (auto it = enemy.begin(); it != enemy.end(); it++)
            {
                if (inRange(*it))
                {
                    enemiesInRange.push_back(*it);
                }
            }
            // 对所有在范围内的怪物进行攻击
            for (auto it = enemiesInRange.begin(); it != enemiesInRange.end(); it++)
            {
                (*it)->HP_calculate(getDamage());
            }
            return true;
        }
        return false;
    }
};

#endif