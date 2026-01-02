#pragma once
#include <iostream>
#include <string>
#include <random>

class Item; // 전방 선언
class Character;

class Monster{
protected:
	std::string Name;
	int Health = 0;
	int Attack = 0;
	bool isAlive = true;

	int dropChance = 30; // 아이템 드랍 확률 (기본값 30%)
	int expDrop = 50; // 경험치 보상값 (기본값 50)

public:
  Monster(std::string name, int playerLevel);

  virtual ~Monster() {}
  
  std::string getName() const; //몬스터의 이름을 반환합니다.

  int getHealth() const; // 몬스터의 체력을 반환합니다.

  int getAttack() const; // 몬스터의 공격력을 반환합니다.

  // 몬스터가 데미지를 입었을 때 체력을 감소시키고, 체력이 0 이하가 되면 isAlive 를 false로 변경합니다.
  void takeDamage(int damage);

  //몬스터가 플레이어를 공격할 때 호출되는 가상 함수입니다.
  virtual int attackPlayer(Character* player);

  //몬스터가 죽었을때 호출되는 가상 함수입니다.
  virtual void onDeath();

  //아이템 랜덤 드랍 함수
  virtual Item* dropItem();

  //경험치 보상 값 반환
  virtual int getExpReward() const;

  //골드 보상 값 랜덤 반환
  virtual int getGoldReward() const;
};

