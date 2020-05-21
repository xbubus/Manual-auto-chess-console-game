#include "Mage.h"


Mage::Mage(std::map<int, double> _stats)
{
	stats = _stats;
	displayChar = 'M';
	name = "Mage";
}