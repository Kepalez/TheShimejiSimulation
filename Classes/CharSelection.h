#pragma once

#include <cocostudio/SimpleAudioEngine.h>
#include "cocos2d.h"
#include "GameMenu.h"
#include "GameLayer.h"

using namespace CocosDenshion;
using namespace cocos2d;

class CharSelection : public Layer {
private:

public:
	static Scene* scene();
	CharSelection();
	~CharSelection();
	virtual bool init();
	void ShijimaChoosed(cocos2d::Ref* sender);
	void MajimeChoosed(cocos2d::Ref* sender);
	CREATE_FUNC(CharSelection);
};