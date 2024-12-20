#include "Tower.h"
#include "Enemy.h"
#include <ctime>
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

// ���÷�����λ��
void Tower::setPosition(int x, int y) {
    tower_position_x = x;
    tower_position_y = y;
}

int Tower::getType() const {
    return Type;
}

// ��ȡ������λ��
double Tower::getPositionX() {
    return tower_position_x;
}

double Tower::getPositionY() {
    return tower_position_y;
}

// ��ȡ�������ȼ�
int Tower::getLevel() {
    return tower_level;
}

// ��ȡ�������˺�
int Tower::getDamage() {
    return damage_per_time[getLevel()];
}

// ��ȡ������������Χ
int Tower::getAttackRange() {
    return attck_range[getLevel()];
}

// ��ȡ����������������
int Tower::getUpgradeCost() {
    return coins_to_level_up[getLevel()];
}

// ���������������Ľ��
bool Tower::upgrade(int& gold_coins) {
    int cost = getUpgradeCost();
    if (gold_coins >= cost) {
        gold_coins -= cost;
        tower_level++;
        return true;
    }
    return false;
}

// �������Ƿ��ڹ�����Χ��
bool Tower::inRange(Enemy* enemy) {
    double dx = enemy->EnemyPositionX() - getPositionX();
    double dy = enemy->EnemyPositionY() - getPositionY();
    return (dx * dx + dy * dy <= getAttackRange() * getAttackRange() && enemy->EnemyPositionX() <= 420);
}

// Ѱ�Ҿ���ָ��λ������ĵ���
Enemy* Tower::nearestEnemy(vector<Enemy*>& enemy, int positionx, int positiony) {
    if (enemy.empty()) return nullptr;

    Enemy* nearest = enemy[0];
    for (size_t i = 1; i < enemy.size(); i++) {
        double dx = enemy[i]->EnemyPositionX() - positionx;
        double dy = enemy[i]->EnemyPositionY() - positiony;
        double nearestDx = nearest->EnemyPositionX() - positionx;
        double nearestDy = nearest->EnemyPositionY() - positiony;

        if (dx * dx + dy * dy < nearestDx * nearestDx + nearestDy * nearestDy) {
            nearest = enemy[i];
        }
    }
    return nearest;
}

// ������Χ������ĵ��˲�����Ѫ��
bool Tower::attack(vector<Enemy*>& enemy, int damage_per_time, Enemy*& target) {
    if (enemy.empty()) return false;

    vector<Enemy*> enemiesInRange;
    for (auto it = enemy.begin(); it != enemy.end(); it++) {
        if (inRange(*it)) {
            enemiesInRange.push_back(*it);
        }
    }

    target = nearestEnemy(enemiesInRange, 75, 420);
    return target != nullptr; 
}