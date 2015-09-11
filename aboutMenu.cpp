#include <iostream>
#include "aboutMenu.h"

//konstruktor
AboutMenu::AboutMenu()
{
	//wczytuj� tekstury przycisk�w
	if (!buttonsTexture.loadFromFile("Graphics/aboutMenuButtons.png"))
		std::cout << "aboutMenuButtons.png loading failed" << std::endl;

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

	//przygotowuj� about text
	aboutText.setFont(metalLord);
	aboutText.setCharacterSize(25);
	aboutText.setPosition(sf::Vector2f(180, 200));
	aboutText.setString(sf::String("This game was developed \n     by Raphael solarski \nsolarski.rafal@gmail.com"));
	
	//domy�lnie wybrana jest opcja na samej g�rze menu
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
		//zamkni�to okno
		if (event.type == sf::Event::Closed)
			window->close();

		//klawiatura
		else if (event.type == sf::Event::KeyPressed)
		{
			//strza�ka w d��
			if (event.key.code == sf::Keyboard::Down)
			{
				/*if (currentOption < 0)
					currentOption++;*/
			}
			//strza�ka w g�r�
			else if (event.key.code == sf::Keyboard::Up)
			{
				/*if (currentOption > 0)
					currentOption--;*/
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

void AboutMenu::render()
{
	//rysuj� t�o
	window->draw(firstBackground);
	window->draw(secondBackground);

	//rysuj� przyciski
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysuj� tekst o tw�rcy
	window->draw(aboutText);

	//rysuj� logo text
	window->draw(logoText);

	window->display();
	window->clear();
}