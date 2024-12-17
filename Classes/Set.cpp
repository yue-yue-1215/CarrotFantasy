#include "Set.h"
#include "Level.h"
#include "Map.h"
#include "PlaceTower.h"

USING_NS_CC;

extern int countnum;
extern int carrot_level;
extern int carrot_HP;

Scene* Default::scene(RenderTexture* sqr)
{
    Scene* scene = Scene::create();
    Default* layer = Default::create();
    scene->addChild(layer, 1);

    // 创建Sprite，使用Game界面截图的纹理
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    back_sqr->setPosition(Vec2(visibleSize.width / 2 + 24, visibleSize.height / 2));
    back_sqr->setFlippedY(true); // 翻转Y轴
    back_sqr->setColor(Color3B(80, 80, 80)); // 设置为灰色
    scene->addChild(back_sqr);

    return scene;
}

extern bool map_one_finish;
extern bool map_two_finish;
extern bool map_one_continue;
extern bool map_two_continue;

bool Default::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建重新开始按钮
    auto restartItem = MenuItemImage::create("Restart.png", "Restart.png", CC_CALLBACK_1(Default::RestartGame, this));
    restartItem->setPosition(Vec2(origin.x - 58, origin.y - 15));

    // 创建返回菜单按钮
    auto returnmenuItem = MenuItemImage::create("ReturnMenu.png", "ReturnMenu.png", CC_CALLBACK_1(Default::ReturnMenuGame, this));
    returnmenuItem->setPosition(Vec2(origin.x + 10, origin.y - 15));

    // 创建通关图框
    auto defaultMenu = Sprite::create("Menu.png");
    defaultMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 15));
    this->addChild(defaultMenu, 1);

    // 创建默认图片
    auto defaultPic = Sprite::create("Default.png");
    defaultPic->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 70));
    this->addChild(defaultPic, 1);

    // 创建菜单
    Vector<MenuItem*> MenuItems;
    MenuItems.pushBack(restartItem);
    MenuItems.pushBack(returnmenuItem);
    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu, 2);

    return true;
}

// 返回菜单
void Default::ReturnMenuGame(Ref* pSender)
{
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();

    if (map_one_continue)
        map_one_continue = false;
    else if (map_two_continue)
        map_two_continue = false;

    auto MyMap = MyMap::createScene();
    Director::getInstance()->pushScene(MyMap);
}

// 重新开始游戏
void Default::RestartGame(Ref* pSender)
{
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

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