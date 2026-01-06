#pragma once

#include <string>
class Character; //전방선언

class Item
{
public:
	virtual ~Item() {}
	virtual Item* clone() const = 0;
	virtual std::string getName() = 0;
	virtual void use(Character* character) = 0;
	virtual int getPrice() = 0;

};