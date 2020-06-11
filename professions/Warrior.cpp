#include "Warrior.h"

Warrior::Warrior(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'W';
	name = "Warrior";
	current_hp = getStat(HP_MAX);
	alive = true;
	current_mana = getStat(STARTING_MANA);
}
std::pair<int, int> Warrior::findCoordToUseSuperPower(char _posData[][BOARD_SIZE])
{
	double ultRange = 2.84; // ~2 *sqrt(2)
	bool areMyUnitsDisplayedLower = islower(getDisplayChar());
	std::vector<std::pair<int, int>> coordsInRange;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_posData[i][j] == ' ') continue;
			if (areMyUnitsDisplayedLower && islower(_posData[i][j])) continue;
			else if (!areMyUnitsDisplayedLower && isupper(_posData[i][j])) continue;
			else if (sqrt(pow(position.first - i, 2) - pow(position.second - j, 2) < ultRange)) coordsInRange.push_back(std::make_pair(i, j));
		}
	}
	if (coordsInRange.empty()) return std::make_pair(-1, -1); //nie ma nic w zasiegu 
	std::pair<int, int> coordToAttack = coordsInRange[0];
	for (auto cord : coordsInRange) //szukam najmniejszej odleglosci
	{
		if (sqrt(pow(cord.first - position.first, 2) + pow(cord.second - position.second, 2)) < sqrt(pow(coordToAttack.first - position.first, 2) + pow(coordToAttack.second - position.second, 2)))
			coordToAttack = cord;
	}
	return coordToAttack;
}



bool Warrior::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][10], std::vector<std::string>& _gameLOG)
{
	std::pair<int, int> coordToAttack = findCoordToUseSuperPower(_posData);
	if (coordToAttack.first == -1) return false;
	for (auto unit : _enemyPlayerUnits)
	{
		if (coordToAttack == unit->getPosition())
		{
			unit->takeDamage(getStat(S_P_VAR));
			unit->setStunned(true);
			_gameLOG.push_back(getPlayerString() + ": " + name + " " + getDisplayCoords(position) + " used Stunning Jump on " + unit->getName() + " " + getDisplayCoords(unit->getPosition())+"\n");

			return true;
		}
	}
	return false;
}
