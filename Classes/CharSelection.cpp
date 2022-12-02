#include "CharSelection.h"

using namespace cocos2d;
using namespace std;

CharSelection::CharSelection() {}
CharSelection::~CharSelection() {}


Scene* CharSelection::scene() {
	auto scene = Scene::create();
	auto layer = CharSelection::create();
	scene->addChild(layer);
	return scene;
}

bool CharSelection::init() {
	const auto winSize = Director::getInstance()->getWinSize();

	auto ShijimaNormal = Sprite::create("../Resources/Image/ShijimaChoose1.png");
	auto ShijimaPressed = Sprite::create("../Resources/Image/ShijimaChoose2.png");
	auto MajimeNormal = Sprite::create("../Resources/Image/MajimeChoose1.png");
	auto MajimePressed = Sprite::create("../Resources/Image/MajimeChoose2.png");
	auto background = Sprite::create("../Resources/Image/CharacterSelectionText.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(-150, -50);
	background->setScale(1.4);

	auto ShijimaButtMenuItem = MenuItemSprite::create(ShijimaNormal, ShijimaPressed, CC_CALLBACK_1(CharSelection::ShijimaChoosed,this));
	auto MajimeButtMenuItem = MenuItemSprite::create(MajimeNormal, MajimePressed, CC_CALLBACK_1(CharSelection::MajimeChoosed, this));
	ShijimaButtMenuItem->setPosition(-128, 0);
	MajimeButtMenuItem->setPosition(128, 0);
	ShijimaButtMenuItem->setScale(0.29f, 0.3f);
	MajimeButtMenuItem->setScale(0.29f, 0.3f);


	auto menu = Menu::create(ShijimaButtMenuItem,MajimeButtMenuItem,nullptr);

	this->addChild(menu);
	this->addChild(background, -1000);

	return true;
}

void CharSelection::ShijimaChoosed(cocos2d::Ref* sender) {
	Director::getInstance()->replaceScene(GameLayer::createScene(1));
}

void CharSelection::MajimeChoosed(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(GameLayer::createScene(2));
}