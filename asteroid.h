//plik nag��wkowy klasy asteroidy
#pragma once
#include <SFML/Graphics.hpp>
#include "collidable.h"

class Asteroid : public Collidable
{
public:
	Asteroid(sf::Vector2f position);	//konstruktor
	sf::Vector2i getSize();	//metoda zwracaj�ca rozmiar asteroidy
	bool update();			//przemieszczenie asteroidy, zwraca false, gdy asteroida poza map�
private:
	sf::Vector2i size;				//rozmiar asteroidy
	//int animationFrameCounter;			//counter potrzebny do animacji asteroidy
	//int animationCounter;			//counter potrzebny do animacji asteroidy
};