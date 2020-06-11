#pragma once
#include "Profession.h"


//#define DEBUG //odkomentowac w celu sprawdzenia poprawnosci wczytanych statow, 


class ProfessionsLibrary {
	std::stringstream professionsData; //dane z pliku
	std::vector<std::pair <std::string, int>> professionsNamesAndCost; //wektor przechowuj¹cy nazwe profesji i jej koszt
	std::map <int, std::map<int, double >> professionsConfig; //mapa wszystkich statow profesji zczytana z pliku




public:
	void loadDataFromFile();
	void findNamesAndCosts();
	void setupProfessionsStats();
	void displayStats();
	std::map<int, double > getProfessionData(int _id);
	std::string getProfName(int _id);
	void displayUnitsAndCosts();
	int convertStats(std::string _statName);
	int getProfessionCost(int _id);
    int convertProf(std::string _name);
	
};

//klasa jest odpowiedzialna za zczytanie statow z pliku i zmapowanie ich
