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
		temp = library->getProfessionData(MAGE);
		return new Mage(temp);

	}
}

ProfessionsLibrary* ProfessionsFactory::getProfLibrary()
{
	return library;
}
