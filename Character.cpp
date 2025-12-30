#include <iostream>
#include <vector>
#include <string>
#include "Character.h"
using namespace std;



Character::Character(string name) :
	_Name(name), _Level(1), _Health(200), _MaxHealth(200), _Attack(30), _Experence(0), _Gold(0)
{
}



int Character::GetLevel()const
{
	return _Level;
}

int Character::GetHealth()const
{
	return _Health;
}

int Character::GetMaxHealth()const
{
	return _MaxHealth;
}

int Character::GetAttack()const
{
	return _Attack;
}


int Character::GetExperence()const
{
	return _Experence;
}

int Character::GetGold()const
{
	return _Gold;
}








void Character::takeDamage(int damage)
{
	_Health -= damage;
	if (_Health < 0)
	{
		_Health = 0;
	}
}

void Character::AddExp()
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

void Character::SetHealth(int health)
{
	_Health = health;
}

void Character::SetAttack(int attack)
{
	_Attack = attack;
}

void Character::SetExperence(int exp)
{
	_Experence = exp;
}


void Character::SetGold(int gold)
{
	_Gold = gold;
}

void Character::ShowStatus()const
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