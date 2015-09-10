#include <iostream>
#include "mainMenu.h"

//konstruktor
MainMenu::MainMenu()
{
	//wczytujê tekstury przycisków
	if (!buttonsTexture.loadFromFile("Graphics/mainMenuButtons.png"))
		std::cout << "mainMenuButtons.png loading failed" << std::endl;

	//wczytujê font
	if (!metalLord.loadFromFile("metalLord.ttf"))
		std::cout << "metalLord.ttf loading failed" << std::endl;

	//przygotowujê logo text
	logoText.setFont(metalLord);
	logoText.setCharacterSize(75);
	logoText.setPosition(sf::Vector2f(90, 50));
	logoText.setString(sf::String("star voyager"));

	//t³o
	if (!backgroundTexture.loadFromFile("Graphics/background.png"))
		std::cout << "background.png loading failed" << std::endl;

	//przygotowujê mapê
	firstBackground.setTexture(backgroundTexture);
	firstBackground.setPosition(firstBackgroundPosition);

	secondBackground.setTexture(backgroundTexture);
	secondBackground.setPosition(secondBackgroundPosition);

	//domyœlnie wybrana jest opcja na samej górze menu
	currentOption = 0;

	//przycisk nowej gry
	sf::Sprite newGameButton;
	newGameButton.setTexture(buttonsTexture);
	newGameButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(151, 27)));
	newGameButton.setPosition(sf::Vector2f(245, 200));
	interactiveElements.push_back(newGameButton);

	//przycisk "SCORES"
	sf::Sprite scoresButton;
	scoresButton.setTexture(buttonsTexture);
	scoresButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 27), sf::Vector2i(108, 27)));
	scoresButton.setPosition(sf::Vector2f(245, 227));
	interactiveElements.push_back(scoresButton);

	//przycisk "ABOUT"
	sf::Sprite aboutButton;
	aboutButton.setTexture(buttonsTexture);
	aboutButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 54), sf::Vector2i(97, 27)));
	aboutButton.setPosition(sf::Vector2f(245, 254));
	interactiveElements.push_back(aboutButton);

	//przycisk "EXIT"
	sf::Sprite exitButton;
	exitButton.setTexture(buttonsTexture);
	exitButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 81), sf::Vector2i(71, 27)));
	exitButton.setPosition(sf::Vector2f(245, 281));
	interactiveElements.push_back(exitButton);
}

void MainMenu::handleEvents()
{
	sf::Event event;
	
	while (window->pollEvent(event))
	{
		//zamkniêto okno
		if (event.type == sf::Event::Closed)
			window->close();

		//klawiatura
		else if (event.type == sf::Event::KeyPressed)
		{
			//strza³ka w dó³
			if (event.key.code == sf::Keyboard::Down)
			{
				if (currentOption < 3)
					currentOption++;
			}
			//strza³ka w górê
			else if (event.key.code == sf::Keyboard::Up)
			{
				if (currentOption > 0)
					currentOption--;
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				switch (currentOption)
				{
				case 0:
					nextLevel = 0;
					setNextState(GAME_STATE_GAME);
					break;
					
				case 1:
					setNextState(GAME_STATE_SCORES_MENU);
					break;

				case 2:
					setNextState(GAME_STATE_ABOUT_MENU);
					break;

				case 3:
					setNextState(GAME_STATE_EXIT);
					break;
				}
			}
		}
	}
}

void MainMenu::logic()
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

void MainMenu::render()
{
	//rysujê t³o
	window->draw(firstBackground);
	window->draw(secondBackground);

	//rysujê przyciski
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysujê logo text
	window->draw(logoText);

	window->display();
	window->clear();
}