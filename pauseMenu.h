#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gameState.h"

class PauseMenu : public GameState
{
public:
	PauseMenu();		//konstruktor
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
	sf::Sprite secondBackground;	//t³o wyœwietlam korzystaj¹c z dwóch sprite'ów
};
