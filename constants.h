//plik spinaj�cy wszystkie sta�e wykorzystywane w grze
#pragma once
#include <SFML/Graphics.hpp>

//wymiary okna
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//docelowa liczba klatek na sekund�
const int FRAMES_PER_SECOND = 60;

//player
const int PLAYER_SIZE_X = 41;
const int PLAYER_SIZE_Y = 47;
const float PLAYER_SPEED = 7.0f;
const int PLAYER_COOLDOWN = 30;		//parametr okre�laj�cy co ile klatek mo�e zosta� oddany strza�

//enemy
const float ENEMY_SPEED = 4.0f;	//pr�dko�� z jak� przeciwnicy lec�.
const sf::Vector2i ENEMY_SIZE = sf::Vector2i(43, 36);
const int ENEMY_COOLDOWN = 30;		//parametr okre�laj�cy co ile klatek mo�e zosta� oddany strza�

//asteroid
const float ASTEROID_SPEED = 4.0f;	//pr�dko�� asteroid(na klatk�).
const sf::Vector2i ASTEROID_SIZE = sf::Vector2i(48, 48);

//missile
const float MISSILE_SPEED = 7.0f;	//pr�dko�� lotu pocisk�w
const sf::Vector2i MISSILE_SIZE = sf::Vector2i(3, 32);	//rozmiar przycisk�w

//scores
const int SCORES_PER_ASTEROID = 25;	//ile punkt�w si� otrzymuje za zniszczenie asteroidy
const int SCORES_PER_ENEMY = 50;		//ile punkt�w si� otrzymuje za znisczenie przeciwnika