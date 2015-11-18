#include "PushBoxScene.h"
#include"HelloWorldScene.h"
#include <sqlite3/include/sqlite3.h>
#include<iostream>
using namespace std;
#pragma execution_character_set("utf-8") 
USING_NS_CC;


#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
//#pragma comment(lib,"D:/cocosexample/demopackage/cocos2d/external/sqlite3/libraries/win32/sqlite3.lib")
const float SIZE_WSAD = 100.0;
const int FONT_SIZE = 100;
const float SIZE_BLOCK = 64;
const int SIZE_MAP_WIDTH = 10;
const int SIZE_MAP_HEIGHT = 10;
const int TAG_WALL = 100;
const int TAG_PLAYER = 1;

Scene* PushBoxScene::createScence(){
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PushBoxScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

PushBoxScene::PushBoxScene()
{
	TMXTiledMap* mytmx = TMXTiledMap::create("Pushbox/map.tmx");
	mytmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	mytmx->setAnchorPoint(Vec2(0,0));
	myx = (visibleSize.width - mytmx->getContentSize().width) / 2;
	myy = (visibleSize.height - mytmx->getContentSize().height) / 2;
	this->addChild(mytmx, 0);

	count = 0;
	success = 0;
	/*mon = Sprite::create("Pushbox/player.png");
	mon->setAnchorPoint(Vec2(0, 0));
	mon->setPosition(Vec2(SIZE_BLOCK*1+myx, SIZE_BLOCK*8+myy));
	mon->setTag(TAG_PLAYER);
	this->addChild(mon, 1);*/



	TMXObjectGroup* objects = mytmx->getObjectGroup("wall");
	//从对象层中获取对象数组
	ValueVector container = objects->getObjects();
	//遍历对象
	for (auto obj : container){
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt();
		int y = values.at("y").asInt();
		Sprite* temp = Sprite::create("Pushbox/wall.png");
		temp->setAnchorPoint(Point(0, 0));
		temp->setPosition(Point(x,y+64));
		mywall.pushBack(temp);
		this->addChild(temp, 1);
	}

	TMXObjectGroup* objects1 = mytmx->getObjectGroup("box");
	//从对象层中获取对象数组
	ValueVector container1 = objects1->getObjects();
	//遍历对象
	for (auto obj : container1){
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt();
		int y = values.at("y").asInt();
		Sprite* temp = Sprite::create("Pushbox/box.png");
		temp->setAnchorPoint(Point(0, 0));
		temp->setPosition(Point(x, y+64));
		mybox.pushBack(temp);
		this->addChild(temp, 3);
	}

	TMXObjectGroup* objects2 = mytmx->getObjectGroup("player");
	//从对象层中获取对象数组
	ValueVector container2 = objects2->getObjects();
	//遍历对象
	for (auto obj : container2){
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt();
		int y = values.at("y").asInt();
		Sprite* temp = Sprite::create("Pushbox/player.png");
		temp->setAnchorPoint(Point(0, 0));
		temp->setPosition(Point(x, y+64));
		mon = temp;
		this->addChild(temp, 2);
	}

	TMXObjectGroup* objects3 = mytmx->getObjectGroup("goal");
	//从对象层中获取对象数组
	ValueVector container3 = objects3->getObjects();
	//遍历对象
	for (auto obj : container3){
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt();
		int y = values.at("y").asInt();
		Sprite* temp = Sprite::create("Pushbox/goal.png");
		temp->setAnchorPoint(Point(0, 0));
		temp->setPosition(Point(x, y+64));
		mygoal.pushBack(temp);
		this->addChild(temp, 1);
	}
}

PushBoxScene::~PushBoxScene()
{

}

bool PushBoxScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	

	visibleSize = Director::getInstance()->getVisibleSize();
	createmysql(this);
	initTouchEvent();

	return true;
}



void PushBoxScene::initTouchEvent(){
	auto menu = Menu::create();
	menu->setPosition(visibleSize.width,0);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(menu,10);

	auto label_W = Label::createWithTTF("W", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_S = Label::createWithTTF("S", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_A = Label::createWithTTF("A", "fonts/Marker Felt.ttf", FONT_SIZE);
	auto label_D = Label::createWithTTF("D", "fonts/Marker Felt.ttf", FONT_SIZE);

	auto button_up = MenuItemLabel::create(label_W, CC_CALLBACK_1(PushBoxScene::onUpPressed, this));
	auto button_down = MenuItemLabel::create(label_S, CC_CALLBACK_1(PushBoxScene::onDownPressed, this));
	auto button_left = MenuItemLabel::create(label_A, CC_CALLBACK_1(PushBoxScene::onLeftPressed, this));
	auto button_right = MenuItemLabel::create(label_D, CC_CALLBACK_1(PushBoxScene::onRightPressed, this));
	
	button_up->setPosition(SIZE_WSAD * -1, SIZE_WSAD * 2);
	button_down->setPosition(SIZE_WSAD * -1, SIZE_WSAD * 0);
	button_left->setPosition(SIZE_WSAD * -2, SIZE_WSAD * 1);
	button_right->setPosition(SIZE_WSAD * 0, SIZE_WSAD * 1);

	button_up->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_down->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_left->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	button_right->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);

	menu->addChild(button_up);
	menu->addChild(button_down);
	menu->addChild(button_left);
	menu->addChild(button_right);
}


bool PushBoxScene::isbox(int tx, int ty) {
	int flag = 0;
cocos2d:Vector<Sprite*>::iterator it = mybox.begin();
	for (; it != mybox.end(); it++)
	{
		if ((*it)->getPositionX() == tx && (*it)->getPositionY() == ty) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		return true;
	}
	else {
		return false;
	}
}


bool PushBoxScene::can(int tx, int ty) {
	int flag = 0;
cocos2d:Vector<Sprite*>::iterator it = mywall.begin();
	for (; it != mywall.end(); it++)
	{
		if ((*it)->getPositionX() == tx && (*it)->getPositionY() == ty) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		return false;
	}
	else {
		return true;
	}
}

void PushBoxScene::onRightPressed(Ref* sender)
{
	/*int flag = 0;
	int flag2 = 0;
	auto tempx = mon->getPositionX();
	auto tempy = mon->getPositionY();
	tempx = tempx + 64;
	auto tem = tempx + 64;
    cocos2d:Vector<Sprite*>::iterator it = mywall.begin();
	for (; it != mywall.end(); it++)
	{
		if ((*it)->getPositionX == tempx && (*it)->getPositionY == tempy) {
			flag = 1;
			break;
		}
		else if ((*it)->getPositionX == tem && (*it)->getPositionY == tempy) {
			flag2 = 1;
			break;
		}
	}
	if (flag == 1) {
		return;
	}
cocos2d:Vector<Sprite*>::iterator it2 = mybox.begin();
cocos2d:Vector<Sprite*>::iterator it3;
	for (; it2 != mybox.end(); it2++) {
		if ((*it2)->getPositionX == tempx && (*it2)->getPositionY == tempy) {
			flag2 = flag2+2;
			it3 = it2;
		}
		else if ((*it2)->getPositionX == tem && (*it2)->getPositionY == tempy) {
			flag2 = flag + 3;
		}
	}
	if (flag2 == 3) {
		return;
	}
	else if (flag2 == 2) {
		(*it2)->setPositionX(tem);
		mon->setPositionX(tempx);
	} 
	else {
		mon->setPositionX(tempx);
	}*/
	auto tempx = mon->getPositionX();
	auto tempy = mon->getPositionY();
	if (!can(tempx+SIZE_BLOCK, tempy)) {
		return;
	}
	else {
		if (isbox(tempx + SIZE_BLOCK, tempy)) {
			if (!can(tempx + SIZE_BLOCK*2, tempy)) {
				return;
			}
			else {
				if (isbox(tempx + SIZE_BLOCK * 2, tempy)) {
					if (!can(tempx + SIZE_BLOCK * 3, tempy)) {
						return;
					}
					else {
						mybox.at(0)->setPositionX(mybox.at(0)->getPositionX() + SIZE_BLOCK);
						mybox.at(1)->setPositionX(mybox.at(1)->getPositionX() + SIZE_BLOCK);
						mon->setPositionX(mon->getPositionX() + SIZE_BLOCK);
						count++;
					}
				}
				else {
					mon->setPositionX(mon->getPositionX() + SIZE_BLOCK);
					if (mon->getPosition() == mybox.at(0)->getPosition()) {
						mybox.at(0)->setPositionX(mon->getPositionX() + SIZE_BLOCK);
					}
					else {
						mybox.at(1)->setPositionX(mon->getPositionX() + SIZE_BLOCK);
					}
					count++;
				}
			}
		}
		else {
			mon->setPositionX(mon->getPositionX() + SIZE_BLOCK);
			count++;
		}
	}
	if (mybox.at(0)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(0)->getPosition() == mygoal.at(1)->getPosition()) {
		if (mybox.at(1)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(1)->getPosition() == mygoal.at(1)->getPosition()) { 
			myend();
}
	}
}

void PushBoxScene::onLeftPressed(Ref* sender)
{
	auto tempx = mon->getPositionX();
	auto tempy = mon->getPositionY();
	if (!can(tempx - SIZE_BLOCK, tempy)) {
		return;
	}
	else {
		if (isbox(tempx - SIZE_BLOCK, tempy)) {
			if (!can(tempx - SIZE_BLOCK * 2, tempy)) {
				return;
			}
			else {
				if (isbox(tempx - SIZE_BLOCK * 2, tempy)) {
					if (!can(tempx - SIZE_BLOCK * 3, tempy)) {
						return;
					}
					else {
						mybox.at(0)->setPositionX(mybox.at(0)->getPositionX() - SIZE_BLOCK);
						mybox.at(1)->setPositionX(mybox.at(1)->getPositionX() - SIZE_BLOCK);
						mon->setPositionX(mon->getPositionX() - SIZE_BLOCK);
						count++;
					}
				}
				else {
					mon->setPositionX(mon->getPositionX() - SIZE_BLOCK);
					if (mon->getPosition() == mybox.at(0)->getPosition()) {
						mybox.at(0)->setPositionX(mon->getPositionX() - SIZE_BLOCK);
					}
					else {
						mybox.at(1)->setPositionX(mon->getPositionX() - SIZE_BLOCK);
					}
					count++;
				}
			}
		}
		else {
			mon->setPositionX(mon->getPositionX() - SIZE_BLOCK);
			count++;
		}
	}
	if (mybox.at(0)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(0)->getPosition() == mygoal.at(1)->getPosition()) {
		if (mybox.at(1)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(1)->getPosition() == mygoal.at(1)->getPosition()) {
			myend();
		}
	}

}

void PushBoxScene::onUpPressed(Ref* sender)
{
	auto tempx = mon->getPositionX();
	auto tempy = mon->getPositionY();
	if (!can(tempx, tempy + SIZE_BLOCK)) {
		return;
	}
	else {
		if (isbox(tempx, tempy + SIZE_BLOCK)) {
			if (!can(tempx, tempy + SIZE_BLOCK * 2)) {
				return;
			}
			else {
				if (isbox(tempx, tempy + SIZE_BLOCK * 2)) {
					if (!can(tempx, tempy + SIZE_BLOCK * 3)) {
						return;
					}
					else {
						mybox.at(0)->setPositionY(mybox.at(0)->getPositionY() + SIZE_BLOCK);
						mybox.at(1)->setPositionY(mybox.at(1)->getPositionY() + SIZE_BLOCK);
						mon->setPositionY(mon->getPositionY() + SIZE_BLOCK);
						count++;
					}
				}
				else {
					mon->setPositionY(mon->getPositionY() + SIZE_BLOCK);
					if (mon->getPosition() == mybox.at(0)->getPosition()) {
						mybox.at(0)->setPositionY(mon->getPositionY() + SIZE_BLOCK);
					}
					else {
						mybox.at(1)->setPositionY(mon->getPositionY() + SIZE_BLOCK);
					}
					count++;
				}
			}
		}
		else {
			mon->setPositionY(mon->getPositionY() + SIZE_BLOCK);
			count++;
		}
	}
	if (mybox.at(0)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(0)->getPosition() == mygoal.at(1)->getPosition()) {
		if (mybox.at(1)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(1)->getPosition() == mygoal.at(1)->getPosition()) {
			myend();
		}
	}

}

void PushBoxScene::onDownPressed(Ref* sender)
{
	auto tempx = mon->getPositionX();
	auto tempy = mon->getPositionY();
	if (!can(tempx, tempy - SIZE_BLOCK)) {
		return;
	}
	else {
		if (isbox(tempx, tempy - SIZE_BLOCK)) {
			if (!can(tempx, tempy - SIZE_BLOCK * 2)) {
				return;
			}
			else {
				if (isbox(tempx, tempy - SIZE_BLOCK * 2)) {
					if (!can(tempx, tempy - SIZE_BLOCK * 3)) {
						return;
					}
					else {
						mybox.at(0)->setPositionY(mybox.at(0)->getPositionY() - SIZE_BLOCK);
						mybox.at(1)->setPositionY(mybox.at(1)->getPositionY() - SIZE_BLOCK);
						mon->setPositionY(mon->getPositionY() - SIZE_BLOCK);
						count++;
					}
				}
				else {
					mon->setPositionY(mon->getPositionY() - SIZE_BLOCK);
					if (mon->getPosition() == mybox.at(0)->getPosition()) {
						mybox.at(0)->setPositionY(mon->getPositionY() - SIZE_BLOCK);
					}
					else {
						mybox.at(1)->setPositionY(mon->getPositionY() - SIZE_BLOCK);
					}
					count++;
				}
			}
		}
		else {
			mon->setPositionY(mon->getPositionY() - SIZE_BLOCK);
			count++;
		}
	}
	if (mybox.at(0)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(0)->getPosition() == mygoal.at(1)->getPosition()) {
		if (mybox.at(1)->getPosition() == mygoal.at(0)->getPosition() || mybox.at(1)->getPosition() == mygoal.at(1)->getPosition()) {
			myend();
		}
	}

}

void PushBoxScene::myend() {
	auto mylabel = Label::create("You Win!", "Arial", 24);
	mylabel->setPosition(visibleSize.width - 300, visibleSize.height - 100);
	mylabel->setTextColor(Color4B::RED);
	this->addChild(mylabel, 2);

	char t[35];
	sprintf(t, "Your steps are : %d", count);
	auto mylabel1 = Label::create(t, "Arial", 24);
	mylabel1->setPosition(visibleSize.width - 300, visibleSize.height - 200);
	mylabel1->setTextColor(Color4B::WHITE);
	this->addChild(mylabel1, 2);

	char tt[35];
	sprintf(tt, "insert into steps values(%d);", count);
	sqlite3* pdb = NULL;
	string path = FileUtils::getInstance()->getWritablePath() + "save.db";
	int result = sqlite3_open(path.c_str(), &pdb);
	string sql = tt;
	sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	//string sql2 = "SELECT * FROM step ORDER BY ID DASC;";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	char **re;
	int row, col;
	sqlite3_get_table(pdb, "select * from steps", &re, &row, &col, NULL);
	CCLog("steps: row is %d,column is %d", row, col);
	//由于第0行是表头，所以真正的数据从第1行开始；
	/*for (int i = 1; i <= row; i++)
	{
	for (int j = 0; j < col; j++)
	{
	log("%s", re[i*col + j]);
	}
	}*/
	int min = 100000;
	for (int i = 0; i < row; ++i)
	{
		//CCLog("row %d ---> id = %s, count = %s", i + 1, re[col + i*col], re[col + i*col + 1]);
		int val = CCString(re[col + i*col]).intValue();
		if (min > val) {
			min = val;
		}
	}
	char t1[35];
	sprintf(t1, "The least steps is : %d", min);
	auto mylabel2 = Label::create(t1, "Arial", 24);
	mylabel2->setPosition(visibleSize.width - 300, visibleSize.height - 300);
	mylabel2->setTextColor(Color4B::YELLOW);
	this->addChild(mylabel2, 2);

	sqlite3_free_table(re);
	sqlite3_close(pdb);

	auto myitem1 = MenuItemLabel::create(Label::createWithSystemFont("Restart", "Cobel", 36), CC_CALLBACK_1(PushBoxScene::myplay, this));
	auto menu1 = Menu::create(myitem1, NULL);
	menu1->setPosition(visibleSize.width - 300, visibleSize.height - 400);
	this->addChild(menu1, 1);
}

void PushBoxScene::myplay(Ref *ref) {
	this->stopAllActions();
	auto scenee = PushBoxScene::createScence();
	Director::getInstance()->replaceScene(scenee);
}

void PushBoxScene::createmysql(Ref* sender)
{
	//数据库指针
	sqlite3* pdb = NULL;

	//数据库的路径
	string path = FileUtils::getInstance()->getWritablePath() + "save.db";

	//创建或打开数据库
	int result = sqlite3_open(path.c_str(), &pdb);

	if (result == SQLITE_OK)
	{
		log("database init");
	}

	//创建一个新表
	string sql = "create table steps(ID int primary key not null);";

	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	if (result == SQLITE_OK)
	{
		log("create table");
	}

	//插入数据
	sql = "insert into steps values(10000);";
	sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	sql = "insert into steps values(1000);";
	sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	sql = "insert into steps values(999);";
	sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//务必关闭数据库，否则会造成内存泄漏
	sqlite3_close(pdb);
}


