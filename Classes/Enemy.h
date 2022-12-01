#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Enemy : public Sprite {
private:
	int randomMovementIteration;
	int type;
	int life;
	float speed;
public:
	virtual bool init();
	Enemy();
	~Enemy();
	void takeDmg(int damage);


	int getLife();
	int getType();
	float getSpeed();
	void setLife(int lifeToSet);
	void setType(int EnemyType);
	void setSpeed(float speedToSet);
	CREATE_FUNC(Enemy);
};