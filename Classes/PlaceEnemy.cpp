#include "Enemy.h"
#include "Enemytype.h"
#include "PlaceEnemy.h"
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
vector<Enemy*> EnemyExist;

// ����һֻ����
void GenerateEnemy::generateOneEnemy(vector<Enemy*>& EnemyExist, int enemyType, double x, double y)
{
    Enemy* newEnemy = nullptr;

    // ���ݵ������ʹ�����Ӧ�ĵ���ʵ��
    switch (enemyType) {
        case 0: newEnemy = new Enemy0(); break;
        case 1: newEnemy = new Enemy1(); break;
        case 2: newEnemy = new Enemy2(); break;
        case 3: newEnemy = new Enemy3(); break;
        case 4: newEnemy = new Enemy4(); break;
        default: return; // ��֧�ֵĵ�������ֱ�ӷ���
    }
    newEnemy->set_x(x);
    newEnemy->set_y(y);
    EnemyExist.push_back(newEnemy);
    // ����ɾ���´����ĵ��ˣ������ڵ����б���
}

// ɾ���������ĵ���
void GenerateEnemy::deleteEnemy(vector<Enemy*>& EnemyExist)
{
    for (auto it = EnemyExist.begin(); it != EnemyExist.end();)
    {
        if (!(*it)->alive())
        {
            delete* it; // ɾ�����˶���
            it = EnemyExist.erase(it); // ���б����Ƴ�
        }
        else
        {
            ++it; // ��������
        }
    }
}

// ͳ�ƴ����˵�����
int GenerateEnemy::numofEnemyAlive(vector<Enemy*>& EnemyExist)
{
    int num = 0;
    for (auto enemy : EnemyExist)
    {
        num += enemy->alive() ? 1 : 0;
    }
    return num;
}

// ����һ������
void GenerateEnemy::generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y)
{
    for (int enemyType : Enemyflag[flag]) 
    {
        generateOneEnemy(EnemyExist, enemyType, x, y);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ����
    }
}