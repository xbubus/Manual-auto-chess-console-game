#include "ProfessionsLibrary.h"
void ProfessionsLibrary::loadDataFromFile()
{
	//if (professionsData.str().size() == 0) std::cout << "ASDASDASD";


	
	std::ifstream file("stats.txt");
	if (file)
	{
		professionsData << file.rdbuf();

		file.close();


	}
}

void ProfessionsLibrary::findNamesAndCosts()
{
	std::string startList = "PROFESSIONS_LIST"; 
	std::string stop = "STOP";
	int startIndex = professionsData.str().find(startList);
	int endIndex = professionsData.str().find(stop, startIndex);

	std::string profData = professionsData.str().substr(startIndex + startList.size(), endIndex-startList.size()-startIndex);
	std::istringstream profDataStream(profData);
	std::string line;
	std::cout << profData;
	while (std::getline(profDataStream, line))
	{
		std::cout << 0;
		int temp = line.find(":");
		if (line.size() > 0)
		{
			std::string name = line.substr(0, temp);
			professionsNamesAndCost.push_back(std::make_pair(name, std::stoi(line.substr(temp + 1))));
		}
		
	}



}

void ProfessionsLibrary::setupProfessionsStats()
{
	std::string firstName = "STATS";
	int firstIndex = professionsData.str().find(firstName);
	for (auto prof : professionsNamesAndCost)
	{
	//	std::cout << "NEWFOR: " << prof.first << std::endl;
		std::string startList = prof.first;
		std::string stop = "STOP";
		int startIndex = professionsData.str().find(startList,firstIndex);
		int endIndex = professionsData.str().find(stop, startIndex+startList.size());

		std::string profData = professionsData.str().substr(startIndex + startList.size(), endIndex - startIndex - startList.size());
		std::istringstream profDataStream(profData);
		std::string line;
		std::cout << profData;
		std::vector<std::pair<std::string, int>> tempVect;


		tempVect.clear();

		std::map<int, double> currentProfStats;

		while (std::getline(profDataStream, line))
		{
			std::cout << " ";
			int temp = line.find(":");
			if (temp > 0)
			{
				std::string statName = line.substr(0, temp);
				tempVect.push_back(std::make_pair(statName, std::stoi(line.substr(temp + 1))));
			//	std::cout << statName << " " << std::stoi(line.substr(temp + 1) )<< "\n";
				currentProfStats[convertStats(statName)] = std::stoi(line.substr(temp + 1));
			}

		}
		professionsNamesAndData.push_back(std::make_pair(prof.first,tempVect));
		professionsConfig[convertProf(prof.first)] = currentProfStats;
		currentProfStats.clear();
	

	}
	/*
	std::cout << "chuj1";
	for (auto v1 : professionsNamesAndData)
	{
		std::cout << v1.first << std::endl;
		for (auto v2 : v1.second)
		{
			std::cout << v2.first << " " << v2.second << std::endl;
		}
	}
	*/
}

void ProfessionsLibrary :: displayStats()

{
	std::cout << "Stats:\n";
	for (auto a : professionsConfig)
	{
	
		std::cout << getProfName(a.first) << std::endl;;
		for (auto b : a.second)
		{
			std::cout << b.first << " "<<b.second<<std::endl;
		}
	}
	//std::cout << "STATS:\n";
	//for (auto v1 : professionsNamesAndData)
	//{
	//	std::cout << v1.first << std::endl;
	//	for (auto v2 : v1.second)
	//	{
	//		std::cout << v2.first << " " << v2.second << std::endl;
	//	}
	//}
}

std::map<int, double > ProfessionsLibrary::getProfessionData(int _id)
{
	return professionsConfig[_id];
}

std::string ProfessionsLibrary::getProfName(int _id)
{
	if (_id == MAGE) return "Mage";
	if (_id == WARRIOR) return "Warrior";
	if (_id == POPE) return "Ork";
}
void ProfessionsLibrary::displayUnitsAndCosts()
{
	int id = 0;
	for (auto unit : professionsNamesAndCost)
	{
		std::cout <<"ID: "<<convertProf(unit.first)<<" Name: " << unit.first << " Cost: " << unit.second << " gold.\n";
	}
}
int ProfessionsLibrary::convertStats(std::string _statName) //znalezc lepsze miejsce
{
	if (_statName == "hp_max")return 0;
	if (_statName == "mana_max")return 1;
	if (_statName == "ad")return 2;
}

int ProfessionsLibrary::getProfessionCost(int _id)
{
	return professionsNamesAndCost[_id].second;
}

int ProfessionsLibrary::convertProf(std::string _name) //znalezc lepsze miejsce
{
	if (_name == "Mage")return 0;
	if (_name == "Warrior")return 1;
	if (_name == "Ork")return 2;
}

