#pragma once
#include "ProfessionsLibrary.h"
#include "professions\Mage.h"
#include "professions\Warrior.h"
#include "professions\Pope.h"
#include "professions\Sniper.h"
#include "professions\Archer.h"
#include "professions\Catcher.h"
#include "professions\Druid.h"
class ProfessionsFactory
{
	ProfessionsLibrary* library;


public:
	ProfessionsFactory();
	~ProfessionsFactory();
	void init();
	Profession* createUnit(int _id);
	ProfessionsLibrary* getProfLibrary();
	void displayUnitsAndCosts();
	int getCost(int _id);

};

//ta klasa odpowiedzialna jest za tworzenie jednostek