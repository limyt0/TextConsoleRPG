#include <string>
#include "Item.h"

using namespace std;

class HealthPotion : public Item
{
public:
	HealthPotion()
	{
		healthRestore = 50;
	}

	string getName()
	{

	}

private:
	string name;
	int healthRestore;
};