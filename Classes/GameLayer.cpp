#include "GameLayer.h"

using namespace cocos2d;
//Cat.Bitmasks Player:1, PlayerBullet:2, Enemy:4, EnemyBullet: 8, kamikaze: 16 
//window size 520, 760

float PlayerXDir = 0.0f, PlayerYDir = 0.0f, PlayerXMov = 0.0f, PlayerYMov = 0.0f;
bool gameOver = false;
Sprite* PlayerSprite;
Sprite* lifeUI;
float playerCollisionWidth = 28,playerCollisionHeight = 80;

Scene* GameLayer::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(true);
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
		auto bala = Sprite::create("../Resources/Image/CornBullet.png");
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
Scene* GameLayer::scene() {
	auto scene = Scene::create();
	scene->addChild(GameLayer::create());
	return scene;
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
bool GameLayer::onContactBegin(PhysicsContact& contact) {
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	auto acol = a->getCategoryBitmask();
	auto bcol = b->getCategoryBitmask();
	//bullet to enenmy
	if ((acol == 4  && bcol == 2) ||( acol == 2 && bcol == 4 )) {
		if (acol == 2) {
			if (a->getOwner() != nullptr) {
				a->getOwner()->removeFromParentAndCleanup(true);
				if (b->getOwner() != nullptr) {
					b->getOwner()->getChildByName<Enemy*>("enemyData")->takeDmg(5);
					if (b->getOwner()->getChildByName<Enemy*>("enemyData")->getLife() <= 0) {
						b->getOwner()->removeFromParentAndCleanup(true);
					}
				}
			}
		}
		else {
			if (b->getOwner() != nullptr) {
				b->getOwner()->removeFromParentAndCleanup(true);
				if (a->getOwner() != nullptr) {
					a->getOwner()->getChildByName<Enemy*>("enemyData")->takeDmg(5);
					if (a->getOwner()->getChildByName<Enemy*>("enemyData")->getLife() <= 0) {
						a->getOwner()->removeFromParentAndCleanup(true);
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
						gameOver = true;
						playerDeath();
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
						a->getOwner()->setVisible(false);
						a->setContactTestBitmask(0);
						gameOver = true;
						playerDeath();
					}
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
	PlayerSprite = Sprite::create("../Resources/Image/Majime_Corn.png");
	PlayerSprite->addChild(playerData);
	PlayerSprite->setPosition(Vec2(254.0f, 90.0f));
	PlayerSprite->setScale(1, 0.8f);
	PlayerSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	PlayerSprite->setPhysicsBody(PhysicsBody::createBox(Size(playerCollisionWidth, playerCollisionHeight), PhysicsMaterial(100, 0, 0)));
	PlayerSprite->getPhysicsBody()->setCollisionBitmask(1);
	PlayerSprite->getPhysicsBody()->setCategoryBitmask(1);
	PlayerSprite->getPhysicsBody()->setContactTestBitmask(8);
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
	auto mainSequence = Sequence::create(
		DelayTime::create(3.0f), 
		GoFirstRound,
		DelayTime::create(10.0f),
		GoSecondRound, 
		DelayTime::create(14.0f),
		GoThirdRound,
		DelayTime::create(26.0f),
		GoFourthRound,
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

}

Sprite* GameLayer::createEnemy(int type,Vec2 initialPosition) {
	Sprite* newEnemy;
	auto enemyData = Enemy::create();
	enemyData->setName("enemyData");
	enemyData->setType(type);
	switch (type) {
	case 1: //blueLobster
		newEnemy = Sprite::create("../Resources/Image/BlueLobster.png");
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

void GameLayer::playerDeath() {
	auto scene = GameMenu::scene();
	Director::getInstance()->replaceScene(scene);
}