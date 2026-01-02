#include <string>
#include "AttackBoost.h"
#include "Character.h"

using namespace std;

AttackBoost::AttackBoost() : name("AttackBoost"), attackincrease(10), price(30) {}

AttackBoost::AttackBoost(const AttackBoost& other) : name(other.name), attackincrease(other.attackincrease), price(other.price) {}


string AttackBoost::getName()
{
	return name;
}

int AttackBoost::getPrice()
{
	return price;
}



void AttackBoost::use(Character* character)
{
	if (!character)
	{
		return;
	}

	character->setAttack(character->getAttack() + attackincrease);
}