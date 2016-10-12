#include "InfoScene.h"
#include "cocostudio/CocoStudio.h"
#include "Global.h"
#include "GameScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* InfoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = InfoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InfoScene::init()
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

    auto info = Sprite::create("image/info.png");
    info->setPosition(visibleSize / 2);
    info->setScale(0.9f, 0.9f);
    this->addChild(info, 0);

    auto button = Button::create("image/next.png");
    button->setPosition(Size(visibleSize.width - button->getContentSize().width / 2, button->getContentSize().height / 2));
    button->setScale(0.5f, 0.5f);
    button->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
        auto scene = GameScene::createScene();
        auto transitions = TransitionFade::create(1.0f, scene);
        Director::getInstance()->replaceScene(transitions);
    });
    this->addChild(button, 2);

    return true;
}
