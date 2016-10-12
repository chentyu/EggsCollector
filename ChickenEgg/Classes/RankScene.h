#ifndef __RANK_SCENE_H__
#define __RANK_SCENE_H__

#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include <string>
#include <vector>
using std::vector;
using std::string;
using namespace cocos2d::ui;
using namespace cocos2d::network;
#include "cocos2d.h"

USING_NS_CC;

class RankScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(RankScene);

    void submit();

    void onRankCompleted(HttpClient *sender, HttpResponse *res);

    void onSubmitCompleted(HttpClient *sender, HttpResponse *response);

    void getRank();
private:
    Size visibleSize;
    TextField * textField;

};

#endif // __RANK_SCENE_H__