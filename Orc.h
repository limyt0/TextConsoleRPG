#pragma once
#include "Monster.h"

class Orc : public Monster
{
public:
	Orc(int playerLevel) : Monster("오크", playerLevel) {}
};

