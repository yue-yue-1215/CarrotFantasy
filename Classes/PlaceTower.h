#ifndef __PLACE__TOWER__H__
#define __PLACE__TOWER__H__
#include"Tower.h"
#include"Towertype.h"
#include<vector>
#include"cocos2d.h"
extern vector<Tower*> TowerExist;
void placeTower(vector<Tower*>& TowerExist, int towerType, int x, int y);
#endif