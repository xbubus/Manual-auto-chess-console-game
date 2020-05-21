#include "GameHandler.h"
#include <iostream>
void GameHandler::displayBoard()
{
	std::cout << std::endl;
	for (int i = 0; i < 10; i++) std::cout << "  " << i << " ";
	std::cout << std::endl;

	std::cout << "  " << char(201) << char(205);
	for (int i = 0; i < 2 * size - 1; i++)
	{
		if (i % 2 == 0) std::cout << char(205);
		else std::cout << char(205) << char(203) << char(205);

	}
	std::cout << char(205) << char(187) << std::endl;


	for (int j = 0; j < 10; j++)
	{
		std::cout << j << " ";
		for (int i = 0; i < 2 * size + 1; i++)
		{
			if (i % 2 == 0) std::cout << char(186);
			else std::cout << " " << positionData[i / 2][j] << " ";
		}


		if (j == 9)break;
		std::cout << std::endl << "  " << char(204) << char(205);
		for (int i = 0; i < 2 * size - 1; i++)
		{
			if (i % 2 == 0) std::cout << char(205);
			else std::cout << char(205) << char(206) << char(205);

		}
		std::cout << char(205) << char(185) << std::endl;

	}


	std::cout << std::endl << "  " << char(200) << char(205);
	for (int i = 0; i < 2 * size - 1; i++)
	{
		if (i % 2 == 0) std::cout << char(205);
		else std::cout << char(205) << char(202) << char(205);

	}
	std::cout << char(205) << char(188) << std::endl;
}

GameHandler::GameHandler()
{
	playerid = 0;
	pf = new ProfessionsFactory();
	clearBoard();
}

void GameHandler::createPlayer()
{
	players.push_back(new Player(playerid++));
}



void GameHandler::updatePositionData() //nazwa update board data czy cos
{
	clearBoard();
	for (auto player : players)
	{
		for (auto player_unit : player->getUnits())
		{
			//if (player_unit->isAlive() == false) continue;
			positionData[player_unit->getPosition().first][player_unit->getPosition().second] = player_unit->getDisplayChar();
			professionBoardData[player_unit->getPosition().first][player_unit->getPosition().second] = player_unit;
		}
	}
}

void GameHandler::clearBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			positionData[i][j] = ' ';
			professionBoardData[i][j] = nullptr;

		}
	}
}
void GameHandler::test()
{
	createPlayer();
	createPlayer();

	askPlayerToBuyUnits(players[0]);
	players[0]->buyUnit(pf->createUnit(0));
	players[0]->moveUnit(players[0]->getUnits()[0], std::make_pair(7, 3));
	//players[1]->buyUnit(sellUnit(0,players[1]));
	//players[1]->moveUnit(players[1]->getUnits()[0], std::make_pair(4, 3));
	updatePositionData();
	displayBoard();
	std::cout<<"char: "<<players[0]->getUnits()[0]->getPosition().first;
	

//	players[1]->getUnits()[0]->attack( professionBoardData[2][3]);

	updatePositionData();

	displayBoard();
	
}

void GameHandler::askPlayerToBuyUnits(Player* _p)
{
	int id;
	std::cout << "hi player " << _p->getID() << std::endl;//nickname
	std::cout << "you have " << _p->getGold() << " gold.\n";
	pf->getProfLibrary()->displayUnitsAndCosts();
	std::cout << "write profession id to buy unit\n";
	std::cin >> id; //zabezp
	if (pf->getProfLibrary()->getProfessionCost(id) > _p->getGold()) // playera nie stac
		return;
	else
		_p->buyUnit(pf->createUnit(id));
	//zapetlic dopoki playera stac na cokolwiek lub dopoki sam nie wyjdzie 
}
void GameHandler::putAllPlayerUnitsOnBoard(Player* _p)
{
	for (auto unit : _p->getUnits())
	{
		bool ok = false;
		std::cout << "Write x and y cords to put your " << unit->getName() << " on board.\n";
		std::pair<int, int> coords;
		while (ok != true)
		{
			coords = askPlayersForCordsToPutUnit();
			if (_p->getID() == 0 && coords.second > 3)
			{
				std::cout << "At the beginning you must put your unit on one of first 3 rows\nTry again\n";
				continue;
			}
			if (_p->getID() == 1 && coords.second < 6)
			{
				std::cout << "At the beginning you must put your unit on one of last 3 rows\nTry again\n";
				continue;
			}
			ok = true;
		}
		unit->setPosition(coords);

	}
}
std::pair<int, int> GameHandler::askPlayersForCordsToPutUnit()
{
	int x=-1, y=-1;
	while (x < 0 || x>9 || y < 0 || y>9)
	{
		std::cout << "Write x cord: \n"; //zabezpieczyc to, only int
		std::cin >> x;
		std::cout << "Write y cord: \n"; //zabezpieczyc to
		std::cin >> y;
		if (professionBoardData[x][y] != nullptr)
		{
			std::cout << "There is already unit on this coords, try again\n";
			x = -1;
			y = -1;
		}
	}
	return std::make_pair(x, y);

}

void GameHandler::manageGame()
{
	createPlayer();
	createPlayer();
	for (auto player:players)
	{
		askPlayerToBuyUnits(player);
		putAllPlayerUnitsOnBoard(player);
	}
	updatePositionData();
	displayBoard();

	//start rozgrywki
	bool gameON = true;
	while (gameON)
	{
		for (auto player : players)
		{
			for (auto unit : player->getUnits())
			{
				doSomethingWithUnit(unit);
			}
		}
		roundsCounter++;
	}
}
void GameHandler::doSomethingWithUnit(Profession* _u)

{

	int choice = -1;
	std::cout << "Unit: " << _u->getName() << " on coords: " << _u->getPosition().first << "," << _u->getPosition().second << std::endl; //sprobowac napisac operator do wysietlania paira
	std::cout << "1-> Move \n 2-> Attack \n 3-> Use superpower\n 4->Wait";

	switch (choice)
	{
	case 1:
		_u->setPosition(askPlayersForCordsToPutUnit());
		break;
	case 2:
		//na poczatku sprawdzac czy jakies postacie sa w zasiegu ataku
		//funkcja ktora zwraca piar na unit ktory chcemy zatakowac,sprawdzac czy nie jest naszym unitem
	case 3:
		//sprawdzac czy ma wystarczajaco many
	case 4:
		return;

	}
}

void GameHandler::updateAllUnitsStatsAfterRound()
{
	for (auto p : players)
	{
		for (auto u : p->getUnits())
		{
			//u->updateStatsAfterRound();
		}
	}
}
