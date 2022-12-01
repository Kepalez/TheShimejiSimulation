#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include <cocostudio/SimpleAudioEngine.h>

using namespace cocos2d;

class GameMenu : public Layer
{
private:

public:
    static cocos2d::Scene* scene();

    void update(float deltaTime);

    virtual bool init();

    void onNewGameClick(cocos2d::Ref* sender);

    CREATE_FUNC(GameMenu);
};
