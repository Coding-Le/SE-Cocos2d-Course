#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Demo :public Layer
{
public:
	static Scene* createScene();
	static Demo* create(PhysicsWorld* world);
	bool init(PhysicsWorld* world);

	void testContact();
	bool onContactBegan(PhysicsContact& contact);
	void testContactFilter();
	void testTouchEvent();
	void testPhysicsJointSpring();
	void testPhysicsJointDistance();

	void testParticleFireworks();
	void testParticleSnow();
	void testExternalParticle();

	void turnoff();
	void testCustomEvent();
private:
	Demo();
	~Demo();
	EventDispatcher* dispatcher;

	MotionStreak* streak;

	Vec2 touch_pos;

	bool isTouching;
	bool isCut;

	PhysicsWorld* m_world;
	Sprite* m_basketball;
	Sprite* m_soccer;
	Sprite* m_cat;
	Sprite* m_cat2;
	Sprite* m_brick;
	Sprite* m_brick2;
	Sprite* m_apple;
	Sprite* m_rope;
	PhysicsJointFixed * rope_apple;
	PhysicsJointPin* my_pin;
};