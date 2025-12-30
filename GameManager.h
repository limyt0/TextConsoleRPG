#pragma once
#include <string>
#include <vector>
#include <Character.h>
#include <Monster.h>
#include <Item.h>

class GameManager
{
private:
    Monster* monster;
public:
    Monster* generateMonster(int level);
    void battle(Chatacter* player);
    void displayInventory(Character* player);
};

