#include "Player.h"
#include "Profession.h"
#include <cctype>

Player::Player(int _id)
{
	id = _id;
	gold = 900;
}
void Player::buyUnit(Profession* _unit)
{
	if (id == 1) _unit->setDisplayChar(tolower(_unit->getDisplayChar()));
	units.push_back(_unit);
}


std::vector<Profession*> Player::getUnits()
{
	return units;
}


void Player::moveUnit(Profession* _myUnit, std::pair<int, int> _pos)//sprawdzac w game handler czy na x i y nic nie stoi
{
	 //blad
	_myUnit->setPosition(_pos);

}
void Player::attackUnit(Profession* _myUnit, Profession* _unitToAttack)
{
//	if (_myUnit->getPlayer() != this) return;
//	if (_unitToAttack->getPlayer() == this) return;
	_myUnit->attack(_unitToAttack);
}

int Player::getID()
{
	return id;
}

int Player::getGold()
{
	return gold;
}