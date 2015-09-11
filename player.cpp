//plik implementuj�cy klas� gracza
#include <iostream>
#include "player.h"
#include "constants.h"

Player::Player()
{
	//wczytanie tektury statku gracza
	if (!playerTexture.loadFromFile("Graphics/player.png"))
		std::cout << "loading player.png failed" << std::endl;
	
	//ustawienie graczowi tekstury
	setTexture(playerTexture);

	//zeruj� cooldown
	fireCooldown = 0;

	//ustawiam 3 �ycia
	lives = 3;

	//ustawiam rozmiar statku
	size = sf::Vector2i(PLAYER_SIZE_X, PLAYER_SIZE_Y);
}

//funkcja strza�u(zwraca stworzony pocisk)
Missile Player::fire()
{
	//zwi�kszam cooldown
	fireCooldown = PLAYER_COOLDOWN;

	//tworz� obiekt pocisku i zwracam go caller'owi
	return Missile(sf::Vector2f(getPosition().x + 16, getPosition().y), MISSILE_SIZE, MISSILE_SPEED, sf::Vector2f(0, -1.0f));
}

//funkcja wywo�ywana co klat� w celu zmniejszenia cooldownu
void Player::reduceCooldown()
{
	if (fireCooldown > 0)
	{
		fireCooldown--;
	}
}

//getter do pola fireCooldown(potrzebny aby klasa game wiedzia�a kiedy mo�na zaakceptowa� strza�
int Player::getFireCooldown()
{
	return fireCooldown;
}

//getter do pola size
sf::Vector2i Player::getSize()
{
	return size;
}

//zwraca liczb� �y�
unsigned int Player::getLives()
{
	return lives;
}

//zaraz kopniesz w kalendarz - jedno �ycie mniej
void Player::oneLiveLess()
{
	if (lives > 0)
	{
		lives--;
	}
}