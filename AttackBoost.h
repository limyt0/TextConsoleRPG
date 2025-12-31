#pragma once
#include <string>
#include "Item.h"

class Character;

class AttackBoost : public Item
{
public:
	AttackBoost();

	std::string getName() override;
	void use(Character* character) override;


private:
	std::string name;
	int attackincrease;
};