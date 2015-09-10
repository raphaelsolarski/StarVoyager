//plik spinaj¹cy wszystkie sta³e wykorzystywane w grze
#pragma once
#include <SFML/Graphics.hpp>

//wymiary okna
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//docelowa liczba klatek na sekundê
const int FRAMES_PER_SECOND = 60;

//player
const int PLAYER_SIZE_X = 41;
const int PLAYER_SIZE_Y = 47;
const float PLAYER_SPEED = 7.0f;
const int PLAYER_COOLDOWN = 30;		//parametr okreœlaj¹cy co ile klatek mo¿e zostaæ oddany strza³

//enemy
const float ENEMY_SPEED = 4.0f;	//prêdkoœæ z jak¹ przeciwnicy lec¹.
const sf::Vector2i ENEMY_SIZE = sf::Vector2i(43, 36);
const int ENEMY_COOLDOWN = 30;		//parametr okreœlaj¹cy co ile klatek mo¿e zostaæ oddany strza³

//asteroid
const float ASTEROID_SPEED = 4.0f;	//prêdkoœæ asteroid(na klatkê).
const sf::Vector2i ASTEROID_SIZE = sf::Vector2i(48, 48);

//missile
const float MISSILE_SPEED = 7.0f;	//prêdkoœæ lotu pocisków
const sf::Vector2i MISSILE_SIZE = sf::Vector2i(3, 32);	//rozmiar przycisków

//scores
const int SCORES_PER_ASTEROID = 25;	//ile punktów siê otrzymuje za zniszczenie asteroidy
const int SCORES_PER_ENEMY = 50;		//ile punktów siê otrzymuje za znisczenie przeciwnika
