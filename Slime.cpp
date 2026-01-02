#include "Slime.h"
#include "Character.h"



Slime::Slime(Character* player) : Monster("슬라임", player) {}

int Slime::attackPlayer() {
	if (player == nullptr || player->getHealth() <= 0) return 2;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);

	if (!isGlued) {
		cout << "\n  " << "\033[1;31m" << Name << "이(가) " << player->getName() << "에게 날라듭니다!" << "\033[0m" << std::endl;

		if(dist(gen) <= 30) { // 30% 확률로 달라붙기 시도
			isGlued = true;
			std::cout << "\n  " << "\033[1;33m" << Name << "이 " << player->getName() << "에게 달라붙었습니다!" << "\033[0m" << std::endl;
			player->takeDamage(getAttack());
		}
		else {
			player->takeDamage(getAttack());
		}
		
	}
	else
	{
		std::cout << "  " << Name << "이(가) 달라붙어 있습니다!" << std::endl;
		player->takeDamage(getAttack());
		// 달라 붙은 후 떼어내기 시도 50%
		if (dist(gen) <= 50 && player->getHealth() > 0) {
			isGlued = false;
			std::cout << player->getName() << "이 몸을 흔들어 " << Name << "을(를) 떼어냈습니다!" << std::endl;
		}
	}
	player->setCanAttack(!isGlued);
	return (player->getHealth() <= 0) ? 0 : 1;
}

void Slime::onDeath() {
	isGlued = false;
	std::cout << "\n\n\033[1;33m  " << Name << "을(를) 물리쳤다!\033[0m" << std::endl;
}