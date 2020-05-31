#pragma once
#include <string>
#include <vector>
#include <iostream>
#include  <sstream>
#include  <map>
#include <fstream>
#include "Profession.h"





class ProfessionsLibrary {
	std::stringstream professionsData;
	std::vector<std::pair <std::string, int>> professionsNamesAndCost;


	std::vector<std::pair <std::string,std::vector< std::pair <std::string,double>>>> professionsNamesAndData; //stary sposob, usunac jak nowy okaze sie ok
	
	
	std::map <int, std::map<int, double >> professionsConfig; //mapa wszystkich statow profesji zczytana z pliku




public:
	void loadDataFromFile();
	void findNamesAndCosts();
	void setupProfessionsStats();
	void displayStats();
	Profession* makeUnit(std::string _name);
	std::map<int, double > getProfessionData(int _id);
	std::string getProfName(int _id);
	void displayUnitsAndCosts();
	int convertStats(std::string _statName);
	int getProfessionCost(int _id);


	int convertProf(std::string _name);
	
};


