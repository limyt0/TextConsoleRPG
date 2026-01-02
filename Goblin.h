#pragma once
#include "Monster.h"
#include "Character.h"

class Goblin : public Monster
{
private:
	bool hasStolen = false; // 플레이어의 아이템을 훔쳤는지 여부
	bool isEnraged = false; // 분노 상태 여부
	int stolenGoldAmount = 0; // 훔친 골드 양
public:
	Goblin(int playerLevel);

	virtual int attackPlayer(Character* player) override;
	
	virtual void onDeath(Character* player) override;
};

