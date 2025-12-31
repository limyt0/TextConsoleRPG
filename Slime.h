#pragma once
#include "Monster.h"

class Slime : public Monster
{
private:
	bool isGlued = false; // 플레이어가 붙잡혔는지 여부

public:
	Slime(int playerLevel) : Monster("슬라임", playerLevel) {}

	virtual int attackPlayer(Character* player) override;

	virtual void onDeath() override;
};