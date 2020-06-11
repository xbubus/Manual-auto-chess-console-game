#include "Profession.h"

#include <cctype>




Profession* Profession::findFarthestEnemyUnit(std::vector<Profession*> _enemyPlayerUnits)
{
	Profession* farthest = _enemyPlayerUnits[0];
	for (auto unit : _enemyPlayerUnits)
	{
		if (sqrt(pow(farthest->getPosition().first - position.first, 2) + pow(farthest->getPosition().second - position.first, 2)) < sqrt(pow(unit->getPosition().first - position.first, 2) + pow(unit->getPosition().second - position.first, 2)))
		{
			farthest=unit;
		}
	}
	return farthest;
}
bool Profession::areMyPlayerUnitsDisplayedLower()
{
	return islower(getDisplayChar());
}
std::string Profession::getPlayerString()
{
	std::string playerString;
	if (areMyPlayerUnitsDisplayedLower()) playerString = "P2";
	else playerString = "P1";

	return playerString;
}

double Profession::getStat(int  _id)
{
	return stats[_id];

}
bool Profession::getStunned()
{
	return stunned;
}
void Profession::setStunned(bool _stunned)
{
	stunned = _stunned;
}
void Profession::setPosition(std::pair<int, int> _pos)
{
	position = _pos;
}
std::pair<int, int> Profession::getPosition()
{
	return position;
}
char Profession::getDisplayChar()
{
	return displayChar;
}
void Profession::setDisplayChar(char _c)
{
	displayChar = _c;
}
void Profession::setCurrentHP(int _hp)
{
	current_hp = _hp;
}
void Profession::attack(Profession* _profToAttack)
{
	_profToAttack->takeDamage(getStat(AD));
}
void Profession::takeDamage(int _damage) 
{
	if (!alive)return;
	current_hp = current_hp - _damage;
	if (current_hp <= 0)
	{
		current_hp = 0;
		alive = false;
	}
	
}
bool Profession::isAlive()
{
	return alive;
}
void Profession::setAlive(bool _alive)
{
	alive = _alive;
}
void Profession::updateStatsAfterRound()
{
	
	current_mana += getStat(MANA_PER_ROUND);
	if (current_mana > getStat(MANA_MAX)) current_mana = getStat(MANA_MAX);
}
std::string Profession::getName()
{
	return name;
}
void Profession::findPossibleMoves(char _posData[][BOARD_SIZE])
{
	possibleMoves.clear();
	double range = getStat(MR);
	int posX = position.first;
	int posY = position.second;

	for (int i = 0; i < BOARD_SIZE; i++) 
	{
		for (int j = 0; j < BOARD_SIZE; j++) 
		{
			double dist = sqrt(((i - posX) * (i - posX)) + ((j - posY) * (j - posY)));
			if (dist <= range&&_posData[i][j]==' ')
			{
				possibleMoves.push_back(std::make_pair(i, j));
			}
		}
	}
	possibleMoves.push_back(position);
}
void Profession::displayPossibleMoves()
{
	std::cout << "Possible coords to move:\n";
	for (auto cord : possibleMoves)
	{
		std::cout << "[" << cord.first << "," << cord.second << "] ";

	}
	std::cout << "\n";
}
bool Profession::checkIfValidMove(std::pair<int, int> _cords)
{
	for (auto cord : possibleMoves)
	{
		if (_cords == cord) return true;
	}
	return false;
}
bool Profession::checkIfValidIdToAttack(int _id)
{
	if (_id >= 0 && _id < possibleAttack.size()) return true;
	return false;
}
bool Profession::findPossibleCordsToAttack(char _posData[][BOARD_SIZE], int _id)
{
	possibleAttack.clear();
	double range = getStat(AR);
	int posX = position.first;
	int posY = position.second;
	bool temp=false;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++) 
		{
			double dist = sqrt(((i - posX) * (i - posX)) + ((j - posY) * (j - posY)));
			if (dist <= range && _posData[i][j] != ' ')
			{
				if ((_id == 0 && islower(_posData[i][j])) || (_id == 1 && isupper(_posData[i][j])))
				{
					possibleAttack.push_back(std::make_pair(i, j));
					temp = true;
				}

			}
		}
	}
	return temp;
}
void Profession::displayPossibleAttack()
{
	std::cout << "Possible coords to attack:\n";
	int i = 0;
	for (auto cord : possibleAttack)
	{
		std::cout << "ID: "<<i++<<cord<<" ";
	

	}
	std::cout << "\n";
}
std::pair<int, int> Profession::getPossibleAttackCords(int _id)
{
	return possibleAttack[_id];
}
int Profession::getCurrentHP()
{
	return current_hp;
}
int Profession::getCurrentMana()
{
	return current_mana;
}
void Profession::setCurrentMana(int _mana)
{
	current_mana = _mana;
}
std::string Profession::getDisplayCoords(std::pair<int, int> _coords)
{
	std::stringstream coordsToPrint;
	coordsToPrint << _coords;
	return coordsToPrint.str();
}


