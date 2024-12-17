#ifndef __ENEMY__H__
#define __ENEMY__H__

#include "cocos2d.h"

class Enemy // ��������Ի���
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

    // ��ʼ�����������ֵ, �ٶȣ����
    void initial(int input_type, int input_HP, float input_velocity, int input_coins, double x, double y);

    // �������Ƿ����
    bool alive();

    // ��ȡ���ӵĽ������
    int getadd_coins();

    // ��ȡ����ĺ�����
    double EnemyPositionX();

    // ��ȡ�����������
    double EnemyPositionY();

    // ���ù���ĺ�����
    void set_x(double input_x);

    // ���ù����������
    void set_y(double input_y);

    // ��ȡ������ƶ��ٶ�
    float get_velocity();

    //��������ֵ
    void HP_calculate(int damage_per_time);

    // ��ȡ���������ֵ�ٷֱ�
    float getHPpercentage();

    int enemytype; // ��������
    bool slowed;   // �Ƿ����
    float slowedtime; // ����ʱ��
    bool dizzy;    // �Ƿ�ѣ��
    float dizzytime; // ѣ��ʱ��
    cocos2d::Sprite* dizzypic; // ѣ�α�־

    cocos2d::Sprite* enemySprite; // ����ľ���
    cocos2d::Sprite* getSprite(); // ��ȡ���ﾫ��

    cocos2d::ProgressTimer* enemyHealthbar; // ����Ѫ��
    cocos2d::Sprite* enemyHealthbar_back; // Ѫ������
};
#endif // __ENEMY__H__