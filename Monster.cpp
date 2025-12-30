#include "Monster.h"

	std::string Monster::getName() const {
		return Name;
	}

	int Monster::getHealth() const {
		return Health;
	}

	int Monster::getattack() const {
		return Attack;
	}

	void Monster::takeDamage(int damage) {
		if (isAlive == false) { return; } // 이미 사망한 몬스터인지 확인

		Health -= damage;
		if (Health <= 0) {
			isAlive = false; // 사망시 isAlive 상태를 false로 변경
			OnDeath();
		}else{
		std::cout << getName() << " 의 체력이 " << getHealth() << " 만큼 남았습니다." << std::endl;
		}
	}

	void Monster::OnDeath() {
		std::cout << getName() << " 가 사망했습니다." << std::endl;
	}