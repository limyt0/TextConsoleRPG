#include "Troll.h"
#include "Character.h"


Troll::Troll(Character* player) : Monster("트롤", player) {
	Health += player->getLevel() * 3; // 트롤 추가 체력 보너스
	Attack += player->getLevel() * 2; // 트롤 추가 공격력 보너스
}


void Troll::takeDamage(int damage) {
	if (isAlive == false) { return; } // 이미 사망한 몬스터인지 확인

	bool skillUsed = player->getUnsingSkill();
	int skillDamage = damage * 1.25;
	int shildDamage = 5;

	if (skillUsed == true) {
		cout << "  " << "\033[1;33m" << Name << "에게 스킬은 효과적이었다!" << "\033[0m" << std::endl;
		Health -= (skillDamage);
		cout << "  " << "\033[1;32m" << Name << "에게 " << skillDamage << "의 데미지를 주었습니다!" << "\033[0m" << std::endl;
	}
	else
	{
		cout << "  " << "\033[1;33m" << Name << "에게 일반 공격은 별로 유효하지 않은 것 같다." << "\033[0m" << std::endl;
		Health -= shildDamage;
		cout << "  " << "\033[1;32m" << Name << "에게 " << shildDamage << "의 데미지를 주었습니다!" << "\033[0m" << std::endl;
	}


	if (Health <= 0) {
		isAlive = false; // 사망시 isAlive 상태를 false로 변경
		onDeath();
	}
	else
	{
		cout << "  " << Name << "의 남은 체력 : " << getHealth() << std::endl;
	}
}

