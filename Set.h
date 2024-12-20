#ifndef __GAME_DEFAULT__H__
#define __GAME_DEFAULT__H__

#include "cocos2d.h"

USING_NS_CC;

class Default : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr);
	CREATE_FUNC(Default);
	void RestartGame(Ref *pSender);
	void ReturnMenuGame(Ref *pSender);
};
#endif 