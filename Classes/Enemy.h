#ifndef __ENEMY__H__
#define __ENEMY__H__

#include "cocos2d.h"

class Enemy // 怪物的属性基类
{
private:
    int enemy_HP;              
    int HP;    
    double enemy_position_x;
    double enemy_position_y;
    float velocity;            
    int add_coins;             
      
public:
    Enemy();
    virtual ~Enemy();

    // 初始化怪物的生命值, 速度，金币
    void initial(int input_type, int input_HP, float input_velocity, int input_coins, double x, double y);

    // 检查怪物是否活着
    bool alive();

    // 获取增加的金币数量
    int getadd_coins();

    // 获取怪物的横坐标
    double EnemyPositionX();

    // 获取怪物的纵坐标
    double EnemyPositionY();

    // 设置怪物的横坐标
    void set_x(double input_x);

    // 设置怪物的纵坐标
    void set_y(double input_y);

    // 获取怪物的移动速度
    float get_velocity();

    //计算生命值
    void HP_calculate(int damage_per_time);

    // 获取怪物的生命值百分比
    float getHPpercentage();

    int enemytype; // 怪物类型
    bool slowed;   // 是否减速
    float slowedtime; // 减速时间
    bool dizzy;    // 是否眩晕
    float dizzytime; // 眩晕时间
    cocos2d::Sprite* dizzypic; // 眩晕标志

    cocos2d::Sprite* enemySprite; // 怪物的精灵
    cocos2d::Sprite* getSprite(); // 获取怪物精灵

    cocos2d::ProgressTimer* enemyHealthbar; // 怪物血条
    cocos2d::Sprite* enemyHealthbar_back; // 血条背景
};
#endif // __ENEMY__H__