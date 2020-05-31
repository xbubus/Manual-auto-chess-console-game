#include "ProfessionsLibrary.h"
void ProfessionsLibrary::loadDataFromFile()
{
	//if (professionsData.str().size() == 0) std::cout << "ASDASDASD";


	
	std::ifstream file("stats.txt");
	if (file)// TODO: zabezpieczenie
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
	//std::cout << profData;
	while (std::getline(profDataStream, line))
	{
		//std::cout << 0;
		int temp = line.find(":");
		if (line.size() > 0)
		{
			std::string name = line.substr(0, temp);
			professionsNamesAndCost.push_back(std::make_pair(name, std::stoi(line.substr(temp + 1))));
		}
		
	}
	//displayUnitsAndCosts();


}

void ProfessionsLibrary::setupProfessionsStats()
{
	std::string firstName = "STATS";
	int firstIndex = professionsData.str().find(firstName);
	for (auto prof : professionsNamesAndCost)
	{
		//std::cout << "NEWFOR: " << prof.first << std::endl;
		std::string startList = prof.first;
		std::string stop = "STOP";
		int startIndex = professionsData.str().find(startList,firstIndex);


		int endIndex = professionsData.str().find(stop, startIndex+startList.size());

		std::string profData = professionsData.str().substr(startIndex + startList.size(), endIndex - startIndex - startList.size());
		std::istringstream profDataStream(profData);
	//	std::cout << profData;
		std::string line;
	//	std::cout << profData;
		std::vector<std::pair<std::string, double>> tempVect;


		tempVect.clear();

		std::map<int, double> currentProfStats;

		while (std::getline(profDataStream, line))
		{
			//std::cout << " ";
			int temp = line.find(":");
			if (temp > 0)
			{
				std::string statName = line.substr(0, temp);
				tempVect.push_back(std::make_pair(statName, std::stod(line.substr(temp + 1))));// chyba wyjebac
		//		std::cout << statName << " readed: " << std::stod(line.substr(temp + 1) )<< "\n";
				currentProfStats[convertStats(statName)] = std::stod(line.substr(temp + 1));
			//	std::cout << currentProfStats[convertStats(statName)] << " <-saved\n";
			}

		}
		//professionsNamesAndData.push_back(std::make_pair(prof.first,tempVect));
		professionsConfig[convertProf(prof.first)] = currentProfStats;
//		std::cout << "\"" << prof.first << "\""<< convertProf(prof.first)<<"\n";
		currentProfStats.clear();
		

	}
	//displayStats();
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
	int i = 0;
	for (auto confData : professionsConfig)
	{
//	std::cout << "Prof id: "<<confData.first<<" AR: "<<confData.second[AR]<<"\n";
		if(confData.first==_id) return professionsConfig[i];
		i++;

		//zabez
	}
//	system("sleep");
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
	return -1;// sprawdzic jak sie zachowuje
}

int ProfessionsLibrary::getProfessionCost(int _id)
{
	for (auto confData : professionsNamesAndCost)
	{
		if (confData.first == getProfName(_id)) return confData.second;
		
	}
}

int ProfessionsLibrary::convertProf(std::string _name) //znalezc lepsze miejsce
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

