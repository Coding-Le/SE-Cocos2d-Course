#ifndef __ChooseLevel_SCENE_H__
#define __ChooseLevel_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
class ChooseLevel : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScence();
	virtual bool init();
	void ReturnMain(Ref *ref);
	void Level_1(Ref* ref);
	void Schedule(Ref *ref);
	CREATE_FUNC(ChooseLevel);
	void updateTime1(float dt);
private:
	float totalTime1;
	cocos2d::Label* timerStr1;
};
#endif