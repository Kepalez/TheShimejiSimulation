#pragma once

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Player : public Sprite {
private:
	int life;
	float speed;
	float playerX;
	float playerY;
public:
	virtual bool init();
	Player();
	~Player();
	void setSpeed(float speedToSet);
	void setLife(int lifeToSet);
	void takeDmg();
	void heal();

	float getSpeed();
	int getLife();

	CREATE_FUNC(Player);
};