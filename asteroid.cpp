//plik implementuj¹cy klasê asteroidy
#include <iostream>
#include "asteroid.h"
#include "constants.h"

//konstruktor
Asteroid::Asteroid(sf::Vector2f position)
{
	//ustawiam pocz¹tkow¹ klatkê animacji
	//animationFrameCounter = 0;
	//animationCounter = 0;

	//ustawiam pozycjê startow¹
	setPosition(position);

	//settujê pola klasy
	this->size = ASTEROID_SIZE;
}

//przemieszczenie asteroidy, zwraca false, gdy asteroida poza map¹
bool Asteroid::update()
{
	/*//ustawiam klatkê animacji
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

	//przemieszcza ska³kê w dó³
	move(sf::Vector2f(0, ASTEROID_SPEED));

	//sprawdzam czy asteroida opuœci³a mapê
	if (getPosition().y >= SCREEN_HEIGHT)
	{
		return false;
	}

	//asteroida wci¹¿ jest na mapie wiêc zwracam true
	return true;
}

//getter do pola size
sf::Vector2i Asteroid::getSize()
{
	return size;
}