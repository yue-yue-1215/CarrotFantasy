#include "Level.h"
#include "Pause.h"
#include "PlaceTower.h"

USING_NS_CC;

extern int countnum;
extern bool map_one_continue;
extern bool map_two_continue;
extern int carrot_level;
extern int carrot_HP;

// ������Ϸ��ͣ����
Scene* Pause::scene(RenderTexture* sqr)
{
    auto scene = Scene::create();
    auto layer = Pause::create();
    scene->addChild(layer, 1);

    // ����������ͼ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    back_sqr->setPosition(Vec2(visibleSize.width / 2 + 24, visibleSize.height / 2));
    back_sqr->setFlippedY(true); // ��תY������ӦUI����
    back_sqr->setColor(Color3B(80, 80, 80)); // ����Ϊ��ɫ
    scene->addChild(back_sqr);

    return scene;
}

// ��ʼ����Ϸ��ͣ��
bool Pause::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����������Ϸ��ť
    auto continueItem = MenuItemImage::create("Continue.png", "Continue.png",
        CC_CALLBACK_1(Pause::ContinueGame, this));
    continueItem->setPosition(Vec2(origin.x - 70, origin.y + 2));

    // �������¿�ʼ��ť
    auto restartItem = MenuItemImage::create("Restart.png", "Restart.png",
        CC_CALLBACK_1(Pause::RestartGame, this));
    restartItem->setPosition(Vec2(origin.x - 23, origin.y + 2));

    // �������ز˵���ť
    auto returnmenuItem = MenuItemImage::create("ReturnMenu.png", "ReturnMenu.png",
        CC_CALLBACK_1(Pause::ReturnMenuGame, this));
    returnmenuItem->setPosition(Vec2(origin.x + 23, origin.y + 2));

    // ������ͣͼ��
    auto pauseMenu = Sprite::create("Pause.png");
    pauseMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 10));
    this->addChild(pauseMenu, 1);

    // �����˵�
    Vector<MenuItem*> MenuItems;
    MenuItems.pushBack(continueItem);
    MenuItems.pushBack(restartItem);
    MenuItems.pushBack(returnmenuItem);
    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu, 2);

    return true;
}

// ������һҳ��
void Pause::ContinueGame(Ref* pSender)
{
    Director::getInstance()->popScene();
}

// ���¿�ʼ��Ϸ
void Pause::RestartGame(Ref* pSender)
{
    // ������Ϸ״̬
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // ������ǰ���������¼�����Ϸ����
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

// ���ز˵�
void Pause::ReturnMenuGame(Ref* pSender)
{
    // ������Ϸ״̬
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // ������ǰ���������ز˵�
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    if (map_one_continue)
        map_one_continue = false;
    if (map_two_continue)
        map_two_continue = false;
}