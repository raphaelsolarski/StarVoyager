#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gameState.h"

class MainMenu : public GameState
{
public:
	MainMenu();		//konstruktor
	void handleEvents();
	void logic();
	void render();
private:
	sf::Texture buttonsTexture;
	sf::Font metalLord;		//font do gry
	std::vector<sf::Sprite> interactiveElements;
	int currentOption;
	sf::Text logoText;
	sf::Texture backgroundTexture;	//tekstura t�a
	sf::Sprite firstBackground;
	sf::Sprite secondBackground;	//t�o wy�wietlam korzystaj�c z dw�ch sprite'�w
};
