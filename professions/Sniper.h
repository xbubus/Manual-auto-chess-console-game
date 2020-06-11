#pragma once
#include "..\Profession.h"

class Sniper : public Profession
{
public:
	Sniper(std::map<int, double> _stats);
	bool useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
};

//sniper atakuje najdalsza wroga jednostke