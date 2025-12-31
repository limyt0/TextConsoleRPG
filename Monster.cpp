#include "Monster.h"
#include "HealthPotion.h"
#include "AttackBoost.h"


// 몬스터 생성자 스탯 랜덤 생성
Monster::Monster(std::string name, int playerLevel) : Name(name), isAlive(true) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	//체력은 20~30 * 플레이어 레벨, 공격력은 5~10 * 플레이어 레벨 범위에서 랜덤 생성
	std::uniform_int_distribution<int> healthDist(playerLevel * 20, playerLevel * 30);
	Health = healthDist(gen);

	std::uniform_int_distribution<int> attackDist(playerLevel * 5, playerLevel * 10);
	Attack = attackDist(gen);
}

	std::string Monster::getName() const {
		return Name;
	}

	int Monster::getHealth() const {
		return Health;
	}

	int Monster::getAttack() const {
		return Attack;
	}

	void Monster::takeDamage(int damage) {
		if (isAlive == false) { return; } // 이미 사망한 몬스터인지 확인

		Health -= damage;
		if (Health <= 0) {
			isAlive = false; // 사망시 isAlive 상태를 false로 변경
			onDeath();
		}
	}

	void Monster::onDeath() {}


	Item* Monster::dropItem() {
	   static std::random_device rd;
	   static std::mt19937 gen(rd());
	   std::uniform_int_distribution<> dist(1, 100);

	   if (dist(gen) > dropChance) {
		  return nullptr;
	   }

	   std::uniform_int_distribution<> itemSelector(1, 2);
	   int choice = itemSelector(gen);

	   switch (choice) {

	   case 1: std::cout << Name << "이(가) 체력포션을 드랍했다!" << std::endl;
		   return new HealthPotion();

	   case 2: std::cout << Name << "이(가) 공격력 포션을 드랍했다!" << std::endl;
		   return new AttackBoost();	

	   default: return nullptr;
	   }
	}


	int Monster::getExpReward() const {
		return expDrop;
	}



	int Monster::getGoldReward() const {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<int> goldDist(10, 20);

		return goldDist(gen);
	}