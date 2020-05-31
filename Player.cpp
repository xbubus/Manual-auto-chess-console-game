#include "Player.h"
#include "Profession.h"
#include <cctype>



Player::Player(int _id)
{
	id = _id;
	gold = 900;
	name = "P" +std::to_string(_id+1);
}
void Player::buyUnit(Profession* _unit,int _cost)
{
	if (id == 1) _unit->setDisplayChar(tolower(_unit->getDisplayChar()));
	units.push_back(_unit);
	gold = gold - _cost;
}


std::vector<Profession*> Player::getUnits()
{
	return units;
}


bool Player::moveUnit(Profession* _myUnit, char _posData[][10], std::vector<std::string>& _gameLOG)
{
	bool finished = false;
	std::pair<int, int>startCoords = _myUnit->getPosition();
	int currX = startCoords.first;
	int currY = startCoords.second;
	_myUnit->findPossibleMoves(_posData);
	std::cout << "Use arrows to move your unit\npress enter when finished\n\n";

	while (!finished)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case KEY_UP:
				
				if (_myUnit->checkIfValidMove(std::make_pair(currX, currY - 1)))
				{
					currY -= 1;
					_myUnit->setPosition(std::make_pair(currX, currY));
					std::cout << "\033[F"; //cofam linie w coucie
					std::cout << "Your unit is now on: "<<_myUnit->getPosition()<<"\n";
				}
				break;
			case KEY_DOWN:
			//	std::cout << "DOWN!\n";
				if (_myUnit->checkIfValidMove(std::make_pair(currX, currY + 1)))
				{
					currY += 1;
					_myUnit->setPosition(std::make_pair(currX, currY));
					std::cout << "\033[F"; //cofam linie w coucie
					std::cout << "Your unit is now on: " << _myUnit->getPosition() << "\n";
				}
				break;
			case KEY_LEFT:
				//std::cout << "LEFT!\n";
				if (_myUnit->checkIfValidMove(std::make_pair(currX-1, currY )))
				{
					currX -= 1;
					_myUnit->setPosition(std::make_pair(currX, currY));
					std::cout << "\033[F"; //cofam linie w coucie
					std::cout << "Your unit is now on: " << _myUnit->getPosition() << "\n";
				}
				break;
			case KEY_RIGHT:
			//	std::cout << "RIGHT!\n";
				if (_myUnit->checkIfValidMove(std::make_pair(currX+1, currY)))
				{
					currX += 1;
					_myUnit->setPosition(std::make_pair(currX, currY));
					std::cout << "\033[F"; //cofam linie w coucie
					std::cout << "Your unit is now on: " << _myUnit->getPosition() << "\n";
				}
				break;
			case '\r':
				finished = true;
				break;
			}
		}
	}

	if (startCoords == _myUnit->getPosition()) return false;

	_gameLOG.push_back(name + ": " + _myUnit->getName() + " moved from " + _myUnit->getDisplayCoords(startCoords) + " to " + _myUnit->getDisplayCoords(_myUnit->getPosition()) + "\n");
	return true;
	
		
}
template <typename T>
std::string to_string_with_precision_0(const T a_value) //gdzie to dac
{
	std::ostringstream out;
	int n = 0;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}
bool Player::attackUnit(Profession* _myUnit, char _posData[][10], Profession* _boardData[][10], std::vector<std::string>& _gameLOG)
{

	bool isThereUnitToAttack = false;
	isThereUnitToAttack = _myUnit->findPossibleCordsToAttack(_posData,id);

	if (!isThereUnitToAttack)
	{
		std::cout << "There is no unit to attack in your range!\n";
		return false;
	}
	_myUnit->displayPossibleAttack();
	int idToAttack = -2;
	while (true)
	{
		std::cout << "Enter ID to attack or -1 to go back\n";
		idToAttack=getValidInput<int>();
		if (idToAttack == -1) return false;
		if (_myUnit->checkIfValidIdToAttack(idToAttack))
		{
			int xCordToAttack = _myUnit->getPossibleAttackCords(idToAttack).first;
			int yCordToAttack = _myUnit->getPossibleAttackCords(idToAttack).second;
			_myUnit->attack(_boardData[xCordToAttack][yCordToAttack]);
			_gameLOG.push_back(name + ": " + _myUnit->getName()+" "+ _myUnit->getDisplayCoords(_myUnit->getPosition()) +" attacked "+ _boardData[xCordToAttack][yCordToAttack]->getName() + " "+_myUnit->getDisplayCoords(_boardData[xCordToAttack][yCordToAttack]->getPosition())+"\n");
			return true;
		}
		std::cout << "You cant attack unit with this id, try again\n";
	}

}



bool Player::useSuperPower(Profession* _myUnit, std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, char _posData[][10], std::vector<std::string>& _gameLOG)
{
	if (_myUnit->getCurrentMana() < _myUnit->getStat(MANA_MAX))
	{
		std::cout << "Not enough mana\n";
		return false;
	}
	return _myUnit->useSuperPower(_myPlayerUnits, _enemyPlayerUnits, _posData,_gameLOG);
}

int Player::getID()
{
	return id;
}

int Player::getGold()
{
	return gold;
}

void Player::doSomethingWithUnit(Profession* _myUnit, char _posData[][10], Profession* _boardData[][10], std::vector<Profession*> _myPlayerUnits, std::vector<Profession*> _enemyPlayerUnits, std::vector<std::string>& _gameLOG)
{
	int choice = 0;
	bool madeValidMove = false;
	std::cout << "Unit: " << _myUnit->getName() << " on coords: " << _myUnit->getPosition().first << "," << _myUnit->getPosition().second << std::endl; //sprobowac napisac operator do wysietlania paira
	std::cout << "1-> Move \n2-> Attack \n3-> Use superpower\n4-> Wait\n";
	while (!madeValidMove)
	{
		
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			madeValidMove = moveUnit(_myUnit, _posData, _gameLOG);
			break;
		case 2:
			madeValidMove = attackUnit(_myUnit, _posData, _boardData, _gameLOG);
			break;
		case 3:
		
				madeValidMove = useSuperPower(_myUnit,_myPlayerUnits, _enemyPlayerUnits,_posData,_gameLOG);
			
				
			break;
		case 4:
			madeValidMove = true;
			_gameLOG.push_back(name + ": " + _myUnit->getName() + " " + _myUnit->getDisplayCoords(_myUnit->getPosition()) + " didnt take any action\n");
			break;
		default:
			std::cout << "Invalid choice, try again\n";
			break;
		}
	}
}

