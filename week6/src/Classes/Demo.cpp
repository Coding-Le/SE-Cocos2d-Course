#include "Demo.h"
using namespace std;


Demo::Demo()
	: m_world(NULL)
	, m_basketball(NULL)
	, m_soccer(NULL)
{

}

Demo::~Demo()
{
}

Scene* Demo::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,-300));

	auto layer = Demo::create(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
	
}

Demo* Demo::create(PhysicsWorld* world)  
{
	Demo* pRet = new Demo();
	if (pRet && pRet->init(world)) 
	{
		return pRet;
	}
	pRet = NULL;
	return NULL;
}

bool Demo::init(PhysicsWorld* world)
{
	if (!Layer::init())
	{
		return false;
	}
	//dispatcher = Director::getInstance()->getEventDispatcher();
	m_world = world;
	isCut = false;
	Size winSize = Director::getInstance()->getWinSize();
	dispatcher = Director::getInstance()->getEventDispatcher();
	streak = MotionStreak::create(0.5f, 10, 30, Color3B::WHITE, "Demo/flash.png");
	this->addChild(streak, 0);

	Sprite* background = Sprite::create("BG.png");
	background->setPosition(winSize.width/2, winSize.height/2);
	addChild(background);
	//边界
	/*Node* bound = Node::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(winSize);
	boundBody->setDynamic(false);
	bound->setPhysicsBody(boundBody);
	bound->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(bound);*/

	Node* ground = Node::create();
	ground->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(0, 29), Vec2(winSize.width, 29)));
	ground->getPhysicsBody()->setDynamic(false);
	addChild(ground);

	m_cat = Sprite::create("cat_cry.png");
	m_cat->setPhysicsBody(PhysicsBody::createBox(m_cat->getContentSize()));
	m_cat->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_cat->setPosition(m_cat->getContentSize().width/2, 30);
	m_cat->setTag(1);
	//m_cat->getPhysicsBody()->setDynamic(false);
	this->addChild(m_cat);
	
	
	m_cat2 = Sprite::create("cat_cry.png");
	m_cat2->setPhysicsBody(PhysicsBody::createBox(m_cat2->getContentSize()));
	m_cat2->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_cat2->setPosition(winSize.width-m_cat2->getContentSize().width/2, 29);
	m_cat2->setTag(1);
	//m_cat2->getPhysicsBody()->setDynamic(false);
	this->addChild(m_cat2);
	

	
	m_rope = Sprite::create("rope.png");
	m_apple = Sprite::create("apple.png");
	m_apple->setPhysicsBody(PhysicsBody::createBox(m_apple->getContentSize()));
	m_apple->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_apple->setTag(2);
	m_apple->setPosition(winSize.width / 2+m_rope->getContentSize().width+m_apple->getContentSize().width/2, winSize.height-m_rope->getContentSize().height/2);
	this->addChild(m_apple);

	m_rope->setPhysicsBody(PhysicsBody::createBox(m_rope->getContentSize()));
	m_rope->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_rope->setTag(3);
	m_rope->setPosition(winSize.width / 2 + m_rope->getContentSize().width / 2, winSize.height - m_rope->getContentSize().height / 2);
	this->addChild(m_rope);

	m_brick = Sprite::create("brick_high.png");
	m_brick->setPhysicsBody(PhysicsBody::createBox(m_brick->getContentSize()));
	m_brick->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_brick->setTag(4);
	m_brick->setPosition(winSize.width-m_cat->getContentSize().width-m_brick->getContentSize().width/2, 30);
	//m_brick->getPhysicsBody()->setDynamic(false);
	this->addChild(m_brick);

	m_brick2 = Sprite::create("brick_high.png");
	m_brick2->setPhysicsBody(PhysicsBody::createBox(m_brick2->getContentSize()));
	m_brick2->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_brick2->setTag(4);
	m_brick2->setPosition(m_cat->getContentSize().width+ m_brick->getContentSize().width / 2, 30);
	//m_brick2->getPhysicsBody()->setDynamic(false);
	this->addChild(m_brick2);

	Node* base = Node::create();
	base->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2::ZERO, Vec2::ZERO));
	base->getPhysicsBody()->setDynamic(false);
	base->setPosition(winSize.width/2, winSize.height-m_rope->getContentSize().height/2);
	addChild(base);
    my_pin = PhysicsJointPin::construct(base->getPhysicsBody(), m_rope->getPhysicsBody(),base->getPosition());
	my_pin->setCollisionEnable(false);
	m_world->addJoint(my_pin);
	rope_apple = PhysicsJointFixed::construct(m_rope->getPhysicsBody(), m_apple->getPhysicsBody(), m_apple->getPosition());
	//PhysicsJointFix *rope_apple = PhysicsJointSpring::construct(m_rope->getPhysicsBody(), m_apple->getPhysicsBody(), m_rope->getAnchorPoint(), m_apple->getAnchorPoint(), 200, 0);
	m_world->addJoint(rope_apple);
	testTouchEvent();
	/*
		注意_contactTestBitmask的默认值为0x00000000，即任何碰撞都不检测
	*/
	/*m_basketball = Sprite::create("basketball.png");
	m_basketball->setPhysicsBody(PhysicsBody::createCircle(m_basketball->getContentSize().width / 2));
	m_basketball->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_basketball->setPosition(300, 300);
	addChild(m_basketball);

	m_soccer = Sprite::create("soccer.png");
	m_soccer->setPhysicsBody(PhysicsBody::createCircle(m_soccer->getContentSize().width / 2));
	m_soccer->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	m_soccer->setPosition(700, 300);
	addChild(m_soccer);*/

	testContact();
	//testContactFilter();

	//testPhysicsJointSpring();
	//testPhysicsJointDistance();
	
	//testParticleFireworks();
	//testParticleSnow();
	//testExternalParticle();
	return true;
}

void Demo::testTouchEvent()
{
	//streak = MotionStreak::create(0.5f, 10, 30, Color3B::WHITE, "Demo/flash.png");
	

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
			if (m_rope->getBoundingBox().containsPoint(touch_pos)) {
				isCut = true;
				//auto my_fade = FadeOut::create(1.0f);
				//m_rope->runAction(my_fade);
				//auto action = MoveTo::create(3, Vec2(Director::getInstance()->getVisibleSize().width / 2, man->getContentSize().height + box->getContentSize().height / 2));
				//auto action1 = ScaleTo::create(3.0f, 1.0f);
				//auto action2 = Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Demo::turnoff, this)), NULL);
				//box->runAction(action2);
				m_world->removeJoint(rope_apple);
				//playEffect();
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


/*
测试物理引擎碰撞检测的功能，当两个小球相撞时，将他们移除
*/
void Demo::testContact()
{
	//m_basketball->getPhysicsBody()->setVelocity(Vec2(100, 0));
	//m_soccer->getPhysicsBody()->setVelocity(Vec2(-100, 0));

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Demo::onContactBegan, this);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Demo::onContactBegan(PhysicsContact& contact)
{
	//m_basketball->removeFromParentAndCleanup(true);
	//m_soccer->removeFromParentAndCleanup(true);
	auto temp1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto temp2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
		if (temp1->getTag() + temp2->getTag() == 3) {
		if (temp1->getTag() == 1) {
			temp1->setVisible(false);
			this->removeChild(temp1);
		}
		else {
			temp2->setVisible(false);
			this->removeChild(temp2);
		}
		testParticleFireworks();
	}
	return true;
}

/*
	通过设置collisionBitmask使小球不产生碰撞效果
*/
void Demo::testContactFilter()
{
	m_basketball->getPhysicsBody()->setVelocity(Vec2(100, 0));
	m_soccer->getPhysicsBody()->setVelocity(Vec2(-100, 0));
	m_basketball->getPhysicsBody()->setCollisionBitmask(0x000000);

}

/*
*/
void Demo::testPhysicsJointSpring()
{
	m_basketball->getPhysicsBody()->setVelocity(Vec2(300, 0));
	m_soccer->getPhysicsBody()->setVelocity(Vec2(-300, 0));

	PhysicsJointSpring* springJoint = PhysicsJointSpring::construct(
		m_basketball->getPhysicsBody(), m_soccer->getPhysicsBody(),
		m_basketball->getAnchorPoint(), m_soccer->getAnchorPoint(),
		200, 0);
	m_world->addJoint(springJoint);
}

void Demo::testPhysicsJointDistance()
{
	m_basketball->getPhysicsBody()->setVelocity(Vec2(300, 0));

	PhysicsJointDistance* distanceJoint = PhysicsJointDistance::construct(
		m_basketball->getPhysicsBody(), m_soccer->getPhysicsBody(),
		Vec2::ZERO, Vec2::ZERO);
	m_world->addJoint(distanceJoint);
}

void Demo::testParticleFireworks()
{
	ParticleFireworks* fireworks = ParticleFireworks::create();
	Size winSize = Director::getInstance()->getWinSize();
	fireworks->setPosition(winSize.width/2, winSize.height/2);
	addChild(fireworks);
}

void Demo::testParticleSnow()
{
	ParticleSnow* snow = ParticleSnow::create();
	snow->setTexture(Director::getInstance()->getTextureCache()->addImage("snow.png"));
	snow->setPosition(500, 500);
	addChild(snow);
}

void Demo::testExternalParticle()
{
	auto paopao = ParticleSystemQuad::create("lizhi_qipao.plist");
	paopao->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
	paopao->setPosition(500, 300);
	paopao->setScale(2.0f);
	addChild(paopao);
}

void Demo::testCustomEvent()
{
	auto listener = EventListenerCustom::create("off", [](EventCustom* event){
		//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	});
	dispatcher->addEventListenerWithFixedPriority(listener, 1);
}

void Demo::turnoff() {
	EventCustom e("off");

	e.setUserData(&touch_pos);

	dispatcher->dispatchEvent(&e);
}