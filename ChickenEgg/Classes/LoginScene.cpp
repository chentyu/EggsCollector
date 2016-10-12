#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "Global.h"
#include "GameScene.h"
#include "InfoScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();

    auto bgsprite = Sprite::create("image/bg.jpg");
    bgsprite->setPosition(visibleSize / 2);
    bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, visibleSize.height / bgsprite->getContentSize().height);
    this->addChild(bgsprite, 0);

    auto cx = Sprite::create("image/cx.png");
    cx->setPosition(cx->getContentSize() / 4);
    cx->setScale(0.5f, 0.5f);
    this->addChild(cx, 0);

    auto gameName = Sprite::create("image/chickenEgg.png");
    gameName->setPosition(visibleSize.width / 2, visibleSize.height * 4 / 5);
    this->addChild(gameName, 0);

    textField = TextField::create("Player Name", "Arial", 42);
    textField->setColor(Color3B::BLACK);
    textField->setPosition(Size(visibleSize.width / 2, visibleSize.height / 2 + textField->getContentSize().height));
    this->addChild(textField, 2);

    auto button = Button::create("image/playgame.png");
    button->setPosition(Size(visibleSize.width / 2, visibleSize.height / 4));
    button->setScale(0.5f, 0.5f);
    button->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            login();
        }
    });
    this->addChild(button, 2);

    return true;
}

void LoginScene::login() {
    string username = textField->getStringValue();
    if (username == "") {
        auto warning = Label::createWithSystemFont("Please input your name", "Microsoft Yahei", 26);
        warning->setColor(Color3B::BLACK);
        warning->setPosition(Size(visibleSize.width / 2, visibleSize.height / 2 - 50));
        this->addChild(warning, 2);
        return;
    }

    Global::username = "";
    for (int i = 0; i < username.size(); i++) {
        if (username[i] != ' ') {
            Global::username += username[i];
        }
    }

    auto scene = InfoScene::createScene();
    auto transitions = TransitionFade::create(1.0f, scene);
    Director::getInstance()->replaceScene(transitions);
}