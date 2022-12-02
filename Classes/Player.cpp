#include "Player.h"

bool Player::init() {
	speed = 330.f;
	life = 5;
	return true;
}

Player::Player() {

}

Player::~Player() {

}

void Player::setSpeed(float speedToSet) {
	speed = speedToSet;
}

void Player::setLife(int lifeToSet)
{
	life = lifeToSet;
}

void Player::takeDmg()
{
	life--;
}

void Player::heal() {
	if(life<10) life++;
}

float Player::getSpeed() {
	return speed;
}

int Player::getLife()
{
	return life;
}
