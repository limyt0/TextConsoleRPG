#include <string>
#include "Item.h"
#include "Character.h"

using namespace std;

class HealthPotion : public Item
{
public:
	HealthPotion() : name("HealthPotion"), healthRestore(50) {}

	string getName()
	{
		return name;
	}

	void use(Character* character)
	{
		if (!character)
		{
			return;
		}

		character->setHealth(character->getHealth() + healthRestore);
	}

private:
	string name;
	int healthRestore;
};