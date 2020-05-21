#pragma once
#include "ProfessionsLibrary.h"
#include "Mage.h"
class ProfessionsFactory
{
	ProfessionsLibrary* library;


public:
	ProfessionsFactory();
	Profession* createUnit(int _id);
	ProfessionsLibrary* getProfLibrary();

};