#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Item.h"

class GameManager
{
private:
    Monster* monster;
    bool isGameOver;
public:
    Monster* generateMonster(int level);
    void battle(Character* player);
    void displayInventory(Character* player);
};

