#pragma once
#include "Player.h"
#include "ProfessionsFactory.h"
class GameHandler
{
	char positionData[BOARD_SIZE][BOARD_SIZE];//przechowuje tutaj znaki do wyswietlania jednostek na planszy
	std::vector<Player*> players;
	int playerid;
	Profession* professionBoardData[BOARD_SIZE][BOARD_SIZE];
	int roundsCounter;
	ProfessionsFactory* pf;
	int linesInDisplayBoard;
	std::vector<std::string> gameLOG;
	/////////////////////////////////////
	void displayBoard();
	void clearBoard();
	void updatePositionData(); //po ruchu trzeba odswiezyc dane, jesli jednostka zmienila poycje/umarla powinna nie byc wyswietlana
	void displayAllplayersUnitsAndBasicStats();//wyswietlanie podstawowych statystyk i po³o¿enia kazdej jednostki
	void displayLog(); //wyswietlanie Logu gry, 5 ostatnich ruchów

	void createPlayer();
	void askPlayerToBuyUnits(Player* _p);
	void putAllPlayerUnitsOnBoard(Player* _p);
	std::pair<int, int> askPlayersForCordsToPutUnit();

	void updateAllUnitsStatsAfterRound(); //przyrost many co runde dla jednostek itp
	bool checkIfPlayersUnitsAreAlive(); //sprawdzam czy wszystkie jednostki jednego z graczy s¹ martwe, jesli tak to gra siê konczy

	template<typename T>
	void destroyVector(std::vector<T>& _v) //metoda do usuwania dynamicznej pamieci w wektorze
	{
		while (!_v.empty()) {
			delete _v.back();
			_v.pop_back();
		}
	}
public:
	GameHandler();
	~GameHandler();
	GameHandler(const GameHandler& _copy) = delete; //zasada trzech
	GameHandler operator=(GameHandler& _other) = delete; //zasada trzech
	void createProfessionsFactory();
	void manageGame(); //glowna metoda do zarzadzania gra
	void resetData();
	
};
