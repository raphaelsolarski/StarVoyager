#include <iostream>
#include "levelFinishedMenu.h"

//konstruktor
LevelFinishedMenu::LevelFinishedMenu()
{
	//ustawienie domy�lnej opcji
	currentOption = 0;

	//wczytanie tekstur
	if (!buttonsTexture.loadFromFile("Graphics/levelFinishedMenuButtons.png"))
		std::cout << "levelFinishedMenuButtons.png loading failed" << std::endl;

	//wczytuj� font
	if (!metalLord.loadFromFile("metalLord.ttf"))
		std::cout << "metalLord.ttf loading failed" << std::endl;

	//t�o
	if (!backgroundTexture.loadFromFile("Graphics/background.png"))
		std::cout << "background.png loading failed" << std::endl;

	//przygotowuj� map�
	firstBackground.setTexture(backgroundTexture);
	firstBackground.setPosition(firstBackgroundPosition);

	secondBackground.setTexture(backgroundTexture);
	secondBackground.setPosition(secondBackgroundPosition);

	//przygotowuj� logo text
	logoText.setFont(metalLord);
	logoText.setCharacterSize(75);
	logoText.setPosition(sf::Vector2f(90, 50));
	logoText.setString(sf::String("star voyager"));

	//przycisk "NEXT"
	sf::Sprite nextButton;
	nextButton.setTexture(buttonsTexture);
	nextButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(63, 27)));
	nextButton.setPosition(sf::Vector2f(269, 200));
	interactiveElements.push_back(nextButton);

	//przycisk "MAIN MENU"
	sf::Sprite mainMenuButton;
	mainMenuButton.setTexture(buttonsTexture);
	mainMenuButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 27), sf::Vector2i(124, 27)));
	mainMenuButton.setPosition(sf::Vector2f(269, 227));
	interactiveElements.push_back(mainMenuButton);

	//przycisk "EXIT"
	sf::Sprite exitButton;
	exitButton.setTexture(buttonsTexture);
	exitButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 54), sf::Vector2i(71, 27)));
	exitButton.setPosition(sf::Vector2f(269, 254));
	interactiveElements.push_back(exitButton);
}

void LevelFinishedMenu::handleEvents()
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
				case 0:		//NEXT
					nextLevel++;
					setNextState(GAME_STATE_GAME);
					break;

				case 1:		//MAIN MENU
					setNextState(GAME_STATE_MAIN_MENU);
					break;

				case 2:		//EXIT
					setNextState(GAME_STATE_EXIT);
					break;
				}
			}
		}
	}
}

void LevelFinishedMenu::logic()
{
	//sprawdzam czy okno nie zosta�o zamkni�te
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}

	//aktualizuj� tekstury przycisk�w
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

	//przesuwam map� w d��
	if (secondBackgroundPosition.y == 0)
		firstBackgroundPosition.y = -1600.0;

	if (firstBackgroundPosition.y == 0)
		secondBackgroundPosition.y = -1600.0;

	firstBackground.setPosition(firstBackgroundPosition);
	firstBackgroundPosition.y = firstBackgroundPosition.y + 1.0f;
	secondBackground.setPosition(secondBackgroundPosition);
	secondBackgroundPosition.y = secondBackgroundPosition.y + 1.0f;
}

void LevelFinishedMenu::render()
{
	//rysuj� t�o
	window->draw(firstBackground);
	window->draw(secondBackground);

	//rysuje przyciski
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysuj� logo text
	window->draw(logoText);

	window->display();
	window->clear();
}