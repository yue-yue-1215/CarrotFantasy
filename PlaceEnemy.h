#ifndef __GENERATE__ENEMY__H__
#define __GENERATE__ENEMY__H__
#include "Enemy.h"
#include "Enemytype.h"
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

extern vector<Enemy*> EnemyExist;

class GenerateEnemy : public cocos2d::Node
{
public:
    void generateOneEnemy(vector<Enemy*>& EnemyExist, int enemyType, double x, double y);
    void deleteEnemy(vector<Enemy*>& EnemyExist);
    int numofEnemyAlive(vector<Enemy*>& EnemyExist);
    void generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y); // 生成一波怪物

    cocos2d::Scene* _currentScene; // 当前场景
    vector<vector<int>> _enemyWaves; // 敌人波次
    unsigned int _currentWave; // 当前波次索引
    unsigned int _currentEnemyIndex; // 当前敌人索引
    double _startX, _startY; // 起始坐标

    GenerateEnemy(cocos2d::Scene* scene, const vector<vector<int>>& waves, double startX, double startY)
        : _currentScene(scene), _enemyWaves(waves), _currentWave(0),
        _currentEnemyIndex(0), _startX(startX), _startY(startY) {}

    void startGenerating()
    {
        this->schedule([this](float) {
            if (_currentWave < _enemyWaves.size()) // 检查是否还有波次
            {
                if (_currentEnemyIndex < _enemyWaves[_currentWave].size()) // 检查当前波次是否还有敌人
                {
                    generateOneEnemy(EnemyExist, _enemyWaves[_currentWave][_currentEnemyIndex], _startX, _startY);
                    ++_currentEnemyIndex; // 增加敌人索引
                }
                else
                {
                    ++_currentWave; // 进入下一波次
                    _currentEnemyIndex = 0; // 重置敌人索引
                }
            }
            }, 0.5f, "generateEnemy_key"); // 每0.5秒生成一个敌人
    }
};
#endif