#pragma once
#include "Monster.h"

class Goblin : public Monster
{
private:
	bool hasStolen = false; // 플레이어의 아이템을 훔쳤는지 여부

public:
	Goblin(int playerLevel);
	
};

