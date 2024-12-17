#ifndef __GAME_PAUSE__H__
#define __GAME_PAUSE__H__
#include "cocos2d.h"
USING_NS_CC;

class Pause : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr);
	CREATE_FUNC(Pause);
	void ContinueGame(Ref *pSender);
	void RestartGame(Ref *pSender);
	void ReturnMenuGame(Ref *pSender);
};
#endif 