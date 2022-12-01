#include "Enemy.h"

bool Enemy::init() {
	randomMovementIteration = 0;
	type = 0;
	life = 0;
	speed = 0.0f;
	return true;
}

Enemy::Enemy() {}
Enemy::~Enemy() {}
void Enemy::takeDmg(int damage) {life -= damage;}
void Enemy::setLife(int x) { life = x; }
void Enemy::setType(int EnemyType) { type = EnemyType; }
void Enemy::setSpeed(float speedToSet) { speed = speedToSet; }
int Enemy::getLife() {return life;}
int Enemy::getType() { return type; }

float Enemy::getSpeed()
{
	return speed;
}
