#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "PlaceTower.h"
#include "GameEnd.h"
#include "GameDefault.h"
#include "Tower_kind.h"
#include "CEnemy.h"
#include "GenerateEnemy.h"
#include <algorithm>
#include <exception>

USING_NS_CC;

using namespace std;
using namespace cocos2d::ui;

int current_gold_coins = 200; // ��ǰ�����
int countnum = 5; // ����ʱʱ��

// �ܲ��������
int coins[4] = { 0,20,40,60 };	//1����2����Ҫ�Ľ��Ϊ coins[1] 
int carrot_health[5] = { 0,5,10,15,20};//1����Ѫ��Ϊ carrot_health[1] 
int carrot_level = 1;
int carrot_HP = 5;

extern bool map_two_unlock;
extern bool map_one_continue;

Scene* Game_one::createScene()
{
	Scene *scene = Scene::create();
	Game_one *layer = Game_one::create();
	scene->addChild(layer);
	return scene;
}

// �Ҳ����ļ�ʱ�׳��쳣
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// ���Ӳ�߷�������ͼ��
void Game_one::createTower0(const std::string& towerImage, const std::string& towerBackImage,
	int upgradeCoins, float positionY, int index)
{
		auto tower = Sprite::create(towerImage);
		auto tower_back = Sprite::create(towerBackImage);
		tower_back->setPosition(Vec2(42, positionY));
		this->addChild(tower_back, 1);  // ����������
		tower->setPosition(Vec2(42, positionY));  // ��߷�����λ��
		this->addChild(tower, 1);

		Label* build = Label::createWithTTF(to_string(upgradeCoins), "fonts/Marker Felt.ttf", 13);  // �������֣���Ҫ���ĵĽ������
		if (build == nullptr)
			problemLoading("'fonts/Marker Felt.ttf'");
		else
		{
			build->setPosition(Vec2(63, positionY - 12));  // ���ӵķ�������������Ҫ��Ǯ��λ��
			this->addChild(build, 1);
		}
		build->setColor(Color3B(0, 0, 0));  // ��ɫ
}

bool Game_one::init()
{
	// ���еĳ�ʼ�������������з����������ý�ң�����һ��
	TowerExist.clear();
	current_gold_coins = 200;
	start_generate = false;
	current_flag = 1;
	carrot_HP = 5;

	if (!Scene::init())
	{
		return false;
	}

	map_one_continue = true;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���뱳��ͼƬ
	auto map_one = Sprite::create("GameBackground_one.png");
	if (map_one == nullptr)
	{
		problemLoading("'GameBackground_one.png'");
	}
	else
	{
		map_one->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(map_one, 1);
	}

	// �����ϱ���ͼƬ
	auto upperboard = Sprite::create("Upperboard.png");
	if (upperboard == nullptr)
	{
		problemLoading("'Upperboard.png'");
	}
	else
	{
		upperboard->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - upperboard->getContentSize().height / 2));
		this->addChild(upperboard, 1);
	}

	// ��ͣ����
	auto pauseItem = MenuItemImage::create("Pause.png",
		"Pause.png", CC_CALLBACK_1(Game_one::Pause, this));

	if (pauseItem == nullptr
		|| pauseItem->getContentSize().width <= 0
		|| pauseItem->getContentSize().height <= 0)
	{
		problemLoading("'Pause.png'");
	}
	else
	{
		pauseItem->setPosition(Vec2(origin.x + 160, origin.y + 143));
	}

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(pauseItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	//�ܲ����
	{
		// ���� "carrot" ͼƬ
		auto carrot_pic = Button::create("carrot.png", "carrot.png");
		carrot_pic->setPosition(Vec2(86, 248));
		this->addChild(carrot_pic, 1);

		// ������ť
		auto levelupcarrotbutton = Button::create("levelup.png");
		levelupcarrotbutton->setPosition(Vec2(96, 224));
		this->addChild(levelupcarrotbutton, 2, "carrot_u");
		levelupcarrotbutton->setVisible(false);

		// �˳���ť
		auto returncarrotbutton = Button::create("exit.png");
		returncarrotbutton->setPosition(Vec2(80, 225));
		this->addChild(returncarrotbutton, 2, "carrot_r");
		returncarrotbutton->setVisible(false);

		// ������ұ�ǩ
		auto levelupcarrotcoin = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 10);
		levelupcarrotcoin->setColor(Color3B(255, 255, 0));
		levelupcarrotcoin->setVisible(false);
		levelupcarrotcoin->setPosition(Vec2(106, 224));
		this->addChild(levelupcarrotcoin, 2, "carrot_c");

		// �ȼ���ǩ
		auto carrotlevel = Label::createWithTTF("Lv.1", "fonts/Marker Felt.ttf", 10);
		carrotlevel->setColor(Color3B(255, 0, 0));
		carrotlevel->setVisible(false);
		carrotlevel->setPosition(Vec2(86, 268));
		this->addChild(carrotlevel, 2, "carrot_l");

		// ����ܲ�ͼƬ
		carrot_pic->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				layout_uplevel = this->getChildByName("carrot_u");
				layout_return = this->getChildByName("carrot_r");
				layout_coin = (Label*)(getChildByName("carrot_c"));
				layout_nowlevel = (Label*)(getChildByName("carrot_l"));

				int money = coins[carrot_level];
				layout_coin->setString(std::to_string(money));
				std::string levelname = "Lv." + std::to_string(carrot_level);
				layout_nowlevel->setString(levelname);

				layout_uplevel->setVisible(true);
				layout_return->setVisible(true);
				layout_coin->setVisible(true);
				layout_nowlevel->setVisible(true);
			}
													break;
			default:
				break;
			}
		});

		// ����ܲ��ķ��ذ�ť
		returncarrotbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				layout_uplevel = this->getChildByName("carrot_u");
				layout_return = this->getChildByName("carrot_r");
				layout_coin = (Label*)(getChildByName("carrot_c"));
				layout_nowlevel = (Label*)(getChildByName("carrot_l"));

				layout_uplevel->setVisible(false);
				layout_return->setVisible(false);
				layout_coin->setVisible(false);
				layout_nowlevel->setVisible(false);
			}
													break;
			default:
				break;
			}
		});

		// �ܲ�����
		levelupcarrotbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				layout_uplevel = this->getChildByName("carrot_u");
				layout_return = this->getChildByName("carrot_r");
				layout_coin = (Label*)(getChildByName("carrot_c"));
				layout_nowlevel = (Label*)(getChildByName("carrot_l"));

				if (carrot_level <= 3)
				{
					if (current_gold_coins >= coins[carrot_level]) {
						current_gold_coins -= coins[carrot_level];
						carrot_level++;
						carrot_HP += 5;
						if (carrot_HP > carrot_health[carrot_level])
							carrot_HP = carrot_health[carrot_level];
						updateGoldCoinsDisplay();
						showTowerGrey();
					}
					else
						showInsufficientGoldLabel();
				}
				else
				{
					showInsufficientLevelLabel();
					layout_uplevel->setVisible(false);
				}

				layout_uplevel->setVisible(false);
				layout_return->setVisible(false);
				layout_coin->setVisible(false);
				layout_nowlevel->setVisible(false);
			}
													break;
			default:
				break;
			}
		});

		// �ܲ�Ѫ������
		auto CarrotHealthBack = Sprite::create("CarrotHealthBack.png");
		CarrotHealthBack->setPosition(Vec2(86, 278));// �ܲ��Ϸ�λ��
		this->addChild(CarrotHealthBack, 1);

		// �����ܲ�Ѫ��
		ProgressTimer* healthBar = ProgressTimer::create(Sprite::create("HealthBar.png"));
		healthBar->setType(ProgressTimer::Type::BAR);
		healthBar->setMidpoint(Vec2(0, 0.5));
		healthBar->setBarChangeRate(Vec2(1, 0));
		healthBar->setPosition(Vec2(86, 278));  // �ܲ��Ϸ�λ��
		healthBar->setPercentage(100.0f);
		this->addChild(healthBar, 2, "healthBar");
		this->schedule(CC_SCHEDULE_SELECTOR(Game_one::carrotHealthUpdate), 1.0f / 60.0f);
	}

	// ���ӳ�����ͼƬ
	auto GuideBoard = Sprite::create("GuideBoard.png");
	if (GuideBoard)
	{
		GuideBoard->setPosition(Vec2(433, 75)); //������λ��
		this->addChild(GuideBoard, 1);
	}
	else
	{
		problemLoading("'GuideBoard.png'");
	}

	// ��������
	auto countdown = Label::createWithTTF("Monsters strike 5 seconds later", "fonts/Marker Felt.ttf", 14);
	if (countdown == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		countdown->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - countdown->getContentSize().height - 1));
		countdown->setColor(Color3B(255, 255, 255));
		this->addChild(countdown, 2, 1000);
		schedule(CC_CALLBACK_1(Game_one::step, this), 1.0f, "step_key");
	}

	//��ʾ��ߵķ�����0
	createTower0("tower_zero.png", "tower_back.png", tower0_upgrade_coins[0], 230, 0);

	//��ʾ��ߵķ�����1
	createTower0("tower_one.png", "tower_back.png", tower1_upgrade_coins[0], 185, 1);

	//��ʾ��ߵķ�����2
	createTower0("tower_two.png", "tower_back.png", tower2_upgrade_coins[0], 140, 2);

	//��ʾ��ߵķ�����3
	createTower0("tower_three.png", "tower_back.png", tower3_upgrade_coins[0], 95, 3);

	// ��ʾ��ߵĻ�ɫ������
	{
		tower_zero0 = Sprite::create("tower_zero0.png");
		tower_back0 = Sprite::create("tower_back0.png");
		tower_back0->setPosition(Vec2(42, 230));
		tower_zero0->setPosition(Vec2(42, 230));  // ��߷�����λ��
		tower_back0->setVisible(false);
		tower_zero0->setVisible(false);
		this->addChild(tower_back0, 1);
		this->addChild(tower_zero0, 1);
		buildcoins0 = Label::createWithTTF(to_string(getTowerUpgradeCoins(0)), "fonts/Marker Felt.ttf", 13);  // �������֣���Ҫ���ĵĽ������
		buildcoins0->setPosition(Vec2(63, 230 - 12));
		buildcoins0->setVisible(false);
		buildcoins0->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins0, 1);

		tower_one0 = Sprite::create("tower_one0.png");
		tower_back1 = Sprite::create("tower_back0.png");
		tower_back1->setPosition(Vec2(42, 185));
		tower_one0->setPosition(Vec2(42, 185));  // ��߷�����λ��
		tower_back1->setVisible(false);
		tower_one0->setVisible(false);
		this->addChild(tower_back1, 1);
		this->addChild(tower_one0, 1);
		buildcoins1 = Label::createWithTTF(to_string(getTowerUpgradeCoins(1)), "fonts/Marker Felt.ttf", 13);  // �������֣���Ҫ���ĵĽ������
		buildcoins1->setPosition(Vec2(63, 185 - 12));
		buildcoins1->setVisible(false);
		buildcoins1->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins1, 1);

		tower_two0 = Sprite::create("tower_two0.png");
		tower_back2 = Sprite::create("tower_back0.png");
		tower_back2->setPosition(Vec2(42, 140));
		tower_two0->setPosition(Vec2(42, 140));  // ��߷�����λ��
		tower_back2->setVisible(false);
		tower_two0->setVisible(false);
		this->addChild(tower_back2, 1);
		this->addChild(tower_two0, 1);
		buildcoins2 = Label::createWithTTF(to_string(getTowerUpgradeCoins(2)), "fonts/Marker Felt.ttf", 13);  // �������֣���Ҫ���ĵĽ������
		buildcoins2->setPosition(Vec2(63, 140 - 12));
		buildcoins2->setVisible(false);
		buildcoins2->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins2, 1);

		tower_three0 = Sprite::create("tower_three0.png");
		tower_back3 = Sprite::create("tower_back0.png");
		tower_back3->setPosition(Vec2(42, 95));
		tower_three0->setPosition(Vec2(42, 95));  // ��߷�����λ��
		tower_back3->setVisible(false);
		tower_three0->setVisible(false);
		this->addChild(tower_back3, 1);
		this->addChild(tower_three0, 1);
		buildcoins3 = Label::createWithTTF(to_string(getTowerUpgradeCoins(3)), "fonts/Marker Felt.ttf", 13);  // �������֣���Ҫ���ĵĽ������
		buildcoins3->setPosition(Vec2(63, 95 - 12));
		buildcoins3->setVisible(false);
		buildcoins3->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins3, 1);
	}

	// ��ʼ����Ҳ���ı�ǩ
	insufficientGoldLabel = Label::createWithTTF("not enough gold coins!", "fonts/Marker Felt.ttf", 14);
	insufficientGoldLabel->setColor(Color3B(255, 0, 0));  // ��ɫ
	insufficientGoldLabel->setVisible(false);  // ��ʼʱ����Ϊ���ɼ�
	insufficientGoldLabel->setPosition(Vec2(90,60));//����λ��
	this->addChild(insufficientGoldLabel, 1);

	// ��ʼ������λ�ô���ı�ǩ
	insufficientPlaceLabel = Label::createWithTTF("wrong place!", "fonts/Marker Felt.ttf", 14);
	insufficientPlaceLabel->setColor(Color3B(255, 0, 0));  // ��ɫ
	insufficientPlaceLabel->setVisible(false);  // ��ʼʱ����Ϊ���ɼ�
	insufficientPlaceLabel->setPosition(Vec2(90, 60));//����λ��
	this->addChild(insufficientPlaceLabel, 1);

	// ��ʼ���ȼ������ı�ǩ
	insufficientLevelLabel = Label::createWithTTF("reach highest level!", "fonts/Marker Felt.ttf", 14);
	insufficientLevelLabel->setColor(Color3B(255, 0, 0));  // ��ɫ
	insufficientLevelLabel->setVisible(false);  // ��ʼʱ����Ϊ���ɼ�
	insufficientLevelLabel->setPosition(Vec2(90, 60));//����λ��
	this->addChild(insufficientLevelLabel, 1);

	// �������ɷ���λ�ñ߿�
	for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
		board[i] = Sprite::create("board.png");
		if (board[i] == nullptr)
		{
			problemLoading("'board.png'");
		}
		else
		{
			board[i]->setPosition(pairxy[i - 1]);
			this->addChild(board[i], 1);
			board[i]->setVisible(false);
		}
	}

	// ������ͼƬ
	auto moneypic = Sprite::create("Money.png");
	if (moneypic == nullptr)
	{
		problemLoading("'Money.png'");
	}
	else
	{
		moneypic->setPosition(Vec2(origin.x + 18, origin.y + visibleSize.height - 16));
		this->addChild(moneypic, 1);
	}

	// �������ֽ������
	mapnum = Label::createWithTTF(to_string(current_gold_coins), "fonts/Marker Felt.ttf", 18);
	if (mapnum == nullptr) {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else {
		mapnum->setPosition(Vec2(origin.x + 48, origin.y + visibleSize.height - 17));
		this->addChild(mapnum, 2);
		mapnum->setColor(Color3B(255, 255, 0));
	}
	updateGoldCoinsDisplay();
	showTowerGrey();

	// �������λ����ʾ
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Game_one::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	auto mouseListener1 = EventListenerMouse::create();
	mouseListener1->onMouseDown = CC_CALLBACK_1(Game_one::onMouseDown1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener1, this);

	EnemyExist.clear();

	flags = { 1,1,1,1,1,1,-1, 1,1,1,2,2,2,-1,2,2,2,2,2,2,-1 ,1,1,1,3,3,3,-1 ,3,3,3,3,3,3,-1,3,3,3,4,4,4,-1,4,4,4,4,4,4,-1,0 };

	generateflag(flags, 420, 75);

	double x_ = 420, y_ = 75;
	for (auto it_enemy = EnemyExist.begin(); it_enemy != EnemyExist.end(); ++it_enemy)
	{
		switch ((*it_enemy)->enemytype)
		{
		case -1:
			(*it_enemy)->enemySprite = nullptr;
			x_ += 300;
			current_flag++;
			continue;
		case 0:
			(*it_enemy)->enemySprite = Sprite::create("Enemy_zero.png");
			(*it_enemy)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enemy)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			(*it_enemy)->dizzypic = cocos2d::Sprite::create("vertigo.png");
			(*it_enemy)->dizzypic->setVisible(false);
			break;
		case 1:
			(*it_enemy)->enemySprite = Sprite::create("Enemy_one.png");
			(*it_enemy)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enemy)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			(*it_enemy)->dizzypic = cocos2d::Sprite::create("vertigo.png");
			(*it_enemy)->dizzypic->setVisible(false);
			break;
		case 2:
			(*it_enemy)->enemySprite = Sprite::create("Enemy_two.png");
			(*it_enemy)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enemy)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			(*it_enemy)->dizzypic = cocos2d::Sprite::create("vertigo.png");
			(*it_enemy)->dizzypic->setVisible(false);
			break;
		case 3:
			(*it_enemy)->enemySprite = Sprite::create("Enemy_three.png");
			(*it_enemy)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enemy)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			(*it_enemy)->dizzypic = cocos2d::Sprite::create("vertigo.png");
			(*it_enemy)->dizzypic->setVisible(false);
			break;
		case 4:
			(*it_enemy)->enemySprite = Sprite::create("Enemy_four.png");
			(*it_enemy)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enemy)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			(*it_enemy)->dizzypic = cocos2d::Sprite::create("vertigo.png");
			(*it_enemy)->dizzypic->setVisible(false);
			break;
		default:
			break;
		}

		(*it_enemy)->set_x(x_);
		(*it_enemy)->set_y(y_);
		(*it_enemy)->enemySprite->setPosition(Vec2(x_, y_));
		(*it_enemy)->enemyHealthbar_back->setPosition(Vec2(x_, y_ + 20));
		(*it_enemy)->enemyHealthbar->setPosition(Vec2(x_, y_ + 20));
		(*it_enemy)->enemyHealthbar->setType(ProgressTimer::Type::BAR);
		(*it_enemy)->enemyHealthbar->setMidpoint(Vec2(0, 0.5)); // ������ʼλ��Ϊˮƽ����е�
		(*it_enemy)->enemyHealthbar->setBarChangeRate(Vec2(1, 0)); // ���ü��ٷ���Ϊˮƽ����
		(*it_enemy)->enemyHealthbar->setPercentage(100.0f);
		(*it_enemy)->dizzypic->setPosition(Vec2(x_ + 5, y_ + 5));

		if (x_ >= 420)
		{
			(*it_enemy)->enemySprite->setVisible(false);
			(*it_enemy)->enemyHealthbar_back->setVisible(false);
			(*it_enemy)->enemyHealthbar->setVisible(false);
		}
		else
		{
			(*it_enemy)->enemySprite->setVisible(true);
			(*it_enemy)->enemyHealthbar_back->setVisible(true);
			(*it_enemy)->enemyHealthbar->setVisible(true);
		}
		x_ += 45;

		this->addChild((*it_enemy)->enemySprite, 1);
		this->addChild((*it_enemy)->enemyHealthbar_back, 1);
		this->addChild((*it_enemy)->enemyHealthbar, 2,"HealthBar.png");
		this->addChild((*it_enemy)->dizzypic, 3, "vertigo.png");
	}

	// ÿ֡���� update ����
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Game_one::startgenerate), 5.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(Game_one::Enemyupdate), 1.0f / 60.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(Game_one::TowerAttack), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(Game_one::addcoins2), 1.0f);
	return true;
}

// ���¹���λ��
void Game_one::Enemyupdate(float dt)// ����ȫ����ڵĹ��ﲢ�Ҹ���������
{
	if (start_generate)
	{
		double speed = 0.5;
		float new_x, new_y;
		for (auto it_enemy = EnemyExist.begin(); it_enemy != EnemyExist.end();)
		{
			if ((*it_enemy)->alive())
			{
				if ((*it_enemy)->dizzy && (*it_enemy)->dizzytime<=0.2)
				{
					speed = 0;
					(*it_enemy)->dizzytime += dt;
				}
				else if ((*it_enemy)->dizzy && (*it_enemy)->dizzytime > 0.2)
				{
					(*it_enemy)->dizzy = false;
					(*it_enemy)->dizzytime = 0;
					(*it_enemy)->dizzypic->setVisible(false);
				}
				else//δ��ѣ��
				{
					if ((*it_enemy)->slowed && (*it_enemy)->slowedtime <= 3)
					{
						speed = (*it_enemy)->get_velocity()*0.5;
						(*it_enemy)->slowedtime += dt;
					}
					else if ((*it_enemy)->slowed && (*it_enemy)->slowedtime > 3)
					{
						(*it_enemy)->slowed = false;
						(*it_enemy)->slowedtime = 0;
					}
					else
					{
						speed = (*it_enemy)->get_velocity();
					}
				}

				new_x = (*it_enemy)->EnemyPositionX(), new_y = (*it_enemy)->EnemyPositionY();

				if (new_x >= 420)
					new_x -= 0.5;
				else if (new_x >= 260 && new_y == 75)
					new_x -= speed;
				else if (new_x >= 259 && new_y >= 75 && new_y <= 245)
					new_y += speed;
				else if (new_y <= 246 && new_x < 261 && new_x > 102)
					new_x -= speed;
				else if (new_x <= 102) {
					(*it_enemy)->HP_calculate(10000);
					carrot_HP -=1;
					// ��Ϸ����
					if (carrot_HP <= 0) {
						// �õ����ڵĴ�С
						auto visibleSize = Director::getInstance()->getVisibleSize();
						RenderTexture *renderTexture = RenderTexture::create(visibleSize.width + 48, visibleSize.height);

						// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
						// �������ƽ�ͼ��
						renderTexture->begin();
						this->getParent()->visit();
						renderTexture->end();

						Director::getInstance()->pushScene(GameDefault::scene(renderTexture));
					}
				}
					
				(*it_enemy)->enemySprite->setPosition(Vec2(new_x, new_y));
				(*it_enemy)->enemyHealthbar_back->setPosition(Vec2(new_x, new_y + 20));
				(*it_enemy)->enemyHealthbar->setPosition(Vec2(new_x, new_y + 20));
				(*it_enemy)->enemyHealthbar->setPercentage((*it_enemy)->getHPpercentage()*100);
				(*it_enemy)->dizzypic->setPosition(Vec2(new_x + 5, new_y + 5));

				(*it_enemy)->set_x(new_x);
				(*it_enemy)->set_y(new_y);
				if (new_x >= 420)
				{
					(*it_enemy)->enemySprite->setVisible(false);
					(*it_enemy)->enemyHealthbar_back->setVisible(false);
					(*it_enemy)->enemyHealthbar->setVisible(false);
					(*it_enemy)->dizzypic->setVisible(false);
				}
				else
				{
					(*it_enemy)->enemySprite->setVisible(true);
					(*it_enemy)->enemyHealthbar_back->setVisible(true);
					(*it_enemy)->enemyHealthbar->setVisible(true);
				}
			}
			else
			{
				// �Ƴ����ﾫ���ɾ���������
				if ((*it_enemy)->enemySprite)
				{
					current_gold_coins += (*it_enemy)->getadd_coins();
					updateGoldCoinsDisplay();
					showTowerGrey();
					(*it_enemy)->enemySprite->removeFromParent();
					(*it_enemy)->enemyHealthbar->removeFromParent();
					(*it_enemy)->enemyHealthbar_back->removeFromParent();
					(*it_enemy)->dizzypic->removeFromParent();
				}
				it_enemy = EnemyExist.erase(it_enemy);
				// ��Ϸ�����ı�־
				if (EnemyExist.empty()&& carrot_HP>0)
				{
					map_two_unlock = true;

					// �õ����ڵĴ�С
					auto visibleSize = Director::getInstance()->getVisibleSize();
					RenderTexture *renderTexture = RenderTexture::create(visibleSize.width + 48, visibleSize.height);

					// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
					// �������ƽ�ͼ��
					renderTexture->begin();
					this->getParent()->visit();
					renderTexture->end();

					Director::getInstance()->pushScene(GameEnd::scene(renderTexture));
				}
				continue;  // ������һ��ѭ��������Ҫִ�� delete ����
			}
			++it_enemy;
		}
	}
}

// �ܲ�Ѫ������
void Game_one::Game_one::carrotHealthUpdate(float Dt)
{
	auto healthBar = (ProgressTimer*)(getChildByName("healthBar"));
	double percent = carrot_HP*100.0 / carrot_health[carrot_level];
	healthBar->setPercentage(percent);
}

// �ڹ������������һֻ����
void Game_one::generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y)
{
	CEnemy* newEnemy = nullptr;

	// ���� enemyType ������ͬ���͵Ĺ���
	switch (enemyType) {
	case 0:
		newEnemy = new Enemy0();
		newEnemy->initial(0, 1500, 0.3f, 100, 0, 0);
		break;
	case 1:
		newEnemy = new Enemy1();
		newEnemy->initial(1, 30, 0.5, 10, 0, 0);
		break;
	case 2:
		newEnemy = new Enemy2();
		newEnemy->initial(2, 50, 0.5, 10, 0, 0);
		break;
	case 3:
		newEnemy = new Enemy3();
		newEnemy->initial(3, 100, 1, 15, 0, 0);
		break;
	case 4:
		newEnemy = new Enemy4();
		newEnemy->initial(4, 200, 0.75f, 30, 0, 0);
		break;

	default:
		newEnemy = new Enemy4();
		newEnemy->initial(-1, 0, 0, 0, 0, 0);
		break;
	}

	if (newEnemy)
	{
		newEnemy->set_x(x);
		newEnemy->set_y(y);
		EnemyExist.push_back(newEnemy);
	}
}

// ����һ�����εĹ����ʼ����Ϊxy
void Game_one::generateflag(vector<int> flags, double x, double y)
{
	for (unsigned int i = 0; i < flags.size(); i++)
	{
		generateOneEnemy(EnemyExist, flags[i], x, y);
	}
}

void Game_one::TowerAttack(float dt)
{
	for (auto tower_it = TowerExist.begin(); tower_it != TowerExist.end(); ++tower_it)
	{
		CTower* tower = *tower_it;
		vector<CEnemy*> inRangeEnemies;
		CEnemy* enemy;
		CEnemy* target;
		for (auto enemy_it = EnemyExist.begin(); enemy_it != EnemyExist.end(); ++enemy_it)
		{
			enemy = *enemy_it;
			if (tower->inRange(enemy)&& enemy->EnemyPositionX()<=419)
			{
				inRangeEnemies.push_back(enemy);
			}
		}

		bool flag = tower->attack(inRangeEnemies, tower->getDamage(), target);
		auto rotateTo = RotateTo::create(2.0f, 2160.0f);
		auto scaleBy = ScaleBy::create(3.0f, 0.5f);

		if (flag) {
			switch (tower->getType()) {
			case 0:
				bulletSprite = Sprite::create("Magicball.png");
				break;
			case 1:
				bulletSprite = Sprite::create("Shuriken.png");
				bulletSprite->runAction(rotateTo);
				break;
			case 2:
				bulletSprite = Sprite::create("Snowball.png");
				break;
			case 3: {
				bulletSprite = Sprite::create("Sunflower.png");
				bulletSprite->runAction(scaleBy);
			}
				break;
			default:
				break;
			}
			bulletSprite->setPosition(Vec2(tower->getPositionX(), tower->getPositionY()));
			this->addChild(bulletSprite, 2);

			Bullet bullet;
			bullet.Tower = tower;
			bullet.Enemy = target;
			bullet.bulletsprite = bulletSprite;
			bullet.flag = false;
			allBulletArray.push_back(bullet);

			// �����ӵ��ٶ�
			schedule(CC_SCHEDULE_SELECTOR(Game_one::moveBullet), 1.0f / 60.0f);	
		}
	}
}

// �ƶ��ӵ�
void Game_one::moveBullet(float dt) {
	for (auto it = allBulletArray.begin(); it != allBulletArray.end(); it++) {
		if ((*it).Tower->getType() != 3) {
			// ����λ��
			(*it).bulletsprite->setPositionX((*it).bulletsprite->getPositionX() +
				((*it).Enemy->EnemyPositionX() - (*it).Tower->getPositionX()) * dt*2);
			(*it).bulletsprite->setPositionY((*it).bulletsprite->getPositionY() +
				((*it).Enemy->EnemyPositionY() - (*it).Tower->getPositionY()) * dt*2);

			// ����ѵ�����ʧλ�ã����Ƴ����ӵ�
			if (fabs((*it).bulletsprite->getPositionX() - (*it).Enemy->EnemyPositionX()) < 15 &&
				fabs((*it).bulletsprite->getPositionY() - (*it).Enemy->EnemyPositionY()) < 15) {
				(*it).bulletsprite->setVisible(false);
				bulletSprite->removeChild((*it).bulletsprite, true);
				if (!(*it).flag) {
					(*it).Enemy->HP_calculate((*it).Tower->getDamage());
					if ((*it).Tower->getType() == 2)
					{
						(*it).Enemy->slowed = true;
						(*it).Enemy->slowedtime = 0.0;
					}
					if ((*it).Tower->getType() == 0)
					{
						(*it).Enemy->dizzy = true;
						(*it).Enemy->dizzytime = 0.0;
						if((*it).Enemy->alive())
							(*it).Enemy->dizzypic->setVisible(true);
					}
					(*it).flag = true;
				}	
			}
		}
		else {
			(*it).bulletsprite->setVisible(false);
			bulletSprite->removeChild((*it).bulletsprite, true);
		}
	}
}

//��ʼ���ɹ���
void Game_one::startgenerate(float dt)
{
	start_generate = true;
}

//�������ÿ���2
void Game_one::addcoins2(float dt)
{
	current_gold_coins += 2;
	updateGoldCoinsDisplay();
	showTowerGrey();
}

// ���½�ҵ�����
void Game_one::updateGoldCoinsDisplay() 
{
	// �������ֽ������
	if (mapnum != nullptr) {
		mapnum->setString(to_string(current_gold_coins));
	}
}

// ���»�ɫ�������Ƿ�ɼ�
void Game_one::showTowerGrey() 
{
	if (current_gold_coins < getTowerUpgradeCoins(0))
	{
		tower_back0->setVisible(true);
		tower_zero0->setVisible(true);
		buildcoins0->setVisible(true);
	}
	else
	{
		tower_back0->setVisible(false);
		tower_zero0->setVisible(false);
		buildcoins0->setVisible(false);
	}
	if (current_gold_coins < getTowerUpgradeCoins(1))
	{
		tower_back1->setVisible(true);
		tower_one0->setVisible(true);
		buildcoins1->setVisible(true);
	}
	else
	{
		tower_back1->setVisible(false);
		tower_one0->setVisible(false);
		buildcoins1->setVisible(false);
	}
	if (current_gold_coins < getTowerUpgradeCoins(2))
	{
		tower_back2->setVisible(true);
		tower_two0->setVisible(true);
		buildcoins2->setVisible(true);
	}
	else
	{
		tower_back2->setVisible(false);
		tower_two0->setVisible(false);
		buildcoins2->setVisible(false);
	}
	if (current_gold_coins < getTowerUpgradeCoins(3))
	{
		tower_back3->setVisible(true);
		tower_three0->setVisible(true);
		buildcoins3->setVisible(true);
	}
	else
	{
		tower_back3->setVisible(false);
		tower_three0->setVisible(false);
		buildcoins3->setVisible(false);
	}
}

// ��ͣ��Ϸ
void Game_one::Pause(Ref* pSender)
{
	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width+48, visibleSize.height);

	// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	// �������ƽ�ͼ��
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}

Vec2 towerPosition;  // ���ڴ洢��������λ��
int tower0Clicked = -1;

// ��������Ҫ�Ľ��
int Game_one::getTowerUpgradeCoins(int towerType)
{
	switch (towerType)
	{
	case 0:
		return tower0_upgrade_coins[0];
	case 1:
		return tower1_upgrade_coins[0];
	case 2:
		return tower2_upgrade_coins[0];
	case 3:
		return tower3_upgrade_coins[0];
	default:
		return 0;
	}
}

// ����xy��ֵ
bool deal_with_xy1(float &x , float& y)
{
	if (x > 102 && x <= 137)
		x = 120;
	else if (x > 137 && x <= 172)
		x = 155;
	else if (x > 172 && x <= 207)
		x = 190;
	else if (x > 207 && x <= 242)
		x = 225;
	else if (x > 242 && x <= 277)
		x = 260;
	else if (x > 277 && x <= 312)
		x = 295;
	else if (x > 312 && x <= 347)
		x = 330;
	else if (x > 347 && x <= 382)
		x = 365;
	else if (x > 382 && x <= 417)
		x = 400;

	if (y > 24 && y <= 58)
		y = 41;
	else if (y > 58 && y <= 92)
		y = 75;
	else if (y > 92 && y <= 126)
		y = 109;
	else if (y > 126 && y <= 160)
		y = 143;
	else if (y > 160 && y <= 194)
		y = 177;
	else if (y > 194 && y <= 228)
		y = 211;
	else if (y > 228 && y <= 262)
		y = 245;

	if (x > 417 || x <= 102 || y > 262 || y <= 24)
		return 0;
	if (y == 245 && x > 102 && x < 277)
		return 0;
	if (y == 75 && x > 242 && x < 417)
		return 0;
	if (x == 260 && y > 58 && y < 262)
		return 0;

	for (unsigned int i = 0; i < TowerExist.size(); i++)
	{
		if (x == TowerExist[i]->getPositionX() && y == TowerExist[i]->getPositionY())
			return 0;
	}

	return 1;
}

int already = 0; // �Ƿ�ѡ�з�����
Vec2 mousePosition;

// �Ѿ�ѡ�з�����׼������
void Game_one::onMouseDown(EventMouse* event)
{
	mousePosition = this->convertToNodeSpace(event->getLocationInView());

	if (already == 1)
	{
		for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++)
		{
			board[i]->setVisible(true);
		}
		towerPosition = mousePosition;
		bool place_success = deal_with_xy1(mousePosition.x, mousePosition.y); // ����xy���꣬�Ƿ�ɹ�����
		bool flag = false; // �Ƿ�������������õĸ�����
		for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
			if (pairxy[i - 1] == Vec2(mousePosition.x, mousePosition.y))
			{
				flag = true;
				break;
			}
		}

		if (flag && place_success)
		{
			towerPosition = Vec2(mousePosition.x, mousePosition.y);
			placeTower(TowerExist, tower0Clicked, mousePosition.x, mousePosition.y);
			current_gold_coins -= getTowerUpgradeCoins(tower0Clicked);
			updateGoldCoinsDisplay();
			showTowerGrey();
			// ���ݵ���ķ��������ʹ�����Ӧ�� Button
			Button* towerSprite=nullptr;
			switch (tower0Clicked)
			{
			case 0:
				towerSprite = Button::create("tower_zero.png", "tower_zero.png");
				break;
			case 1:
				towerSprite = Button::create("tower_one.png", "tower_one.png");
				break;
			case 2:
				towerSprite = Button::create("tower_two.png", "tower_two.png");
				break;
			case 3:
				towerSprite = Button::create("tower_three.png", "tower_three.png");
				break;
			default:
				break;
			}
			towerSprite->setPosition(towerPosition);
			// ÿ��������������������������Ϊ���ǵ�����
			// ��˿���ͨ����������������ҵ���Ӧ�ķ�����
			char*name1 = new char[20], *name2 = new char[20], *name3 = new char[20],
				*name4 = new char[20], *name5 = new char[20], *name6 = new char[20],
				*name7 = new char[20];

			sprintf(name1, "%d%d", int(mousePosition.x), int( mousePosition.y));
			this->addChild(towerSprite, 1, name1);

			// ɾ����ť
			auto deletebutton = Button::create("delete.png");
			sprintf(name2, "%d%d_d", int(mousePosition.x), int(mousePosition.y));
			deletebutton->setPosition(Vec2(towerPosition.x + 10, towerPosition.y));
			this->addChild(deletebutton, 2, name2);
			deletebutton->setVisible(false);

			// ������ť
			auto levelupbutton = Button::create("levelup.png");
			sprintf(name3, "%d%d_u", int(mousePosition.x), int(mousePosition.y));
			levelupbutton->setPosition(Vec2(towerPosition.x + 10, towerPosition.y + 10));
			this->addChild(levelupbutton, 2, name3);
			levelupbutton->setVisible(false);

			// �˳���ť
			auto returnbutton = Button::create("exit.png");
			sprintf(name4, "%d%d_r", int(mousePosition.x), int(mousePosition.y));
			returnbutton->setPosition(Vec2(towerPosition.x + 10, towerPosition.y - 10));
			this->addChild(returnbutton, 2, name4);
			returnbutton->setVisible(false);

			// ������ұ�ǩ
			auto levelupcoin = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 10);
			levelupcoin->setColor(Color3B(255, 255, 0));
			levelupcoin->setVisible(false);
			levelupcoin->setPosition(Vec2(towerPosition.x + 20, towerPosition.y + 10));
			sprintf(name5, "%d%d_c", int(mousePosition.x), int(mousePosition.y));
			this->addChild(levelupcoin, 2, name5);

			// �������ȼ���ǩ
			auto towerlevel = Label::createWithTTF("Lv.1", "fonts/Marker Felt.ttf", 10);
			towerlevel->setColor(Color3B(255, 0, 0));
			towerlevel->setVisible(false);
			towerlevel->setPosition(Vec2(towerPosition.x - 10, towerPosition.y - 10));
			sprintf(name6, "%d%d_l", int(mousePosition.x), int(mousePosition.y));
			this->addChild(towerlevel, 2, name6);

			// ������������Χ
			auto towerrange = Sprite::create("range.png");
			towerrange->setVisible(false);
			towerrange->setPosition(Vec2(towerPosition.x, towerPosition.y));
			sprintf(name7, "%d%d_g", int(mousePosition.x), int(mousePosition.y));
			this->addChild(towerrange, 2, name7);

			delete[]name1;
			delete[]name2;
			delete[]name3;
			delete[]name4;
			delete[]name5;
			delete[]name6;
			delete[]name7;

			// ���������
			towerSprite->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				deal_with_xy1(mousePosition.x, mousePosition.y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name2 = new char[20], *name3 = new char[20],
						*name4 = new char[20], *name5 = new char[20],
						*name6 = new char[20], *name7 = new char[20];

					sprintf(name2, "%d%d_d", int(mousePosition.x), int(mousePosition.y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(mousePosition.x), int(mousePosition.y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(mousePosition.x), int(mousePosition.y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(mousePosition.x), int(mousePosition.y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(mousePosition.x), int(mousePosition.y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					sprintf(name7, "%d%d_g", int(mousePosition.x), int(mousePosition.y));
					layout_range = (Sprite*)(getChildByName(name7));

					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;
					delete[]name7;

					// ������Ѱ����ѡ�ķ�����
					auto it = TowerExist.begin();
					int i = 0;
					while (it != TowerExist.end())
					{
						if (mousePosition.x == TowerExist[i]->getPositionX() && mousePosition.y == TowerExist[i]->getPositionY()) {
							int money = TowerExist[i]->getUpgradeCost();
							layout_coin->setString(std::to_string(money));
							char* levelname = new char[10];
							sprintf(levelname, "Lv.%d", TowerExist[i]->getLevel());
							layout_nowlevel->setString(levelname);
							delete levelname;
							break;
						}
						else {
							i++;
							it++;
						}
					}

					// �������������ɾ����������ť��Ϊ�ɼ�
					layout_delete->setVisible(true);
					layout_uplevel->setVisible(true);
					layout_return->setVisible(true);
					layout_coin->setVisible(true);
					layout_nowlevel->setVisible(true);
					layout_range->setVisible(true);
				}
					break;
				default:
					break;
				}
			});

			// ������ذ�ť
			returnbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				deal_with_xy1(mousePosition.x,mousePosition.y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name2 = new char[20], *name3 = new char[20],
						*name4 = new char[20], *name5 = new char[20],
						*name6 = new char[20], *name7 = new char[20];
					sprintf(name2, "%d%d_d", int(mousePosition.x), int(mousePosition.y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(mousePosition.x), int(mousePosition.y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(mousePosition.x), int(mousePosition.y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(mousePosition.x), int(mousePosition.y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(mousePosition.x), int(mousePosition.y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					sprintf(name7, "%d%d_g", int(mousePosition.x), int(mousePosition.y));
					layout_range = (Sprite*)(getChildByName(name7));

					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;
					delete[]name7;

					// ����˳���ť����ɾ����������ť��Ϊ���ɼ�
					layout_return->setVisible(false);
					layout_delete->setVisible(false);
					layout_uplevel->setVisible(false);
					layout_coin->setVisible(false);
					layout_nowlevel->setVisible(false);
					layout_range->setVisible(false);
				}
					break;
				default:
					break;
				}
			});

			// ���ɾ����ť
			deletebutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				deal_with_xy1(mousePosition.x, mousePosition.y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name1 = new char[20], *name2 = new char[20], *name3 = new char[20],
						*name4 = new char[20], *name5 = new char[20], *name6 = new char[20],
						*name7 = new char[20];
					sprintf(name1, "%d%d", int(mousePosition.x), int(mousePosition.y));
					auto layout_tower = this->getChildByName(name1);

					sprintf(name2, "%d%d_d", int(mousePosition.x), int(mousePosition.y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(mousePosition.x), int(mousePosition.y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(mousePosition.x), int(mousePosition.y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(mousePosition.x), int(mousePosition.y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(mousePosition.x), int(mousePosition.y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					sprintf(name7, "%d%d_g", int(mousePosition.x), int(mousePosition.y));
					layout_range = (Sprite*)(getChildByName(name7));

					delete[]name1;
					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;
					delete[]name7;

					// ���ɾ����ť���򽫷���������������ȫ���Ƴ�
					layout_tower->removeFromParentAndCleanup(true);
					layout_delete->removeFromParentAndCleanup(true);
					layout_uplevel->removeFromParentAndCleanup(true);
					layout_return->removeFromParentAndCleanup(true);
					layout_coin->removeFromParentAndCleanup(true);
					layout_nowlevel->removeFromParentAndCleanup(true);
					layout_range->removeFromParentAndCleanup(true);

					// ��Ҫע�����֮ǰ�������Ѿ�����vector�У��������ҲҪɾ��
					for (auto it = TowerExist.begin(); it != TowerExist.end();) {
						if (mousePosition.x == (*it)->getPositionX() && mousePosition.y == (*it)->getPositionY()) {
							it = TowerExist.erase(it);
							current_gold_coins += 10;
							updateGoldCoinsDisplay();
							showTowerGrey();
							break;
						}
						else {
							it++;
						}
					}
				}
					break;
				default:
					break;
				}
			});

			// ���������ť
			levelupbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				deal_with_xy1(mousePosition.x, mousePosition.y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name2 = new char[20], *name3 = new char[20],
						*name4 = new char[20], *name5 = new char[20],
						*name6 = new char[20], *name7 = new char[20];

					sprintf(name2, "%d%d_d", int(mousePosition.x), int(mousePosition.y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(mousePosition.x), int(mousePosition.y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(mousePosition.x), int(mousePosition.y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(mousePosition.x), int(mousePosition.y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(mousePosition.x), int(mousePosition.y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					sprintf(name7, "%d%d_g", int(mousePosition.x), int(mousePosition.y));
					layout_range = (Sprite*)(getChildByName(name7));

					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;
					delete[]name7;

					// ���������ť��������ͨ��������Ѱ����Ҫ�����ķ�����
					auto it = TowerExist.begin();
					int i = 0;
					while (it != TowerExist.end())
					{
						if (mousePosition.x == (*it)->getPositionX() && mousePosition.y == (*it)->getPositionY()) {
							// ����ȼ�С������
							if (TowerExist[i]->getLevel() < 4)
							{
								// ���Ǯ��
								if (TowerExist[i]->upgrade(current_gold_coins)) {
									updateGoldCoinsDisplay();
									showTowerGrey();
								}
								else
									showInsufficientGoldLabel();
							}
							else
							{
								showInsufficientLevelLabel();
								layout_uplevel->setVisible(false);
							}
							break;
						}
						else {
							i++;
							it++;
						}
					}
					layout_delete->setVisible(false);
					layout_uplevel->setVisible(false);
					layout_return->setVisible(false);
					layout_coin->setVisible(false);
					layout_nowlevel->setVisible(false);
					layout_range->setVisible(false);
				}
					break;
				default:
					break;
				}
			});
			// ����֮�󽫿ɽ���λ����Ϊ���ɼ�
			for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
				board[i]->setVisible(false);
			}
		}

		else if (place_success)
		{
			showInsufficientPlaceLabel();
		}
		already = 0;
	}
}

// ��δѡ�з�����
void Game_one::onMouseDown1(EventMouse* event)
{
	mousePosition = this->convertToNodeSpace(event->getLocationInView());
	if(already==0)
	{
		tower0Clicked = checkTower0Clicked(mousePosition);
		if (tower0Clicked != -1)
		{
			// �������������߼�
			if (current_gold_coins < getTowerUpgradeCoins(tower0Clicked))
			{
				showInsufficientGoldLabel();
				already = 0;
			}
			else
			{
				already = 1;
			}

		}
		else
		{
			already = 0;
			for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
				board[i]->setVisible(false);
			}
		}
		return;
		
	}
}

// �Ƿ�������ߵķ�������
int Game_one::checkTower0Clicked(const Vec2& touchLocation)
{
	// �����߷�������λ�úʹ�С
	Rect towerRects[] = {
		Rect(26, 212, 45, 36),  // ��߷�����0�����½����꣬�Ϳ��ȣ��߶�
		Rect(26, 167, 45, 36),  // ��߷�����1
		Rect(26, 122, 45, 36),  // ��߷�����2
		Rect(26, 77,  45, 36)   // ��߷�����3
	};

	for (int i = 0; i < 4; ++i)
	{
		if (towerRects[i].containsPoint(touchLocation))
		{
			// �������������������ط�������������ֵ
			return i;
		}
	}

	// ���û�е����������������-1
	return -1;
}

// ��ʾ��Ҳ��㣬1�����ʧ
void Game_one::showInsufficientGoldLabel()
{
	insufficientGoldLabel->setVisible(true);

	// ʹ�ö�ʱ���ӳ�1������ر�ǩ
	this->scheduleOnce([this](float dt) {
		insufficientGoldLabel->setVisible(false);
	}, 1.0f, "hideInsufficientGoldLabel");
}

// ��ʾ����λ�ô���1�����ʧ
void Game_one::showInsufficientPlaceLabel()
{
	insufficientPlaceLabel->setVisible(true);

	// ʹ�ö�ʱ���ӳ�1������ر�ǩ
	this->scheduleOnce([this](float dt) {
		insufficientPlaceLabel->setVisible(false);
	}, 1.0f, "hideInsufficientPlaceLabel");
}

// ��ʾ�Ѵﵽ��߼���1�����ʧ
void Game_one::showInsufficientLevelLabel()
{
	insufficientLevelLabel->setVisible(true);

	// ʹ�ö�ʱ���ӳ�1������ر�ǩ
	this->scheduleOnce([this](float dt) {
		insufficientLevelLabel->setVisible(false);
	}, 1.0f, "hideInsufficientLevelLabel");
}

// ������ʱ��
void Game_one::step(float Dt)
{
	countnum -= 1;
	char StringOfNum[50] = { 0 };
	if (countnum > 0) {
		sprintf(StringOfNum, "Monsters strike %d seconds later", countnum);
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= 0 && countnum > -18) {
		sprintf(StringOfNum, "Wave 1 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -18 && countnum > -36) {
		sprintf(StringOfNum, "Wave 2 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -36 && countnum > -56) {
		sprintf(StringOfNum, "Wave 3 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -56 && countnum > -75) {
		sprintf(StringOfNum, "Wave 4 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -75 && countnum > -94) {
		sprintf(StringOfNum, "Wave 5 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -94 && countnum > -113) {
		sprintf(StringOfNum, "Wave 6 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -113 && countnum > -133) {
		sprintf(StringOfNum, "Wave 7 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else {
		sprintf(StringOfNum, "Wave 8 / 8");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
}