#include "ProfessionsLibrary.h"
void ProfessionsLibrary::loadDataFromFile()
{
	std::ifstream file("stats.txt");
	if (file.is_open())
	{
		professionsData << file.rdbuf();
		file.close();
	}
	else
	{
		throw "CANNOT_OPEN_FILE";	
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
	while (std::getline(profDataStream, line))
	{
		int temp = line.find(":");
		if (line.size() > 0)
		{
			std::string name = line.substr(0, temp);
			professionsNamesAndCost.push_back(std::make_pair(name, std::stoi(line.substr(temp + 1))));
		}
		
	}
#ifdef DEBUG
	displayUnitsAndCosts();
#endif


}

void ProfessionsLibrary::setupProfessionsStats()
{
	std::string firstName = "STATS";
	int firstIndex = professionsData.str().find(firstName);
	for (auto prof : professionsNamesAndCost)
	{
#ifdef DEBUG
		std::cout << "NEWFOR: " << prof.first << std::endl;
#endif
		std::string startList = prof.first;
		std::string stop = "STOP";
		int startIndex = professionsData.str().find(startList,firstIndex);


		int endIndex = professionsData.str().find(stop, startIndex+startList.size());

		std::string profData = professionsData.str().substr(startIndex + startList.size(), endIndex - startIndex - startList.size());
		std::istringstream profDataStream(profData);
		std::string line;
#ifdef DEBUG
		std::cout << profData;
#endif
		std::vector<std::pair<std::string, double>> tempVect;


		tempVect.clear();

		std::map<int, double> currentProfStats;

		while (std::getline(profDataStream, line))
		{
			int temp = line.find(":");
			if (temp > 0)
			{
				std::string statName = line.substr(0, temp);
				tempVect.push_back(std::make_pair(statName, std::stod(line.substr(temp + 1))));// chyba wyjebac
		
				currentProfStats[convertStats(statName)] = std::stod(line.substr(temp + 1));
#ifdef DEBUG
				std::cout << statName << " readed: " << std::stod(line.substr(temp + 1) )<< "\n";
				std::cout << currentProfStats[convertStats(statName)] << " <-saved\n";
#endif
			}

		}
		professionsConfig[convertProf(prof.first)] = currentProfStats;
		currentProfStats.clear();
		

	}
#ifdef DEBUG
	displayStats();
#endif

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

}

std::map<int, double > ProfessionsLibrary::getProfessionData(int _id)
{
	int i = 0;
	for (auto confData : professionsConfig)
	{
		if(confData.first==_id) return professionsConfig[i];
		i++;
	}

}

std::string ProfessionsLibrary::getProfName(int _id)
{
	if (_id == MAGE) return "Mage";
	if (_id == SNIPER) return "Sniper";
	if (_id == WARRIOR) return "Warrior";
	if (_id == POPE) return "Pope";
	if (_id == ARCHER) return "Archer";
	if (_id == DRUID) return "Druid";
	if (_id == CATCHER) return "Catcher";
	throw "Invalid_ID";
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
	if (_statName == "hp_max")return HP_MAX;
	if (_statName == "mana_max")return MANA_MAX;
	if (_statName == "mana_per_round")return MANA_PER_ROUND;
	if (_statName == "starting_mana")return STARTING_MANA;
	if (_statName == "ad")return AD;
	if (_statName == "ar")return AR;
	if (_statName == "mr")return MR;
	if (_statName == "s_p_var") return S_P_VAR;
	return -1;
};

int ProfessionsLibrary::getProfessionCost(int _id)
{
	for (auto confData : professionsNamesAndCost)
	{
		if (confData.first == getProfName(_id)) return confData.second;
		
	}
	//nie mozliwe jest zeby _id podane do tej funkcji bylo niepoprawne
}

int ProfessionsLibrary::convertProf(std::string _name) 
{
	if (_name == "Mage")return MAGE;
	if (_name == "Sniper")return SNIPER;
	if (_name == "Warrior")return WARRIOR;
	if (_name == "Pope")return POPE;
	if (_name == "Archer")return ARCHER;
	if (_name == "Druid")return DRUID;
	if (_name == "Catcher")return CATCHER;
	throw "Invalid_Name";
}

