#pragma once
#include <string>
#include <vector>
#include <map>
#include "Character.h"
#include "Monster.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Item.h"
#include <random>



class GameManager
{
private:
    Monster* monster;
    bool isGameOver;
    map<string, int> killCount;
public:
    GameManager();
    Monster* generateMonster(int level);
    void battle(Character* player);
    void displayInventory(Character* player);
    void displayKillCount(Character* player);
    bool getIsGameOver();
};