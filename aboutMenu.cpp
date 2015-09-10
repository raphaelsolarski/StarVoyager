#include <iostream>
#include "aboutMenu.h"

//konstruktor
AboutMenu::AboutMenu()
{
	//wczytujê tekstury przycisków
	if (!buttonsTexture.loadFromFile("Graphics/aboutMenuButtons.png"))
		std::cout << "aboutMenuButtons.png loading failed" << std::endl;

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

	//przygotowujê about text
	aboutText.setFont(metalLord);
	aboutText.setCharacterSize(25);
	aboutText.setPosition(sf::Vector2f(180, 200));
	aboutText.setString(sf::String("This game was developed \n     by Raphael solarski \nsolarski.rafal@gmail.com"));
	
	//domyœlnie wybrana jest opcja na samej górze menu
	currentOption = 0;

	//przycisk "BACK"
	sf::Sprite backButton;
	backButton.setTexture(buttonsTexture);
	backButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(63, 27)));
	backButton.setPosition(sf::Vector2f(289, 330));
	interactiveElements.push_back(backButton);

}

void AboutMenu::handleEvents()
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
				if (currentOption < 0)
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
					setNextState(GAME_STATE_MAIN_MENU);
					break;
				}
			}
		}
	}
}

void AboutMenu::logic()
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

void AboutMenu::render()
{
	//rysujê t³o
	window->draw(firstBackground);
	window->draw(secondBackground);

	//rysujê przyciski
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysujê tekst o twórcy
	window->draw(aboutText);

	//rysujê logo text
	window->draw(logoText);

	window->display();
	window->clear();
}