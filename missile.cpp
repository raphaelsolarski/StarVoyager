//plik implementuj¹cy klasê pocisku
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

	//ustawiam pozycjê startow¹
	setPosition(position);

	//wczytujê teksturê pocisku
	if (!missileTexture.loadFromFile("Graphics/missile.png"))
		std::cout << "missile.png loading failed" << std::endl;
}

//metoda zwracaj¹ca rozmiar pocisku
sf::Vector2i Missile::getSize()
{
	return size;
}

//metoda zwracaj¹ca szybkoœæ pocisku(pociski mog¹ mieæ ró¿n¹ prêdkoœc)
float Missile::getSpeed()
{
	return speed;
}

//metoda aktualizuj¹ca pozycjê pocisku
bool Missile::update()
{
	//przesuwam pocisk
	move(sf::Vector2f(MISSILE_SPEED * direction.x, MISSILE_SPEED * direction.y));

	//sprawdzam czy pocisk wylecia³ za mapê
	if (getPosition().y < -MISSILE_SIZE.y || getPosition().y >= SCREEN_HEIGHT)
	{
		return false;
	}
	//jeœli pocisk znajduje siê na mapie to zwracam true
	return true;
}