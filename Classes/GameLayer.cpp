#include "GameLayer.h"

using namespace cocos2d;
//Cat.Bitmasks Player:1, PlayerBullet:2, Enemy:4, EnemyBullet: 8, MedKit: 16 
//window size 520, 760

int playerCharacter;
float PlayerXDir = 0.0f, PlayerYDir = 0.0f, PlayerXMov = 0.0f, PlayerYMov = 0.0f;
string playerbulletDirec;
bool gameOver = false;
Sprite* PlayerSprite;
Sprite* lifeUI;
float playerCollisionWidth = 28,playerCollisionHeight = 80;

Scene* GameLayer::createScene(int characterChoose) {
	playerCharacter = characterChoose;
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(false);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = GameLayer::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}
GameLayer::GameLayer() {

}
void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		PlayerYDir++;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		PlayerXDir--;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		PlayerYDir--;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		PlayerXDir++;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		auto bala = Sprite::create(playerbulletDirec);
		bala->setPosition(PlayerSprite->getPosition().x, PlayerSprite->getPosition().y + playerCollisionHeight / 2);
		bala->setAnchorPoint(Vec2(0.5, 0.5));
		bala->setPhysicsBody(PhysicsBody::createBox(Size(bala->getContentSize().width, bala->getContentSize().height), PhysicsMaterial(1, 0, 0)));
		bala->getPhysicsBody()->setCategoryBitmask(2);
		bala->getPhysicsBody()->setCollisionBitmask(4);
		bala->getPhysicsBody()->setContactTestBitmask(4);
		SimpleAudioEngine::getInstance()->playEffect("../Resources/Sound/playerShoot.mp3");
		this->addChild(bala);
		bala->runAction(Sequence::create(
			MoveTo::create((Director::getInstance()->getVisibleSize().height - PlayerSprite->getPosition().y) / 600.0f, Vec2(PlayerSprite->getPosition().x, Director::getInstance()->getVisibleSize().height + 5)),
			CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
			NULL));
	}
}
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		PlayerYDir--;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		PlayerXDir++;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		PlayerYDir++;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		PlayerXDir--;
	}
}


void GameLayer::doRemoveFromParentAndCleanup(Node* sender, bool cleanup)
{
	sender->removeFromParentAndCleanup(cleanup);
}
void GameLayer::moveRandom(Sprite* sender) {
	auto p1 = Point(RandomHelper::random_real<float>(10, 510), RandomHelper::random_real<float>(500, 750));
	auto moveTo = MoveTo::create(p1.getDistance(sender->getPosition()) / 300.0f,p1);
	auto delayTime = DelayTime::create(0.5);
	auto moveAgainFunc = CallFunc::create([=]()
		{
			moveRandom(sender);
		});
	auto blueShoot = CallFunc::create([=]() {
		auto bullet = Sprite::create("../Resources/Image/EnemyBullet.png", Rect(0, 0, 60, 60));
		bullet->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(1, 0, 0)));
		bullet->setScale(0.3);
		bullet->setPosition(sender->getPosition());
		bullet->getPhysicsBody()->setCategoryBitmask(8);
		bullet->getPhysicsBody()->setContactTestBitmask(1);
		bullet->getPhysicsBody()->setCollisionBitmask(1);
		auto playerPos = Point(PlayerSprite->getPosition());
		auto bulletMoveBy = MoveBy::create(playerPos.getDistance(bullet->getPosition()) * 2 / 100.0f, (playerPos - bullet->getPosition()) * 5.0f);
		this->addChild(bullet);
		bullet->runAction(Sequence::create(
			bulletMoveBy,
			CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
			NULL));
		});
	auto redShoot = CallFunc::create([=]() {
		auto bullet1 = Sprite::create("../Resources/Image/EnemyBullet.png", Rect(60, 60, 60, 60));
		bullet1->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(1, 0, 0)));
		bullet1->setScale(0.3);
		bullet1->setPosition(sender->getPosition());
		bullet1->getPhysicsBody()->setCategoryBitmask(8);
		bullet1->getPhysicsBody()->setContactTestBitmask(1);
		bullet1->getPhysicsBody()->setCollisionBitmask(1);
		auto playerPos = Point(PlayerSprite->getPosition());
		auto bulletMoveBy = MoveBy::create(playerPos.getDistance(bullet1->getPosition()) * 2 / 100.0f, (playerPos - bullet1->getPosition()) * 5.0f);
		this->addChild(bullet1);
		bullet1->runAction(Sequence::create(
			bulletMoveBy,
			CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
			NULL));

		auto bullet2 = Sprite::create("../Resources/Image/EnemyBullet.png", Rect(60, 60, 60, 60));
		bullet2->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(1, 0, 0)));
		bullet2->setScale(0.3);
		bullet2->setPosition(sender->getPosition());
		bullet2->getPhysicsBody()->setCategoryBitmask(8);
		bullet2->getPhysicsBody()->setContactTestBitmask(1);
		bullet2->getPhysicsBody()->setCollisionBitmask(1);
		playerPos = Point(PlayerSprite->getPosition().x + 100.0f, PlayerSprite->getPosition().y);
		bulletMoveBy = MoveBy::create(playerPos.getDistance(bullet2->getPosition()) * 2 / 100.0f, (playerPos - bullet2->getPosition()) * 5.0f);
		this->addChild(bullet2);
		bullet2->runAction(Sequence::create(
			bulletMoveBy,
			CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
			NULL));

		auto bullet3 = Sprite::create("../Resources/Image/EnemyBullet.png", Rect(60, 60, 60, 60));
		bullet3->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(1, 0, 0)));
		bullet3->setScale(0.3);
		bullet3->setPosition(sender->getPosition());
		bullet3->getPhysicsBody()->setCategoryBitmask(8);
		bullet3->getPhysicsBody()->setContactTestBitmask(1);
		bullet3->getPhysicsBody()->setCollisionBitmask(1);
		playerPos = Point(PlayerSprite->getPosition().x - 100.0f, PlayerSprite->getPosition().y);
		bulletMoveBy = MoveBy::create(playerPos.getDistance(bullet3->getPosition()) * 2 / 100.0f, (playerPos - bullet3->getPosition()) * 5.0f);
		this->addChild(bullet3);
		bullet3->runAction(Sequence::create(
			bulletMoveBy,
			CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
			NULL));
		});
	switch (sender->getChildByName<Enemy*>("enemyData")->getType()) {
	case 1:
		sender->runAction(Sequence::create(moveTo, delayTime, blueShoot, moveAgainFunc, nullptr));
		break;
	case 2:
		sender->runAction(Sequence::create(moveTo, delayTime, redShoot, moveAgainFunc, nullptr));
		break;
	}
}
void GameLayer::bossAttack(Node* bossController) {
	if (!gameOver) {
		int randAttack = RandomHelper::random_int(1, 3);
		auto delay = DelayTime::create(5.0f);
		auto attackAgain = CallFunc::create([=]() {bossAttack(bossController); });
		switch (randAttack) {
		case 1: //summon blueLobsters
			moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
			moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
			moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
			moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
			moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
			moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
			break;
		case 3: //summon redLobsters
			moveRandom(createEnemy(2, Vec2(-20.0f, 600.0f)));
			moveRandom(createEnemy(2, Vec2(-20.0f, 600.0f)));
			break;
		case 2: //Shoot
			auto bullet = Sprite::create("../Resources/Image/EnemyBullet.png", Rect(60.0f, 0.0f, 60.0f, 60.0f));
			bullet->setPhysicsBody(PhysicsBody::createCircle(30, PhysicsMaterial(1, 0, 0)));
			Vec2 lobsterBody = Vec2(bossController->getChildByName<Sprite*>("body")->getPosition());
			bullet->setPosition(lobsterBody.x, lobsterBody.y - 30.0f);
			bullet->getPhysicsBody()->setCategoryBitmask(8);
			bullet->getPhysicsBody()->setContactTestBitmask(1);
			bullet->getPhysicsBody()->setCollisionBitmask(1);
			auto playerPos = Point(PlayerSprite->getPosition());
			auto bulletScale = ScaleTo::create(1.0f, 3.0f);
			auto bulletMoveBy = MoveBy::create(playerPos.getDistance(bullet->getPosition()) * 2 / 100.0f, (playerPos - bullet->getPosition()) * 5.0f);
			this->addChild(bullet);
			bullet->runAction(Sequence::create(
				bulletScale,
				DelayTime::create(0.5f),
				bulletMoveBy,
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				NULL));

		}
		bossController->runAction(Sequence::create(
			delay,
			attackAgain,
			nullptr
		));
	}
}
bool GameLayer::onContactBegin(PhysicsContact& contact) {
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	auto acol = a->getCategoryBitmask();
	auto bcol = b->getCategoryBitmask();
	//bullet to enenmy
	if ((acol == 4  && bcol == 2) ||( acol == 2 && bcol == 4 )) {
		Sprite* aOwner = (Sprite*)a->getOwner();
		Sprite* bOwner = (Sprite*)b->getOwner();
		if (acol == 2) {
			if (aOwner != nullptr) {
				aOwner->removeFromParentAndCleanup(true);
				if (bOwner != nullptr) {
					bOwner->getChildByName<Enemy*>("enemyData")->takeDmg(5);
					bOwner->runAction(Sequence::create(TintTo::create(0.0f, 125, 125, 125),DelayTime::create(0.1f),TintTo::create(0.0f,255,255,255),nullptr));
					if (bOwner->getChildByName<Enemy*>("enemyData")->getLife() <= 0) {
						if (bOwner->getName() == "left" || bOwner->getName() == "right") {
							if (bOwner->getName() == "left") bOwner->setTexture("../Resources/Image/GiantLeftArmB.png");
							else bOwner->setTexture("../Resources/Image/GiantRightArmB.png");
							bOwner->pause();
							auto boss = bOwner->getParent();
							if (boss->getChildByName<Sprite*>("left")->getChildByName<Enemy*>("enemyData")->getLife() <= 0 && boss->getChildByName<Sprite*>("right")->getChildByName<Enemy*>("enemyData")->getLife() <= 0) {
								gameOver = true;
								GameOver();
							}
						}
						else {
							int chanceOfMedKit = RandomHelper::random_int(0, 100);
							if (chanceOfMedKit > 90) {
								auto medKit = Sprite::create("../Resources/Image/MedKit.png");
								medKit->setAnchorPoint(Vec2(0.5f, 0.5f));
								medKit->setScale(0.8);
								medKit->setPosition(0.0f, 0.0f);
								medKit->setPhysicsBody(PhysicsBody::createBox(Size(medKit->getContentSize())));
								medKit->getPhysicsBody()->setContactTestBitmask(1);
								medKit->getPhysicsBody()->setCategoryBitmask(16);
								medKit->getPhysicsBody()->setCollisionBitmask(1);
								this->addChild(medKit);
								medKit->runAction(Sequence::create(
									MoveTo::create(0.0f, b->getPosition()),
									MoveTo::create((b->getPosition().y + 20) / 100.0f, Vec2(b->getPosition().x, -20)),
									CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
									nullptr
								));
							}
							bOwner->removeFromParentAndCleanup(true);
						}
					}
				}
			}
		}
		else {
			if (bOwner != nullptr) {
				bOwner->removeFromParentAndCleanup(true);
				if (aOwner != nullptr) {
					aOwner->getChildByName<Enemy*>("enemyData")->takeDmg(5);
					aOwner->runAction(Sequence::create(TintTo::create(0.0f, 125, 125, 125), DelayTime::create(0.1f), TintTo::create(0.0f, 255, 255, 255), nullptr));
					if (aOwner->getChildByName<Enemy*>("enemyData")->getLife() <= 0) {
						if (aOwner->getName() == "left" || aOwner->getName() == "right") {
							if (aOwner->getName() == "left") aOwner->setTexture("../Resources/Image/GiantLeftArmB.png");
							else aOwner->setTexture("../Resources/Image/GiantRightArmB.png");
							aOwner->pause();
							auto boss = aOwner->getParent();
							if (boss->getChildByName<Sprite*>("left")->getChildByName<Enemy*>("enemyData")->getLife() <= 0 && boss->getChildByName<Sprite*>("right")->getChildByName<Enemy*>("enemyData")->getLife() <= 0) {
								gameOver = true;
								GameOver();
							}
						}
						else
						{
							int chanceOfMedKit = RandomHelper::random_int(0, 100);
							if (chanceOfMedKit > 90) {
								auto medKit = Sprite::create("../Resources/Image/MedKit.png");
								medKit->setAnchorPoint(Vec2(0.5f, 0.5f));
								medKit->setScale(0.8);
								medKit->setPosition(0.0f, 0.0f);
								medKit->setPhysicsBody(PhysicsBody::createBox(Size(medKit->getContentSize())));
								medKit->getPhysicsBody()->setContactTestBitmask(1);
								medKit->getPhysicsBody()->setCategoryBitmask(16);
								medKit->getPhysicsBody()->setCollisionBitmask(1);
								this->addChild(medKit);
								medKit->runAction(Sequence::create(
									MoveTo::create(0.0f, a->getPosition()),
									MoveTo::create((a->getPosition().y + 20) / 100.0f, Vec2(a->getPosition().x, -20)),
									CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
									nullptr
								));
							}
							a->getOwner()->removeFromParentAndCleanup(true);
						}
					}
				}
			}
		}
	}
	
	//bullet to player
	if ((acol == 1 && bcol == 8)|| (bcol == 1 && acol == 8)) {
		if (acol == 8) {
			if (a->getOwner() != nullptr) {
				a->getOwner()->removeFromParentAndCleanup(true);
				if (b->getOwner() != nullptr) {
					b->getOwner()->getChildByName<Player*>("playerData")->takeDmg();
					lifeUI->setTextureRect(Rect(0, 0, 48 * b->getOwner()->getChildByName<Player*>("playerData")->getLife(), 42));
					if (b->getOwner()->getChildByName<Player*>("playerData")->getLife() <= 0) {
						b->getOwner()->setVisible(false);
						b->setContactTestBitmask(0);
						PlayerSprite->pause();
						gameOver = true;
						GameOver();
					}
				}
			}
		}
		else {
			if (b->getOwner() != nullptr) {
				b->getOwner()->removeFromParentAndCleanup(true);
				if (a->getOwner() != nullptr) {
					a->getOwner()->getChildByName<Player*>("playerData")->takeDmg();
					lifeUI->setTextureRect(Rect(0, 0, 48 * a->getOwner()->getChildByName<Player*>("playerData")->getLife(), 42));
					if (a->getOwner()->getChildByName<Player*>("playerData")->getLife() <= 0) {
						a->getOwner()->pause();
						gameOver = true;
						GameOver();
					}
				}
			}
		}
	}

	//medKit to player
	if ((acol == 1 && bcol == 16) || (bcol == 1 && acol == 16)) {
		if (acol == 16) {
			if (a->getOwner() != nullptr) {
				a->getOwner()->removeFromParentAndCleanup(true);
				if (b->getOwner() != nullptr) {
					b->getOwner()->getChildByName<Player*>("playerData")->heal();
					lifeUI->setTextureRect(Rect(0, 0, 48 * b->getOwner()->getChildByName<Player*>("playerData")->getLife(), 42));
				}
			}
		}
		else {
			if (b->getOwner() != nullptr) {
				b->getOwner()->removeFromParentAndCleanup(true);
				if (a->getOwner() != nullptr) {
					a->getOwner()->getChildByName<Player*>("playerData")->heal();
					lifeUI->setTextureRect(Rect(0, 0, 48 * a->getOwner()->getChildByName<Player*>("playerData")->getLife(), 42));
				}
			}
		}
	}

	return true;
}
bool GameLayer::init() {
	gameOver = false;
	PlayerXDir = 0.0f; PlayerYDir = 0.0f; PlayerXMov = 0.0f; PlayerYMov = 0.0f;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("../Resources/Sound/Lvl1Music.mp3");
	//load player and other stuff
	auto playerData = Player::create();
	playerData->setName("playerData");
	if (playerCharacter == 1) {
		PlayerSprite = Sprite::create("../Resources/Image/Shijima_Fish.png");
		playerbulletDirec = "../Resources/Image/BubbleBullet.png";
	}
	else {
		PlayerSprite = Sprite::create("../Resources/Image/Majime_Corn.png");
		playerbulletDirec = "../Resources/Image/CornBullet.png";
	}
	PlayerSprite->addChild(playerData);
	PlayerSprite->setPosition(Vec2(254.0f, 90.0f));
	PlayerSprite->setScale(1, 0.8f);
	PlayerSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	PlayerSprite->setPhysicsBody(PhysicsBody::createBox(Size(playerCollisionWidth, playerCollisionHeight), PhysicsMaterial(100, 0, 0)));
	PlayerSprite->getPhysicsBody()->setCollisionBitmask(1);
	PlayerSprite->getPhysicsBody()->setCategoryBitmask(1);
	PlayerSprite->getPhysicsBody()->setContactTestBitmask(24);
	this->addChild(PlayerSprite, 1);

	auto background = Sprite::create("../Resources/Image/Lvl1Background.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setScale(0.58f, 0.58f);
	background->setPosition(0, 0);
	this->addChild(background, -1000);

	lifeUI = Sprite::create("../Resources/Image/Hearts.png",Rect(0,0,48*PlayerSprite->getChildByName<Player*>("playerData")->getLife(),42));
	lifeUI->setAnchorPoint(Vec2(0.0f, 0.5f));
	lifeUI->setPosition(Vec2(10.0f, 730.0f));
	this->addChild(lifeUI,100);

	//load enemy events
	auto GoFirstRound = CallFunc::create([=]() {FirstRound();});
	auto GoSecondRound = CallFunc::create([=]() {SecondRound();});
	auto GoThirdRound = CallFunc::create([=]() {ThirdRound();});
	auto GoFourthRound = CallFunc::create([=]() {FourthRound();});
	auto GoFinalBoss = CallFunc::create([=]() {BossFight(); });
	auto mainSequence = Sequence::create(
		DelayTime::create(3.0f),
		GoFirstRound,
		DelayTime::create(10.0f),
		GoSecondRound,
		DelayTime::create(12.0f),
		GoThirdRound,
		DelayTime::create(26.0f),
		GoFourthRound,
		DelayTime::create(26.0f),
		GoFinalBoss,
		nullptr
	);
	this->runAction(mainSequence);
	//Load evenListeners

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin,this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	return true;
}
void GameLayer::update(float dt) {
	if (!gameOver) {
		Vec2 playerMovement((PlayerXDir * PlayerSprite->getChildByName<Player*>("playerData")->getSpeed() * dt), (PlayerYDir * PlayerSprite->getChildByName<Player*>("playerData")->getSpeed() * dt));
		auto playerBody = PlayerSprite->getPhysicsBody();
		PlayerSprite->setRotation(0);
		//check border collision
		{
			if (PlayerSprite->getPosition().x + playerMovement.x + playerCollisionWidth / 2 >= Director::getInstance()->getVisibleSize().width) {
				playerMovement.x = Director::getInstance()->getVisibleSize().width - PlayerSprite->getPosition().x - playerCollisionWidth / 2;
			}
			if (PlayerSprite->getPosition().x + playerMovement.x - playerCollisionWidth / 2 <= 0) {
				playerMovement.x = -PlayerSprite->getPosition().x + playerCollisionWidth / 2;
			}
			if (PlayerSprite->getPosition().y + playerMovement.y + playerCollisionHeight / 2 > Director::getInstance()->getVisibleSize().height) {
				playerMovement.y = Director::getInstance()->getVisibleSize().height - PlayerSprite->getPosition().y - playerCollisionHeight / 2;
			}
			if (PlayerSprite->getPosition().y + playerMovement.y - playerCollisionHeight / 2 < 0) {
				playerMovement.y = -PlayerSprite->getPosition().y + playerCollisionHeight / 2;
			}
			PlayerSprite->setPosition(Vec2(PlayerSprite->getPosition().x + playerMovement.x, PlayerSprite->getPosition().y + playerMovement.y));
		}
	}
}
void GameLayer::FirstRound() {
	log("FirstRound starts");
	moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
	moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
}
void GameLayer::SecondRound() {
	log("SecondRound starts");
	moveRandom(createEnemy(1, Vec2(173.3f, -20)));
	moveRandom(createEnemy(1, Vec2(173.3f, -20)));
	moveRandom(createEnemy(1, Vec2(346.6f, -20)));
	moveRandom(createEnemy(1, Vec2(346.3f, -20)));
	auto red1 = createEnemy(2, Vec2(173.3f, 780));
	red1->runAction(Sequence::create(
		MoveTo::create(2, Vec2(173.3f, 700)),
		CallFuncN::create(CC_CALLBACK_0(GameLayer::moveRandom, this, red1)),
		nullptr));
	auto red2 = createEnemy(2, Vec2(346.6f, 780));
	red2->runAction(Sequence::create(
		MoveTo::create(2, Vec2(346.6f, 700)),
		CallFuncN::create(CC_CALLBACK_0(GameLayer::moveRandom, this, red2)),
		nullptr));
}
void GameLayer::ThirdRound() {
	log("Third round starts");
	auto redLobsterSpawner = Node::create();
	auto greenLobsterSpawner = Node::create();
	auto spawnReds = CallFunc::create([=]() {
		auto redLobster = createEnemy(2, Vec2(-20, 700));
		redLobster->runAction(Sequence::create(
			MoveTo::create(1.5f, Vec2(40, 700)),
			CallFuncN::create(CC_CALLBACK_0(GameLayer::moveRandom, this, redLobster)),
			nullptr
		));
		redLobster = createEnemy(2, Vec2(540, 700));
		redLobster->runAction(Sequence::create(
			MoveTo::create(1.5f, Vec2(480, 700)),
			CallFuncN::create(CC_CALLBACK_0(GameLayer::moveRandom, this, redLobster)),
			nullptr
		));
		});
	auto spawnGreens = CallFunc::create([=]() {
		int x = RandomHelper::random_int(1, 8);
		Sprite* newGreen;
		Point toReach;
		float speed = 500.0f;
		switch (x) {
		case 1: //left
			newGreen = createEnemy(3, Vec2(-20.0f, 380.0f));
			newGreen->setRotation(270);
			toReach = Point(560.0f, 380.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(0.0f, 380.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 2: //top-left
			newGreen = createEnemy(3, Vec2(-20.0f, 780.0f));
			newGreen->setRotation(315);
			toReach = Point(560.0f, -20.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(0.0f, 760.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 3: //top
			newGreen = createEnemy(3, Vec2(260.0f, 780.0f));
			toReach = Point(260.0f, -20.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(260.0f, 760.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 4: //top-right
			newGreen = createEnemy(3, Vec2(540.0f, 780.0f));
			newGreen->setRotation(45);
			toReach = Point(-20.0f, -20.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(520.0f, 760.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 5: //right
			newGreen = createEnemy(3, Vec2(540.0f, 380.0f));
			newGreen->setRotation(90);
			toReach = Point(-20.0f, 380.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(520.0f, 380.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 6: //bottom-right
			newGreen = createEnemy(3, Vec2(540.0f, -20.0f));
			newGreen->setRotation(135);
			toReach = Point(-20.0f, 780.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(520.0f, 0.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 7: //bottom
			newGreen = createEnemy(3, Vec2(260.0f, -20.0f));
			newGreen->setRotation(180);
			toReach = Point(260.0f, 780.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(260.0f, 0.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 8: //bottom-left
			newGreen = createEnemy(3, Vec2(-20.0f, -20.0f));
			newGreen->setRotation(225);
			toReach = Point(540.0f, 780.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(0.0f, 0.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
		}
		});
	this->addChild(redLobsterSpawner);
	this->addChild(greenLobsterSpawner);

	redLobsterSpawner->runAction(Sequence::create(
		spawnReds,DelayTime::create(5.0f),
		spawnReds, DelayTime::create(5.0f),
		spawnReds, DelayTime::create(5.0f),
		spawnReds, DelayTime::create(5.0f),
		spawnReds, DelayTime::create(5.0f),
		nullptr
	));
	
	greenLobsterSpawner->runAction(Sequence::create(
		spawnGreens,DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		spawnGreens, DelayTime::create(4.0f),
		nullptr
	));
}
void GameLayer::FourthRound() {
	log("Forth round starts");
	auto spawnGreens = CallFunc::create([=]() {
		int x = RandomHelper::random_int(1, 8);
		Sprite* newGreen;
		Point toReach;
		float speed = 500.0f;
		switch (x) {
		case 1: //left
			newGreen = createEnemy(3, Vec2(-20.0f, 380.0f));
			newGreen->setRotation(270);
			toReach = Point(560.0f, 380.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(0.0f, 380.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 2: //top-left
			newGreen = createEnemy(3, Vec2(-20.0f, 780.0f));
			newGreen->setRotation(315);
			toReach = Point(560.0f, -20.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(0.0f, 760.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 3: //top
			newGreen = createEnemy(3, Vec2(260.0f, 780.0f));
			toReach = Point(260.0f, -20.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(260.0f, 760.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 4: //top-right
			newGreen = createEnemy(3, Vec2(540.0f, 780.0f));
			newGreen->setRotation(45);
			toReach = Point(-20.0f, -20.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(520.0f, 760.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 5: //right
			newGreen = createEnemy(3, Vec2(540.0f, 380.0f));
			newGreen->setRotation(90);
			toReach = Point(-20.0f, 380.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(520.0f, 380.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 6: //bottom-right
			newGreen = createEnemy(3, Vec2(540.0f, -20.0f));
			newGreen->setRotation(135);
			toReach = Point(-20.0f, 780.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(520.0f, 0.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 7: //bottom
			newGreen = createEnemy(3, Vec2(260.0f, -20.0f));
			newGreen->setRotation(180);
			toReach = Point(260.0f, 780.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(260.0f, 0.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
			break;
		case 8: //bottom-left
			newGreen = createEnemy(3, Vec2(-20.0f, -20.0f));
			newGreen->setRotation(225);
			toReach = Point(540.0f, 780.0f);
			newGreen->runAction(Sequence::create(
				MoveTo::create(3.0f, Vec2(0.0f, 0.0f)), DelayTime::create(0.2f),
				MoveTo::create(toReach.distance(newGreen->getPosition()) / speed, toReach),
				CallFuncN::create(CC_CALLBACK_1(GameLayer::doRemoveFromParentAndCleanup, this, true)),
				nullptr));
		}
		});
	auto spawnBlues = CallFunc::create([=]() {
		moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(-20.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
		moveRandom(createEnemy(1, Vec2(540.0f, 600.0f)));
		});
	auto greenLobsterSpawner = Node::create();
	auto blueLobsterSpawner = Node::create();
	this->addChild(greenLobsterSpawner);
	this->addChild(blueLobsterSpawner);
	greenLobsterSpawner->runAction(Sequence::create(
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		spawnGreens, DelayTime::create(3.0f),
		nullptr
	));
	blueLobsterSpawner->runAction(Sequence::create(
		spawnBlues, DelayTime::create(4.0f),
		spawnBlues, DelayTime::create(4.0f),
		spawnBlues, DelayTime::create(4.0f),
		spawnBlues, DelayTime::create(4.0f),
		spawnBlues, DelayTime::create(4.0f),
		spawnBlues, DelayTime::create(4.0f),
		nullptr
	));
}
void GameLayer::BossFight() {
	log("Boss fight starts");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto changeMusic = CallFunc::create([=]() {SimpleAudioEngine::getInstance()->playBackgroundMusic("../Resources/Sound/FinalBossTheme.mp3"); });
	auto bossDirector = Node::create();
	this->addChild(bossDirector);
	auto leftArm = Sprite::create("../Resources/Image/GiantLeftArm.png");
	leftArm->setName("left");
	auto rightArm = Sprite::create("../Resources/Image/GiantRightArm.png");
	rightArm->setName("right");
	auto lobsterBody = Sprite::create("../Resources/Image/GiantLobsterBody.png");
	lobsterBody->setName("body");

	leftArm->setAnchorPoint(Vec2(0.5f, 0.5f));
	leftArm->setPosition(173.3f, 860.0f);
	lobsterBody->setAnchorPoint(Vec2(0.5f, 0.5f));
	lobsterBody->setPosition(260.0f, 850.0f);
	rightArm->setAnchorPoint(Vec2(0.5f, 0.5f));
	rightArm->setPosition(346.6f, 860.0f);
	bossDirector->addChild(leftArm);
	bossDirector->addChild(lobsterBody);
	bossDirector->addChild(rightArm);

	auto setupBoss = CallFunc::create([bossDirector,leftArm,rightArm]()
		{
			auto enemyData1 = Enemy::create();
			enemyData1->setName("enemyData");
			enemyData1->setLife(300);
			leftArm->setPhysicsBody(PhysicsBody::createBox(leftArm->getContentSize()));
			leftArm->getPhysicsBody()->setContactTestBitmask(2);
			leftArm->getPhysicsBody()->setCollisionBitmask(2);
			leftArm->getPhysicsBody()->setCategoryBitmask(4);
			leftArm->addChild(enemyData1);

			auto enemyData2 = Enemy::create();
			rightArm->setPhysicsBody(PhysicsBody::createBox(rightArm->getContentSize()));
			enemyData2->setName("enemyData");
			enemyData2->setLife(300);
			rightArm->getPhysicsBody()->setContactTestBitmask(2);
			rightArm->getPhysicsBody()->setCollisionBitmask(2);
			rightArm->getPhysicsBody()->setCategoryBitmask(4);
			rightArm->addChild(enemyData2);
		});
	leftArm->runAction(Sequence::create(DelayTime::create(17.0f),MoveBy::create(3,Vec2(0,-190)),nullptr));
	lobsterBody->runAction(Sequence::create(DelayTime::create(17.0f), MoveBy::create(3, Vec2(0, -140)), nullptr));
	rightArm->runAction(Sequence::create(DelayTime::create(17.0f), MoveBy::create(3, Vec2(0, -190)), nullptr));
	auto bossIntro = Sequence::create(
		DelayTime::create(2.0f),
		changeMusic,DelayTime::create(18.0f), 
		setupBoss,
		CallFuncN::create(CC_CALLBACK_1(GameLayer::bossAttack, this)), 
		nullptr
	);
	bossDirector->runAction(bossIntro);
}

Sprite* GameLayer::createEnemy(int type,Vec2 initialPosition) {
	Sprite* newEnemy;
	auto enemyData = Enemy::create();
	enemyData->setName("enemyData");
	enemyData->setType(type);
	switch (type) {
	case 1: //blueLobster
		newEnemy = Sprite::create("../Resources/Image/BlueLobster.png");
		newEnemy->setName("Generic");
		newEnemy->setAnchorPoint(Vec2(0.5, 0.5));
		newEnemy->setPosition(initialPosition);
		newEnemy->setPhysicsBody(PhysicsBody::createBox(Size(newEnemy->getContentSize().width, newEnemy->getContentSize().height), PhysicsMaterial(0, 0, 0)));
		newEnemy->getPhysicsBody()->setContactTestBitmask(2);
		newEnemy->getPhysicsBody()->setCategoryBitmask(4);
		newEnemy->getPhysicsBody()->setCollisionBitmask(2);
		newEnemy->addChild(enemyData);
		newEnemy->getChildByName<Enemy*>("enemyData")->setLife(10);
		this->addChild(newEnemy, 1);
		break;
	case 2:
		newEnemy = Sprite::create("../Resources/Image/RedLobster.png");
		newEnemy->setName("Generic");
		newEnemy->setScale(1.2f);
		newEnemy->setAnchorPoint(Vec2(0.5, 0.5));
		newEnemy->setPosition(initialPosition);
		newEnemy->setPhysicsBody(PhysicsBody::createBox(Size(newEnemy->getContentSize().width, newEnemy->getContentSize().height), PhysicsMaterial(0, 0, 0)));
		newEnemy->getPhysicsBody()->setContactTestBitmask(2);
		newEnemy->getPhysicsBody()->setCategoryBitmask(4);
		newEnemy->getPhysicsBody()->setCollisionBitmask(2);
		newEnemy->addChild(enemyData);
		newEnemy->getChildByName<Enemy*>("enemyData")->setLife(25);
		this->addChild(newEnemy, 1);
		break;
	case 3:
		newEnemy = Sprite::create("../Resources/Image/GreenLobster.png");
		newEnemy->setName("Generic");
		newEnemy->setScale(1.2f);
		newEnemy->setAnchorPoint(Vec2(0.5, 0.5));
		newEnemy->setPosition(initialPosition);
		newEnemy->setPhysicsBody(PhysicsBody::createBox(Size(newEnemy->getContentSize().width, newEnemy->getContentSize().height), PhysicsMaterial(0, 0, 0)));
		newEnemy->getPhysicsBody()->setContactTestBitmask(1);
		newEnemy->getPhysicsBody()->setCategoryBitmask(8);
		newEnemy->getPhysicsBody()->setCollisionBitmask(1);
		newEnemy->addChild(enemyData);
		newEnemy->getChildByName<Enemy*>("enemyData")->setLife(10);
		newEnemy->getChildByName<Enemy*>("enemyData")->setSpeed(300.0f);
		this->addChild(newEnemy, 1);
	}
	return newEnemy;
}

void GameLayer::GameOver() {
	auto toWinScreen = CallFunc::create([=]() {
		Director::getInstance()->replaceScene(WinScreen::scene());
		});
	auto backToMenu = CallFunc::create([=]()
		{
			auto scene = GameMenu::scene();
			Director::getInstance()->replaceScene(scene);
		});

	log("GameOver");
	if (PlayerSprite->getChildByName<Player*>("playerData")->getLife() == 0){
		this->runAction(Sequence::create(DelayTime::create(2.0f), backToMenu, nullptr));
	}
	else { 
		this->runAction(Sequence::create(DelayTime::create(2.0f), toWinScreen, nullptr));
	}
}