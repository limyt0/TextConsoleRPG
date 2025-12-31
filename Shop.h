#pragma once
#include <vector>
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Character.h"

class Shop
{
private:
	int priceHealthPotion;
	int priceAttackBoost;
	vector<Item*>sellList;
public:
	Shop();

	~Shop();

	//int getPriceHealthPotion(int a)const;
	//int getPriceAttackBoost(int b)const;*/


	//int setPriceHealthPotion(int a); //매개변수
	//int setPriceAttackBoost(int b); // 매개변수

	int itemSell(int index, Character* player);     //여기 매개변수는 뭘넣어어야하나
	Item* buyItem(int itemindex, Character* player);    //여기도

	vector<Item*>getSellList();
};