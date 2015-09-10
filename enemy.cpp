//plik implementuj¹cy klasê przeciwnika
#include <iostream>
#include "enemy.h"
#include "constants.h"

//konstruktor
Enemy::Enemy(sf::Vector2f position)
{
	//ustawiam pozycjê startow¹
	setPosition(position);

	//ustawiam pole size
	size = ENEMY_SIZE;

	//zerujê cooldown
	fireCooldown = 0;
}

//getter do pola size
sf::Vector2i Enemy::getSize()
{
	return size;
}

//update pozycji przeciwnika
bool Enemy::update()
{
	//przesuwam przeciwnika w dó³
	move(sf::Vector2f(0, ENEMY_SPEED));

	//sprawdzam czy przeciwnik opóœci³ mapê
	if (getPosition().y >= SCREEN_HEIGHT)
	{	//opóœci³
		return false;
	}

	//nie opóœci³
	return true;
}

//strza³ przeciwnika, zwraca obiekt pocisku
Missile Enemy::fire()
{
	//zwiêkszam cooldown
	fireCooldown = ENEMY_COOLDOWN;

	//tworzê obiekt pocisku i zwracam go caller'owi
	return Missile(sf::Vector2f(getPosition().x + 20, getPosition().y + 36), MISSILE_SIZE, MISSILE_SPEED, sf::Vector2f(0, 1.0f));
}

//getter do pola fireCooldown
int Enemy::getFireCooldown()
{
	return fireCooldown;
}

//metoda, której wywo³anie zmniejsza cooldown o jedn¹ klatkê
void Enemy::reduceCooldown()
{
	if (fireCooldown > 0)
	{
		fireCooldown--;
	}
}