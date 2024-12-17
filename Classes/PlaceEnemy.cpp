#include "Enemy.h"
#include "Enemytype.h"
#include "PlaceEnemy.h"
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
vector<Enemy*> EnemyExist;

// 生成一只怪物
void GenerateEnemy::generateOneEnemy(vector<Enemy*>& EnemyExist, int enemyType, double x, double y)
{
    Enemy* newEnemy = nullptr;

    // 根据敌人类型创建对应的敌人实例
    switch (enemyType) {
        case 0: newEnemy = new Enemy0(); break;
        case 1: newEnemy = new Enemy1(); break;
        case 2: newEnemy = new Enemy2(); break;
        case 3: newEnemy = new Enemy3(); break;
        case 4: newEnemy = new Enemy4(); break;
        default: return; // 不支持的敌人类型直接返回
    }
    newEnemy->set_x(x);
    newEnemy->set_y(y);
    EnemyExist.push_back(newEnemy);
    // 不再删除新创建的敌人，保持在敌人列表中
}

// 删除已死亡的敌人
void GenerateEnemy::deleteEnemy(vector<Enemy*>& EnemyExist)
{
    for (auto it = EnemyExist.begin(); it != EnemyExist.end();)
    {
        if (!(*it)->alive())
        {
            delete* it; // 删除敌人对象
            it = EnemyExist.erase(it); // 从列表中移除
        }
        else
        {
            ++it; // 继续遍历
        }
    }
}

// 统计存活敌人的数量
int GenerateEnemy::numofEnemyAlive(vector<Enemy*>& EnemyExist)
{
    int num = 0;
    for (auto enemy : EnemyExist)
    {
        num += enemy->alive() ? 1 : 0;
    }
    return num;
}

// 生成一波怪物
void GenerateEnemy::generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y)
{
    for (int enemyType : Enemyflag[flag]) 
    {
        generateOneEnemy(EnemyExist, enemyType, x, y);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停生成
    }
}