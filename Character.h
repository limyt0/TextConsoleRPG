#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class GameMnager;
class Monster;
class Item;
class Shop;
class Skill;

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
	int _isBoosted;
	bool _canAttack =true;
	Skill* _Skill;
	//여기에 넣을려면

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
	bool isAlive = true;
	vector<Item*> getInventory();
	~Character();
	bool getCanAttack()const;
	void setCanAttack(bool setattack);




	void takeDamage(int damage);
	int AttackMonster(Monster* monster);

	void useItem(int index);
	void deleteItem(int index);
	void levelup();
	void setSkill();
	void addItem(Item* item);
	void setHealth(int health);
	void setAttack(int attack);
	void setExperence(int exp);
	void setGold(int gold);
	void showStatus()const;
	void setisBoosted(int boost);
};