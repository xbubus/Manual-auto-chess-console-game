#include "Profession.h"
#include "Player.h"




double Profession::getStat(int  _id)
{
	return stats[_id];
		
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


void Profession::attack(Profession* _profToAttack)
{
	_profToAttack->takeDamage(getStat(AD));
}

void Profession::takeDamage(int _damage) 
{
	std::cout << current_hp;
	current_hp = current_hp - _damage;
	if (current_hp <= 0)
	{
		current_hp = 0;
		alive = false;
	}
	std::cout << current_hp;
}

bool Profession::isAlive()
{
	return alive;
}

//void Profession::updateStatsAfterRound()
//{
//	hp += hp_per_round;
//	if (hp > hp_max) hp = hp_max;
//	mana += mana_per_round;
//	if (mana > mana_max) mana = mana_max;
//}

std::string Profession::getName()
{
	return name;
}