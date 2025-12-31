#include <string>
#include "HealthPotion.h"
#include "Character.h"

using namespace std;

HealthPotion::HealthPotion() : name("HealthPotion"), healthRestore(50), price(30) {}

	
string HealthPotion::getName()
{
	return name;
}

int HealthPotion::getPrice()
{
	return price;
}


void HealthPotion::use(Character* character)
{
	if (!character)
	{
		return;
	}

	character->setHealth(character->getHealth() + healthRestore);
	
	if (character->getHealth() > character->getMaxHealth())
	{
		character->setHealth(character->getMaxHealth());
	}
}