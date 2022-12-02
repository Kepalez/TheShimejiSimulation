#pragma once
#include <cocostudio/SimpleAudioEngine.h>
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "GameMenu.h"
#include "WinScreen.h"

using namespace CocosDenshion;
using namespace cocos2d;

class GameLayer:public Layer{
private:
	PhysicsWorld* sceneWorld;
	void SetPhysicsWorld(PhysicsWorld* world) { sceneWorld = world; }
	bool onContactBegin(PhysicsContact& contact);
public:
	GameLayer();
	virtual bool init();
	void update(float deltaTime);
	static Scene* createScene(int characterChoose);
	CREATE_FUNC(GameLayer);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void doRemoveFromParentAndCleanup(Node* sender, bool cleanup);
	void FirstRound();
	void SecondRound();
	void ThirdRound();
	void FourthRound();
	void BossFight();
	void GameOver();
	Sprite* createEnemy(int type, Vec2 initialPosition);
	void moveRandom(Sprite* sender);
	void bossAttack(Node* bossDirector);
};