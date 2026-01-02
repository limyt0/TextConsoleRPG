#pragma once
#include <string>
#include "Item.h"

class Character;

class Sword : public Item
{
public:
	Sword();
	Sword(const Sword& other);


	std::string getName() override;
	void use(Character* character) override;
	int getPrice();
	Item* clone() const override {
		return new Sword(*this);
	}

private:
	std::string name;
	int swordattackpower;
	int price;
};