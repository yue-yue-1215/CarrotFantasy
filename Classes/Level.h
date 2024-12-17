#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "cocos/math/Vec2.h"
#include "AudioEngine.h"
#include "Enemy.h"
#include "Tower.h"
#include <vector>
using namespace cocos2d;

// 外部变量声明
extern int current_gold_coins; // 当前金币数量
extern Vec2 towerPosition;     // 塔的位置
extern int tower0Clicked;      // 是否点击了塔
extern int already;            // 是否已经执行了某些操作
extern Vec2 mousePosition;     // 鼠标位置

struct Bullet {
    Tower* Tower;         // 发射子弹的塔
    Enemy* Enemy;         // 目标敌人
    Sprite* bulletsprite;  // 子弹的 sprite
    bool flag;             // 标志位，可能用于表示子弹的状态
};

// 游戏场景基类，定义公共接口和成员变量
class GameScene : public Scene {
public:
    // 创建场景的静态方法
    static Scene* createScene();

    // 初始化场景，纯虚函数，需子类实现
    virtual bool init() = 0;

    // 其他纯虚函数，需子类实现
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

    // 成员变量
    Label* mapnum;                        // 地图编号标签
    std::vector<int> flags;               // 标志数组，可能用于记录某些状态
    int current_flag;                     // 当前标志
    std::vector<Bullet> allBulletArray;   // 所有子弹的数组
    Sprite* bulletSprite;                 // 子弹的 sprite

    // 侧边防御塔的图标
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

    // 防御塔组件图标
    Node* layout_delete;
    Node* layout_uplevel;
    Node* layout_return;
    Label* layout_coin;
    Label* layout_nowlevel;
    Sprite* layout_range;

    // 提示标签
    Label* insufficientGoldLabel;  // 金币不足提示
    Label* insufficientPlaceLabel; // 放置位置错误提示
    Label* insufficientLevelLabel; // 等级已满提示

    bool start_generate; // 是否开始生成敌人
    Sprite* board[30]; // 可放置位置的边框
};

class Game_one : public GameScene {
public:
    // 创建 Game_one 场景的静态方法
    static Scene* createScene();

    // 初始化场景，需重写
    bool init() override;

    // 重写基类的纯虚函数
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

    // Game_one 场景中塔的可放置位置
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
    // 创建 Game_two 场景的静态方法
    static Scene* createScene();

    // 初始化场景，需重写
    bool init() override;

    // 重写基类的纯虚函数
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

    // Game_two 场景中塔的可放置位置
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