//plik implementuj�cy klas� asteroidy
#include <iostream>
#include "asteroid.h"
#include "constants.h"

//konstruktor
Asteroid::Asteroid(sf::Vector2f position)
{
	//ustawiam pocz�tkow� klatk� animacji
	//animationFrameCounter = 0;
	//animationCounter = 0;

	//ustawiam pozycj� startow�
	setPosition(position);

	//settuj� pola klasy
	this->size = ASTEROID_SIZE;
}

//przemieszczenie asteroidy, zwraca false, gdy asteroida poza map�
bool Asteroid::update()
{
	/*//ustawiam klatk� animacji
	if (animationFrameCounter == 2)
	{
		animationCounter = (animationCounter + 1) % 16;
		setTextureRect(sf::IntRect(sf::Vector2i(0, 64 * animationCounter), sf::Vector2i(64, 64)));
		animationFrameCounter = 0;
	}
	else
	{
		animationFrameCounter++;
	}*/

	//przemieszcza ska�k� w d��
	move(sf::Vector2f(0, ASTEROID_SPEED));

	//sprawdzam czy asteroida opu�ci�a map�
	if (getPosition().y >= SCREEN_HEIGHT)
	{
		return false;
	}

	//asteroida wci�� jest na mapie wi�c zwracam true
	return true;
}

//getter do pola size
sf::Vector2i Asteroid::getSize()
{
	return size;
}