#include <iostream>
#include "pauseMenu.h"

//konstruktor
PauseMenu::PauseMenu()
{
	//ustawienie domyœlnej opcji
	currentOption = 0;

	//wczytanie tekstur
	if (!buttonsTexture.loadFromFile("Graphics/pauseMenuButtons.png"))
		std::cout << "pauseMenuButtons.png loading failed" << std::endl;

	//wczytujê font
	if (!metalLord.loadFromFile("metalLord.ttf"))
		std::cout << "metalLord.ttf loading failed" << std::endl;

	//t³o
	if (!backgroundTexture.loadFromFile("Graphics/background.png"))
		std::cout << "background.png loading failed" << std::endl;

	//przygotowujê mapê
	firstBackground.setTexture(backgroundTexture);
	firstBackground.setPosition(firstBackgroundPosition);

	secondBackground.setTexture(backgroundTexture);
	secondBackground.setPosition(secondBackgroundPosition);

	//przygotowujê logo text
	logoText.setFont(metalLord);
	logoText.setCharacterSize(75);
	logoText.setPosition(sf::Vector2f(90, 50));
	logoText.setString(sf::String("star voyager"));

	//przycisk "RESTUME"
	sf::Sprite restumeButton;
	restumeButton.setTexture(buttonsTexture);
	restumeButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(103, 27)));
	restumeButton.setPosition(sf::Vector2f(269, 200));
	interactiveElements.push_back(restumeButton);

	//przycisk "MAIN MENU"
	sf::Sprite scoresButton;
	scoresButton.setTexture(buttonsTexture);
	scoresButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 27), sf::Vector2i(124, 27)));
	scoresButton.setPosition(sf::Vector2f(269, 227));
	interactiveElements.push_back(scoresButton);

	//przycisk "EXIT"
	sf::Sprite exitButton;
	exitButton.setTexture(buttonsTexture);
	exitButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 54), sf::Vector2i(71, 27)));
	exitButton.setPosition(sf::Vector2f(269, 254));
	interactiveElements.push_back(exitButton);
}

void PauseMenu::handleEvents()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Down)
			{
				if (currentOption < 2)
				{
					currentOption++;
				}
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				if (currentOption > 0)
				{
					currentOption--;
				}
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				switch (currentOption)
				{
				case 0:
					setNextState(GAME_STATE_RESTUME);
					break;

				case 1:
					setNextState(GAME_STATE_MAIN_MENU);
					break;

				case 2:
					setNextState(GAME_STATE_EXIT);
					break;
				}
			}
		}
	}
}

void PauseMenu::logic()
{
	//sprawdzam czy okno nie zosta³o zamkniête
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}

	//aktualizujê tekstury przycisków
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		if (i == currentOption)
		{
			//to jest aktywny przycisk
			interactiveElements[i].setColor(sf::Color(255, 255, 255));
		}
		else
		{
			//to nie jest aktywny przycisk
			interactiveElements[i].setColor(sf::Color(96, 96, 96));
		}
	}

	//przesuwam mapê w dó³
	if (secondBackgroundPosition.y == 0)
		firstBackgroundPosition.y = -1600.0;

	if (firstBackgroundPosition.y == 0)
		secondBackgroundPosition.y = -1600.0;

	firstBackground.setPosition(firstBackgroundPosition);
	firstBackgroundPosition.y = firstBackgroundPosition.y + 1.0f;
	secondBackground.setPosition(secondBackgroundPosition);
	secondBackgroundPosition.y = secondBackgroundPosition.y + 1.0f;
}

void PauseMenu::render()
{
	//rysuje przyciski
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysujê logo text
	window->draw(logoText);

	window->display();
	window->clear();
}