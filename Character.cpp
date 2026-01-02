#include <iostream>
#include <vector>
#include <string>
#include "Character.h"
#include "Item.h"
#include "Monster.h"
using namespace std;



Character::Character(string name) :
	_Name(name), _Level(1), _Health(200), _MaxHealth(200), _Attack(30), _Experence(0), _Gold(0),_isBoosted(false)
{
}

string Character::getName()const
{
	return _Name;
}

int Character::getLevel()const
{
	return _Level;
}

int Character::getHealth()const
{
	return _Health;
}

int Character::getMaxHealth()const
{
	return _MaxHealth;
}

int Character::getAttack()const
{
	return _Attack;
}


int Character::getExperence()const
{
	return _Experence;
}

int Character::getGold()const
{
	return _Gold;
}

int Character :: getisBoosted()const
{
	return _isBoosted;
}

vector<Item*> Character::getInventory()
{
	return _inventory;
}

bool Character:: getCanAttack()const
{
	return _canAttack;
}

void Character :: setCanAttack(bool setattack)
{
	_canAttack = setattack;
}


void Character::takeDamage(int damage)
{
	if (isAlive == false) { return ; }
	_Health -= damage;

	cout << "  " << "\033[1;32m" << _Name << "에게 " << damage << "의 데미지를 주었습니다!" << "\033[0m" << std::endl;
	if (_Health <= 0)
	{	
		isAlive = false;
		_Health = 0;
	}
	else 
	{
		cout << "  " << _Name << "의 남은 체력 : " << getHealth() << endl;
	}
}



void Character:: addItem(Item* item)
{
	_inventory.push_back(item);
}



void Character:: useItem (int index)
{
	_inventory[index]->use(this);
	deleteItem(index);
}  

void Character::deleteItem(int index)
{
	delete _inventory[index];
	_inventory.erase(_inventory.begin() + index);
}



void Character ::setisBoosted(int boost)
{
	_isBoosted = boost;
}

int Character:: AttackMonster(Monster*monster)
{
	if(getCanAttack() == false)
	{
		return 4;
	}
	if (monster == nullptr) 
	{
		return 2; 
	}
	cout << "\n  " << "\033[1;31m" << _Name << "이(가) " << monster->getName() << "을(를) 공격합니다!" << "\033[0m" << std::endl;
	monster->takeDamage(getAttack());
	if(monster->getHealth()<=0)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}


void Character::levelup()
{
	if (100 <= _Experence)
	{
		if (_Level < 10)
		{
			_Level++;
			cout << "  ㅁ             레벨 업!             ㅁ " << endl;
			_MaxHealth += (_Level * 20);
			cout << "  최대체력이 증가했습니다. 현재 최대체력 [" << _MaxHealth << "]" << endl;
			_Attack += (_Level * 5);
			cout << "  공격력이 증가했습니다. 현재 공격력 [" << _Attack << "]" << endl;
			_Health = _MaxHealth;
			cout << "  체력이 회복되었습니다. 현재 체력 [" << _Health << "]\n" << endl;
		}
	_Experence -= 100;
	}
}

void Character::setHealth(int health)
{
	_Health = health;
}

void Character::setAttack(int attack)
{
	_Attack = attack;
}

void Character::setExperence(int exp)
{
	_Experence = exp;
}


void Character::setGold(int gold)
{
	_Gold = gold;
}

void Character::showStatus()const
{
	cout << "================================ 캐릭터 정보 =========================================" << endl;
	cout << "  캐릭터 이름 [ " << _Name << " ] " << endl;
	cout << "  현재  레벨  [ " << _Level << " ] " << endl;
	cout << "  현재 공격력 [ " << _Attack << " ] " << endl;
	cout << "  현재  체력  [ " << _Health << " ] " << endl;
	cout << "  현재  골드  [ " << _Gold << " ] " << endl;
	cout << "  현재 경험치 [ " << _Experence << " ] " << endl;
}

