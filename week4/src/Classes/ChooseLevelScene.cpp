#include "ChooseLevelScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* ChooseLevel::createScence(){
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChooseLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ChooseLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}
	totalTime1 = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//creat Level_1
	/*auto level_1 = MenuItemImage::create(
		"levelbutton/button_level_1.png", "levelbutton/button_clicked_level_1.png", "levelbutton/button_locked_level_1.png", CC_CALLBACK_1(ChooseLevel::Level_1, this));

	//creat Level_2
	auto level_2 = MenuItemImage::create(
		"levelbutton/button_level_2.png", "levelbutton/button_clicked_level_2.png", "levelbutton/button_locked_level_2.png", CC_CALLBACK_1(ChooseLevel::Level_1, this));
	level_2->setEnabled(false);

	auto menu = Menu::create(level_1, level_2, NULL);
	menu->alignItemsHorizontallyWithPadding(level_1->getContentSize().width / 3 * 2);
	menu->setPosition(visibleSize.width / 2, visibleSize.height-visibleSize.height/4);
	this->addChild(menu,1);*/
	auto level_1 = MenuItemImage::create(
		"meizi1.png", "meizi3.png", "meizi2.png", CC_CALLBACK_1(ChooseLevel::Level_1, this));

	//creat Level_2
	auto level_2 = MenuItemImage::create(
		"meizi1.png", "meizi3.png", "meizi2.png", CC_CALLBACK_1(ChooseLevel::Level_1, this));
	level_2->setEnabled(false);

	auto menu = Menu::create(level_1, level_2, NULL);
	menu->alignItemsHorizontallyWithPadding(level_1->getContentSize().width / 3 * 2);
	menu->setPosition(visibleSize.width / 2, visibleSize.height - visibleSize.height / 4);
	this->addChild(menu, 1);

	auto bgsprite = Sprite::create("my2.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds =  bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1/odds);
	bgsprite->setPosition(Vec2(visibleSize / 2) + origin);
	this->addChild(bgsprite,0);


	//background
	auto backItem = MenuItemImage::create("back_normal.png", "back_clicked.png", CC_CALLBACK_1(ChooseLevel::ReturnMain, this));
	backItem->setPosition(origin + Vec2(visibleSize.width,0) - Vec2(backItem->getContentSize().width,-backItem->getContentSize().height));
	auto menuback = Menu::create(backItem, NULL);
	menuback->setPosition(Vec2::ZERO);
	this->addChild(menuback, 1);

	//SpriteFrame
	auto newSprite = Sprite::create("image/Blue_Front1.png");
	newSprite->setPosition(Director::getInstance()->getVisibleSize().width / 5 * 4, Director::getInstance()->getVisibleSize().height / 5);
	this->addChild(newSprite);
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(12);
	animFrames.pushBack(SpriteFrame::create("image/Blue_Front1.png", Rect(0, 0,65,81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Front2.png", Rect(0, 0, 65,81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Front3.png", Rect(0, 0, 65,81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Left1.png", Rect(0, 0, 65,81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Left2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Left3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Back1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Back2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Back3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Right1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Right2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("image/Blue_Right3.png", Rect(0, 0, 65, 81)));
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	auto animate = Animate::create(animation);
	newSprite->runAction(RepeatForever::create(animate));

	Vector<SpriteFrame*> animFrames1;
	auto newSprite1 = Sprite::create("image/1.png");
	newSprite1->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(newSprite1);
	animFrames1.reserve(17);
	animFrames1.pushBack(SpriteFrame::create("image/1.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/2.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/3.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/4.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/5.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/6.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/7.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/8.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/9.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/10.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/11.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/12.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/13.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/14.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/15.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/16.png", Rect(0, 0, 135, 100)));
	animFrames1.pushBack(SpriteFrame::create("image/17.png", Rect(0, 0, 135, 100)));
	// create the animation out of the frames
	auto animation1 = Animation::createWithSpriteFrames(animFrames1, 0.2f);
	auto animate1 = Animate::create(animation1);
	newSprite1->runAction(RepeatForever::create(animate1));

	
	//progressBar
	auto progressSprite = Sprite::create("image/Blue_Front1.png");
	auto pT = ProgressTimer::create(progressSprite);
	pT->setType(ProgressTimer::Type::BAR);
	pT->setMidpoint(Point(0, 0));
	pT->setBarChangeRate(Point(1, 0));
	pT->runAction(RepeatForever::create(ProgressFromTo::create(5, 0, 100)));
	pT->setPosition(Point(200,200));
	this->addChild(pT);

	auto nSprite = Sprite::create("image/rge.png");
	

	auto myitem3 = MenuItemLabel::create(Label::createWithTTF("Start", "fonts/STRIPES STARS Normal.ttf", 48), CC_CALLBACK_1(ChooseLevel::Schedule, this));

	// create menu, it's an autorelease object
	auto menu1 = Menu::create(myitem3, NULL);
	menu1->setPosition(Director::getInstance()->getVisibleSize().width / 2, 275);
	menu1->alignItemsVerticallyWithPadding(24);
	this->addChild(menu1, 1);

	timerStr1 = Label::createWithTTF("0%", "fonts/Marker Felt.ttf", 40);
	auto timerStrPos = Vec2(Director::getInstance()->getVisibleSize().width / 2, 100);
		//Point(Director::getInstance()->getVisibleSize().width / 5 * 4, Director::getInstance()->getVisibleSize().height / 5 * 2);
	timerStr1->setColor(Color3B::BLACK);
	timerStr1->setPosition(timerStrPos);
	this->addChild(timerStr1, 1);
	return true;
}

void ChooseLevel::ReturnMain(Ref *ref)
{
	this->stopAllActions();
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void ChooseLevel::Level_1(Ref* ref)
{
	
}

void ChooseLevel::updateTime1(float dt){
	totalTime1 += dt;
	if (totalTime1 > 10) {
		totalTime1 = totalTime1 - 10;
	}
	char t[10];
	char* who = "%";
	int d = totalTime1 * 10;
	sprintf(t, "%d%s", d, who);
	timerStr1->setString(t);
}

void ChooseLevel::Schedule(Ref *ref) {
	schedule(schedule_selector(ChooseLevel::updateTime1), 0.1f);
	auto progressSprite1 = Sprite::create("image/rge.png");
	auto pT1 = ProgressTimer::create(progressSprite1);
	pT1->setType(ProgressTimer::Type::BAR);
	pT1->setMidpoint(Point(0, 0));
	pT1->setBarChangeRate(Point(1, 0));
	pT1->runAction(RepeatForever::create(ProgressFromTo::create(10, 0, 100)));
	pT1->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 100));
	this->addChild(pT1);
}