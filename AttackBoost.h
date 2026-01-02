#pragma once
#include <string>
#include "Item.h"

class Character;

class AttackBoost : public Item
{
public:
	AttackBoost();
	AttackBoost(const AttackBoost& other);


	std::string getName() override;
	void use(Character* character) override;
	int getPrice();
	Item* clone() const override {
		return new AttackBoost(*this);
	}

private:
	std::string name;
	int attackincrease;
	int price;
};