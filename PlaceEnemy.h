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
    void generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y); // ����һ������

    cocos2d::Scene* _currentScene; // ��ǰ����
    vector<vector<int>> _enemyWaves; // ���˲���
    unsigned int _currentWave; // ��ǰ��������
    unsigned int _currentEnemyIndex; // ��ǰ��������
    double _startX, _startY; // ��ʼ����

    GenerateEnemy(cocos2d::Scene* scene, const vector<vector<int>>& waves, double startX, double startY)
        : _currentScene(scene), _enemyWaves(waves), _currentWave(0),
        _currentEnemyIndex(0), _startX(startX), _startY(startY) {}

    void startGenerating()
    {
        this->schedule([this](float) {
            if (_currentWave < _enemyWaves.size()) // ����Ƿ��в���
            {
                if (_currentEnemyIndex < _enemyWaves[_currentWave].size()) // ��鵱ǰ�����Ƿ��е���
                {
                    generateOneEnemy(EnemyExist, _enemyWaves[_currentWave][_currentEnemyIndex], _startX, _startY);
                    ++_currentEnemyIndex; // ���ӵ�������
                }
                else
                {
                    ++_currentWave; // ������һ����
                    _currentEnemyIndex = 0; // ���õ�������
                }
            }
            }, 0.5f, "generateEnemy_key"); // ÿ0.5������һ������
    }
};
#endif