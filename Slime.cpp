#include "Slime.h"
#include "Character.h"



Slime::Slime(Character* player) : Monster("슬라임", player) {}

int Slime::attackPlayer() {
	if (player == nullptr || player->getHealth() <= 0) return 2;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);

	if (!isGlued) {
		cout << "\n  " << "\033[1;31m" << Name << "이 당신에게 튀어오릅니다!" << "\033[0m" << std::endl;
		player->takeDamage(getAttack());
		if(dist(gen) <= 30) { // 30% 확률로 달라붙기 시도
			isGlued = true;
			std::cout << "\n  " << "\033[1;33m" << Name << "이 당신에게 달라붙었습니다!" << "\033[0m" << std::endl;
		}
		
	}
	else
	{
		Health += (getAttack()); // 달라붙은 상태에서 공격할 때마다 체력 회복
		std::cout << "\033[1;33m  " << Name << "이 달라붙어 당신의 체력을 빼았습니다! [" << Name << "의 현재 체력은 : " << getHealth() << "]" << "\033[0m" << std::endl;
		player->takeDamage(getAttack());

		// 달라 붙은 후 떼어내기 시도 50%
		if (dist(gen) <= 50 && player->getHealth() > 0) {
			isGlued = false;
			std::cout << "\n" << "\033[1;32m  당신은 몸에서 " << Name << "을 때어냈습니다!\n" << "\033[0m" << std::endl;
		}
	}
	player->setCanAttack(!isGlued);
	return (player->getHealth() <= 0) ? 0 : 1;
}

void Slime::onDeath() {
	isGlued = false;
	std::cout << "\n\n\033[1;33m  " << Name << "을(를) 처치했다!\033[0m" << std::endl;
}