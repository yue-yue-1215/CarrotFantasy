#include "Enemy.h"
#include "cocos2d.h"
#include <unordered_map>

// 构造函数
Enemy::Enemy()
    : enemytype(0), enemy_HP(0), HP(0), velocity(0), add_coins(0),
    enemy_position_x(0), enemy_position_y(0), slowed(false),
    slowedtime(0.0), dizzy(false), dizzytime(0.0), enemySprite(nullptr),
    enemyHealthbar(nullptr), enemyHealthbar_back(nullptr), dizzypic(nullptr) {}

// 析构函数
Enemy::~Enemy() {
    if (enemySprite) {
        enemySprite->removeFromParent(); 
    }
}

// 初始化怪物的属性，类型、生命值、速度、金币和出生点
void Enemy::initial(int input_type, int input_HP, float input_velocity,
    int input_coins, double x, double y)
{
    enemytype = input_type; 
    enemy_HP = input_HP;    
    HP = enemy_HP;          
    velocity = input_velocity;
    add_coins = input_coins; 
    enemy_position_x = x;    
    enemy_position_y = y;    

    // 使用unordered_map存储怪物类型
    static const std::unordered_map<int, std::string> enemySpriteMap = {
        {0, "Enemy_zero.png"},
        {1, "Enemy_one.png"},
        {2, "Enemy_two.png"},
        {3, "Enemy_three.png"},
        {4, "Enemy_four.png"}
    };

    // 初始化怪物精灵和血条
    if (input_type >= 0 && input_type <= 4) {
        enemySprite = cocos2d::Sprite::create(enemySpriteMap.at(input_type));
        enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png"); 
        enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("EnemyHealthBar.png")); 
        dizzypic = cocos2d::Sprite::create("vertigo.png"); 
    }
    else {
        // 如果类型不在有效范围内，设置为nullptr
        enemySprite = nullptr;
        enemyHealthbar = nullptr;
        enemyHealthbar_back = nullptr;
    }
}

// 判断怪物是否活着
bool Enemy::alive()
{
    return HP > 0;
}

// 获取当前生命值的百分比
float Enemy::getHPpercentage()
{
    return static_cast<float>(HP) / enemy_HP; 
}

// 获取怪物的横坐标
double Enemy::EnemyPositionX()
{
    return enemy_position_x; 
}

// 获取怪物的纵坐标
double Enemy::EnemyPositionY()
{
    return enemy_position_y;
}

// 计算生命值，减少受到的伤害
void Enemy::HP_calculate(int damage_per_time)
{
    HP -= damage_per_time; 
}

// 设置怪物的横坐标
void Enemy::set_x(double input_x)
{
    enemy_position_x = input_x;
}

// 设置怪物的纵坐标
void Enemy::set_y(double input_y)
{
    enemy_position_y = input_y; 
}

// 获取怪物的移动速度
float Enemy::get_velocity()
{
    return velocity; 
}

// 获取怪物的精灵
cocos2d::Sprite* Enemy::getSprite()
{
    return enemySprite; 
}

// 获取怪物死亡后增加的金币数量
int Enemy::getadd_coins()
{
    return add_coins; 
}