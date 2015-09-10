//plik nag³ówkowy klasy gracza
#pragma once
#include <SFML/Graphics.hpp>
#include "collidable.h"
#include "missile.h"

class Player : public Collidable
{
public:
	Player();	//konstruktor
	//~Player();	//destruktor
	Missile fire();	//funkcja strza³u(zwraca stworzony pocisk)
	void reduceCooldown();	//funkcja wywo³ywana co klatê w celu zmniejszenia cooldownu
	int getFireCooldown();	//getter do pola fireCooldown(potrzebny aby klasa game wiedzia³a kiedy mo¿na zaakceptowaæ strza³)
	sf::Vector2i getSize();		//getter do size;
	unsigned int getLives();	//zwraca liczbê ¿yæ
	void oneLiveLess();			//zaraz kopniesz w kalendarz - jedno ¿ycie mniej
private:
	unsigned int lives;			//liczba ¿yæ gracza
	sf::Texture playerTexture;	//tekstura statku gracza
	sf::Vector2i size;			//rozmiar statku
	int fireCooldown;			//cooldown strza³u
};
