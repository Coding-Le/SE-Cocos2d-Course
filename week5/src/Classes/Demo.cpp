#include "Demo.h"
#include <string>
using namespace std;
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* Demo::createScene(){
	// 'scene' is an autorelease object
	
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Demo::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}
Demo::Demo()
{

}

Demo::~Demo()
{

}

bool Demo::init()
{
	isCut = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!Layer::init())
	{
		return false;
	}
	preloadMusic();
	dispatcher = Director::getInstance()->getEventDispatcher();

    man = Sprite::create("Demo/monster.png");
	man->setPosition(visibleSize.width / 2, man->getContentSize().height/2);
	this->addChild(man,1);

	rope = Sprite::create("Demo/rope.png");
	rope->setPosition(visibleSize.width / 2, visibleSize.height-rope->getContentSize().height/2);
	this->addChild(rope, 1);

	box = Sprite::create("Demo/box.png");
	box->setPosition(visibleSize.width / 2, visibleSize.height - rope->getContentSize().height-box->getContentSize().height/2);
	this->addChild(box, 1);
	//preloadMusic();
	//playBgm();

	//此demo中自定义事件由触摸事件onTouchBegan触发
	testTouchEvent();
	testCustomEvent();
	
	playBgm();
	//testKeyboardEvent();
	//testMouseEvent();
	
	//testAccelerationEvent();

	//testDemo();

	return true;
}

void Demo::preloadMusic()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/Ninja_Turtles_Theme_Song.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/shoot.mp3");
}

void Demo::playBgm()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/Ninja_Turtles_Theme_Song.mp3", true);
}

void Demo::playEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("music/shoot.mp3");
}



void Demo::testTouchEvent()
{
	streak = MotionStreak::create(0.5f, 10, 30, Color3B::WHITE, "Demo/flash.png");
	this->addChild(streak, 2);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		touch_pos = touch->getLocation();
		
		EventCustom e("test");

		e.setUserData(&touch_pos);

		dispatcher->dispatchEvent(&e);

		return true;
	};

	listener->onTouchMoved = [&](Touch* touch, Event* event){
		touch_pos = touch->getLocation();
		//滑动拖尾效果
		if (!isCut) {
			if (abs(touch_pos.x - rope->getPositionX()) < rope->getContentSize().width / 2 && abs(touch_pos.y - rope->getPositionY()) < rope->getContentSize().height / 2) {
				isCut = true;
				auto my_fade = FadeOut::create(1.0f);
				rope->runAction(my_fade);
				auto action = MoveTo::create(3, Vec2(Director::getInstance()->getVisibleSize().width / 2, man->getContentSize().height + box->getContentSize().height / 2));
				auto action1 = ScaleTo::create(3.0f, 1.0f);
				auto action2 = Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Demo::turnoff,this)), NULL);
				box->runAction(action2);
				playEffect();
			}
		}
		streak->setPosition(touch_pos);
		/*if (abs(touch_pos.x - rope->getPositionX()) < rope->getContentSize().width / 2 && abs(touch_pos.y - rope->getPositionY()) < rope->getContentSize().height / 2) {
			if (isCut = false) {
				isCut = true;
				auto action = MoveTo::create(3, Vec2(Director::getInstance()->getVisibleSize().width/2, man->getContentSize().height + box->getContentSize().height / 2));
				auto action1 = Speed::create(action, 1.0f);
				this->runAction(action);
			}
		}*/
	};

	listener->onTouchEnded = [&](Touch* touch, Event* event){
		log("onTouchEnded");
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Demo::testAccelerationEvent()
{
	Device::setAccelerometerEnabled(true);

	auto listener = EventListenerAcceleration::create([](Acceleration* acceleration, Event* event){
		log("X: %f; Y: %f; Z:%f; ", acceleration->x, acceleration->y, acceleration->z);
	});

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Demo::testKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event){
		if (code==EventKeyboard::KeyCode::KEY_A)
		{
			log("onKeyPressed--A");
		}
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event){
		if (code == EventKeyboard::KeyCode::KEY_A)
		{
			log("onKeyReleased--A");
		}
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Demo::testMouseEvent()
{
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [&](Event* event){
		log("onMouseDown");
	};

	listener->onMouseMove = [&](Event* event){
		EventMouse* my_mouse = (EventMouse*)event;

	};

	listener->onMouseUp = [&](Event* event){
		log("onMouseUp");
	};

	listener->onMouseScroll = [&](Event* event){
		log("onMouseScroll");
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Demo::testCustomEvent()
{
	auto listener = EventListenerCustom::create("off", [](EventCustom* event){
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	});
	dispatcher->addEventListenerWithFixedPriority(listener, 1);
}

void Demo::turnoff() {
	EventCustom e("off");

	e.setUserData(&touch_pos);

	dispatcher->dispatchEvent(&e);
}