#pragma once
#include <string>
#include "Potion.h"

class Character;

class AttackBoost : public Potion
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