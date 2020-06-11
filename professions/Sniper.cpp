#include "Sniper.h"

Sniper::Sniper(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'S';
	name = "Sniper";
	current_hp = getStat(HP_MAX);
	alive = true;
	current_mana = getStat(STARTING_MANA);
}

bool Sniper::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG)
{
	Profession* farthestEnemyUnit = findFarthestEnemyUnit(_enemyPlayerUnits);
	farthestEnemyUnit->takeDamage(getStat(S_P_VAR));
	_gameLOG.push_back(getPlayerString() + ": " + name + " " + getDisplayCoords(position) + " used Precise Shot on " + farthestEnemyUnit->getName() + " " + getDisplayCoords(farthestEnemyUnit->getPosition()) + "\n");
	current_mana = 0;
	return true;
}
