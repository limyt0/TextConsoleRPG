#include <iostream>
#include <vector>
#include <string>
#include "Character.h"
#include "Item.h"
using namespace std;



Character::Character(string name) :
	_Name(name), _Level(1), _Health(200), _MaxHealth(200), _Attack(30), _Experence(0), _Gold(0)
{
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





vector<Item*> Character:: getInventory()
{
	return inventory;
}





void Character::takeDamage(int damage)
{
	_Health -= damage;
	if (_Health < 0)
	{
		_Health = 0;
	}
}

void Character::addExp()
{
	if (_Level < 10)
	{
		_Experence += 50;
		levelup();
	}
	else
	{
		_Experence = 0;
	}
}



//int Character:: characterdie()
//{
//	if (_Health <= 0)
//	{
//		cout << "캐릭터가 사망하여 게임이 종료됩니다" << endl;
//		return 0;
//	}
//}


// 수정 사항 생길수있음
void Character::levelup()
{
	if (100 <= _Experence)
	{
		if (_Level < 10)
		{
			_Level++;
			_Experence -= 100;
			_MaxHealth += (_Level * 20);
			cout << "최대체력이 증가했습니다. 현재 최대체력:" << _MaxHealth << endl;
			_Attack += (_Level * 5);
			cout << "공격력이 증가했습니다. 현재 공격력:" << _Attack << endl;
			_Health = _MaxHealth;
			cout << "체력이 회복되었습니다. 현재 체력:" << _Health << endl;
		}
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
	cout << "현재 스테이터스창" << endl;
	cout << "이       름:" << _Name << endl;
	cout << "현재   레벨:" << _Level << endl;
	cout << "현재 공격력:" << _Attack << endl;
	cout << "현재   체력:" << _Health << endl;
	cout << "현재   골드:" << _Gold << endl;
	cout << "현재 경험치:" << _Experence << endl;
}


//int main()
//{
//	Character a("Yahoo");
//}