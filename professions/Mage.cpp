#include "Mage.h"
#include <vector>

Mage::Mage(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'M';
	name = "Mage";
	current_hp = getStat(HP_MAX);
	current_mana = getStat(MANA_MAX);
	alive = true;
}

bool Mage::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG)
{
	for (auto u : _enemyPlayerUnits)
	{
		u->takeDamage(getStat(S_P_VAR));
	}
	_gameLOG.push_back(getPlayerString() + ": " + name + " " + getDisplayCoords(position) + " used Requiem " + "\n");
	return true;
}
