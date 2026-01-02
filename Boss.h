#pragma once
#include "Monster.h"

class Boss : public Monster {
public:
    Boss(Character* player);

    //virtual int attackPlayer(class Character* player) override;

    virtual void onDeath() override;

};