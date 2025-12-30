#pragma once
#include "Monster.h"

class Troll : public Monster
{
public:
	Troll(int playerLevel) : Monster("트롤", playerLevel) {}
};

