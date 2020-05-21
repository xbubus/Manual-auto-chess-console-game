#pragma once
#define BOARD_SIZE 10
#include <vector>
#include "Player.h"

#include "ProfessionsFactory.h"
class GameHandler
{

	const int size = BOARD_SIZE;
	char positionData[BOARD_SIZE][BOARD_SIZE];
	std::vector<Player*> players;
	int playerid;
	Profession* professionBoardData[BOARD_SIZE][BOARD_SIZE];// 
	int roundsCounter;
	ProfessionsFactory* pf;
public:
	GameHandler();
	void displayBoard();
	void createPlayer();
	void clearBoard();
	void updatePositionData();
	void test();
	void askPlayerToBuyUnits(Player* _p);
	void putAllPlayerUnitsOnBoard(Player* _p);
	std::pair<int,int> askPlayersForCordsToPutUnit();

	void doSomethingWithUnit(Profession* _u);
	void updateAllUnitsStatsAfterRound(); // przyrost many co runde dla jednostek itp
	void manageGame();


	
	

};