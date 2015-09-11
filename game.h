#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "player.h"
#include "missile.h"
#include "enemy.h"
#include "asteroid.h"
#include "collidable.h"

class Game : public GameState
{
public:
	Game();		//konstruktor
	void handleEvents();
	void logic();
	void render();

private:
	Player player;
	sf::Texture asteroidTexture;	//teksturka asteroidy
	sf::Texture enemyTexture;		//teksturka przeciwnika
	sf::Texture missileTexture;		//tekstura pocisku
	sf::Texture heartTexture;		//tekstura serduszka
	sf::Sprite* livesSprites;		//sprite serduszek
	std::vector<Missile> enemyMissiles;	//vektor zawieraj�cy wszystkie pociski przeciwnik�w na mapie
	std::vector<Missile> playerMissiles;//vektor zawieraj�cy wszystkie pociski gracza na mapie
	std::vector<Enemy> enemies;		//vektor zawieraj�cy wszystkich przeciwnik�w na mapie
	std::vector<Asteroid> asteroids;	//vektor zawieraj�cy wszystkie asteroidy na mapie
	sf::Texture backgroundTexture;	//tekstura t�a
	sf::Sprite firstBackground;
	sf::Sprite secondBackground;	//t�o wy�wietlam korzystaj�c z dw�ch sprite'�w
	sf::Font scoresFont;			//font potrzebny do wy�wietlania liczby punkt�w
	sf::Text scoresText;			//tekst "SCORES: 1234"
	unsigned int scores;	//punkty

	//modu� wczytywania mapy
	unsigned long rowsInMap;	//pole okre�laj�ca z ilu wierszy sk�ada si� gra(gdy zostanie osi�gni�ty ostatni to gra si� ko�czy)
	void loadRow();			//funkcja wczytuj�ca kolejny wiersz
	std::ifstream mapFile;	//obiekt strumienia s�u��cy do wczytywania danych z pliku mapy
	unsigned long currentRow;	//licznik wierszy(do modu�u wczytuj�cego przeciwnik�w i asteroidy)
	unsigned long nextRowInFile;	//zmienna zawieraj�ca numer wiersza na jakim si� zatrzyma� parser
	int framesBetweenRowsCounter;	//licznik licz�cy ile min��o klatek od ostatniego wczytania wiersza
};