#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gameState.h"

class AboutMenu : public GameState
{
public:
	AboutMenu();		//konstruktor
	void handleEvents();
	void logic();
	void render();
private:
	sf::Texture buttonsTexture;
	sf::Font metalLord;		//font do gry
	std::vector<sf::Sprite> interactiveElements;
	unsigned int currentOption;
	sf::Text logoText;
	sf::Text aboutText;
	sf::Texture backgroundTexture;	//tekstura t�a
	sf::Sprite firstBackground;
	sf::Sprite secondBackground;	//t�o wy�wietlam korzystaj�c z dw�ch sprite'�w
};
