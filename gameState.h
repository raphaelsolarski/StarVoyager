#pragma once
#include <SFML/Graphics.hpp>

//typ okre�laj�cy wszystkie stany gry
//je�li dodajesz nowy stan to musisz go tutaj uwzgl�dni�
enum GameStates
{
	GAME_STATE_NULL,
	GAME_STATE_RESTUME,		//state, kt�ry rozkazuje przywr�ci� u�pion� gr�
	GAME_STATE_MAIN_MENU,
	//GAME_STATE_LOADING_MENU,	//nie wykorzystuj� tego puki co
	GAME_STATE_PAUSE_MENU,
	GAME_STATE_LEVEL_FINISHED_MENU,
	GAME_STATE_DEFEAT_MENU,		//menu pora�ki
	GAME_STATE_ABOUT_MENU,
	GAME_STATE_SCORES_MENU,
	GAME_STATE_GAME,
	GAME_STATE_EXIT
};

//g��wna klasa GameState po kt�rej b�dzie dziedziczy� ka�da klasa state'a
class GameState
{
public:
	static void freeResources();
	static void changeState();
	static void setNextState(GameStates newState);
	static void init(GameState* initialState, sf::RenderWindow *window);
	static GameStates getStateID();
	static GameState& getCurrentState();
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState(){};

protected:
	static int nextLevel;		//numer aktualnego poziomu
	static GameStates stateID;
	static GameStates nextState;
	static GameState *currentState;
	static GameState *sleepedState;	//wska�nik do u�pionego state'a (potrzebne dla menu pauzy);
	static sf::RenderWindow * window;	//wska�nik do okna gry(wsp�lnego dla wszystkich state'�w)	
	static sf::Vector2f firstBackgroundPosition;	//oba pola s� potrzebne do p�ynnego przechodzenia mi�dzy oknami menu
	static sf::Vector2f secondBackgroundPosition;	
};