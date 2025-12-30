#pragma once
#include "Monster.h"

class Slime : public Monster
{
public:
	Slime(int playerLevel) : Monster("슬라임", playerLevel) {}
};

