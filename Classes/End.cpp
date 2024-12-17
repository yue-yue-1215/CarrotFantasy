#include "End.h"
#include "Level.h"
#include "Map.h"
#include "PlaceTower.h"

USING_NS_CC;

extern int countnum;
extern bool map_one_finish;
extern bool map_two_finish;
extern bool map_one_continue;
extern bool map_two_continue;
extern int carrot_level;
extern int carrot_HP;

// 创建游戏结束场景
Scene* GameEnd::scene(RenderTexture* sqr)
{
    auto scene = Scene::create();
    auto layer = GameEnd::create();
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

// 初始化游戏结束层
bool GameEnd::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建继续游戏按钮
    auto continueItem = MenuItemImage::create("Continue.png", "Continue.png",
        CC_CALLBACK_1(GameEnd::ContinueGame, this));
    continueItem->setPosition(Vec2(origin.x - 58, origin.y - 15));

    // 创建返回菜单按钮
    auto returnmenuItem = MenuItemImage::create("ReturnMenu.png", "ReturnMenu.png",
        CC_CALLBACK_1(GameEnd::ReturnMenuGame, this));
    returnmenuItem->setPosition(Vec2(origin.x + 10, origin.y - 15));

    // 创建菜单
    Vector<MenuItem*> MenuItems;
    MenuItems.pushBack(continueItem);
    MenuItems.pushBack(returnmenuItem);
    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu, 2);

    // 创建通关图框
    auto successMenu = Sprite::create("Menu.png");
    successMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 15));
    this->addChild(successMenu, 1);

    // 创建通关图片
    auto successPic = Sprite::create("Success.png");
    successPic->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 70));
    this->addChild(successPic, 1);

    return true;
}

// 继续游戏逻辑
void GameEnd::ContinueGame(Ref* pSender)
{
    // 重置游戏状态
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // 弹出当前场景
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();

    // 根据当前地图状态继续游戏
    if (map_one_continue) {
        map_one_finish = true;
        map_one_continue = false;
        auto MyMap = MyMap::createScene();
        Director::getInstance()->pushScene(MyMap);
        auto Game_two = Game_two::createScene();
        Director::getInstance()->pushScene(Game_two);
        map_two_continue = true;
    }
    else if (map_two_continue) {
        map_two_finish = true;
        map_two_continue = false;
        auto MyMap = MyMap::createScene();
        Director::getInstance()->pushScene(MyMap);
    }
}

// 返回菜单逻辑
void GameEnd::ReturnMenuGame(Ref* pSender)
{
    // 重置游戏状态
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // 弹出当前场景
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();

    // 根据当前地图状态返回菜单
    if (map_one_continue) {
        map_one_finish = true;
        map_one_continue = false;
    }
    else if (map_two_continue) {
        map_two_finish = true;
        map_two_continue = false;
    }

    // 进入地图场景
    auto MyMap = MyMap::createScene();
    Director::getInstance()->pushScene(MyMap);
}
