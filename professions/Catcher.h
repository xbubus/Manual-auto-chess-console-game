#pragma once
#include "..\Profession.h"

class Catcher : public Profession
{
	std::pair<int, int> findFreePositionNearMe(char _posData[][BOARD_SIZE]);
public:
	Catcher(std::map<int, double> _stats);
	bool useSuperPower(std::vector<Profession*> _myPlayerUnits , std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
};

//Catcher przyciaga do siebie najdalsza wrog¹ jednostke