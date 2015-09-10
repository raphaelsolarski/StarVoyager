//plik nag³ówkowy klasy pocisku
#pragma once
#include <SFML/Graphics.hpp>
#include "collidable.h"
#include "constants.h"

class Missile : public Collidable
{
public:
	Missile(sf::Vector2f position, sf::Vector2i size, float speed, sf::Vector2f direction);	//konstruktor
	sf::Vector2i getSize();	//metoda zwracaj¹ca rozmiar pocisku
	float getSpeed();		//metoda zwracaj¹ca szybkoœæ pocisku(pociski mog¹ mieæ ró¿n¹ prêdkoœc)
	bool update();			//metoda aktualizuj¹ca pozycjê pocisku i zwracaj¹ca false w przypadku gdy pocisk wylecia³ za mapê
private:
	sf::Vector2i size;	//rozmiar pocisku
	float speed;		//prêdkoœæ pocisku
	sf::Vector2f direction;	//kierunek lotu pocisku
	sf::Texture missileTexture;	//tekstura pocisku
};
