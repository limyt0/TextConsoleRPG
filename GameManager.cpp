#include "GameManager.h"
#include <iostream>
#include <random>

using namespace std;

Monster* GameManager::generateMonster(int level) {
    random_device rd;   // 난수 시드
    mt19937 gen(rd());  // Mersenne Twister 엔진
    uniform_int_distribution<> dis(1, 4);   // 1~4 균등 분포

    int monsterNumber = dis(gen);   // 난수 생성

    switch (monsterNumber) {
    case(1):
        monster = new Goblin(level);
    case(2):
        monster = new Orc(level);
    case(3):
        monster = new Troll(level);
    case(4):
        monster = new Slime(level);
    }

    return monster;
}

void GameManager::battle(Chatacter* player) {
    if (monster == nullptr) {
        cout << "몬스터가 생성되어있지 않습니다." << endl;
        return;
    }
    cout << "몬스터 " << monster->getName() << " 등장! 체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << endl;
    while (true) {
        monster->takeDamage(player->getAttack());
        if (monster->getHealth() > 0) {
            cout << player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! " << monster->getName() << " 체력: " << monster->getHealth() << endl;
        }
        else {
            delete monster;
            monster = nullptr;
            cout << player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! " << monster->getName() << " 처치!" << endl;
            random_device rd;   // 난수 시드
            mt19937 gen(rd());  // Mersenne Twister 엔진
            uniform_int_distribution<> dis(10, 20);   // 1~4 균등 분포

            int gold = dis(gen);   // 난수 생성
            // 캐릭터 경험치 50 증가
            // 캐릭터 골드 10~20 증가
            cout << player->getName() << "이(가) 50 EXP와 " << gold << " 골드를 획득했습니다. 현재 EXP: " << player->getExp() << "/100, 골드: " << player->getGold() << endl;
            return;
        }
        player->takeDamage(monster->getAttack());
        if (player->getHealth() > 0) {
            cout << monster->getName() << "이(가) " << player->getName() << "을(를) 공격합니다! " << player->getName() << " 체력: " << player->getHealth() << endl;
        }
        else {
            cout << monster->getName() << "이(가) " << player->getName() << "을(를) 공격합니다! " << player->getName() << " 체력: 0" << endl;
            cout << player->getName() << "이(가) 사망했습니다. 게임 오버!" << endl;

            delete monster;
            // 게임 오버 설정
            return;
        }
    }
}

void GameManager::displayInventory(Character* player);