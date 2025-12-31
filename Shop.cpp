#include <iostream>
#include <vector>
#include "Character.h"
#include "Item.h"
#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
using namespace std;

Shop::Shop() : priceHealthPotion(30), priceAttackBoost(30) 
{
	sellList.push_back(new HealthPotion);
	sellList.push_back(new AttackBoost);
}

Shop:: ~Shop() 
{
	delete sellList[0];
	delete sellList[1];
}

void itemSell(Character* character)   //여기 매개변수는 뭘넣어어야하나
{
	character->setGold(character->getGold() + 18);
}

void itembut(Character* character)
{
	character->setGold(character->getGold() -30);
}

Item* Shop::buyItem(int itemindex, Character* player)
{
	player->setGold(player->getGold() - sellList[itemindex]->getPrice());
	player->addItem(sellList[itemindex]);
	return sellList[itemindex];
}

int  Shop::itemSell(int index,Character*player)
{
	player->setGold(player->getGold() + player->getInventory()[index]->getPrice() * (6 / 10));
	player->deleteItem(index);
	return;
}