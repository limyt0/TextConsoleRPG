#pragma once
#include <iostream>
#include <string>
#include <random>

class Monster{
protected:
	std::string Name;
	int Health = 0;
	int Attack = 0;
	bool isAlive = true;

public:
  Monster(std::string name, int playerLevel);

  virtual ~Monster() {}
  
  std::string getName() const; //몬스터의 이름을 반환합니다.

  int getHealth() const; // 몬스터의 체력을 반환합니다.

  int getAttack() const; // 몬스터의 공격력을 반환합니다.


  // 몬스터가 데미지를 입었을 때 체력을 감소시키고, 체력이 0 이하가 되면 isAlive 를 false로 변경합니다.
  void takeDamage(int damage);


  //몬스터가 플레이어를 공격할 때 호출되는 가상 함수입니다.
  virtual void attackPlayer() {}

  //몬스터가 죽었을때 호출되는 가상 함수입니다.
  virtual void onDeath();
};

