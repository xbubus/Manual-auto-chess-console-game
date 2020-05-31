#include "Archer.h"
#include <vector>

Archer::Archer(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'A';
	name = "Archer";
	current_hp = getStat(HP_MAX);
	alive = true;
	current_mana = getStat(MANA_MAX);
}

bool Archer::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG)//moze zaatakowac wlasne jednostki
{
	std::pair<int,int> coordsToAttack = findTheBestCoordToUseSuperPower(_posData);
	for (auto unit : _myPlayerUnits)
	{
		if (checkIfUnitIsIn3x3Square(coordsToAttack, unit->getPosition())) unit->takeDamage(getStat(S_P_VAR));
	}
	for (auto unit : _enemyPlayerUnits)
	{
		if (checkIfUnitIsIn3x3Square(coordsToAttack, unit->getPosition())) unit->takeDamage(getStat(S_P_VAR));
	}
	
	_gameLOG.push_back(getPlayerString()+": "+name+" "+getDisplayCoords(position)+" used Arrow Shower on "+getDisplayCoords(coordsToAttack) + "\n");
	return true;
}

std::pair<int, int> Archer::findTheBestCoordToUseSuperPower(char _posData[][10])
{
	std::pair <int, int> bestCoords;
	int bestValue = -20; //-20 to jakas wartosc inicjalizacyjna, nie ma wiekszego znaczenia jaka bedzie dokladnie,byle by mniejsza od zera
	int coordValue[BOARD_SIZE][BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			coordValue[i][j] = 0;
		}
	}
	bool areMyUnitsDisplayedLower = islower(getDisplayChar());
	// tutaj robie coœ ala konwolucje  przez plansze i szukam najlepszego kwadratu 3x3 do zaatakowania
	// obliczam wartoœæ dla kazdego pola, jesli na kwadracie 3x3 znajduje sie przeciwnik dodaje 2,jesli sojusznik odejmuje 1
	//na koncu zwracam coordy najbardziej oplacalne do ataku
	for (int i = 1; i < BOARD_SIZE-1; i++)
	{
		for (int j = 1; j < BOARD_SIZE-1; j++)
		{
			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j-1; l <= j + 1; l++)
				{
					if (_posData[k][l] == ' ') continue;

					if (islower(_posData[k][l]))
					{
						if(areMyUnitsDisplayedLower) coordValue[i][j]-=1;
						else coordValue[i][j]+=2;
					}
					else
					{
						if (areMyUnitsDisplayedLower) coordValue[i][j] += 2;
						else coordValue[i][j] -= 1;
					}
				}
			}
		}
	}
	
	for (int i = 1; i < BOARD_SIZE-1; i++)
	{
		for (int j = 1; j < BOARD_SIZE-1; j++)
		{
			if (coordValue[i][j] > bestValue)
			{
				bestValue = coordValue[i][j];
				bestCoords = std::make_pair(i, j);
			}
		}
	}
	
	return bestCoords;
}

bool Archer::checkIfUnitIsIn3x3Square(std::pair<int, int> _squareCenter, std::pair<int, int> _unitCoords)
{
	int centerX = _squareCenter.first;
	int centerY = _squareCenter.second;
	for (int i = centerX - 1; i <= centerX + 1; i++)
	{
		for (int j = centerY - 1; j <= centerY + 1; j++)
		{
			if (_unitCoords.first == i && _unitCoords.second == j) return true;
		}
	}
	return false;
}
