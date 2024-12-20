#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__
#include "cocos2d.h"
class MyMap : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuOkCallback(Ref *pSender);
	CREATE_FUNC(MyMap);
};
#endif 