#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "myinitScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // load game resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish.plist");
	//CCRect rr = CCRectMake(0, 0, 40,40);
	char totalFrames = 9;
	char frameName[20];
	//auto ff = SpriteFrame::create("NormalClose.png", rr);
	//char framen[20] = "NormalClose.png";
	Animation* fishAnimation = Animation::create();
	//Animation* weaponAnimation = Animation::create();
	
	//CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("animations/NormalClose.png");
	for (int i = 1; i <= totalFrames; i++) 
	{
		sprintf(frameName, "fish13_0%d.png", i);
		fishAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		//weaponAnimation->addSpriteFrame(ff);
	}
	fishAnimation->setDelayPerUnit(0.1);
	//weaponAnimation->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(fishAnimation, "fishAnimation");
	//AnimationCache::getInstance()->addAnimation(weaponAnimation, "weaponAnimation");
	auto scene = myScene::createScene();
    //auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
