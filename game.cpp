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

	//sprawdzam czy okno nie zosta³o zamkniête
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);

	//sprawdzam czy level nie zosta³ ukoñczony
	if (currentRow == rowsInMap)
	{
		setNextState(GAME_STATE_LEVEL_FINISHED_MENU);
	}

	//sprawdzam czy graczowi pozosta³y jeszcze ¿ycia
	if (player.getLives() == 0)
	{
		//gracz przegra³
		setNextState(GAME_STATE_DEFEAT_MENU);
	}

	//aktualizujê numer wiersza oraz jeœli jest to potrzebne wczytujê nowy
	if (framesBetweenRowsCounter == 15)
	{
		currentRow++;
		loadRow();
		framesBetweenRowsCounter = 0;
	}
	else
	{
		framesBetweenRowsCounter++;		//inkrementujê licznik klatek od ostatniego wczytania wiersza
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

	//odœwierzam licznik punktów
	scoresText.setString(sf::String("scores: " + std::to_string(scores)));
	
	//redukujê cooldowny
	player.reduceCooldown();
	
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		it->reduceCooldown();
	}

	//rzut o strza³ dla przeciwników
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		//sprawdzam czy dany przeciwnik ma mo¿liwoœæ strza³u
		if (it->getFireCooldown() == 0)
		{
			//rzut losowy
			if ((rand() % 200) == 0)	//jeœli wylosowano liczbê podzieln¹ przez 200  to ognia
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
		//dokonuje update'a i sprawdzam czy asteroida nie opóœci³a mapy
		if (!it->update())
		{
			//asteroida opóœci³a mapê
			it = asteroids.erase(it);	//usuwam element z vectora oraz pobieram iterator do nastêpnego elementu
		}
		else
		{
			//asteroida znajduje siê na mapie
			it++;
		}
	}

	//update przeciwników
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();)
	{
		//dokonuje update'a i sprawdzam czy przeciwnik nie opóœci³ mapy
		if (!it->update())
		{
			//przeciwnik opóœci³ mapê
			it = enemies.erase(it);		//element jest usuwany z vektora, a funkcja zwraca iterator do nastêpnego elementu
		}
		else
		{
			//przeciwnik wci¹¿ jest na mapie
			it++;
		}
	}

	//update pozycji pocisków przeciwników
	for (std::vector<Missile>::iterator it = enemyMissiles.begin(); it != enemyMissiles.end();)
	{
		if (!it->update())
		{
			//pocisk wylecia³ za mapê
			it = enemyMissiles.erase(it);	//element jest usuwany z vektora, a funkcja zwraca iterator do nastêpnego elementu
		}
		else
		{
			it++;
		}
	}

	//update pozycji pocisków gracza
	for (std::vector<Missile>::iterator it = playerMissiles.begin(); it != playerMissiles.end();)
	{
		if (!it->update())
		{
			//pocisk wylecia³ za mapê
			it = playerMissiles.erase(it);	//element jest usuwany z vektora, a funkcja zwraca iterator do nastêpnego elementu
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
		bool collisionFlag = false;	//flaga potrzebna do usuniêcia pocisku(zewnêtrzna pêtla)
		for (std::vector<Asteroid>::iterator asteroid = asteroids.begin(); asteroid != asteroids.end();)
		{
			//sprawdzam czy dosz³o do kolizji
			if (playerMissile->checkCollision(&(*asteroid)))
			{
				//dosz³o - niszczê pocisk(ustawiam flagê), asteroidê oraz koñczê pêtlê
				asteroids.erase(asteroid);
				scores += SCORES_PER_ASTEROID;	//dodajê punkty za zniszczenie asteroidy
				collisionFlag = true;
				break;
			}
			else
			{
				//nie dosz³o
				asteroid++;
			}
		}
		
		//sprawdzam czy flaga kolizji nie jest ustawiona
		if (collisionFlag)
		{
			//niszczê pocisk
			playerMissile = playerMissiles.erase(playerMissile);
			continue;
		}
		else
		{
			//sprawdzm teraz kolizje z innymi statkami
			for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end();)
			{
				//sprawdzam czy dosz³o do kolizji
				if (playerMissile->checkCollision(&(*enemy)))
				{
					//dosz³o - niszczê pocisk(ustawiam flagê), asteroidê oraz koñczê pêtlê
					enemies.erase(enemy);
					scores += SCORES_PER_ENEMY;	//dodajê punkty za zniszczenie przeciwnika
					collisionFlag = true;
					break;
				}
				else
				{
					//nie dosz³o
					enemy++;
				}
			}

			if (collisionFlag)
			{
				//niszczê pocisk
				playerMissile = playerMissiles.erase(playerMissile);
				continue;
			}
			{
				//ten pocisk z niczym siê nie zderzy³
				playerMissile++;
			}
		}
	}

	//kolizje obcych pocisków ze statkiem gracza
	for (std::vector<Missile>::iterator missile = enemyMissiles.begin(); missile != enemyMissiles.end();)
	{
		//sprawdzam czy dosz³o do kolizji
		if (player.checkCollision(&(*missile)))
		{
			//dosz³o do kolizji
			//niszczê pocisk
			missile = enemyMissiles.erase(missile);

			//odbieram graczowi jedno ¿ycie
			player.oneLiveLess();
		}
		else
		{
			//nie dosz³o do kolizji
			missile++;
		}
	}

	//kolizje asteroid ze statkiem gracza
	for (std::vector<Asteroid>::iterator asteroid = asteroids.begin(); asteroid != asteroids.end();)
	{
		//sprawdzam czy dosz³o do kolizji
		if (player.checkCollision(&(*asteroid)))
		{
			//dosz³o do kolizji
			//niszczê asteroidê
			asteroid = asteroids.erase(asteroid);

			//odbieram graczowi jedno ¿ycie
			player.oneLiveLess();
		}
		else
		{
			//nie dosz³o do kolizji
			asteroid++;
		}
	}

	//kolizje obcych statków ze statkiem gracza
	for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end();)
	{
		//sprawdzam czy dosz³o do kolizji
		if (player.checkCollision(&(*enemy)))
		{
			//dosz³o do kolizji
			//niszczê statek
			enemy = enemies.erase(enemy);

			//odbieram graczowi jedno ¿ycie
			player.oneLiveLess();
		}
		else
		{
			//nie dosz³o do kolizji
			enemy++;
		}
	}
}

void Game::render()
{
	//rysujê t³o
	window->draw(firstBackground);
	window->draw(secondBackground);

	//rysujê asteroidy
	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		window->draw(asteroids[i]);
	}

	//rysujê przeciwników
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		window->draw(enemies[i]);
	}

	//rysujê pociski gracza
	for (unsigned int i = 0; i < playerMissiles.size(); i++)
	{
		window->draw(playerMissiles[i]);
	} 

	//rysujê pociski przeciwników
	for (unsigned int i = 0; i < enemyMissiles.size(); i++)
	{
		window->draw(enemyMissiles[i]);
	}

	//rysujê gracza
	window->draw(player);

	//rysujê interfejs
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

//funkcja wczytuj¹ca kolejny wiersz
void Game::loadRow()
{
	//sprawdzam czy obecny wiersz nie figuruje w pliku
	if (nextRowInFile == currentRow)
	{
		//jeœli tak to go wczytujê
		char actualSymbol;
		for (int i = 0; i < 10; i++)
		{
			//wczytujê kolejny znak
			mapFile >> actualSymbol;

			//sprawdzam czy jest to asteroida
			if (actualSymbol == 'A')
			{
				//przygotowujê now¹ asteroidkê
				Asteroid newAsteroid(sf::Vector2f(64.0f * i, -64.0f));		//wczytywany wiersz znajduje siê 64 px przed polem widzenia
				newAsteroid.setTexture(asteroidTexture);
				newAsteroid.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), ASTEROID_SIZE));
				asteroids.push_back(newAsteroid);
			}
			else if (actualSymbol == 'E')
			{	//przeciwnik?
				//przygotowujê nowego przeciwnika
				Enemy newEnemy(sf::Vector2f(64.0f * i, -64.0f));		//wczytywany wiersz znajduje siê 64 px przed polem widzenia
				newEnemy.setTexture(enemyTexture);
				enemies.push_back(newEnemy);
			}
		}
		//sprawdzam czy to nie koniec pliku
		if (!mapFile.eof())
		{
			//wczytujê numer kolejnego wiersza
			mapFile >> nextRowInFile;
		}
	}
}
