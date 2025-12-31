#include "GameManager.h"
#include <iostream>
#include <random>

using namespace std;

GameManager::GameManager() :isGameOver(false), monster(nullptr) {
    killCount.insert({ "고블린", 0 });
    killCount.insert({ "오크", 0 });
    killCount.insert({ "트롤", 0 });
    killCount.insert({ "슬라임", 0 });
};

Monster* GameManager::generateMonster(int level) {
    random_device rd;   // 난수 시드
    mt19937 gen(rd());  // Mersenne Twister 엔진
    uniform_int_distribution<> dis(1, 4);   // 1~4 균등 분포

    int monsterNumber = dis(gen);   // 난수 생성

    switch (monsterNumber) {
    case(1):
        monster = new Goblin(level);
        break;
    case(2):
        monster = new Orc(level);
        break;
    case(3):
        monster = new Troll(level);
        break;
    case(4):
        monster = new Slime(level);
        break;
    }

    return monster;
}

void GameManager::battle(Character* player) {
    if (monster == nullptr) {
        cout << "몬스터가 생성되어있지 않습니다." << endl;
        return;
    }
    cout << "몬스터 " << monster->getName() << " 등장! 체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << endl;
    while (true) {
        if (monster == nullptr) {
            break;
        }
        monster->takeDamage(player->getAttack());
        if (monster->getHealth() > 0) {
            cout << player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! " << monster->getName() << " 체력: " << monster->getHealth() << endl;
        }
        // 몬스터 처치
        else {
            cout << player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! " << monster->getName() << " 처치!" << endl;
            if (killCount.find(monster->getName()) != killCount.end()) {
                killCount[monster->getName()]++;
            }

            player->setExperence(player->getExperence()+ monster->getExpReward());
            player->levelup();
            player->setGold(player->getGold() + monster->getGoldReward());
            Item* droppedItem = monster->dropItem();
            if (droppedItem != nullptr) {
                player->addItem(droppedItem);
                cout << player->getName() << "이(가) " << droppedItem->getName() << " 한 개를 획득했습니다." << endl;
            }
            cout << player->getName() << "이(가) " << monster->getExpReward() << "EXP와 " << monster->getGoldReward() << " 골드를 획득했습니다. 현재 EXP : " << player->getExperence() << " / 100, 골드 : " << player->getGold() << endl;
            
            delete monster;
            monster = nullptr;
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
            isGameOver = true;
            return;
        }
    }
}

void GameManager::displayInventory(Character* player) {
    if (player == nullptr) return;

    cout << "==========인벤토리==========" << endl;
    for (int i = 0; i < player->getInventory().size(); ++i) {
        cout << player->getInventory()[i]->getName();
        if (i != player->getInventory().size() - 1) {
            cout << ", ";
        }
    }
    cout << "============================" << endl;
}

void GameManager::displayKillCount(Character* player) {
    if (player == nullptr) return;

    cout << "======몬스터 처치 로그======" << endl;
    for (pair<const string, int> count : killCount) {
        cout << count.first << " 처치 횟수: " << count.second << endl;
    }
    cout << "============================" << endl;
}

bool GameManager::getIsGameOver() {
    return isGameOver;
}