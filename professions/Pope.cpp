#include "Pope.h"

Pope::Pope(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'P';
	name = "Pope";
	current_hp = getStat(HP_MAX);
	alive = true;
	current_mana = getStat(STARTING_MANA);
}

bool Pope::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG)
{
	std::vector<Profession*> _myDeathUnits;
	for (auto u : _myPlayerUnits)
	{
		if (u->isAlive() == false) _myDeathUnits.push_back(u);
	}
	if (_myDeathUnits.empty()) return false;
	int try_ = 0;
	while (try_ < _myDeathUnits.size())
	{
		int _indexToRevive = rand() % _myDeathUnits.size();

		if (_posData[_myDeathUnits[_indexToRevive]->getPosition().first][_myDeathUnits[_indexToRevive]->getPosition().second] == ' ')
		{
			_myDeathUnits[_indexToRevive]->setAlive(true);
			_myDeathUnits[_indexToRevive]->setCurrentHP((int)_myDeathUnits[_indexToRevive]->getStat(HP_MAX) / 2); //revive z polowa hp i many
			_myDeathUnits[_indexToRevive]->setCurrentMana((int)_myDeathUnits[_indexToRevive]->getStat(MANA_MAX) / 2);
			current_mana = 0;
			_gameLOG.push_back(getPlayerString() + ": " + name + " " + getDisplayCoords(position) + " used Revive on " + _myDeathUnits[_indexToRevive]->getName() + " " + getDisplayCoords(_myDeathUnits[_indexToRevive]->getPosition()) + "\n");
			return true;
		}
		else
		{
			try_++;
			_myDeathUnits.erase(_myDeathUnits.begin() + _indexToRevive);
		}
	}
	return false;

}
