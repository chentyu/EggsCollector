#include "GameScene.h"
#include "RankScene.h"
#include "Global.h"
#include "LoginScene.h"

using namespace CocosDenshion;

#include <cstdlib>

USING_NS_CC;

void GameScene::setPhysicsWorld(PhysicsWorld * world) {m_world = world;}

Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -200));

	auto layer = GameScene::create(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

bool GameScene::init(PhysicsWorld* world) {
	if (!Layer::init())
	{
		return false;
	}

	this->setPhysicsWorld(world);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	preloadMusic();
	score = 0;

	addBackground();
	addBasket();
	addChicken();

	addKeyboardListener();

	this->schedule(schedule_selector(GameScene::update), 00.1);

	addtimePT();
	schedule(schedule_selector(GameScene::updateTime), 1.0f, kRepeatForever, 0);

	auto scorelabelstring = Label::createWithSystemFont("Score: ", "Microsoft Yahei", 40);
	scorelabelstring->setPosition(Vec2(100, visibleSize.height - scorelabelstring->getContentSize().height / 2));
	this->addChild(scorelabelstring, 2);

	scorelabel = Label::createWithSystemFont("0", "Microsoft Yahei", 40);
	scorelabel->setPosition(Vec2(200, visibleSize.height - scorelabel->getContentSize().height / 2));
	this->addChild(scorelabel, 2);

	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("sound/ready.mp3");
	scheduleOnce(schedule_selector(GameScene::playGo), 1);
	return true;
}

GameScene* GameScene::create(PhysicsWorld* world) {
	GameScene* pRet = new(std::nothrow) GameScene();
	if (pRet && pRet->init(world)) {
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = NULL;
	return NULL;
}

void GameScene::addBackground() {
    TMXTiledMap* tmx = TMXTiledMap::create("bg.tmx");
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	tmx->setPosition(visibleSize / 2);
	scale = visibleSize.height / tmx->getContentSize().height;
	tmx->setScale(visibleSize.width / tmx->getContentSize().width, scale);
 	addChild(tmx,0);


	auto bottom = Sprite::create("image/image 210.png");
	bottom->setPosition(visibleSize.width / 2, bottom->getContentSize().height / 2);
	bottom->setScale(visibleSize.width / bottom->getContentSize().width, 1);
	this->addChild(bottom, 0);

	auto stick = Sprite::create("image/stick.png");
	stick->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 3 - 20);
	stick->setScale(visibleSize.width / stick->getContentSize().width, scale);
	this->addChild(stick, 0);
}


void GameScene::addBasket() {
	basket = Sprite::create("image/image 137.png");
	basket->setPosition(visibleSize.width / 4.5 * 2 + 48, visibleSize.height / 5);
	basket->setScale(scale, scale);
	BasketPos = 2;
	this->addChild(basket, 1);
}

void GameScene::playGo(float t) {
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("sound/go.mp3");
	schedule(schedule_selector(GameScene::CXlayEgg), 1);
}

void GameScene::addChicken() {
	for (int i = 0; i < 5; i++) {
		Sprite* chicken = Sprite::create("image/chick.png");
		chicken->setScale(0.3);
		chicken->setAnchorPoint(Vec2(0, 0));
		chicken->setPosition(Vec2(visibleSize.width / 4.5 * i, visibleSize.height * 2 / 3 - 20));
		addChild(chicken, 1);
		chickens.push_back(chicken);

		Sprite* leftleg = Sprite::create("image/left.png");
		leftleg->setScale(0.25);
		leftleg->setPosition(Vec2(visibleSize.width / 4.5 *i + 25, visibleSize.height * 2 / 3 - 20));
		addChild(leftleg, 0);

		Sprite* rightleg = Sprite::create("image/right.png");
		rightleg->setScale(0.25);
		rightleg->setPosition(Vec2(visibleSize.width / 4.5 *i + 60, visibleSize.height * 2 / 3 - 20));
		addChild(rightleg, 0);
	}
}

void GameScene::newEgg() { //选择所下的蛋的类型
	srand(time(NULL));
	int chickenSelect = rand() % 5;
	/*5中类型，1~4分数递增，0扣分*/
	int type = 1;
	if (CCRANDOM_0_1() > 0.85) { type = 0; }
	else if (CCRANDOM_0_1() > 0.8) { type = 4; }
	else if (CCRANDOM_0_1() > 0.7) { type = 3; }
	else if (CCRANDOM_0_1() > 0.6) { type = 2; }

	addEgg(chickenSelect ,type);
}

void GameScene::addEgg(int pos,int type) {
	char path[100];
	int tag;

	switch (type) {
	case 0:
		sprintf(path, "image/-10.png");
		tag = -10;
		break;
	case 1:
		sprintf(path, "image/1.png");
		tag = 1;
		break;
	case 2:
		sprintf(path, "image/2.png");
		tag = 2;
		break;
	case 3:
		sprintf(path, "image/3.png");
		tag = 3;
		break;
	case 4:
		sprintf(path, "image/5.png");
		tag = 5;
		break;
	}

	auto egg = Sprite::create(path);
	if (egg == nullptr) return;
	egg->setPhysicsBody(PhysicsBody::create(egg->getContentSize().height / 2));
    egg->setAnchorPoint(Vec2(0.5, 0.5));
	egg->setScale(0.25);
	egg->setPosition(Vec2(visibleSize.width / 4.5 * pos+43, visibleSize.height * 2 / 3 - 25));

	egg->getPhysicsBody()->setCategoryBitmask(0x01);
    egg->getPhysicsBody()->setCollisionBitmask(0x01);
    egg->getPhysicsBody()->setContactTestBitmask(0x12);
    egg->getPhysicsBody()->setTag(tag);

	egg->getPhysicsBody()->setVelocity
	((Point(visibleSize.width / 4.5 * pos + 43, visibleSize.height/2) - egg->getPosition()) * (1));

	eggs.push_back(egg);
	addChild(egg);

	//music
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("sound/chickenlayegg.mp3");

	auto it = chickens.begin() + pos;
	(*it)->setScaleY(0.25);
	scheduleOnce(schedule_selector(GameScene::recoverchicken), 0.5f);
}

void GameScene::recoverchicken(float a) {
	for (auto it = chickens.begin(); it != chickens.end(); it++)
		(*it)->setScaleY(0.3f);
}

//键盘事件
void GameScene::addKeyboardListener() {
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (BasketPos > 0) {
			BasketPos--;
			basket->setPosition(visibleSize.width / 4.5 * BasketPos + 48, visibleSize.height / 5);
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		if (BasketPos < 4) {
			BasketPos++;
			basket->setPosition(visibleSize.width / 4.5 * BasketPos + 48, visibleSize.height / 5);
		}
		break;
	default:
		break;
	}
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
}

void GameScene::CXlayEgg(float dt) {
	if (CCRANDOM_0_1() > 0.35) newEgg();
}
void GameScene::update(float dt) {
	if (brokenEgg != NULL) {
		brokenEgg->removeFromParentAndCleanup(true);
		brokenEgg = NULL;
	}

	for (unsigned i = 0; i < eggs.size(); i++) {
		if (eggs[i] != NULL) {
			if (basket->getPosition().getDistance(eggs[i]->getPosition()) < 30) {
				int tag = eggs[i]->getPhysicsBody()->getTag();
				score += tag;
				//music
				auto audio = SimpleAudioEngine::getInstance();
				audio->playEffect("sound/get.mp3");

				if (score < 0)
					score = 0;
				updatescore(score);
				eggs[i]-> removeFromParentAndCleanup(true);
				eggs[i] = NULL;

			}
			else if (eggs[i]->getPositionY() < visibleSize.height / 5) {
				Point point = eggs[i]->getPosition();
				char path[100];
				if (eggs[i]->getPhysicsBody()->getTag() == -10) {
					brokenEgg = Sprite::create("image/6.png");
					brokenEgg->setScale(0.2);

					auto audio = SimpleAudioEngine::getInstance();
					audio->playEffect("sound/pbreak.mp3");
				}
				else {
					brokenEgg = Sprite::create("image/image 222.png");

					auto audio = SimpleAudioEngine::getInstance();
					audio->playEffect("sound/eggbreak.mp3");
				}

				eggs[i]->removeFromParentAndCleanup(true);

				brokenEgg->setPosition(point);
				eggs[i] = NULL;
				this->addChild(brokenEgg, 1);
			}
		}
	}
}

void GameScene::updateTime(float dt) {	//计时函数
	if (timePT->getPercentage() > 0) {
		auto timemove = ProgressFromTo::create(1, timePT->getPercentage(), timePT->getPercentage() - 2.5);
		timePT->runAction(timemove);
	} else {
		Global::score = score;
		auto scene = RankScene::createScene();
    	Director::getInstance()->replaceScene(scene);
	}
}

void GameScene::addtimePT() {
	Sprite* sp0 = Sprite::create("image/hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("image/hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//使用hp条设置progressBar
	timePT = ProgressTimer::create(sp);
	timePT->setScaleX(90);
	timePT->setAnchorPoint(Vec2(0, 0));
	timePT->setType(ProgressTimerType::BAR);
	timePT->setBarChangeRate(Point(1, 0));
	timePT->setMidpoint(Point(0, 1));
	timePT->setPercentage(100);
	timePT->setPosition(Vec2(origin.x + 14 * timePT->getContentSize().width +530, origin.y + visibleSize.height - 2 * timePT->getContentSize().height));
	addChild(timePT, 2);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + timePT->getContentSize().width + 530, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0, 1);
}

void GameScene::updatescore(float score) {
	if (score <= 0)
		score = 0;
	char stringscore[20];
	itoa(score, stringscore, 10);
	scorelabel->setString(stringscore);
}

void GameScene::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadEffect("sound/chickenlayegg.mp3");
	audio->preloadEffect("sound/eggbreak.mp3");
	audio->preloadEffect("sound/get.mp3");
	audio->preloadEffect("sound/go.mp3");
	audio->preloadEffect("sound/pbreak.mp3");
	audio->preloadEffect("sound/ready.mp3");
}
