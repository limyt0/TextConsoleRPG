#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(int playerLevel) : Monster("Gobline", playerLevel) {}
};

