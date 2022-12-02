#include "WinScreen.h"
#include <string>

using namespace cocos2d;
using namespace std;

WinScreen::WinScreen(){}
WinScreen::~WinScreen(){}


Scene* WinScreen::scene(){
	auto scene = Scene::create();
	auto layer = WinScreen::create();
	scene->addChild(layer);
	return scene;
}

bool WinScreen::init() {
	const auto winSize = Director::getInstance()->getWinSize();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("../Resources/Sound/VictoryTheme.mp3");
	auto background = Sprite::create("../Resources/Image/WinBackGround.jpg");
	background->setPosition(0, 0);
	background->setAnchorPoint(Vec2(0, 0));
	background->setScale(0.3);
	this->addChild(background, -1000);
	auto playNormal = Sprite::create("../Resources/Image/ReturnToMenu1.png");
	auto playSelected = Sprite::create("../Resources/Image/ReturnToMenu2.png");
	auto youwinText = Label::createWithTTF("YOU WIN!","../Resources/Fonts/Marker Felt.ttf",80.0f,Size(200.0f,200.0f),TextHAlignment::CENTER,TextVAlignment::CENTER);
	youwinText->setTextColor(Color4B::BLACK);
	youwinText->setAnchorPoint(Vec2(0.5f, 0.5f));
	youwinText->setPosition(0.0f,200.0f);
	auto youwinTextMenu = MenuItemLabel::create(youwinText);
	auto playButtMenuItem = MenuItemSprite::create(playNormal, playSelected, CC_CALLBACK_1(WinScreen::onMainMenuClick, this));

	auto menu = Menu::create(playButtMenuItem, youwinTextMenu, nullptr);

	this->addChild(menu);

	return true;
}

void WinScreen::onMainMenuClick(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(GameMenu::scene());
}