#pragma once
#include "..\Profession.h"

class Mage : public Profession
{
public:
	Mage(std::map<int, double> _stats);
	bool useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
};

//mag atakuje wszystkie wrogie jednostki