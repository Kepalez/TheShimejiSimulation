#include "GameMenu.h"
#include <string>

USING_NS_CC;

using namespace cocos2d;

Scene* GameMenu::scene() {
	Scene* scene = nullptr;

	scene = Scene::create();
	auto* layer = GameMenu::create();

	scene->addChild(layer);
	return scene;
}

void GameMenu::update(float deltaTime) {

}

bool GameMenu::init() {
	const auto winSize = Director::getInstance()->getWinSize();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("../Resources/Sound/MainMenuTheme.mp3");
	auto mainTitle = Sprite::create("../Resources/Image/MainTitle.png");
	mainTitle->setAnchorPoint(Vec2(0.5f, 0.5f));
	mainTitle->setScale(0.8);
	mainTitle->setPosition(winSize.width / 2, winSize.height - 200);
	auto Background = Sprite::create("../Resources/Image/MenuBackground.png");
	Background->setAnchorPoint(Vec2(0,0));
	auto playNormal = Sprite::create("../Resources/Image/PlayButton.png");
	playNormal->setScale(1.2f);
	auto playSelected = Sprite::create("../Resources/Image/PlayButton2.png");
	playSelected->setScale(1.2f);
	auto quitNormal = Sprite::create("../Resources/Image/ExitButton.png");
	quitNormal->setScale(1.2f);
	auto quitSelected = Sprite::create("../Resources/Image/ExitButton2.png");
	quitSelected->setScale(1.2f);
	auto playButtMenuItem = MenuItemSprite::create(playNormal, playSelected,CC_CALLBACK_1(GameMenu::onNewGameClick,this));
	auto exitButtMenuItem = MenuItemSprite::create(quitNormal, quitSelected, CC_CALLBACK_1(GameMenu::onExitClick,this));
	playButtMenuItem->setPosition(-10, 0);
	exitButtMenuItem->setPosition(-10, -150);
	auto menu = Menu::create(playButtMenuItem,exitButtMenuItem,nullptr);

	this->addChild(Background);
	this->addChild(menu);
	this->addChild(mainTitle);
	
	return true;
}

void GameMenu::onNewGameClick(cocos2d::Ref * sender)
{
	Director::getInstance()->replaceScene(CharSelection::scene());

void GameMenu::onExitClick(cocos2d::Ref* sender) {
	Director::getInstance()->end();
}