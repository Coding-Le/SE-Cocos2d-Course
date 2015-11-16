#ifndef __MYINITSCENE_SCENE_H__
#define __MYINITSCENE_SCENE_H__
#include "cocos2d.h"
#include <string>
using namespace std;
USING_NS_CC;

class myScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(myScene);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	void myScene::myClick(Ref *ref);
private:
	Sprite* mybutton;
};
#endif