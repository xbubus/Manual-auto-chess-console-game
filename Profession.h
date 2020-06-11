#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
//te rzeczy chcia³em trzymaæ w enumach ale mia³em bledy linkera i zdecydowa³em siê na takie rozwi¹zanie
#define BOARD_SIZE 10
#define MAGE 0
#define SNIPER 1
#define WARRIOR 2
#define POPE 3
#define ARCHER 4
#define DRUID 5
#define	CATCHER 6
#define HP_MAX 0
#define MANA_MAX 1
#define MANA_PER_ROUND 2
#define STARTING_MANA 3
#define AD 4
#define AR 5 //attack range
#define MR 6// movement range
#define S_P_VAR 7 //super power variable //w zaleznosci od postaci -si³a ataku z supermocy, za ile leczy itp.
// co mozna dodac: umiejetnosc pasywna, hp regen co runde
class Profession
{
protected:
	int current_hp; 
	int current_mana;
	std::map<int, double> stats;
	std::pair<int, int> position;
	std::vector <std::pair<int, int>> possibleMoves;
	std::vector <std::pair<int, int>> possibleAttack;
	bool alive;
	bool stunned;
	char displayChar;
	std::string name;
	Profession* findFarthestEnemyUnit(std::vector<Profession*> _enemyPlayerUnits);
	bool areMyPlayerUnitsDisplayedLower();
	std::string getPlayerString();
public:
	double getStat(int _id);
	bool getStunned();
	void setStunned(bool _stunned);
	void setPosition(std::pair<int, int> _pos);
	std::pair<int, int> getPosition();
	char getDisplayChar();
	void setDisplayChar(char _c);
	void setCurrentHP(int _hp);
	void attack(Profession* _profToAttack);
	void takeDamage(int _damage);
	bool isAlive();
	void setAlive(bool _alive);
	void updateStatsAfterRound();
	std::string getName();
	void findPossibleMoves(char _posData[][BOARD_SIZE]); //define board size
	void displayPossibleMoves();
	bool checkIfValidMove(std::pair<int,int> _cords);
	bool checkIfValidIdToAttack(int _id);
	bool findPossibleCordsToAttack(char _posData[][BOARD_SIZE],int _id);
	void displayPossibleAttack();
	std::pair<int, int> getPossibleAttackCords(int _i);
	int getCurrentHP();
	int getCurrentMana();
	void setCurrentMana(int _mana);
	virtual bool useSuperPower(std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][10], std::vector<std::string>& _gameLOG)=0;
	std::string getDisplayCoords(std::pair<int, int> _coords);

};

inline std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& pair)
{
	return os << "[" << pair.first << "," << pair.second << "]";
}


template <typename T> 
T getValidInput()
{
	T input;
	while (true)
	{
		std::cin >> input;
		if (std::cin.fail() == true)
		{
			std::cout << "Not valid input, try again\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
			return input;
		
	}
}


//profession do klasa abstrakcyjna