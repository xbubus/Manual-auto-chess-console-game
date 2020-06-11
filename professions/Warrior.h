#pragma once
#include "..\Profession.h"

class Warrior : public Profession
{
	std::pair<int, int> findCoordToUseSuperPower(char _posData[][BOARD_SIZE]);
public:
	Warrior(std::map<int, double> _stats);
	bool useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][10], std::vector<std::string>& _gameLOG);
};

//Warrior skacze na przeciwnika w zasiegu 2 pol,zadaje obrazenia i go stunnuje