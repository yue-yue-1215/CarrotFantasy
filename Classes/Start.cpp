#include "Map.h"
#include "Start.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;
using namespace cocos2d::ui;

USING_NS_CC;

bool map_one_finish = false; // ��һ���Ƿ����
bool map_two_finish = false; // �ڶ����Ƿ����
bool map_two_unlock = false; // �ڶ����Ƿ����
bool map_one_continue = false; // ��һ���Ƿ����ڽ���
bool map_two_continue = false; // �ڶ����Ƿ����ڽ���
bool sound = true; // �����Ƿ���
int backgroundAudioID;

Scene* Start::createScene() {
    return Start::create();
}

static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Button* createButton(const char* normalImg, const char* selectedImg, float x, float y) {
    auto button = Button::create(normalImg, selectedImg);
    if (!button || button->getContentSize().width <= 0 || button->getContentSize().height <= 0) {
        problemLoading(normalImg);
        return nullptr;
    }
    button->setPosition(Vec2(x, y));
    return button;
}

bool Start::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    AudioEngine::preload("BackgroundMusic.mp3");
    backgroundAudioID = AudioEngine::play2d("BackgroundMusic.mp3", true);

    // ���뱳��ͼƬ
    auto startBackground = Sprite::create("StartBackground.png");
    if (startBackground) {
        startBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(startBackground, 0);
    }
    else {
        problemLoading("'StartBackground.png'");
    }

    // ��ʼ��Ϸ��ť
    auto startItem = createButton("StartButton.png", "StartButton_selected.png", origin.x + 140, origin.y + 50);
    if (startItem) {
        startItem->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                auto myMap = MyMap::createScene();
                Director::getInstance()->pushScene(TransitionFade::create(0.5, myMap, Color3B(255, 255, 255)));
            }
            });
        this->addChild(startItem);
    }

    // �ر���Ϸ��ť
    auto closeItem = createButton("EndButton.png", "EndButton_selected.png", origin.x + visibleSize.width - 145, origin.y + 50);
    if (closeItem) {
        closeItem->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
#endif
            }
            });
        this->addChild(closeItem);
    }

    // ����������ť
    auto soundItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Start::openAndCloseSound, this),
        MenuItemImage::create("SoundButton.png", "SoundButton.png"),
        MenuItemImage::create("SoundCloseButton.png", "SoundCloseButton.png"), nullptr);

    if (soundItem) {
        soundItem->setPosition(Vec2(origin.x + 170, origin.y + 120));
        Vector<MenuItem*> menuItems;
        menuItems.pushBack(soundItem);
        auto menu = Menu::createWithArray(menuItems);
        this->addChild(menu, 1);
    }
    else {
        problemLoading("'SoundButton.png'");
    }

    return true;
}

void Start::openAndCloseSound(Ref* pSender) {
    if (!sound) {
        AudioEngine::resume(backgroundAudioID);
        sound = true;
    }
    else {
        AudioEngine::pause(backgroundAudioID);
        sound = false;
    }
}