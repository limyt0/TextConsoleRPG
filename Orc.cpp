#include "Orc.h"
#include "Character.h"


Orc::Orc(Character* player) : Monster("오크", player) {
   Attack += player->getLevel() * 3; // 오크 추가 공격력 보너스
}

int Orc::attackPlayer() {
	if (player == nullptr || player->getHealth() <= 0) return 2;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);
	if (dist(gen) <= 20) { // 20% 확률로 강력한 일격
		cout << "\n  " << "\033[1;31m" << Name << "이(가) 강력한 일격을 날립니다!" << "\033[0m" << std::endl;
		int strongAttack = getAttack() * 2;
		player->takeDamage(strongAttack);
	}
	else {
		cout << "\n  " << "\033[1;31m" << Name << "이(가) " << player->getName() << "을(를) 공격합니다!" << "\033[0m" << std::endl;
		player->takeDamage(getAttack());
	}
	return (player->getHealth() <= 0) ? 0 : 1;
}