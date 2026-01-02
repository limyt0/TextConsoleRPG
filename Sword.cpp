#include <string>
#include "Sword.h"
#include "Character.h"

using namespace std;

Sword::Sword() : name("Sword"), swordattackpower(20), price(50) {}

Sword::Sword(const Sword& other) : name(other.name), swordattackpower(other.swordattackpower), price(other.price) {}


string Sword::getName()
{
	return name;
}

int Sword::getPrice()
{
	return price;
}



void Sword::use(Character* character)
{
	if (!character)
	{
		return;
	}

	character->setAttack(character->getAttack() + swordattackpower);
}