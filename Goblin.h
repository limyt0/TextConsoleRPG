#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(int playerLevel) : Monster("고블린", playerLevel) {}
};

