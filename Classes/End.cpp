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

// ������Ϸ��������
Scene* GameEnd::scene(RenderTexture* sqr)
{
    auto scene = Scene::create();
    auto layer = GameEnd::create();
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

// ��ʼ����Ϸ������
bool GameEnd::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����������Ϸ��ť
    auto continueItem = MenuItemImage::create("Continue.png", "Continue.png",
        CC_CALLBACK_1(GameEnd::ContinueGame, this));
    continueItem->setPosition(Vec2(origin.x - 58, origin.y - 15));

    // �������ز˵���ť
    auto returnmenuItem = MenuItemImage::create("ReturnMenu.png", "ReturnMenu.png",
        CC_CALLBACK_1(GameEnd::ReturnMenuGame, this));
    returnmenuItem->setPosition(Vec2(origin.x + 10, origin.y - 15));

    // �����˵�
    Vector<MenuItem*> MenuItems;
    MenuItems.pushBack(continueItem);
    MenuItems.pushBack(returnmenuItem);
    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu, 2);

    // ����ͨ��ͼ��
    auto successMenu = Sprite::create("Menu.png");
    successMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 15));
    this->addChild(successMenu, 1);

    // ����ͨ��ͼƬ
    auto successPic = Sprite::create("Success.png");
    successPic->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 70));
    this->addChild(successPic, 1);

    return true;
}

// ������Ϸ�߼�
void GameEnd::ContinueGame(Ref* pSender)
{
    // ������Ϸ״̬
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // ������ǰ����
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();

    // ���ݵ�ǰ��ͼ״̬������Ϸ
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

// ���ز˵��߼�
void GameEnd::ReturnMenuGame(Ref* pSender)
{
    // ������Ϸ״̬
    TowerExist.clear();
    countnum = 5;
    carrot_level = 1;
    carrot_HP = 5;

    // ������ǰ����
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();

    // ���ݵ�ǰ��ͼ״̬���ز˵�
    if (map_one_continue) {
        map_one_finish = true;
        map_one_continue = false;
    }
    else if (map_two_continue) {
        map_two_finish = true;
        map_two_continue = false;
    }

    // �����ͼ����
    auto MyMap = MyMap::createScene();
    Director::getInstance()->pushScene(MyMap);
}
