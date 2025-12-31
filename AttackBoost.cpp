#include <string>
#include "AttackBoost.h"
#include "Character.h"

using namespace std;

AttackBoost::AttackBoost() : name("AttackBoost"), attackincrease(10) {}


string AttackBoost::getName()
{
	return name;
}

void AttackBoost::use(Character* character)
{
	if (!character)
	{
		return;
	}

	character->setAttack(character->getAttack() + attackincrease);
}