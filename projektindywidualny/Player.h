#pragma once
#include <vector>
class Profession;
class Player
{
	std::vector<Profession*> units;
	int gold;
	int id;
public:
	Player(int _id);
	void buyUnit(Profession* _unit);
	


	std::vector<Profession*> getUnits();

	void moveUnit(Profession* _myUnit,std::pair<int,int> _pos);
	void attackUnit(Profession* _myUnit, Profession* _unitToAttack);
	int getID();
	int getGold();

};