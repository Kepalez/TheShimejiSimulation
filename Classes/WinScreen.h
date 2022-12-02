#pragma once

#include <cocostudio/SimpleAudioEngine.h>
#include "cocos2d.h"
#include "GameMenu.h"

using namespace CocosDenshion;
using namespace cocos2d;

class WinScreen : public Layer {
private:

public:
	static Scene* scene();
	WinScreen();
	~WinScreen();
	virtual bool init();
	void onMainMenuClick(cocos2d::Ref* sender);
	CREATE_FUNC(WinScreen);
};