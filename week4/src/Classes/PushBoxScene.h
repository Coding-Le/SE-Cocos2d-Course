#ifndef __PushBoxScene_SCENE_H__
#define __PushBoxScene_SCENE_H__

#include "cocos2d.h"
#include<vector>
USING_NS_CC;

class PushBoxScene :public Layer
{
public:
	PushBoxScene();
	~PushBoxScene();
	static cocos2d::Scene* createScence();
	CREATE_FUNC(PushBoxScene);

	virtual bool init();


	void initTouchEvent();
	bool can(int tx, int ty);
	bool isbox(int tx, int ty);

	void onRightPressed(Ref* sender);
	void onLeftPressed(Ref* sender);
	void onUpPressed(Ref* sender);
	void onDownPressed(Ref* sender);
	void createmysql(Ref* sender);
	void myend();
	void myplay(Ref *ref);
private:
	Size visibleSize;
	Sprite* mon;
	float myx;
	float myy;
	int count;
	Vector<Sprite*>mywall;
	Vector<Sprite*>mybox;
	Vector<Sprite*>mygoal;
	int success;
};
#endif