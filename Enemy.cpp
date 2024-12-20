#include "Enemy.h"
#include "cocos2d.h"
#include <unordered_map>

// ���캯��
Enemy::Enemy()
    : enemytype(0), enemy_HP(0), HP(0), velocity(0), add_coins(0),
    enemy_position_x(0), enemy_position_y(0), slowed(false),
    slowedtime(0.0), dizzy(false), dizzytime(0.0), enemySprite(nullptr),
    enemyHealthbar(nullptr), enemyHealthbar_back(nullptr), dizzypic(nullptr) {}

// ��������
Enemy::~Enemy() {
    if (enemySprite) {
        enemySprite->removeFromParent(); 
    }
}

// ��ʼ����������ԣ����͡�����ֵ���ٶȡ���Һͳ�����
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

    // ʹ��unordered_map�洢��������
    static const std::unordered_map<int, std::string> enemySpriteMap = {
        {0, "Enemy_zero.png"},
        {1, "Enemy_one.png"},
        {2, "Enemy_two.png"},
        {3, "Enemy_three.png"},
        {4, "Enemy_four.png"}
    };

    // ��ʼ�����ﾫ���Ѫ��
    if (input_type >= 0 && input_type <= 4) {
        enemySprite = cocos2d::Sprite::create(enemySpriteMap.at(input_type));
        enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png"); 
        enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("EnemyHealthBar.png")); 
        dizzypic = cocos2d::Sprite::create("vertigo.png"); 
    }
    else {
        // ������Ͳ�����Ч��Χ�ڣ�����Ϊnullptr
        enemySprite = nullptr;
        enemyHealthbar = nullptr;
        enemyHealthbar_back = nullptr;
    }
}

// �жϹ����Ƿ����
bool Enemy::alive()
{
    return HP > 0;
}

// ��ȡ��ǰ����ֵ�İٷֱ�
float Enemy::getHPpercentage()
{
    return static_cast<float>(HP) / enemy_HP; 
}

// ��ȡ����ĺ�����
double Enemy::EnemyPositionX()
{
    return enemy_position_x; 
}

// ��ȡ�����������
double Enemy::EnemyPositionY()
{
    return enemy_position_y;
}

// ��������ֵ�������ܵ����˺�
void Enemy::HP_calculate(int damage_per_time)
{
    HP -= damage_per_time; 
}

// ���ù���ĺ�����
void Enemy::set_x(double input_x)
{
    enemy_position_x = input_x;
}

// ���ù����������
void Enemy::set_y(double input_y)
{
    enemy_position_y = input_y; 
}

// ��ȡ������ƶ��ٶ�
float Enemy::get_velocity()
{
    return velocity; 
}

// ��ȡ����ľ���
cocos2d::Sprite* Enemy::getSprite()
{
    return enemySprite; 
}

// ��ȡ�������������ӵĽ������
int Enemy::getadd_coins()
{
    return add_coins; 
}