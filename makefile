OBJECTS = aboutMenu.cpp asteroid.cpp collidable.cpp defeatMenu.cpp enemy.cpp game.cpp gameState.cpp levelFinishedMenu.cpp main.cpp mainMenu.cpp missile.cpp pauseMenu.cpp player.cpp scoresMenu.cpp
LIBS = -lsfml-window -lsfml-graphics -lsfml-system

ALL: $(OBJECTS)
	g++ -Wall -Wextra -Wpedantic -std=c++11 -o StarVoyager $(OBJECTS) $(LIBS) 
