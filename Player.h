#pragma once
#include <vector>
#include <conio.h>
#include <string>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
class Profession;
class Player
{
	std::vector<Profession*> units;
	int gold;
	int id;
	std::string name;
public:
	Player(int _id);
	void buyUnit(Profession* _unit, int _cost);
	


	std::vector<Profession*> getUnits();

	bool moveUnit(Profession* _myUnit, char _posData[][10], std::vector<std::string>& _gameLOG); //tutaj dac azmiast 10 define
	bool attackUnit(Profession* _myUnit, char _posData[][10],Profession* _boardData[][10], std::vector<std::string>& _gameLOG);
	bool useSuperPower(Profession* _myUnit, std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][10], std::vector<std::string>& _gameLOG);
	int getID();
	int getGold();
	void doSomethingWithUnit(Profession* _myUnit, char _posData[][10], Profession* _boardData[][10], std::vector<Profession*> myPlayerUnits, std::vector<Profession*> enemyPlayerUnits,std::vector<std::string>& _gameLOG);


};