#pragma once
#include "Profession.h"
#include <conio.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
class Player
{
	std::vector<Profession*> units;
	int gold;
	int id;
	std::string name;
	bool moveUnit(Profession* _myUnit, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG); 
	bool attackUnit(Profession* _myUnit, char _posData[][BOARD_SIZE], Profession* _boardData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
	bool useSuperPower(Profession* _myUnit, std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][BOARD_SIZE], std::vector<std::string>& _gameLOG);
public:
	Player(int _id);
	void buyUnit(Profession* _unit, int _cost);
	std::vector<Profession*>& getUnits();
	int getID();
	int getGold();
	void doSomethingWithUnit(Profession* _myUnit, char _posData[][BOARD_SIZE], Profession* _boardData[][BOARD_SIZE], std::vector<Profession*> myPlayerUnits, std::vector<Profession*> enemyPlayerUnits,std::vector<std::string>& _gameLOG, bool& _gameON);


};

//Jesli gracz zdecyduje sie ruszyc jednostke ale nie zmieni jej pozycji nie traci ruchu. Jesli gracz uzyje ulta ale nie moze on zostac uzyty(np Papiez nie moze wskrzesic jednostke jesli
// na polu na ktorym umarla stoi  inna jednostka) nie traci ruchu.