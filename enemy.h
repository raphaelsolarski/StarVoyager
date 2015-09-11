//plik nag��wkowy klasy przeciwnika
#pragma once
#include "collidable.h"
#include "missile.h"

class Enemy : public Collidable
{
public:
	Enemy(sf::Vector2f position);	//konstruktor
	sf::Vector2i getSize();		//getter do pola size
	bool update();		//update pozycji przeciwnika, zwraca false, gdy przeciwnik wylecia� poza map�
	Missile fire();		//strza� przeciwnika, zwraca obiekt pocisku
	int getFireCooldown();	//getter do pola fireCooldown
	void reduceCooldown();	//metoda, kt�rej wywo�anie zmniejsza cooldown o jedn� klatk�
private:
	int fireCooldown;	//czas ch�odzenia po strzale
	sf::Vector2i size;	//rozmiar sprite'a
};