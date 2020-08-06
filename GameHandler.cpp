#include "GameHandler.h"

//metody publiczne
GameHandler::GameHandler()
{
	playerid = 0;
	clearBoard();
	linesInDisplayBoard = 24;
}
GameHandler::~GameHandler()
{
	for (auto p : players)
	{
		destroyVector <Profession*>(p->getUnits());
	}
	destroyVector<Player*>(players);
	delete pf;
	//std::cout << "Destroyed!!\n";
}
void GameHandler::createProfessionsFactory()
{
	pf = new ProfessionsFactory();
	pf->init();
}
void GameHandler::manageGame()
{
	createPlayer();
	createPlayer();
	std::cout << "Take a look how does the board look like: \n";
	displayBoard();
	std::cout << "First all players have to buy units and place them on board.\n";
	system("pause");
	for (auto player : players)
	{

		askPlayerToBuyUnits(player);
		putAllPlayerUnitsOnBoard(player);
	}
	updatePositionData();
	system("cls");
	//start rozgrywki
	bool gameON = true;
	while (gameON)
	{
		for (auto player : players)
		{
			if (!gameON) break;
			for (auto unit : player->getUnits())
			{
				gameON = checkIfPlayersUnitsAreAlive();
				if (!gameON) break;
				if (unit->isAlive())
				{
					if (unit->getStunned()) //jesli unit jest zestunowany i jest jego kolej to zdejmuje mu stuna i pomijam jego ruch, stun ma zabierac jeden ruch
					{
						unit->setStunned(false);
						continue;
					}
					displayBoard();
					displayAllplayersUnitsAndBasicStats();
					displayLog();
					player->doSomethingWithUnit(unit, positionData, professionBoardData, player->getUnits(), players[abs(player->getID() - 1)]->getUnits(), gameLOG,gameON); //abs(player->getID()-1) daje przeciwnego playera, jesli player ma id 0 to przeciwny ma abs(0-1),jesli 1 to abs(1-1)
					updatePositionData();
					system("cls");



				}
				if (!gameON) break;//konieczne
			}

		}
		updateAllUnitsStatsAfterRound();
		roundsCounter++;


	}
	displayBoard();
	displayAllplayersUnitsAndBasicStats();
	displayLog();
	printGameLogToFileAndDelete();
	std::cout << "<----- GAME OVER ----->\n";
	system("pause");
	return;
}
void GameHandler::resetData()
{
	for (auto p : players)
	{
		destroyVector <Profession*>(p->getUnits());
	}
	destroyVector<Player*>(players);
	clearBoard();
	playerid = 0;
}
//metody prywatne
void GameHandler::displayBoard()
{
	std::cout << std::endl << "  ";
	for (int i = 0; i < 10; i++) std::cout << "  " << i << " ";
	std::cout << std::endl;

	std::cout << "  " << char(201) << char(205);
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++)
	{
		if (i % 2 == 0) std::cout << char(205);
		else std::cout << char(205) << char(203) << char(205);

	}
	std::cout << char(205) << char(187) << std::endl;


	for (int j = 0; j < 10; j++)
	{
		std::cout << j << " ";
		for (int i = 0; i < 2 * BOARD_SIZE + 1; i++)
		{
			if (i % 2 == 0) std::cout << char(186);
			else std::cout << " " << positionData[i / 2][j] << " ";
		}


		if (j == 9)break;
		std::cout << std::endl << "  " << char(204) << char(205);
		for (int i = 0; i < 2 * BOARD_SIZE - 1; i++)
		{
			if (i % 2 == 0) std::cout << char(205);
			else std::cout << char(205) << char(206) << char(205);

		}
		std::cout << char(205) << char(185) << std::endl;

	}


	std::cout << std::endl << "  " << char(200) << char(205);
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++)
	{
		if (i % 2 == 0) std::cout << char(205);
		else std::cout << char(205) << char(202) << char(205);

	}
	std::cout << char(205) << char(188) << std::endl;
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
void GameHandler::updatePositionData() 
{
	clearBoard();
	for (auto player : players)
	{
		for (auto player_unit : player->getUnits())
		{
			if (player_unit->isAlive())
			{
				positionData[player_unit->getPosition().first][player_unit->getPosition().second] = player_unit->getDisplayChar();
				professionBoardData[player_unit->getPosition().first][player_unit->getPosition().second] = player_unit;
			}
		}
	}
}
void GameHandler::displayAllplayersUnitsAndBasicStats()
{
	//w tej metodzie i nastepnej cofam linie w coucie i wyswietlam obok juz wyswietlonych rzeczy inne rzeczy uzywaj¹c kilku tab
	//wygl¹da to troche nieelegancko ale dzia³a i nie znalaz³em innego sposobu
	int newNewLines = 0;
	for (int i = 0; i < linesInDisplayBoard - 5; i++)
	{
		std::cout << "\033[F"; //cofam linie w coucie
	}

	for (auto p : players)
	{
		std::cout << "\t\t\t\t\t\t\t" << "Player " << p->getID()+1 << ":\n";
		newNewLines++;
		for (auto u : p->getUnits())
		{
			if (u->isAlive())
			{
				if (u->getStunned())
				{
					std::cout << "\t\t\t\t\t\t\t" << u->getPosition() << " " << u->getName() << " STUNNED\n";
					continue;
				}
				std::cout << "\t\t\t\t\t\t\t" << u->getPosition() << " " << u->getName() << " HP: " << u->getCurrentHP() << "/" << u->getStat(HP_MAX);
				std::cout << " MANA: " << u->getCurrentMana() << "/" << u->getStat(MANA_MAX) << " AR: " << u->getStat(AR) << "\n";
			}
			else
				std::cout << "\t\t\t\t\t\t\t" << u->getPosition() << " " << u->getName() << " DEATH \n";
			newNewLines++;
		}
	}
	for (int i = 0; i < linesInDisplayBoard - 5 - newNewLines; i++)
	{
		std::cout << "\n"; //odcofuje linie w coucie
	}
}
void GameHandler::displayLog()
{
	int linesToBack = 0;
	if (!gameLOG.empty())
	{
		linesToBack = 1;
		std::cout << "\t\t\t\t\t\t" << "Game LOG: \n";
	}
	for (int i = (int)gameLOG.size() - 1; i > (int)gameLOG.size() - 6; i--)
	{

		if (i < 0) break;
		if (gameLOG.empty()) break;
		std::cout << "\t\t\t\t\t\t" << gameLOG[i];
		linesToBack++;
	}
	for (int i = 0; i < linesToBack; i++) std::cout << "\033[F"; //cofam linie w coucie
}

void GameHandler::createPlayer()
{
	players.push_back(new Player(playerid++));
}
void GameHandler::askPlayerToBuyUnits(Player* _p)

{
	int id;
	while (true)
	{
		system("cls");
		std::cout << "Hi player " << _p->getID() +1<< std::endl;//ewentualnie nickname
		std::cout << "You have " << _p->getGold() << " gold.\n";
		pf->getProfLibrary()->displayUnitsAndCosts();
		std::cout << "Write profession id to buy unit or -1 to exit shop\n";
		id=getValidInput<int>(); 
		if (id == -1)
		{
			if (_p->getUnits().size() <= 0)
			{
				std::cout << "You have to buy at least 1 unit\n";
				system("pause");
				continue;
			}

			else
				break;
		}
		try
		{
			if (pf->getProfLibrary()->getProfessionCost(id) > _p->getGold()) // playera nie stac
				std::cout << "You have not enough gold to buy this unit!\n";
			else
				_p->buyUnit(pf->createUnit(id), pf->getCost(id));
		}
		catch (const char* error)
		{
			std::cout << "Something went wrong,check if unit ID is valid\n";
			system("pause");
		}
	}
	
}
void GameHandler::putAllPlayerUnitsOnBoard(Player* _p)
{
	system("cls");
	for (auto unit : _p->getUnits())
	{
		bool ok = false;
		std::cout << "P" << _p->getID() + 1 << ":\n";
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
		updatePositionData();
		system("cls");

	}
	std::stringstream allplayerUnits;
	allplayerUnits<<"P" <<(_p->getID() + 1) << " ";
	for (auto unit : _p->getUnits())
	{
		allplayerUnits << unit->getName() << " " << unit->getPosition() << " ";
	}
	allplayerUnits << "\n";
	gameLOG.push_back(allplayerUnits.str());
}
std::pair<int, int> GameHandler::askPlayersForCordsToPutUnit()
{
	int x=-1, y=-1;
	while (x < 0 || x>9 || y < 0 || y>9)
	{
		std::cout << "Write x cord: \n"; 
		x=getValidInput<int>();
		std::cout << "Write y cord: \n"; 
		y=getValidInput<int>();
		if (x < 0 || x>9 || y < 0 || y>9||professionBoardData[x][y] != nullptr)
		{
			std::cout << "There is already unit on this coords/Out of board range, try again\n";
			x = -1;
			y = -1;
		}
	}
	return std::make_pair(x, y);

}

bool GameHandler::checkIfPlayersUnitsAreAlive()
{
	bool temp = true;
	for (auto p : players)
	{
		temp = false;
		for (auto u : p->getUnits())
		{
			if (u->isAlive()&&temp==false)
			{
				temp=true;
				
			}
		
		}
		if (temp == false)
		{
			gameLOG.push_back("Game Finished\n");
			return temp;
			
		}
	}
	return temp;
	
}
void GameHandler::printGameLogToFileAndDelete() 
{
	const time_t time = std::time(nullptr);
	std::ostringstream oss;
	oss<< std::put_time(std::localtime(&time), "%F_%T");
	std::string fileName = "LOG_" + oss.str() + ".txt";
	std::replace(fileName.begin(), fileName.end(), ':', ';'); // w nazwie pliku nie moze byc :
	std::ofstream file(fileName);
	if (file.is_open())
	{
		while (!gameLOG.empty())
		{
			file << gameLOG.back();
			gameLOG.pop_back();
		}

		file.close();
	}
}
void GameHandler::updateAllUnitsStatsAfterRound()
{
	for (auto p : players)
	{
		for (auto u : p->getUnits())
		{
			u->updateStatsAfterRound();
		}
	}
}

