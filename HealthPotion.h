#pragma once
#include <string>
#include "Potion.h"

class Character;

class HealthPotion : public Potion
{
public:
	HealthPotion();
	HealthPotion(const HealthPotion& other);

	std::string getName() override;
	void use(Character* character) override;
	int getPrice();
	Item* clone() const override{
		return new HealthPotion(*this);
	}


private:
	std::string name;
	int healthRestore;
	int price;
};