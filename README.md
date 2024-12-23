## 项目简介
参考游戏《保卫萝⼘》，创建萝卜、怪物、防御塔等三种基本精灵，实现攻击逻辑、收益计算和过关认定等

## 功能实现
- ⽀持⾄少3种防御塔和防御塔的删除。
- 需要每种防御塔的攻击特效，⾄少要完成发射物弹道
- 怪物、萝⼘⽣命值显示
- ⽀持资源功能，资源可⽤于购买防御塔，资源可通过击杀怪物获得
- ⽀持每种防御塔的升级，⾄少可升级2次
- ⽀持萝⼘的升级，⾄少可升级2次
- ⽀持⾄少3种怪物
- ⽀持⾄少2张地图
- ⽀持背景⾳乐
- 需要关卡选择界⾯和保存通关进度记录功能（即已完成哪些关卡，可进⾏哪些关卡，哪些关卡还需解锁）
- ⽀持攻击、建造、击杀时的⾳效
- ⽀持选定攻击⽬标
- ⽀持场景破坏功能，即需要先将场景中的元素破坏后再⽣成防御塔底座进⽽建造防御塔的设定（提示：本功能最好以选定攻击⽬标功能为前提）
- ⽀持特殊技能，如AOE/单体伤害技能或增益技能
- 暂停游戏功能
- ⽀持中途退出时记录当前状态，下次进⼊同⼀关卡继续上⼀次游戏进程的功能

## 项目结构
* **Classes**
  
- **界面创建相关**  
  - `Start`
  - 游戏的主菜单界面，包括背景图片、开始游戏按钮、关闭游戏按钮和声音控制按钮
  - `Pause`
  - 创建和管理游戏暂停场景,包括暂停界面、继续游戏、重新开始游戏和返回菜单  
  - `Set`
  - 实现游戏失败的界面逻辑，包括显示菜单、重新开始游戏和返回主菜单的功能  
  - `End`
  - 创建和管理游戏结束场景，在玩家完成关卡时显示，提供继续游戏或返回主菜单的选项
    

 - **怪物创建相关**  
    - `Enemy`
    - 定义了一个名为Enemy的类，用于表示游戏中的敌人状态，包括敌人的属性和行为，如生命值、速度、位置、状态（如减速、眩晕、死后获得金币）等
    - `EnemyType`
    - 定义了多个敌人类型，每个类都继承自一个基类Enemy，重写了构造函数和析构函数  
    - `Place Enemy`
    - 用于生成、删除和管理游戏中的敌人 

- **防御塔创建相关**
- `Tower`
    - 实现了防御塔的核心功能，包括设置位置、获取属性、升级、攻击敌人等。防御塔的攻击逻辑依赖于判断敌人的位置是否在防御塔的攻击范围
    - `EnemyType`
    - 定义了多个敌人类型，每个类都继承自一个基类Enemy，重写了构造函数和析构函数  
    - `PlaceTower`
    - 游戏中放置不同类型的防御塔，并将新创建的塔添加到TowerExist中储存，初始化塔的类型、等级、升级金币等
    
- **地图创建相关**
   - ` Map`
   - 定义了一个MyMap类，用于创建和管理游戏的地图选择场景。它提供了地图选择界面，包括地图一和地图二的按钮，以及地图完成状态和解锁状态的显示
- **游戏场景整合**
   - ` level`
   - 创建场景并初始化，加载背景和UI元素
   - 实现萝卜升级，检查金币是否足够，更新萝卜的生命值和等级
   - 创建并更新萝卜的血条，并设置初始百分比为100%
   - 创建侧边防御塔图标，并显示升级所需的金币数量
   - 显示金币不足、放置错误、等级已满等提示
   - 敌人的移动、路径控制和状态更新（如眩晕、减速）
   - 敌人的生命值变化和血条更新
   - 敌人的死亡处理和金币奖励
   - 实现防御塔的攻击逻辑，包括子弹的生成和移动
   - 判断游戏结束和胜利条件，并切换到相应的场景
   - 判断开始生成怪物
   - 每秒增加金币，并更新金币显示
   - 根据金币数量更新灰色防御塔的可见性
   - 暂停游戏并切换到暂停场景
   - 更新敌人波数信息

* **Resources**
- 资源文件
* **cocos2d**
- Cocos2d依赖文件

## 功能展示
  * [x]界面精美
    高度还原保卫萝卜游戏，在游戏中截取清晰的精灵图片并调整为合适的大小，生命值采用进度条的方式水平滑动更加流畅，且为独立完成
    
  * [x] C++特性实现

    * 类和多态性
    * 解释：
    - GameScene提供了多个纯虚函数，需要在派生类中实现具体的场景逻辑
    - Game_one和Game_two分别常量数组定义了不同的塔可放置的位置并通过重写基类的纯虚函数来实现各自的场景逻辑
    - 优点：利用多态性，使不同的游戏场景可以共享相同的接口，同时拥有各自的特性
      
    ```cpp
    * // 游戏场景基类，定义公共接口和成员变量
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
    }；
    
    ```cpp
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
    }；
    
* STL容器和迭代器
  
     * 解释：
    - EnemyExist是一个STL容器，用于存储敌人对象
    - 优点：提供了动态数组的功能，可以方便地存储和操作多个对象
    - enemy_it是一个迭代器，用于遍历EnemyExist容器中的元素。
      EnemyExist.begin()：返回容器的起始迭代器，指向容器中的第一个元素。EnemyExist.end()：返回容器的结束迭代器，指向容器中最后一个元素的下一个位置。
    - 优点：允许在不暴露底层数据结构的情况下遍历和修改容器

* 指针的使用
   * 解释：
    - 引用传递一个vector<Tower*>，表示当前存在的塔列表，创建Tower0对象，并调用initial方法初始化塔的属性
    - 优点：允许动态内存分配、多态性和灵活的对象管理
      
    ```cpp
    void placeTower(vector<Tower*>& TowerExist, int towerType, int x, int y){
	  Tower* newTower = nullptr;
	  switch (towerType) {
	  case 0:
		newTower = new Tower0();
		newTower->initial(0, 1, tower0_upgrade_coins, tower0_attack, tower0_attack_range, 0);
		break;
	  case 1:
		newTower = new Tower1();
		newTower->initial(1, 1, tower1_upgrade_coins, tower1_attack, tower1_attack_range, 0);
		break;
	  case 2:
		newTower = new Tower2();
		newTower->initial(2, 1, tower2_upgrade_coins, tower2_attack, tower2_attack_range, 0);
		break;
	  case 3:
		newTower = new Tower3();
		newTower->initial(3, 1, tower3_upgrade_coins, tower3_attack, tower3_attack_range, 0);
		break;
	  default:
		break;
	  }
	  if (newTower){
		    newTower->setPosition(x, y);
		    TowerExist.push_back(newTower);
		    cout << newTower->getType();
		    cout << newTower->getDamage();
		    cout << newTower->getType();
	    }
    }
    
* 哈希表的使用
   * 解释：
    - 定义了一个哈希表，键类型为int，值类型为std::string,用于存储敌人类型与其对应精灵图片的关联
    - 优点：提供了平均常数时间复杂度的查找性能，适合需要快速获取对应资源的场景，通过映射，避免了大量的switch-case 语句，使代码更加简洁
      
  ```cpp
  // 使用unordered_map存储怪物类型
  static const std::unordered_map<int, std::string> enemySpriteMap = {
     {0, "Enemy_zero.png"},
     {1, "Enemy_one.png"},
     {2, "Enemy_two.png"},
     {3, "Enemy_three.png"},
     {4, "Enemy_four.png"}
   };

## 开发日志

* 2024/12/2
- 放弃cocos2d-x 4.0版本改用3.17版本，所有环境已经配置好

* 2024/12/5
- 打开界面、暂停界面、结束界面设计

* 2024/12/8
- 制作游戏地图，完成菜单栏实现

* 2024/12/11
- 处理防御塔位置放置和攻击逻辑

* 2024/12/13
- 设计怪物属性和行为

* 2024/12/17
- 进一步调整血条设置、升级与删除条件设置通关判定条件

* 2024/12/22 
- 编写详细文档说明，制作幻灯片
