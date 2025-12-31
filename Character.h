#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "Item.h"
using namespace std;
class GameMnager;
class Item;

class Character
{
private:
	string _Name;
	int _Level;
	int _Health;
	int _MaxHealth;
	int _Attack;
	int _Experence;
	int _Gold;
	vector<Item*> _inventory;
	int  _isBoosted;
	

public:
	
	Character(string name);
	string getName()const;
	int getLevel()const;
	int getHealth()const;
	int getMaxHealth()const;
	int getAttack()const;
	int getExperence()const;
	int getGold()const;
	int getisBoosted()const;

	vector<Item*> getInventory();
	void takeDamage(int damage);
	//void addExp();

	// 수정 사항 생길수있음
	void useItem(int index);
	void levelup();
	//int SetHealth()
	//{
	//	return _Health;
	//	// 포션사용시 50 회복
	//	// 레벨업시 maxhealth만큼 회복
	//}
	void addItem(Item* item);
	void setHealth(int health);
	void setAttack(int attack);
	void setExperence(int exp);
	void setGold(int gold);
	void showStatus()const;
	void setisBoosted(int boost);
};