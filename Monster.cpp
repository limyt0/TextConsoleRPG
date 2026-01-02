#include "Monster.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Character.h"


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
		if (isAlive == false) {return;} // 이미 사망한 몬스터인지 확인

		Health -= damage;
		cout << "  " << "\033[1;32m" << Name << "에게 " << damage << "의 데미지를 주었습니다!" << "\033[0m" << std::endl;
		if (Health <= 0) {
			isAlive = false; // 사망시 isAlive 상태를 false로 변경
			onDeath();
		}
		else
		{
			cout << "  " << Name << "의 남은 체력 : " << getHealth() << std::endl;
		}
	}

	int Monster::attackPlayer(Character* player) {
		if (player == nullptr) return 2; // 플레이어가 null인지 확인

		cout << "\n  " << "\033[1;31m" << Name << "이(가) " << player->getName() << "을(를) 공격합니다!" << "\033[0m" << std::endl;
		player->takeDamage(getAttack()); // 플레이어 공격

		if (player->getHealth() <= 0) //플레이어의 체력이 0 이하인지 확인
		{
			return 0; // 플레이어가 사망했음을 나타내는 값 반환
		}else{
			return 1; // 플레이어가 살아있음을 나타내는 값 반환
		}

    }



	void Monster::onDeath() {
		std::cout << "\n  " << Name << "이(를) 처치했다!" << std::endl;
	}


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

	   case 1: std::cout << "  " << Name << "이(가) 체력포션을 드랍했다!" << std::endl;
		   return new HealthPotion();

	   case 2: std::cout << "  " << Name << "이(가) 공격력 포션을 드랍했다!" << std::endl;
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