#include <string>
#include "Item.h"

using namespace std;

class Attackincrease : public Item
{
public:
	Attackincrease() : name("AttackBoost"), attackincrease(10) {}

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

		character->SetAttack(character->GetAttack() + attackincrease);
	}

private:
	string name;
	int attackincrease;
};