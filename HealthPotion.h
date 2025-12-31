#pragma once
#include <string>
#include "Item.h"

class Character;

class HealthPotion : public Item
{
public:
	HealthPotion();

	std::string getName() override;
	void use(Character* character) override;
	int getPrice();


private:
	std::string name;
	int healthRestore;
	int price;
};