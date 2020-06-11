#pragma once
#include "..\Profession.h"

class Archer : public Profession
{
	std::pair<int, int> findTheBestCoordToUseSuperPower(char _posData[][BOARD_SIZE]);
	bool checkIfUnitIsIn3x3Square(std::pair<int, int>_squareCenter, std::pair<int, int> _unitCoords);
public:
	Archer(std::map<int, double> _stats);
	bool useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
	
};

//Umiejetnosc Archera atakuje wszystkie postacie(nawet wlasnego playera),w kwadracie 3x3. Archer sam znajduje najlepsze miejsce (srodek kwadratu) do zaatakowania
//za pomoca czegos w rodzaju konwolucji