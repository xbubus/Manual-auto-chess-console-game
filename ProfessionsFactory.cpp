#include "ProfessionsFactory.h"



ProfessionsFactory::ProfessionsFactory()
{
	library = new ProfessionsLibrary;
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
	//	std::cout << _id << "\n";
		temp = library->getProfessionData(MAGE);
		return new Mage(temp);
	case WARRIOR:
	//	std::cout << _id << "\n";
		temp = library->getProfessionData(WARRIOR);
		return new Warrior(temp);
	case DRUID:
	//	std::cout << _id << "\n";
		temp = library->getProfessionData(DRUID);
		return new Druid(temp);
	case ARCHER:
	//	std::cout << _id << "\n";
		temp = library->getProfessionData(ARCHER);
		return new Archer(temp);
	case CATCHER:
	//	std::cout << _id << "\n";
		temp = library->getProfessionData(CATCHER);
		return new Catcher(temp);
	case SNIPER:
	//	temp = library->getProfessionData(SNIPER);
		return new Sniper(temp);
	case POPE:
	//	std::cout << _id << "\n";
		temp = library->getProfessionData(POPE);
		return new Pope(temp);
	default:
		std::cout << "Invaid ID\n"; //wyjatek?
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
