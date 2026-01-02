#include "Goblin.h"
#include "windows.h"

Goblin::Goblin(Character* player) : Monster("고블린", player) {
    Attack += player->getLevel(); // 고블린 추가 공격력 보너스
}

int Goblin::attackPlayer() {
    if (player == nullptr) return 2; // 플레이어가 null인지 확인

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    if (!hasStolen) {
        if (dist(gen) <= 50) { // 50% 확률로 도둑질 시도
            int stolenTarget = (dist(gen) % 50) + 10; // 목표 금액 10~60

            if (player->getGold() >= stolenTarget) {
                Sleep(500);
                stolenGoldAmount = stolenTarget;
                // 충분히 훔쳤을 때
                player->setGold(player->getGold() - stolenTarget);
                hasStolen = true;
                std::cout << "\n  \033[1;33m " << Name << "이(가) 당신의 주머니에서 " << stolenTarget << " 골드를 훔쳐 달아나려 합니다!\033[0m" << std::endl;
            }
            else {
                // 돈이 부족할 때 (분노 발생)
                stolenGoldAmount = stolenTarget - player->getGold();
                int actualStolen = player->getGold();
                player->setGold(0);

                hasStolen = true;
                isEnraged = true; // 분노 true 설정

                std::cout << "\n  \033[1;33m " << Name << "이(가) " << actualStolen << " 골드만 훔친 것에 분노했습니다!\033[0m" << std::endl;
                Attack += stolenGoldAmount; // 못 훔친 만큼 공격력 상승
                std::cout << "  \033[1;31m " << Name << "의 공격력이 " << stolenGoldAmount << "만큼 증가! (현재: " << Attack << ")\033[0m" << std::endl;
            }
        }
        player->takeDamage(getAttack()); // 일반 공격 (분노 시 즉시 적용됨)
    }
    else {
        Sleep(500);
        if (isEnraged) {
            std::cout << "  " << Name << "이(가) 눈이 벌게진 채 날뜁니다!" << std::endl;
            player->takeDamage(getAttack());
        }
        else {
            // 만족스럽게 훔친 고블린은 도망 시도
            std::cout << "  " << Name << "이(가) 훔친 골드를 챙기며 비열하게 웃고 있습니다!" << std::endl;
            player->takeDamage(getAttack() / 2); // 도망 준비로 약해진 공격

            if (dist(gen) <= 30) {
                std::cout << "  \033[1;35m[도주] " << Name << "이(가) 숲속으로 도망쳤습니다!\033[0m" << std::endl;
                Health = 0;
                return 3; // 도망 성공 리턴
            }
        }
    }

    return (player->getHealth() <= 0) ? 0 : 1;
}

void Goblin::onDeath() {
    if (player == nullptr) return;
    Sleep(500);
    std::cout << "\n\n\033[1;33m  " << Name << "을(를) 처치했다!\033[0m" << std::endl;
    if (hasStolen) {
        if (isEnraged) {
            player->setGold(player->getGold() + stolenGoldAmount);
            std::cout << "  죽은 고블린의 손에 꽉 쥐여진 몇 안 되는 동전을 회수했습니다." << std::endl;
        }
        else {
            player->setGold(player->getGold() + stolenGoldAmount);
            std::cout << "\033[1;32m  [회수 성공] 고블린이 훔쳐갔던 골드 주머니를 되찾았습니다!\033[0m" << std::endl;
        }
    }
}