#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include "Global.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d::ui;
USING_NS_CC;

#include "network/HttpClient.h"
using namespace cocos2d::network;

using std::string;

class GameScene : public cocos2d::Layer
{
public:
	void setPhysicsWorld(PhysicsWorld * world);
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(PhysicsWorld* world);

	// implement the "static create()" method manually
	static GameScene* create(PhysicsWorld* world);

    void addBackground();

	void recoverchicken(float a);

	/*添加下蛋公鸡和接蛋篮子*/
	void addBasket();
	void addChicken();
	/*添加蛋*/
	void newEgg();
	void addEgg(int,int);
	//添加事件监听器
	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);

	//void addContactListener();
	//bool onConcactBegan(PhysicsContact& contact);

	void update(float);
	void CXlayEgg(float);

	//更新时间
	void updateTime(float a);
	void playGo(float t);
	void addtimePT();
	void updatescore(float);

	void preloadMusic();

private:
	PhysicsWorld* m_world;

    Size visibleSize;
	cocos2d::Vec2 origin;

	int score;
	cocos2d::Label* scorelabel;

    float scale;            //放大比例
	int BasketPos; //记录框的位置

	//篮子与鸡
	Sprite* basket;
	std::vector<Sprite*> chickens;
	//所下的蛋
	std::vector<Sprite*> eggs;
	//蛋落地
	Sprite* brokenEgg;
	//添加时间条
	cocos2d::ProgressTimer* timePT;

	TextField * score_field;
    TextField * rank_field;

	Button *submit_button;
    Button *rank_button;
};
