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

vector<Item*> Shop:: getSellList()
{
	

	return sellList;
}

void itemSell(Character* character)   
{
	character->setGold(character->getGold() + 18);
}

void itembut(Character* character)
{
	character->setGold(character->getGold() -30);
}

Item* Shop::buyItem(int itemindex, Character* player)
{
	if (player->getGold() - sellList[itemindex]->getPrice() < 0) {
		return nullptr;
	}
	player->setGold(player->getGold() - sellList[itemindex]->getPrice());
	Item* item = sellList[itemindex]->clone();
	player->addItem(item);
	return item;
}

int  Shop::itemSell(int index,Character*player)
{
	float price = player->getInventory()[index]->getPrice() * 6 / 10;
	//cout << "price1: " << player->getInventory()[index]->getPrice() << endl;
	//cout << "price2: " << price << endl;
	player->setGold(player->getGold() + (int)price);
	player->deleteItem(index);
	return price;
}
