#ifndef __TOWER__KIND__H__
#define __TOWER__KIND__H__
#include "Tower.h"
#include <vector>
using namespace std;

// ��0����������
extern int tower0_upgrade_coins[MAXlevel + 1]; // ��0���ȼ�����������
extern int tower0_attack[MAXlevel + 1];       // ��0���ȼ�������
extern double tower0_attack_range[MAXlevel + 1]; // ��0���ȼ�������Χ

// ��1����������
extern int tower1_upgrade_coins[MAXlevel + 1]; // ��1���ȼ�����������
extern int tower1_attack[MAXlevel + 1];       // ��1���ȼ�������
extern double tower1_attack_range[MAXlevel + 1]; // ��1���ȼ�������Χ

// ��2����������
extern int tower2_upgrade_coins[MAXlevel + 1]; // ��2���ȼ�����������
extern int tower2_attack[MAXlevel + 1];       // ��2���ȼ�������
extern double tower2_attack_range[MAXlevel + 1]; // ��2���ȼ�������Χ

// ��3����������
extern int tower3_upgrade_coins[MAXlevel + 1]; // ��3���ȼ�����������
extern int tower3_attack[MAXlevel + 1];       // ��3���ȼ�������
extern double tower3_attack_range[MAXlevel + 1]; // ��3���ȼ�������Χ

// ��0�࣬�̳���CTower
class Tower0 : public Tower
{
public:
    Tower0();
    virtual ~Tower0();
};

// ��1�࣬�̳���CTower
class Tower1 : public Tower
{
public:
    Tower1();
    virtual ~Tower1();
};

// ��2�࣬�̳���CTower
class Tower2 : public Tower
{
public:
    Tower2();
    virtual ~Tower2();
};

// ��3�࣬�̳���CTower
class Tower3 : public Tower
{
public:
    Tower3();
    virtual ~Tower3();

    // ��д��������
    bool attack(vector<Enemy*>& enemy, int damage_per_time, Enemy*& target) override
    {
        if (!enemy.empty())
        {
            // �洢�ڹ�����Χ�ڵĹ���
            vector<Enemy*> enemiesInRange;
            // �����ڹ�����Χ�ڵĹ���
            for (auto it = enemy.begin(); it != enemy.end(); it++)
            {
                if (inRange(*it))
                {
                    enemiesInRange.push_back(*it);
                }
            }
            // �������ڷ�Χ�ڵĹ�����й���
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