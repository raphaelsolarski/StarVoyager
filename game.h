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
	std::vector<Missile> enemyMissiles;	//vektor zawieraj¹cy wszystkie pociski przeciwników na mapie
	std::vector<Missile> playerMissiles;//vektor zawieraj¹cy wszystkie pociski gracza na mapie
	std::vector<Enemy> enemies;		//vektor zawieraj¹cy wszystkich przeciwników na mapie
	std::vector<Asteroid> asteroids;	//vektor zawieraj¹cy wszystkie asteroidy na mapie
	sf::Texture backgroundTexture;	//tekstura t³a
	sf::Sprite firstBackground;
	sf::Sprite secondBackground;	//t³o wyœwietlam korzystaj¹c z dwóch sprite'ów
	sf::Font scoresFont;			//font potrzebny do wyœwietlania liczby punktów
	sf::Text scoresText;			//tekst "SCORES: 1234"
	unsigned int scores;	//punkty

	//modu³ wczytywania mapy
	unsigned long rowsInMap;	//pole okreœlaj¹ca z ilu wierszy sk³ada siê gra(gdy zostanie osi¹gniêty ostatni to gra siê koñczy)
	void loadRow();			//funkcja wczytuj¹ca kolejny wiersz
	std::ifstream mapFile;	//obiekt strumienia s³u¿¹cy do wczytywania danych z pliku mapy
	unsigned long currentRow;	//licznik wierszy(do modu³u wczytuj¹cego przeciwników i asteroidy)
	unsigned long nextRowInFile;	//zmienna zawieraj¹ca numer wiersza na jakim siê zatrzyma³ parser
	int framesBetweenRowsCounter;	//licznik licz¹cy ile minê³o klatek od ostatniego wczytania wiersza
};
