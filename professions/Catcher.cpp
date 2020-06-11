#include "Catcher.h"


Catcher::Catcher(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'C';
	name = "Catcher";
	current_hp = getStat(HP_MAX);
	alive = true;
	current_mana = getStat(STARTING_MANA);
}

std::pair<int, int> Catcher::findFreePositionNearMe(char _posData[][BOARD_SIZE])
{
	std::pair <int, int> nearest=std::make_pair(-1,-1);
	for (int i = position.first-1; i <= position.first +1; i++)
	{
		for (int j = position.second-1; j <=position.second+1; j++)
		{
			if (i >= 0 && i <= BOARD_SIZE-1 && j >= 0 && j <= BOARD_SIZE-1)
			{
				if (_posData[i][j] == ' ')
				{
					if (position.second < 5) //oczekuje ze przyciagniety unit bedzie z przodu catchera
					{
						if (j == position.second + 1)
						{
							nearest = std::make_pair(i, j);
							return nearest;
						}
						else nearest = std::make_pair(i, j); //jesli nie da sie z przodu biore cokolwiek

					}
					if (position.second >= 5) //oczekuje ze przyciagniety unit bedzie z przodu catchera
					{
						if (j == position.second - 1)
						{
							nearest = std::make_pair(i, j);
							return nearest;
						}
						else nearest = std::make_pair(i, j); //jesli nie da sie z przodu biore cokolwiek

					}
				}
			}
		}
	}
	return nearest; //jesli nie ma wolnego miejsca z przodu zwracam jakies miejsce z tylu, jesli nie ma zadnego zwracam -1,-1
}


bool Catcher::useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG)
{
	
		std::pair<int, int> freeNearPos = findFreePositionNearMe(_posData);
		if (freeNearPos.first == -1) return false; //nie mozna uzyc ulta, nie ma miejsca obok catchera
		Profession* farthestEnemyUnit = findFarthestEnemyUnit(_enemyPlayerUnits);
		farthestEnemyUnit->setPosition(freeNearPos);
		farthestEnemyUnit->takeDamage(getStat(S_P_VAR));
		current_mana = 0;
		_gameLOG.push_back(getPlayerString() + ": " + name + " " + getDisplayCoords(position) + " used Grab on " + farthestEnemyUnit->getName()+" "+getDisplayCoords(farthestEnemyUnit->getPosition()) + "\n");
		return true;
}
