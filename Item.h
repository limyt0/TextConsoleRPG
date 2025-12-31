#pragma once

#include <string>
class Character; //전방선언

class Item
{
public:
	//Item(string name, int value )
	virtual std::string getName() = 0;
	virtual void use(Character* character) = 0;
};