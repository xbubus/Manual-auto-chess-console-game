#pragma once
#include "..\Profession.h"

class Pope : public Profession
{
public:
	Pope(std::map<int, double> _stats);
	bool useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
};

//Papie¿ wskrzesza losow¹ nie¿yw¹ postaæ swojego Playera