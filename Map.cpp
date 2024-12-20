#include "Map.h"
#include "Start.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Level.h"
#include "End.h"
using namespace cocos2d::ui;
USING_NS_CC;

extern bool map_one_finish;
extern bool map_two_finish;
extern bool map_two_unlock;

Scene* MyMap::createScene() {
    return MyMap::create();
}

static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MyMap::init() {
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加标题文字
    auto mapLabel = Label::createWithTTF("Map", "fonts/Marker Felt.ttf", 24);
    auto mapLabelOne = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 24);
    auto mapLabelTwo = Label::createWithTTF("2", "fonts/Marker Felt.ttf", 24);
    if (!mapLabel || !mapLabelOne || !mapLabelTwo) {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else {
        mapLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - mapLabel->getContentSize().height));
        mapLabelOne->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + visibleSize.height - mapLabel->getContentSize().height - 50));
        mapLabelTwo->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100, origin.y + visibleSize.height - mapLabel->getContentSize().height - 50));
        this->addChild(mapLabel, 1);
        this->addChild(mapLabelOne, 1);
        this->addChild(mapLabelTwo, 1);
    }
    mapLabel->setColor(Color3B::BLACK);
    mapLabelOne->setColor(Color3B::BLACK);
    mapLabelTwo->setColor(Color3B::BLACK);

    // 创建返回按钮
    auto returnItem = MenuItemImage::create("Return.png", "Return.png", CC_CALLBACK_1(MyMap::menuOkCallback, this));
    if (!returnItem || returnItem->getContentSize().width <= 0 || returnItem->getContentSize().height <= 0) {
        problemLoading("'Return.png'");
    }
    else {
        returnItem->setPosition(Vec2(175, Director::getInstance()->getWinSize().height - 148));
        this->addChild(returnItem, 1);
    }

    // 加入背景图片
    auto mapBackground = Sprite::create("Background.png");
    if (!mapBackground) {
        problemLoading("'Background.png'");
    }
    else {
        mapBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(mapBackground, 0);
    }

    // 地图一按钮
    auto mapOneButton = Button::create("Map_one.png", "Map_one_selected.png");
    if (!mapOneButton || mapOneButton->getContentSize().width <= 0 || mapOneButton->getContentSize().height <= 0) {
        problemLoading("'Map_one.png'");
    }
    else {
        mapOneButton->setPosition(Vec2(115, 140));
        mapOneButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                auto gameOneScene = Game_one::createScene();
                Director::getInstance()->pushScene(TransitionFade::create(0.5, gameOneScene, Color3B::WHITE));
            }
            });
        this->addChild(mapOneButton, 1);
    }

    // 地图一完成状态标志
    if (map_one_finish) {
        auto finishOne = Sprite::create("Finish.png");
        if (!finishOne) problemLoading("'Finish.png'");
        else {
            finishOne->setPosition(Vec2(visibleSize.width / 2 - 20, visibleSize.height / 2 + 35));
            this->addChild(finishOne, 2);
        }
    }
    else {
        auto unfinishOne = Sprite::create("Unfinish.png");
        if (!unfinishOne) problemLoading("'Unfinish.png'");
        else {
            unfinishOne->setPosition(Vec2(visibleSize.width / 2 - 30, visibleSize.height / 2 + 35));
            this->addChild(unfinishOne, 2);
        }
    }

    // 地图二按钮
    auto mapTwoButton = Button::create("Map_two.png", "Map_two_selected.png", "Map_two_unlocked.png");
    if (!mapTwoButton || mapTwoButton->getContentSize().width <= 0 || mapTwoButton->getContentSize().height <= 0) {
        problemLoading("'Map_two.png'");
    }
    else {
        mapTwoButton->setPosition(Vec2(visibleSize.width - 108, 140));
        if (!map_two_unlock) {
            mapTwoButton->setBright(false);
            mapTwoButton->setTouchEnabled(false);
        }
        mapTwoButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                auto gameTwoScene = Game_two::createScene();
                Director::getInstance()->pushScene(TransitionFade::create(0.5, gameTwoScene, Color3B::WHITE));
            }
            });
        this->addChild(mapTwoButton, 1);
    }

    // 地图二完成状态和解锁标志
    if (map_two_unlock) {
        if (map_two_finish) {
            auto finishTwo = Sprite::create("Finish.png");
            if (!finishTwo) problemLoading("'Finish.png'");
            else {
                finishTwo->setPosition(Vec2(visibleSize.width - 30, visibleSize.height / 2 + 35));
                this->addChild(finishTwo, 2);
            }
        }
        else {
            auto unfinishTwo = Sprite::create("Unfinish.png");
            if (!unfinishTwo) problemLoading("'Unfinish.png'");
            else {
                unfinishTwo->setPosition(Vec2(visibleSize.width - 40, visibleSize.height / 2 + 35));
                this->addChild(unfinishTwo, 2);
            }
        }
    }
    else {
        auto unlockTwo = Sprite::create("Unlock.png");
        if (!unlockTwo) problemLoading("'Unlock.png'");
        else {
            unlockTwo->setPosition(Vec2(visibleSize.width - 40, visibleSize.height / 2 + 35));
            this->addChild(unlockTwo, 2);
        }
    }

    return true;
}
// 返回上一页面
void MyMap::menuOkCallback(Ref* pSender) {
    Director::getInstance()->popScene();
}