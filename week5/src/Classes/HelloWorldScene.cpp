#include "HelloWorldScene.h"
#include"ChooseLevelScene.h"
#include"PushBoxScene.h"
#pragma execution_character_set("utf-8") 
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object

    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	totalTime = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto label = Label::createWithBMFont("fonts/futura-48.fnt", "Paper Plane");
	auto label1 = Label::create("action", "Arial", 48);
	label1->setTextColor(Color4B::GREEN);
	auto label2 = Label::createWithBMFont("fonts/blue2.fnt", "New Label");
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height-50));
	label2->setPosition(Point(visibleSize.width / 2 , 100));
	this->addChild(label1,1);
	this->addChild(label2,1);
	//TTFConfig ttfConfig;
	//ttfConfig.fontSize = 30;
	//ttfConfig.fontFilePath = "Paint Boy.ttf";
	auto label3 = LabelTTF::create("Create with LabelTTF", "Arial", 50);
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height - 100));
	this->addChild(label3,1);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	auto myitem1 = MenuItemLabel::create(Label::createWithSystemFont("myplay", "Cobel", label->getContentSize().height), CC_CALLBACK_1(HelloWorld::myplay, this));
	auto myitem2 = MenuItemLabel::create(Label::createWithTTF("mymove", "fonts/KR Wreath Of Hearts.ttf", label->getContentSize().height), CC_CALLBACK_1(HelloWorld::mymove, this));
	auto myitem3 = MenuItemLabel::create(Label::createWithTTF("myschedule", "fonts/STRIPES STARS Normal.ttf", label->getContentSize().height), CC_CALLBACK_1(HelloWorld::myschedule, this));
	
	// create menu, it's an autorelease object
	auto menu1 = Menu::create(myitem1, myitem2, myitem3, NULL);
	menu1->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	menu1->alignItemsVerticallyWithPadding(label->getContentSize().height/2);
	this->addChild(menu1, 1);


    // add bg
	auto bgsprite = Sprite::create("my3.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds = bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1 / odds);
	bgsprite->setPosition(Vec2(visibleSize / 2) + origin);
	this->addChild(bgsprite, 0);

	//
	//
	timerStr = Label::createWithTTF("0.0", "fonts/Marker Felt.ttf", 40);
	auto timerStrPos = Point(Director::getInstance()->getVisibleSize().width / 5 * 4, Director::getInstance()->getVisibleSize().height / 5*2);
	timerStr->setColor(Color3B::BLACK);
	timerStr->setPosition(timerStrPos);
	this->addChild(timerStr,1);
    return true;
}

void HelloWorld::PlayMenu(Ref *ref){
	this->stopAllActions();
	auto scene = ChooseLevel::createScence();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::myplay(Ref *ref) {
	this->stopAllActions();
	auto scene = ChooseLevel::createScence();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::mymove(Ref *ref) {
	auto moveSprite = Sprite::create("image/elizabeth.png");
	moveSprite->setPosition(Director::getInstance()->getVisibleSize().width / 5, Director::getInstance()->getVisibleSize().height / 5);
	this->addChild(moveSprite, 1);
	auto actionTo = JumpTo::create(8, Point(Director::getInstance()->getVisibleSize().width / 5 * 4, Director::getInstance()->getVisibleSize().height / 5), 150, 8);
	auto action1 = RotateTo::create(8, 180);
	auto action4 = ScaleTo::create(2.0f, 2.0f);
	auto action2 = TintTo::create(2, 255, 0, 255);
	auto ac = Spawn::create(actionTo,action1, NULL);
	auto action3 = FadeOut::create(2.0f);
	//顺序执行以上两个动作之后，移除精灵.
	auto action = Sequence::create(action4,ac, action3, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, moveSprite)), NULL);
	moveSprite->runAction(action);
}

void HelloWorld::myschedule(Ref *ref) {

}
void HelloWorld::Move(Ref *ref){
	auto moveSprite = Sprite::create("image/bird.png");
	moveSprite->setPosition(Director::getInstance()->getVisibleSize().width/5*4,Director::getInstance()->getVisibleSize().height/5);
	this->addChild(moveSprite, 1);
	auto moveToAction = MoveTo::create(3, Point(Director::getInstance()->getVisibleSize().width / 5, Director::getInstance()->getVisibleSize().height / 5));
	auto ScaleToAction = ScaleTo::create(3, 2);
	//顺序执行以上两个动作之后，移除精灵.
	auto action = Sequence::create(moveToAction, ScaleToAction,CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent,moveSprite)),NULL);
	moveSprite->runAction(action);
}

void HelloWorld::Schedule_(Ref *ref){
	schedule(schedule_selector(HelloWorld::updateTime), 0.1f);
}

void HelloWorld::updateTime(float dt){
	totalTime += dt;
	char t[10];
	sprintf(t, "%.1f", totalTime);
	timerStr->setString(t);
}