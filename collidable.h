#pragma once
#include <SFML/Graphics.hpp>

class Collidable : public sf::Sprite
{
public:
	virtual sf::Vector2i getSize() = 0;
	bool checkCollision(Collidable* obj);	//metoda sprawdzaj¹ca czy dosz³o do kolizji ze wskazanym obiektem
};
