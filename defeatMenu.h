#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gameState.h"

class DefeatMenu : public GameState
{
public:
	DefeatMenu();		//konstruktor
	void handleEvents();
	void logic();
	void render();
private:
	sf::Texture buttonsTexture;
	sf::Font metalLord;		//font do gry
	std::vector<sf::Sprite> interactiveElements;
	unsigned int currentOption;
	sf::Text logoText;
	sf::Texture backgroundTexture;
	sf::Sprite firstBackground;
	sf::Sprite secondBackground;	//t�o wy�wietlam korzystaj�c z dw�ch sprite'�w
};