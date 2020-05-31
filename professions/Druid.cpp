#include "Druid.h"
#include <vector>

Druid::Druid(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'D';
	name = "Druid";
	current_hp = getStat(HP_MAX);
	alive = true;
}

bool Druid::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG)
{
	for (auto u : _myPlayerUnits)
	{
		if (u == this) continue;
		if (u->isAlive() == false) continue;
		u->setCurrentHP(u->getCurrentHP() + getStat(S_P_VAR));
		if (u->getCurrentHP() > u->getStat(HP_MAX)) u->setCurrentHP(HP_MAX);

	}
	current_mana = 0;
	_gameLOG.push_back(getPlayerString() + ": " + name + " " + getDisplayCoords(position) + " used Heal My Mates " + "\n");
	return true;
}
