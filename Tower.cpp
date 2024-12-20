#include "Tower.h"
#include "Enemy.h"
#include <ctime>
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

// 设置防御塔位置
void Tower::setPosition(int x, int y) {
    tower_position_x = x;
    tower_position_y = y;
}

int Tower::getType() const {
    return Type;
}

// 获取防御塔位置
double Tower::getPositionX() {
    return tower_position_x;
}

double Tower::getPositionY() {
    return tower_position_y;
}

// 获取防御塔等级
int Tower::getLevel() {
    return tower_level;
}

// 获取防御塔伤害
int Tower::getDamage() {
    return damage_per_time[getLevel()];
}

// 获取防御塔攻击范围
int Tower::getAttackRange() {
    return attck_range[getLevel()];
}

// 获取防御塔升级所需金币
int Tower::getUpgradeCost() {
    return coins_to_level_up[getLevel()];
}

// 升级防御塔并消耗金币
bool Tower::upgrade(int& gold_coins) {
    int cost = getUpgradeCost();
    if (gold_coins >= cost) {
        gold_coins -= cost;
        tower_level++;
        return true;
    }
    return false;
}

// 检查敌人是否在攻击范围内
bool Tower::inRange(Enemy* enemy) {
    double dx = enemy->EnemyPositionX() - getPositionX();
    double dy = enemy->EnemyPositionY() - getPositionY();
    return (dx * dx + dy * dy <= getAttackRange() * getAttackRange() && enemy->EnemyPositionX() <= 420);
}

// 寻找距离指定位置最近的敌人
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

// 攻击范围内最近的敌人并减少血量
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