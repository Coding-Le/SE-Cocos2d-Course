#include "HelloWorldScene.h"
#include <iostream>
#include <string>

#pragma execution_character_set("utf-8")
using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
	
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* background = Sprite::create("background.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background);

	fisher_layer = Layer::create();
	weapon_layer = Layer::create();
	
	fisher_layer->setAnchorPoint(ccp(0, 0));
	fisher_layer->setPosition(0, visibleSize.width/2);
	weapon_layer->setAnchorPoint(ccp(0,0));
	weapon_layer->setPosition(0, 0);
	this->addChild(fisher_layer);
	this->addChild(weapon_layer);
    

	//add background
	

	//create a fish sprite and run animation
	m_fish = Sprite::createWithSpriteFrameName("fish13_01.png");
	Animate* fishAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("fishAnimation"));
	m_fish->runAction(RepeatForever::create(fishAnimate));
	fisher_layer->addChild(m_fish);
	m_fish->setPosition(visibleSize.width / 2, 0);

	
	auto wea = MenuItemLabel::create(Label::createWithTTF("Shoot", "fonts/Marker Felt.ttf", 36), CC_CALLBACK_1(HelloWorld::myClick, this));
	//button->setPosition(Vec2(origin.x + visibleSize.width - button->getContentSize().width / 2,
	//origin.y + button->getContentSize().height / 2));
	auto menu = Menu::create(wea, NULL);
	//menu->setPosition(Vec2(origin.x + visibleSize.width - menu->getContentSize().width / 2,
	//origin.y + visibleSize.height - menu->getContentSize().height / 2));
	menu->setPosition(visibleSize.width-100, 50);
	this->addChild(menu, 1);

	m_weapon = Sprite::create("CloseNormal.png");
	//Sprite* m_weapon = Sprite::create("NormalClose.png");
	//Animate* weaponAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("weaponAnimation"));
	//m_weapon->runAction(RepeatForever::create(weaponAnimate));
	m_weapon->setPosition(visibleSize.width / 2, 50);
	weapon_layer->addChild(m_weapon);
	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//add click listener 

	
    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCPoint poss = touch->getLocation();
	CCPoint p = fisher_layer->convertToNodeSpace(poss);
	auto curveMove = MoveTo::create(0.3f, p);
	auto myangle = -atan((p.y - m_fish->getPositionY()) / (p.x - m_fish->getPositionX())) / 3.1415926 * 180;
	if (p.y > m_fish->getPositionY() && p.x > m_fish->getPositionX()){
		myangle = myangle + 180;
	}
	else if (p.y < m_fish->getPositionY() && p.x > m_fish->getPositionX()) {
		myangle = myangle + 180;
	}
	m_fish->runAction(curveMove);
	m_fish->setRotation(myangle);
	return true;
}

void HelloWorld::myClick(Ref* ref) {
	CCPoint po = m_fish->getPosition();
	CCPoint pos = fisher_layer->convertToWorldSpace(po);
	CCPoint poss = weapon_layer->convertToNodeSpace(pos);
	//CCPoint p = m_fish->getPosition();
	auto curveMove = MoveTo::create(0.6f, poss);
	m_weapon->runAction(curveMove);
}