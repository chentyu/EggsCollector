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

	/*����µ������ͽӵ�����*/
	void addBasket();
	void addChicken();
	/*��ӵ�*/
	void newEgg();
	void addEgg(int,int);
	//����¼�������
	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);

	//void addContactListener();
	//bool onConcactBegan(PhysicsContact& contact);

	void update(float);
	void CXlayEgg(float);

	//����ʱ��
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

    float scale;            //�Ŵ����
	int BasketPos; //��¼���λ��

	//�����뼦
	Sprite* basket;
	std::vector<Sprite*> chickens;
	//���µĵ�
	std::vector<Sprite*> eggs;
	//�����
	Sprite* brokenEgg;
	//���ʱ����
	cocos2d::ProgressTimer* timePT;

	TextField * score_field;
    TextField * rank_field;

	Button *submit_button;
    Button *rank_button;
};
