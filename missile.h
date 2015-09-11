//plik nag��wkowy klasy pocisku
#pragma once
#include <SFML/Graphics.hpp>
#include "collidable.h"
#include "constants.h"

class Missile : public Collidable
{
public:
	Missile(sf::Vector2f position, sf::Vector2i size, float speed, sf::Vector2f direction);	//konstruktor
	sf::Vector2i getSize();	//metoda zwracaj�ca rozmiar pocisku
	float getSpeed();		//metoda zwracaj�ca szybko�� pocisku(pociski mog� mie� r��n� pr�dko�c)
	bool update();			//metoda aktualizuj�ca pozycj� pocisku i zwracaj�ca false w przypadku gdy pocisk wylecia� za map�
private:
	sf::Vector2i size;	//rozmiar pocisku
	float speed;		//pr�dko�� pocisku
	sf::Vector2f direction;	//kierunek lotu pocisku
	sf::Texture missileTexture;	//tekstura pocisku
};