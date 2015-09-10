OBJECTS = aboutMenu.o asteroid.o collidable.o defeatMenu.o enemy.o game.o gameState.o levelFinishedMenu.o main.o mainMenu.o missile.o pauseMenu.o player.o scoresMenu.o
LIBS = -lsfml-window -lsfml-graphics -lsfml-system
CC=g++
WAR=-Wall -Wextra -Wpedantic
CFLAGS=$(WAR) -c -std=c++11
LFLAGS=$(WAR) -std=c++11

ALL: $(OBJECTS)
	$(CC) $(LFLAGS) -o StarVoyager $(OBJECTS) $(LIBS) 

aboutMenu.o: aboutMenu.cpp
	$(CC) $(CFLAGS) -o aboutMenu.o aboutMenu.cpp
	
asteroid.o: asteroid.cpp
	$(CC) $(CFLAGS) -o asteroid.o asteroid.cpp

collidable.o: collidable.cpp
	$(CC) $(CFLAGS) -o collidable.o collidable.cpp

defeatMenu.o: defeatMenu.cpp
	$(CC) $(CFLAGS) -o defeatMenu.o defeatMenu.cpp

enemy.o: enemy.cpp
	$(CC) $(CFLAGS) -o enemy.o enemy.cpp

game.o: game.cpp
	$(CC) $(CFLAGS) -o game.o game.cpp

gameState.o: gameState.cpp
	$(CC) $(CFLAGS) -o gameState.o gameState.cpp

levelFinishedMenu.o: levelFinishedMenu.cpp
	$(CC) $(CFLAGS) -o levelFinishedMenu.o levelFinishedMenu.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o main.cpp

mainMenu.o: mainMenu.cpp
	$(CC) $(CFLAGS) -o mainMenu.o mainMenu.cpp

missile.o: missile.cpp
	$(CC) $(CFLAGS) -o missile.o missile.cpp

pauseMenu.o: pauseMenu.cpp
	$(CC) $(CFLAGS) -o pauseMenu.o pauseMenu.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) -o player.o player.cpp

scoresMenu.o: scoresMenu.cpp
	$(CC) $(CFLAGS) -o scoresMenu.o scoresMenu.cpp
