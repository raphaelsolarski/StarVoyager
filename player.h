//plik nag��wkowy klasy gracza
#pragma once
#include <SFML/Graphics.hpp>
#include "collidable.h"
#include "missile.h"

class Player : public Collidable
{
public:
	Player();	//konstruktor
	//~Player();	//destruktor
	Missile fire();	//funkcja strza�u(zwraca stworzony pocisk)
	void reduceCooldown();	//funkcja wywo�ywana co klat� w celu zmniejszenia cooldownu
	int getFireCooldown();	//getter do pola fireCooldown(potrzebny aby klasa game wiedzia�a kiedy mo�na zaakceptowa� strza�)
	sf::Vector2i getSize();		//getter do size;
	unsigned int getLives();	//zwraca liczb� �y�
	void oneLiveLess();			//zaraz kopniesz w kalendarz - jedno �ycie mniej
private:
	unsigned int lives;			//liczba �y� gracza
	sf::Texture playerTexture;	//tekstura statku gracza
	sf::Vector2i size;			//rozmiar statku
	int fireCooldown;			//cooldown strza�u
};