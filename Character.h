#pragma once
#include <iostream>
#include <string>
using namespace std;

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

public:
	Character(string name);
	int GetLevel()const;

	int GetHealth()const;
	
	int GetMaxHealth()const;
	
	int GetAttack()const;
	

	int GetExperence()const;
	

	int GetGold()const;
	
	void takeDamage(int damage);
	void AddExp();
	
	// 수정 사항 생길수있음
	void levelup();
	//int SetHealth()
	//{
	//	return _Health;
	//	// 포션사용시 50 회복
	//	// 레벨업시 maxhealth만큼 회복
	//}
	void SetHealth(int health);
	void SetAttack(int attack);
	void SetExperence(int exp);
	void SetGold(int gold);
	void ShowStatus()const;
	
};