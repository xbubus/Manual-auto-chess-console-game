#pragma once
#include <string>
#include <iostream>
#include  <sstream>
#include <map>
#include <fstream>


#define MAGE  0
#define WARRIOR  1
#define POPE  2




#define HP_MAX 0
#define MANA_MAX 1
#define AD  2
//znalezc lepsze miejsce na te define
class Player;

//atrybuty do dodania : aktualne hp, aktualna mana, zasieg ataku, koszt umiejetnosci specjalnej...

//dodac umiejetnosc specjalna, jako zbior metod i atrybutow lub osobna klase
// umiejetnosc pasywna? jakis hp regen, zwiekszanie ad

// ogarnac czy da sie sensownie przetrzymywac wszystkie staty w mapie stats
class Profession
{
protected:
	int current_hp; 
	std::map<int, double> stats;
	std::pair<int, int> position;
	bool alive;
	char displayChar;
	std::string name;
//	std::stringstream professionsData; // nie potrzebne 
//	Player* player;
	
public:

	double getStat(int _id);
	
	void setPosition(std::pair<int, int> _pos);
	std::pair<int, int> getPosition();
	char getDisplayChar();
	void setDisplayChar(char _c);
	//Player* getPlayer();
	void attack(Profession* _profToAttack);
	void takeDamage(int _damage);
	bool isAlive();
	void updateStatsAfterRound();
	std::string getName();



	

	


};
