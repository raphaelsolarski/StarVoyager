//plik implementuj�cy klas� przeciwnika
#include <iostream>
#include "enemy.h"
#include "constants.h"

//konstruktor
Enemy::Enemy(sf::Vector2f position)
{
	//ustawiam pozycj� startow�
	setPosition(position);

	//ustawiam pole size
	size = ENEMY_SIZE;

	//zeruj� cooldown
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
	//przesuwam przeciwnika w d�
	move(sf::Vector2f(0, ENEMY_SPEED));

	//sprawdzam czy przeciwnik op�ci� map�
	if (getPosition().y >= SCREEN_HEIGHT)
	{	//op�ci�
		return false;
	}

	//nie op�ci�
	return true;
}

//strza� przeciwnika, zwraca obiekt pocisku
Missile Enemy::fire()
{
	//zwi�kszam cooldown
	fireCooldown = ENEMY_COOLDOWN;

	//tworz� obiekt pocisku i zwracam go caller'owi
	return Missile(sf::Vector2f(getPosition().x + 20, getPosition().y + 36), MISSILE_SIZE, MISSILE_SPEED, sf::Vector2f(0, 1.0f));
}

//getter do pola fireCooldown
int Enemy::getFireCooldown()
{
	return fireCooldown;
}

//metoda, kt�rej wywo�anie zmniejsza cooldown o jedn� klatk�
void Enemy::reduceCooldown()
{
	if (fireCooldown > 0)
	{
		fireCooldown--;
	}
}