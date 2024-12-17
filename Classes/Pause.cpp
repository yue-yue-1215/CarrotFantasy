#include "Level.h"
#include "Pause.h"
#include "PlaceTower.h"

USING_NS_CC;

extern int countnum;
extern bool map_one_continue;
extern bool map_two_continue;
extern int carrot_level;
extern int carrot_HP;

// 创建游戏暂停场景
Scene* Pause::scene(RenderTexture* sqr)
{
    auto scene = Scene::create();
    auto layer = Pause::create();
    scene->addChild(layer, 1);

    // 创建背景截图
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    back_sqr->setPosition(Vec2(visibleSize.width / 2 + 24, visibleSize.height / 2));
    back_sqr->setFlippedY(true); // 翻转Y轴以适应UI坐标
    back_sqr->setColor(Color3B(80, 80, 80)); // 设置为灰色
    scene->addChild(back_sqr);

    return scene;
}

// 初始化游戏暂停层
bool Pause::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建继续游戏按钮
    auto continueItem = MenuItemImage::create("Continue.png", "Continue.png",
        CC_CALLBACK_1(Pause::ContinueGame, this));
    continueItem->setPosition(Vec2(origin.x - 70, origin.y + 2));

    // 创建重新开始按钮
    auto restartItem = MenuItemImage::create("Restart.png", "Restart.png",
        CC_CALLBACK_1(Pause::RestartGame, this));
    restartItem->setPosition(Vec2(origin.x - 23, origin.y + 2));

    // 创建返回菜单按钮
    auto returnmenuItem = MenuItemImage::create("ReturnMenu.png", "ReturnMenu.png",
        CC_CALLBACK_1(Pause::ReturnMenuGame, this));
    returnmenuItem->setPosition(Vec2(origin.x + 23, origin.y + 2));

    // 创建暂停图框
    auto pauseMenu = Sprite::create("Pause.png");
    pauseMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 10));
    this->addChild(pauseMenu, 1);

    // 创建菜单
    Vector<MenuItem*> MenuItems;
    MenuItems.pushBack(continueItem);
    MenuItems.pushBack(restartItem);
    MenuItems.pushBack(returnmenuItem);
    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu, 2);

    return true;
}

// 返回上一页面
void Pause::ContinueGame(Ref* pSender)
{
    Director::getInstance()->popScene();
}

// 重新开始游戏
void Pause::RestartGame(Ref* pSender)
{
    // 重置游戏状态
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // 弹出当前场景并重新加载游戏场景
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    if (map_one_continue) {
        auto Game_one = Game_one::createScene();
        Director::getInstance()->pushScene(Game_one);
    }
    if (map_two_continue) {
        auto Game_two = Game_two::createScene();
        Director::getInstance()->pushScene(Game_two);
    }
}

// 返回菜单
void Pause::ReturnMenuGame(Ref* pSender)
{
    // 重置游戏状态
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // 弹出当前场景并返回菜单
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    if (map_one_continue)
        map_one_continue = false;
    if (map_two_continue)
        map_two_continue = false;
}