#pragma once
#include "Monster.h"

class Slime : public Monster
{
private:
	bool isGlued = false; // 플레이어가 붙잡혔는지 여부

public:
	Slime(Character* player);

    virtual EntityState attackPlayer() override;

	virtual void onDeath() override;
};