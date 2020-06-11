#include "ProfessionsFactory.h"



ProfessionsFactory::ProfessionsFactory()
{
	library = new ProfessionsLibrary;
	
}

ProfessionsFactory::~ProfessionsFactory()
{
	delete library;
}

void ProfessionsFactory::init()
{
	library->loadDataFromFile();
	library->findNamesAndCosts();
	library->setupProfessionsStats();
}


Profession* ProfessionsFactory::createUnit(int _id)
{
	std::map<int, double> temp;

	switch (_id)
	{
	case MAGE:
		temp = library->getProfessionData(MAGE);
		return new Mage(temp);
	case WARRIOR:
		temp = library->getProfessionData(WARRIOR);
		return new Warrior(temp);
	case DRUID:
		temp = library->getProfessionData(DRUID);
		return new Druid(temp);
	case ARCHER:
		temp = library->getProfessionData(ARCHER);
		return new Archer(temp);
	case CATCHER:
		temp = library->getProfessionData(CATCHER);
		return new Catcher(temp);
	case SNIPER:
		temp = library->getProfessionData(SNIPER);
		return new Sniper(temp);
	case POPE:

		temp = library->getProfessionData(POPE);
		return new Pope(temp);
	default:
		return nullptr; 

	}
}

ProfessionsLibrary* ProfessionsFactory::getProfLibrary()
{
	return library;
}

void ProfessionsFactory::displayUnitsAndCosts()
{
	library->displayUnitsAndCosts();
}

int ProfessionsFactory::getCost(int _id)
{
	return library->getProfessionCost(_id);
}
