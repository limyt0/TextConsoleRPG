#pragma once
#include "Monster.h"

class Boss : public Monster {
public:
    Boss(int playerLevel);

    virtual int attackPlayer(class Character* player) override;

    virtual void onDeath() override;

};