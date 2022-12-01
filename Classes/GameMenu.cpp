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
	auto Background = Sprite::create("../Resources/Image/MenuBackground.png");
	Background->setAnchorPoint(Vec2(0,0));
	auto playNormal = Sprite::create("../Resources/Image/MenuButtons.png", Rect(Vec2(0, 0), Size(300,150)));
	auto playSelected = Sprite::create("../Resources/Image/MenuButtons.png", Rect(Vec2(300, 0), Size(300, 150)));


	auto playButtMenuItem = MenuItemSprite::create(playNormal, playSelected,CC_CALLBACK_1(GameMenu::onNewGameClick,this));
	
	auto menu = Menu::create(playButtMenuItem,nullptr);

	this->addChild(Background);
	this->addChild(menu);
	
	return true;
}

void GameMenu::onNewGameClick(cocos2d::Ref * sender)
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
}