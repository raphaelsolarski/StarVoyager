#include <iostream>
#include "collidable.h"

bool Collidable::checkCollision(Collidable *obj)
{
	//sprawdzam czy dosz�o do kolizji -- d�ugi warunek
	if (getPosition().x <= obj->getPosition().x + obj->getSize().x &&
		getPosition().x + getSize().x >= obj->getPosition().x &&
		getPosition().y <= obj->getPosition().y + obj->getSize().y &&
		getPosition().y + getSize().y >= obj->getPosition().y)
	{
		//dosz�o do kolizji
		std::cout << "Collision" << std::endl;
		return true;
	}
	else
	{
		//nie dosz�o do kolizji
		return false;
	}
}