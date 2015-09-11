#include <iostream>
#include <cstdlib>
#include <ctime>
#include "gameState.h"
#include "game.h"
#include "constants.h"

Game::Game()
{
	//load needed textures
	//asteroid texture
	if (!asteroidTexture.loadFromFile("Graphics/asteroid.png"))
		std::cout << "asteroid.png loading failed" << std::endl;

	//enemy texture
	if (!enemyTexture.loadFromFile("Graphics/enemy.png"))
		std::cout << "enemy.png loading failed" << std::endl;

	//missile texture
	if (!missileTexture.loadFromFile("Graphics/missile.png"))
		std::cout << "missile.png loading failed" << std::endl;

	//heart texture
	if (!heartTexture.loadFromFile("Graphics/heart.png"))
		std::cout << "heart.png loading failed" << std::endl;

	//background texture
	if (!backgroundTexture.loadFromFile("Graphics/background.png"))
		std::cout << "background.png loading failed" << std::endl;

	//font to draw scores
	if (!scoresFont.loadFromFile("metalLord.ttf"))
		std::cout << "metalLord.ttf loading failed" << std::endl;

	//prepare the map
	firstBackground.setTexture(backgroundTexture);
	firstBackground.setPosition(firstBackgroundPosition);

	secondBackground.setTexture(backgroundTexture);
	secondBackground.setPosition(secondBackgroundPosition);

	//prepare a sprites of lives
	livesSprites = new sf::Sprite[player.getLives()];

	for (unsigned int i = 0; i < player.getLives(); i++)
	{
		livesSprites[i].setTexture(heartTexture);
		livesSprites[i].setPosition(sf::Vector2f(static_cast<float>(532 + i * 32), 0));
	}

	//map loading module
	//open a file of map
	mapFile.open("Maps/level1.dat");

	//zero row counter
	currentRow = 0;
	framesBetweenRowsCounter = 0;

	//zero scores counter
	scores = 0;

	//prepare scores counter (text)
	scoresText.setString("scores: 0");
	scoresText.setFont(scoresFont);
	scoresText.setPosition(sf::Vector2f(0, 0));

	//load the first row of map file witch contains a number of rows in whole map(in game, not map file)
	mapFile >> rowsInMap;

	//load a number of first row of objects(enemy/asteroid) witch figures in a map file 
	mapFile >> nextRowInFile;

	//function witch loads the whole rows to the game
	loadRow();

	//set a start player position
	player.setPosition(sf::Vector2f((SCREEN_WIDTH - PLAYER_SIZE_X) / 2, SCREEN_HEIGHT-PLAYER_SIZE_Y));

	//start a random machine
	srand(static_cast<unsigned int>(time(NULL)));
}

void Game::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)	//if a "x" was clicked, close the game window
			window->close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				setNextState(GAME_STATE_PAUSE_MENU);
			}
		}
	}
}

void Game::logic()
{
	/*
	//diagnostic block
	std::cout << "enemies vector size:" << enemies.size() << std::endl;
	std::cout << "asteroids vector size:" << asteroids.size() << std::endl;
	std::cout << "playerMissiles vector size:" << playerMissiles.size() << std::endl;
	std::cout << std::endl;*/

	//sprawdzam czy okno nie zosta�o zamkni�te
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);

	//sprawdzam czy level nie zosta� uko�czony
	if (currentRow == rowsInMap)
	{
		setNextState(GAME_STATE_LEVEL_FINISHED_MENU);
	}

	//sprawdzam czy graczowi pozosta�y jeszcze �ycia
	if (player.getLives() == 0)
	{
		//gracz przegra�
		setNextState(GAME_STATE_DEFEAT_MENU);
	}

	//aktualizuj� numer wiersza oraz je�li jest to potrzebne wczytuj� nowy
	if (framesBetweenRowsCounter == 15)
	{
		currentRow++;
		loadRow();
		framesBetweenRowsCounter = 0;
	}
	else
	{
		framesBetweenRowsCounter++;		//inkrementuj� licznik klatek od ostatniego wczytania wiersza
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

	//od�wierzam licznik punkt�w
	scoresText.setString(sf::String("scores: " + std::to_string(scores)));
	
	//redukuj� cooldowny
	player.reduceCooldown();
	
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		it->reduceCooldown();
	}

	//rzut o strza� dla przeciwnik�w
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		//sprawdzam czy dany przeciwnik ma mo�liwo�� strza�u
		if (it->getFireCooldown() == 0)
		{
			//rzut losowy
			if ((rand() % 200) == 0)	//je�li wylosowano liczb� podzieln� przez 200  to ognia
			{
				Missile newMissile = it->fire();
				newMissile.setTexture(missileTexture);
				enemyMissiles.push_back(newMissile);
			}
		}
	}

	//sterowanie statkiem
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))				//LEFT
	{
		if (player.getPosition().x > 0) 
			player.move(sf::Vector2f(-PLAYER_SPEED, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))		//RIGHT
	{
		if (player.getPosition().x < SCREEN_WIDTH - PLAYER_SIZE_X)
			player.move(sf::Vector2f(PLAYER_SPEED, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))			//SPACJA
	{
		if (player.getFireCooldown() == 0)
		{
			Missile newMissile = player.fire();
			newMissile.setTexture(missileTexture);
			playerMissiles.push_back(newMissile);
		}
	}
	
	//update asteroid
	for (std::vector<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end();)
	{
		//dokonuje update'a i sprawdzam czy asteroida nie op��ci�a mapy
		if (!it->update())
		{
			//asteroida op��ci�a map�
			it = asteroids.erase(it);	//usuwam element z vectora oraz pobieram iterator do nast�pnego elementu
		}
		else
		{
			//asteroida znajduje si� na mapie
			it++;
		}
	}

	//update przeciwnik�w
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();)
	{
		//dokonuje update'a i sprawdzam czy przeciwnik nie op��ci� mapy
		if (!it->update())
		{
			//przeciwnik op��ci� map�
			it = enemies.erase(it);		//element jest usuwany z vektora, a funkcja zwraca iterator do nast�pnego elementu
		}
		else
		{
			//przeciwnik wci�� jest na mapie
			it++;
		}
	}

	//update pozycji pocisk�w przeciwnik�w
	for (std::vector<Missile>::iterator it = enemyMissiles.begin(); it != enemyMissiles.end();)
	{
		if (!it->update())
		{
			//pocisk wylecia� za map�
			it = enemyMissiles.erase(it);	//element jest usuwany z vektora, a funkcja zwraca iterator do nast�pnego elementu
		}
		else
		{
			it++;
		}
	}

	//update pozycji pocisk�w gracza
	for (std::vector<Missile>::iterator it = playerMissiles.begin(); it != playerMissiles.end();)
	{
		if (!it->update())
		{
			//pocisk wylecia� za map�
			it = playerMissiles.erase(it);	//element jest usuwany z vektora, a funkcja zwraca iterator do nast�pnego elementu
		}
		else
		{
			it++;
		}
	}
	
	//wykrywanie kolizji
	
	//pociski gracza ->asteroidy, przeciwnicy
	for (std::vector<Missile>::iterator playerMissile = playerMissiles.begin(); playerMissile != playerMissiles.end();)
	{
		bool collisionFlag = false;	//flaga potrzebna do usuni�cia pocisku(zewn�trzna p�tla)
		for (std::vector<Asteroid>::iterator asteroid = asteroids.begin(); asteroid != asteroids.end();)
		{
			//sprawdzam czy dosz�o do kolizji
			if (playerMissile->checkCollision(&(*asteroid)))
			{
				//dosz�o - niszcz� pocisk(ustawiam flag�), asteroid� oraz ko�cz� p�tl�
				asteroids.erase(asteroid);
				scores += SCORES_PER_ASTEROID;	//dodaj� punkty za zniszczenie asteroidy
				collisionFlag = true;
				break;
			}
			else
			{
				//nie dosz�o
				asteroid++;
			}
		}
		
		//sprawdzam czy flaga kolizji nie jest ustawiona
		if (collisionFlag)
		{
			//niszcz� pocisk
			playerMissile = playerMissiles.erase(playerMissile);
			continue;
		}
		else
		{
			//sprawdzm teraz kolizje z innymi statkami
			for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end();)
			{
				//sprawdzam czy dosz�o do kolizji
				if (playerMissile->checkCollision(&(*enemy)))
				{
					//dosz�o - niszcz� pocisk(ustawiam flag�), asteroid� oraz ko�cz� p�tl�
					enemies.erase(enemy);
					scores += SCORES_PER_ENEMY;	//dodaj� punkty za zniszczenie przeciwnika
					collisionFlag = true;
					break;
				}
				else
				{
					//nie dosz�o
					enemy++;
				}
			}

			if (collisionFlag)
			{
				//niszcz� pocisk
				playerMissile = playerMissiles.erase(playerMissile);
				continue;
			}
			{
				//ten pocisk z niczym si� nie zderzy�
				playerMissile++;
			}
		}
	}

	//kolizje obcych pocisk�w ze statkiem gracza
	for (std::vector<Missile>::iterator missile = enemyMissiles.begin(); missile != enemyMissiles.end();)
	{
		//sprawdzam czy dosz�o do kolizji
		if (player.checkCollision(&(*missile)))
		{
			//dosz�o do kolizji
			//niszcz� pocisk
			missile = enemyMissiles.erase(missile);

			//odbieram graczowi jedno �ycie
			player.oneLiveLess();
		}
		else
		{
			//nie dosz�o do kolizji
			missile++;
		}
	}

	//kolizje asteroid ze statkiem gracza
	for (std::vector<Asteroid>::iterator asteroid = asteroids.begin(); asteroid != asteroids.end();)
	{
		//sprawdzam czy dosz�o do kolizji
		if (player.checkCollision(&(*asteroid)))
		{
			//dosz�o do kolizji
			//niszcz� asteroid�
			asteroid = asteroids.erase(asteroid);

			//odbieram graczowi jedno �ycie
			player.oneLiveLess();
		}
		else
		{
			//nie dosz�o do kolizji
			asteroid++;
		}
	}

	//kolizje obcych statk�w ze statkiem gracza
	for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end();)
	{
		//sprawdzam czy dosz�o do kolizji
		if (player.checkCollision(&(*enemy)))
		{
			//dosz�o do kolizji
			//niszcz� statek
			enemy = enemies.erase(enemy);

			//odbieram graczowi jedno �ycie
			player.oneLiveLess();
		}
		else
		{
			//nie dosz�o do kolizji
			enemy++;
		}
	}
}

void Game::render()
{
	//rysuj� t�o
	window->draw(firstBackground);
	window->draw(secondBackground);

	//rysuj� asteroidy
	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		window->draw(asteroids[i]);
	}

	//rysuj� przeciwnik�w
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		window->draw(enemies[i]);
	}

	//rysuj� pociski gracza
	for (unsigned int i = 0; i < playerMissiles.size(); i++)
	{
		window->draw(playerMissiles[i]);
	} 

	//rysuj� pociski przeciwnik�w
	for (unsigned int i = 0; i < enemyMissiles.size(); i++)
	{
		window->draw(enemyMissiles[i]);
	}

	//rysuj� gracza
	window->draw(player);

	//rysuj� interfejs
	for (unsigned int i = 0; i < player.getLives(); i++)
	{
		//serduszka
		window->draw(livesSprites[i]);
	}

	//punkty
	window->draw(scoresText);

	window->display();
	window->clear(sf::Color(128, 128, 128));
}

//funkcja wczytuj�ca kolejny wiersz
void Game::loadRow()
{
	//sprawdzam czy obecny wiersz nie figuruje w pliku
	if (nextRowInFile == currentRow)
	{
		//je�li tak to go wczytuj�
		char actualSymbol;
		for (int i = 0; i < 10; i++)
		{
			//wczytuj� kolejny znak
			mapFile >> actualSymbol;

			//sprawdzam czy jest to asteroida
			if (actualSymbol == 'A')
			{
				//przygotowuj� now� asteroidk�
				Asteroid newAsteroid(sf::Vector2f(64.0f * i, -64.0f));		//wczytywany wiersz znajduje si� 64 px przed polem widzenia
				newAsteroid.setTexture(asteroidTexture);
				newAsteroid.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), ASTEROID_SIZE));
				asteroids.push_back(newAsteroid);
			}
			else if (actualSymbol == 'E')
			{	//przeciwnik?
				//przygotowuj� nowego przeciwnika
				Enemy newEnemy(sf::Vector2f(64.0f * i, -64.0f));		//wczytywany wiersz znajduje si� 64 px przed polem widzenia
				newEnemy.setTexture(enemyTexture);
				enemies.push_back(newEnemy);
			}
		}
		//sprawdzam czy to nie koniec pliku
		if (!mapFile.eof())
		{
			//wczytuj� numer kolejnego wiersza
			mapFile >> nextRowInFile;
		}
	}
}