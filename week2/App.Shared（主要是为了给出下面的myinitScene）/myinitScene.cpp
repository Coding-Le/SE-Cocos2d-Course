#include "myinitScene.h"
#include"HelloWorldScene.h"
#include <iostream>
#include <string>

#pragma execution_character_set("utf-8")
using namespace std;

USING_NS_CC;

Scene* myScene::createScene()
{
	auto scene = Scene::create();
	auto layer = myScene::create();
	scene->addChild(layer);

	return scene;
}

bool myScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//add background
	//Sprite* background = Sprite::create("denglu.jpg");
	//background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//addChild(background);
	
	//create a fish sprite and run animation
	//mybutton = Sprite::createWithSpriteFrameName("fish13_01.png");
	//Animate* fishAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("fishAnimation"));
	//m_fish->runAction(RepeatForever::create(fishAnimate));
	//mybutton->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//addChild(button);
	auto button = MenuItemLabel::create(Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 36), CC_CALLBACK_1(myScene::myClick, this));
	//button->setPosition(Vec2(origin.x + visibleSize.width - button->getContentSize().width / 2,
		//origin.y + button->getContentSize().height / 2));
	auto menu = Menu::create(button, NULL);
	//menu->setPosition(Vec2(origin.x + visibleSize.width - menu->getContentSize().width / 2,
		//origin.y + visibleSize.height - menu->getContentSize().height / 2));
	menu->setPosition(visibleSize/2);
	this->addChild(menu,1);
	//addChild(mybutton);
	
	
	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(myScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool myScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	/*
	to be implemented
	*/
	return true;
}
void myScene::myClick(Ref* ref) {
	CCDirector::getInstance()->replaceScene(HelloWorld::createScene());
}