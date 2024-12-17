#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "cocos/math/Vec2.h"
#include "AudioEngine.h"
#include "Enemy.h"
#include "Tower.h"
#include <vector>
using namespace cocos2d;

// �ⲿ��������
extern int current_gold_coins; // ��ǰ�������
extern Vec2 towerPosition;     // ����λ��
extern int tower0Clicked;      // �Ƿ�������
extern int already;            // �Ƿ��Ѿ�ִ����ĳЩ����
extern Vec2 mousePosition;     // ���λ��

struct Bullet {
    Tower* Tower;         // �����ӵ�����
    Enemy* Enemy;         // Ŀ�����
    Sprite* bulletsprite;  // �ӵ��� sprite
    bool flag;             // ��־λ���������ڱ�ʾ�ӵ���״̬
};

// ��Ϸ�������࣬���幫���ӿںͳ�Ա����
class GameScene : public Scene {
public:
    // ���������ľ�̬����
    static Scene* createScene();

    // ��ʼ�����������麯����������ʵ��
    virtual bool init() = 0;

    // �������麯����������ʵ��
    virtual void step(float dt) = 0;
    virtual void TowerAttack(float dt) = 0;
    virtual void Enemyupdate(float dt) = 0;
    virtual void carrotHealthUpdate(float dt) = 0;
    virtual void moveBullet(float dt) = 0;

    virtual void Pause(Ref* pSender) = 0;
    virtual void onMouseDown(EventMouse* event) = 0;
    virtual void onMouseDown1(EventMouse* event) = 0;
    virtual void createTower0(const std::string& towerImage, const std::string& towerBackImage, int upgradeCoins, float positionY, int index) = 0;
    virtual int checkTower0Clicked(const Vec2& touchLocation) = 0;
    virtual int getTowerUpgradeCoins(int towerType) = 0;
    virtual void updateGoldCoinsDisplay() = 0;
    virtual void addcoins2(float dt) = 0;
    virtual void showInsufficientGoldLabel() = 0;
    virtual void showInsufficientPlaceLabel() = 0;
    virtual void showInsufficientLevelLabel() = 0;
    virtual void showTowerGrey() = 0;
    virtual void generateOneEnemy(std::vector<Enemy*>& EnemyExist, int enemyType, double x, double y) = 0;
    virtual void generateflag(std::vector<int> flags, double x, double y) = 0;
    virtual void startgenerate(float dt) = 0;

    // ��Ա����
    Label* mapnum;                        // ��ͼ��ű�ǩ
    std::vector<int> flags;               // ��־���飬�������ڼ�¼ĳЩ״̬
    int current_flag;                     // ��ǰ��־
    std::vector<Bullet> allBulletArray;   // �����ӵ�������
    Sprite* bulletSprite;                 // �ӵ��� sprite

    // ��߷�������ͼ��
    Sprite* tower_zero0;
    Sprite* tower_one0;
    Sprite* tower_two0;
    Sprite* tower_three0;
    Sprite* tower_back0;
    Sprite* tower_back1;
    Sprite* tower_back2;
    Sprite* tower_back3;

    Label* buildcoins0;
    Label* buildcoins1;
    Label* buildcoins2;
    Label* buildcoins3;

    // ���������ͼ��
    Node* layout_delete;
    Node* layout_uplevel;
    Node* layout_return;
    Label* layout_coin;
    Label* layout_nowlevel;
    Sprite* layout_range;

    // ��ʾ��ǩ
    Label* insufficientGoldLabel;  // ��Ҳ�����ʾ
    Label* insufficientPlaceLabel; // ����λ�ô�����ʾ
    Label* insufficientLevelLabel; // �ȼ�������ʾ

    bool start_generate; // �Ƿ�ʼ���ɵ���
    Sprite* board[30]; // �ɷ���λ�õı߿�
};

class Game_one : public GameScene {
public:
    // ���� Game_one �����ľ�̬����
    static Scene* createScene();

    // ��ʼ������������д
    bool init() override;

    // ��д����Ĵ��麯��
    void step(float dt) override;
    void TowerAttack(float dt) override;
    void Enemyupdate(float dt) override;
    void carrotHealthUpdate(float dt) override;
    void moveBullet(float dt) override;

    void Pause(Ref* pSender) override;
    void onMouseDown(EventMouse* event) override;
    void onMouseDown1(EventMouse* event) override;
    void createTower0(const std::string& towerImage, const std::string& towerBackImage, int upgradeCoins, float positionY, int index) override;
    int checkTower0Clicked(const Vec2& touchLocation) override;
    int getTowerUpgradeCoins(int towerType) override;
    void updateGoldCoinsDisplay() override;
    void addcoins2(float dt) override;
    void showInsufficientGoldLabel() override;
    void showInsufficientPlaceLabel() override;
    void showInsufficientLevelLabel() override;
    void showTowerGrey() override;
    void generateOneEnemy(std::vector<Enemy*>& EnemyExist, int enemyType, double x, double y) override;
    void generateflag(std::vector<int> flags, double x, double y) override;
    void startgenerate(float dt) override;

    // Game_one ���������Ŀɷ���λ��
    const Vec2 pairxy[23] = {
        Vec2(155,211), Vec2(190,211), Vec2(190,177), Vec2(190,211), Vec2(225,211),
        Vec2(225,177), Vec2(225,143), Vec2(225,109), Vec2(225,75), Vec2(225,41),
        Vec2(260,41), Vec2(295,41), Vec2(330,41), Vec2(365,41), Vec2(400,41),
        Vec2(295,109), Vec2(330,109), Vec2(365,109), Vec2(400,109), Vec2(295,143),
        Vec2(295,177), Vec2(295,211), Vec2(295,245)
    };
    CREATE_FUNC(Game_one);
};

class Game_two : public GameScene {
public:
    // ���� Game_two �����ľ�̬����
    static Scene* createScene();

    // ��ʼ������������д
    bool init() override;

    // ��д����Ĵ��麯��
    void step(float dt) override;
    void TowerAttack(float dt) override;
    void Enemyupdate(float dt) override;
    void carrotHealthUpdate(float dt) override;
    void moveBullet(float dt) override;

    void Pause(Ref* pSender) override;
    void onMouseDown(EventMouse* event) override;
    void onMouseDown1(EventMouse* event) override;
    void createTower0(const std::string& towerImage, const std::string& towerBackImage, int upgradeCoins, float positionY, int index) override;
    int checkTower0Clicked(const Vec2& touchLocation) override;
    int getTowerUpgradeCoins(int towerType) override;
    void updateGoldCoinsDisplay() override;
    void addcoins2(float dt) override;
    void showInsufficientGoldLabel() override;
    void showInsufficientPlaceLabel() override;
    void showInsufficientLevelLabel() override;
    void showTowerGrey() override;
    void generateOneEnemy(std::vector<Enemy*>& EnemyExist, int enemyType, double x, double y) override;
    void generateflag(std::vector<int> flags, double x, double y) override;
    void startgenerate(float dt) override;

    // Game_two ���������Ŀɷ���λ��
    const Vec2 pairxy[27] = {
        Vec2(128,28), Vec2(162,28), Vec2(196,28), Vec2(230,28), Vec2(264,28),
        Vec2(298,28), Vec2(332,28), Vec2(366,28), Vec2(128,72), Vec2(128,160),
        Vec2(128,204), Vec2(128,116), Vec2(196,116), Vec2(230,116), Vec2(264,116),
        Vec2(298,116), Vec2(332,116), Vec2(366,116), Vec2(162,204), Vec2(196,204),
        Vec2(230,204), Vec2(264,204), Vec2(298,204), Vec2(332,204), Vec2(400,204),
        Vec2(400,248), Vec2(400,160)
    };
    CREATE_FUNC(Game_two);
};
#endif