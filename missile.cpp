//plik implementuj�cy klas� pocisku
#include <iostream>
#include "missile.h"
#include "constants.h"

//konstruktor
Missile::Missile(sf::Vector2f position, sf::Vector2i size, float speed, sf::Vector2f direction)
{
	//settuje pola klasy
	this->size = size;
	this->speed = speed;
	this->direction = direction;

	//ustawiam pozycj� startow�
	setPosition(position);

	//wczytuj� tekstur� pocisku
	if (!missileTexture.loadFromFile("Graphics/missile.png"))
		std::cout << "missile.png loading failed" << std::endl;
}

//metoda zwracaj�ca rozmiar pocisku
sf::Vector2i Missile::getSize()
{
	return size;
}

//metoda zwracaj�ca szybko�� pocisku(pociski mog� mie� r��n� pr�dko�c)
float Missile::getSpeed()
{
	return speed;
}

//metoda aktualizuj�ca pozycj� pocisku
bool Missile::update()
{
	//przesuwam pocisk
	move(sf::Vector2f(MISSILE_SPEED * direction.x, MISSILE_SPEED * direction.y));

	//sprawdzam czy pocisk wylecia� za map�
	if (getPosition().y < -MISSILE_SIZE.y || getPosition().y >= SCREEN_HEIGHT)
	{
		return false;
	}
	//je�li pocisk znajduje si� na mapie to zwracam true
	return true;
}