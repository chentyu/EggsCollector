#include "RankScene.h"
#include "cocostudio/CocoStudio.h"
#include "Global.h"
#include "GameScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* RankScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = RankScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RankScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    submit();

    visibleSize = Director::getInstance()->getVisibleSize();

    auto bgsprite = Sprite::create("image/bg.jpg");
    bgsprite->setPosition(visibleSize / 2);
    bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, visibleSize.height / bgsprite->getContentSize().height);
    this->addChild(bgsprite, 0);

    auto cx = Sprite::create("image/cx.png");
    cx->setPosition(cx->getContentSize() / 4);
    cx->setScale(0.5f, 0.5f);
    this->addChild(cx, 0);

    auto highscore = Sprite::create("image/highscore2.png");
    highscore->setPosition(visibleSize.width / 2, visibleSize.height - highscore->getContentSize().height / 4);
    highscore->setScale(0.5f, 0.5f);
    this->addChild(highscore, 0);

    auto table = Sprite::create("image/table.png");
    table->setPosition(visibleSize / 2);
    table->setScale(0.9f, 0.9f);
    this->addChild(table, 0);

    auto button = Button::create("image/playgame.png");
    button->setPosition(Size(visibleSize.width - button->getContentSize().width / 4, button->getContentSize().height / 4));
    button->setScale(0.25f, 0.25f);
    button->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            auto scene = GameScene::createScene();
            auto transitions = TransitionFade::create(1.0f, scene);
            Director::getInstance()->replaceScene(transitions);
        }
    });
    this->addChild(button, 2);

    auto lable = Label::createWithSystemFont("Rank", "Microsoft Yahei", 20);
    lable->setPosition(visibleSize.width / 2 - 290, visibleSize.height / 2 + 125);
    this->addChild(lable, 2);

    lable = Label::createWithSystemFont("Name", "Microsoft Yahei", 20);
    lable->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 + 125);
    this->addChild(lable, 2);

    lable = Label::createWithSystemFont("Score", "Microsoft Yahei", 20);
    lable->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2 + 125);
    this->addChild(lable, 2);

    return true;
}


void RankScene::submit() {
    char postData[100] = "";
    sprintf(postData, "name=%s&score=%d", Global::username.c_str(), Global::score);
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://egg.chenjx.cn/");
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(CC_CALLBACK_2(RankScene::onSubmitCompleted, this));

    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    request->setHeaders(headers);

    request->setRequestData(postData, strlen(postData));
    request->setTag("Submit");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void RankScene::onSubmitCompleted(HttpClient *sender, HttpResponse *response) {
    if (!response) {
        return;
    }
    if (!response->isSucceed()) {
        // error
        return;
    }

    getRank();
}

void RankScene::getRank() {
    int rNum = rand();
    char rChars[10] = "";
    itoa(rNum, rChars, 10);
    string rString = rChars;
    string reqUrl = "http://egg.chenjx.cn/?rnd=" + rString;

    HttpRequest* request = new HttpRequest();
    request->setUrl(reqUrl.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(RankScene::onRankCompleted, this));

    request->setTag("Rank");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}


void RankScene::onRankCompleted(HttpClient *sender, HttpResponse *response) {
    if (!response) {
        return;
    }
    if (!response->isSucceed()) {
        // error
        return;
    }

    std::vector<char> *buffer = response->getResponseData();
    string rankData = Global::toString(buffer);


    auto lable = Label::createWithSystemFont("Rank", "Microsoft Yahei", 20);
    lable->setPosition(visibleSize.width / 2 - 290, visibleSize.height / 2 + 125);
    this->addChild(lable, 2);

    lable = Label::createWithSystemFont("Name", "Microsoft Yahei", 20);
    lable->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 + 125);
    this->addChild(lable, 2);

    lable = Label::createWithSystemFont("Score", "Microsoft Yahei", 20);
    lable->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2 + 125);
    this->addChild(lable, 2);

    int rank = 1;
    int begin = 0, end = 0, flag = 0;
    for (unsigned i = 0; i < rankData.size(); i++) {
        if (rankData[i] == '|') {
            if (begin) {
                end = i;
                if (!flag) {   // name
                    char c[10] = "";
                    itoa(rank, c, 10);
                    string cs = c;
                    auto lable = Label::createWithSystemFont(cs, "Microsoft Yahei", 20);
                    lable->setColor(Color3B::BLACK);
                    lable->setPosition(visibleSize.width / 2 - 290, visibleSize.height / 2 + 125 - 47 * rank);
                    this->addChild(lable, 2);
                    lable = Label::createWithSystemFont(rankData.substr(begin, end-begin), "Microsoft Yahei", 20);
                    lable->setColor(Color3B::BLACK);
                    lable->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 + 125 - 47 * rank);
                    this->addChild(lable, 2);
                } else {       // score
                    auto lable = Label::createWithSystemFont(rankData.substr(begin, end-begin), "Microsoft Yahei", 20);
                    lable->setColor(Color3B::BLACK);
                    lable->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2 + 125 - 47 * rank);
                    this->addChild(lable, 2);
                    rank++;
                }
                flag = 1 - flag;
                begin = end + 1;
            } else {
                begin = i + 1;
            }
        }
    }

}
