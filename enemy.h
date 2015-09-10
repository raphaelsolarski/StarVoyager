//plik nag³ówkowy klasy przeciwnika
#pragma once
#include "collidable.h"
#include "missile.h"

class Enemy : public Collidable
{
public:
	Enemy(sf::Vector2f position);	//konstruktor
	sf::Vector2i getSize();		//getter do pola size
	bool update();		//update pozycji przeciwnika, zwraca false, gdy przeciwnik wylecia³ poza mapê
	Missile fire();		//strza³ przeciwnika, zwraca obiekt pocisku
	int getFireCooldown();	//getter do pola fireCooldown
	void reduceCooldown();	//metoda, której wywo³anie zmniejsza cooldown o jedn¹ klatkê
private:
	int fireCooldown;	//czas ch³odzenia po strzale
	sf::Vector2i size;	//rozmiar sprite'a
};