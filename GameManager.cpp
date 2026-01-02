#include "GameManager.h"
#include <iostream>
#include <Windows.h>

using namespace std;

GameManager::GameManager() :isGameOver(false), monster(nullptr) 
{
    killCount.insert({ "고블린", 0 });
    killCount.insert({ "오크", 0 });
    killCount.insert({ "트롤", 0 });
    killCount.insert({ "슬라임", 0 });
};

Monster* GameManager::generateMonster(Character* player) 
{
    random_device rd1;   // 난수 시드
    mt19937 gen(rd1());  // Mersenne Twister 엔진

    uniform_int_distribution<> dis(1, 4);   // 1~4 균등 분포

    int monsterNumber = dis(gen);   // 난수 생성

    switch (monsterNumber)
    {
    case(1):
        monster = new Goblin(player);
        break;
    case(2):
        monster = new Orc(player);
        break;
    case(3):
        monster = new Troll(player);
        break;
    case(4):
        monster = new Slime(player);
        break;
    }
    return monster;
}

Monster* GameManager::generateBossMonster(Character* player)
{
    monster = new Boss(player);
    return monster;
}

void GameManager::battle(Character* player)
{
    if (monster == nullptr)
    {
        cout << "몬스터가 생성되어있지 않습니다." << endl;
        return;
    }
    cout << "\n=============================== 몬스터 등장 ==========================================" << endl;
    cout << "  이름: " << monster->getName() << ", 체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << endl;
    cout << "\n================================ 배틀  시작 ==========================================" << endl;
    while (true)
    {
        if (monster == nullptr) break;
        Sleep(1000);
        int playerAttack = player->AttackMonster(monster);
        Sleep(1000);
        if (playerAttack == 0) // 몬스터 사망
        {
            if (killCount.find(monster->getName()) != killCount.end())
            {
                killCount[monster->getName()]++;
            }
            Item* droppedItem = monster->dropItem();
            if (droppedItem != nullptr)
            {
                player->addItem(droppedItem);
                cout << "  " << player->getName() << "이(가) " << droppedItem->getName() << " 한 개를 획득했습니다.\n" << endl;
                Sleep(1000);
            }
            player->setExperence(player->getExperence() + monster->getExpReward());
            int gold = monster->getGoldReward();
            player->setGold(player->getGold() + gold);            
            cout << "  " << player->getName() << "이(가) [" << monster->getExpReward() << "] EXP 와 [" << gold << "] 골드를 획득했습니다. 현재 EXP [" << player->getExperence() << " / 100], 골드 [" << player->getGold() << "]" << endl << endl;
            Sleep(1000);
            player->levelup();
            break;
        }
        else if (playerAttack == 2) // 몬스터가 nullptr
        {
            cout << "  error. 몬스터가 존재하지 않습니다." << endl;
            break;
        }
        useRandomItem(player);
        Sleep(1000);
        int monsterAttack = monster->attackPlayer();
        Sleep(1000);
        if (monsterAttack == 0) // 플레이어 사망
        {
            cout << "  " << player->getName() << "이(가) 사망했습니다. 게임 오버!" << endl;
            isGameOver = true;
            break;
        }
        else if (monsterAttack == 3) // 몬스터 도망
        {
            break;
        }
        else if (monsterAttack == 2) // 플레이어가 nullptr
        {
            cout << "  error. 플레이어가 존재하지 않습니다." << endl;
            break;
		}
    }
    delete monster;
    monster = nullptr;
    resetBoost(player);
}

void GameManager::bossBattle(Character* player)
{
    if (monster == nullptr)
    {
        cout << "몬스터가 생성되어있지 않습니다." << endl;
        return;
    }
    cout << "\n=============================== 보스 몬스터 등장 ===============================" << endl;
    cout << "  이름: " << monster->getName() << ", 체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << endl;
    cout << "\n================================ 배틀  시작 ====================================" << endl;
    while (true)
    {
        if (monster == nullptr) break;
        Sleep(1000);
        int playerAttack = player->AttackBossMonster(monster);
        Sleep(1000);
        if (playerAttack == 0) // 몬스터 사망
        {
            isGameOver = true;
            break;
        }
        else if (playerAttack == 2) // 몬스터가 nullptr
        {
            cout << "  error. 몬스터가 존재하지 않습니다." << endl;
            break;
        }
        useRandomItem(player);
        Sleep(1000);
        int monsterAttack = monster->attackPlayer();
        Sleep(1000);
        if (monsterAttack == 0)
        {
            cout << "  " << player->getName() << "이(가) 사망했습니다. 게임 오버!" << endl;
            isGameOver = true;
            break;
        }
    }
    delete monster;
    monster = nullptr;
    resetBoost(player);
}

void GameManager::useRandomItem(Character* player)
{
    size_t itemsize = player->getInventory().size();
    if (itemsize >= 1)
    {
        random_device rd1;   // 난수 시드
        mt19937 gen(rd1());  // Mersenne Twister 엔진
        uniform_int_distribution<> dis(1, 2);   // 1~2 균등 분포
        int useitemrandom = dis(gen);   // 난수 생성
        uniform_int_distribution<> dis2(0, int(itemsize) - 1);
        int itemindex = dis2(gen);   // 난수 생성
        if (useitemrandom == 1)
        {
            cout << " | " << player->getInventory()[itemindex]->getName() << "아이템 사용" << " | " << endl;
            if (player->getInventory()[itemindex]->getName() == "AttackBoost")
            {
                player->setisBoosted(player->getisBoosted() + 1);
            }
            player->useItem(itemindex);
        }
    }
    return;
}

void GameManager::resetBoost(Character* player)
{
    if (player->getisBoosted() > 0)
    {
        player->setAttack(player->getAttack() - (10 * player->getisBoosted()));
        player->setisBoosted(0);
    }
    return;
}

void GameManager::useShop(Character* player)
{
    Shop* shop = new Shop();
    bool isContinue = true;
    while (isContinue)
    {
        cout << "\n===================================== 상점 ===========================================" << endl;
        cout << "  1. [물건 구매] \n  2. [물건 판매] \n  3. [상점 나가기] " << endl;
        cout << "======================================================================================" << endl;
        string select;
        cin >> select;
        int shopnum = -1;
        try
        {
            shopnum = stoi(select);
        }
        catch (const invalid_argument&)
        {
            cout << "\033[1;31m" << "[Error] 잘못된 입력입니다." << "\033[0m" << endl;
            continue;
        }
        system("cls");
        switch (shopnum)
        {
        // 물건 구매
        case 1:
            buyItem(shop, player);
            break;
        // 물건 판매
        case 2:
            sellItem(shop, player);
            break;
        // 상점 나가기
        case 3:
            cout << "상점을 나갑니다." << endl;
            isContinue = false;
            break;
        default:
            break;
        }
    }
    return;
}

void GameManager::buyItem(Shop* shop, Character* player)
{
    bool isContinue = true;
    while (isContinue)
    {
        cout << "\n================================= 아이템 리스트 ======================================" << endl;
        for (int i = 0; i < shop->getSellList().size(); i++)
        {
            cout << "  " << i+1 << ". [" << shop->getSellList()[i]->getName() << "]" << endl;
        }
        cout << "  0. [구매 취소하기]" << endl;
        cout << "======================================================================================" << endl;

        string select;
        cin >> select;
        int a = -1;
        try
        {
            a = stoi(select);
        }
        catch (const invalid_argument&)
        {
            cout << "\033[1;31m" << "[Error] 잘못된 입력입니다." << "\033[0m" << endl;
            continue;
        }
        cout << endl;
        system("cls");
        Item* it;
        switch (a)
        {
            case  1:
                it = shop->buyItem(0, player);
                if (it == nullptr)
                {
                    cout << "돈이 부족합니다." << endl;
                }
                else
                {
                    cout << it->getName() << " 구매" << endl;
                }            
                break;
            case 2:
                it = shop->buyItem(1, player);
                if (it == nullptr)
                {
                    cout << "돈이 부족합니다." << endl;
                }
                else
                {
                    cout << it->getName() << " 구매" << endl;
                }
                break;
            case 3:
                it = shop->buyItem(2, player);
                if (it == nullptr)
                {
                    cout << "돈이 부족합니다." << endl;
                }
                else
                {
                    cout << it->getName() << " 구매" << endl;
                }
                break;
            case 0:
                isContinue = false;
                break;
            default:
                cout << "\033[1;31m" << "[Error] 입력 범위를 초과하였습니다. 다시 입력해주세요." << "\033[0m" << endl;
                break;
        }
    }
    return;
}

void GameManager::sellItem(Shop * shop, Character* player)
{
    bool isContinue = true;
    while (isContinue)
    {
        cout << "\n================================= 인벤토리 ===========================================" << endl;
        for (int i = 0; i < player->getInventory().size(); i++) {
            cout << "  " << i + 1 << ". [" << player->getInventory()[i]->getName() << "]" << endl;
        }
        cout << "  0. [판매 취소하기]" << endl;
        cout << "======================================================================================" << endl;

        string select;
        cin >> select;
        int a = -1;
        try
        {
            a = stoi(select);
        }
        catch (const invalid_argument&)
        {
            cout << "\033[1;31m" << "[Error] 잘못된 입력입니다." << "\033[0m" << endl;
            continue;
        }
        cout << endl;
        system("cls");
        if (a > player->getInventory().size())
        {
            cout << "\033[1;31m" << "[Error] 입력 범위를 초과하였습니다. 다시 입력해주세요." << "\033[0m" << endl;
        }
        else if (a == 0)
        {
            isContinue = false;
        }
        else
        {
            cout << shop->itemSell(a - 1, player) << "골드 획득" << endl;
        }
    }
    return;
}

void GameManager::displayInventory(Character* player) const
{
    if (player == nullptr) return;

    cout << "\n================================= 인벤토리 ===========================================" << endl;
    for (int i = 0; i < player->getInventory().size(); ++i)
    {
        cout << player->getInventory()[i]->getName();
        if (i != player->getInventory().size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl << "======================================================================================" << endl;
    cout << endl;
}

void GameManager::displayKillCount(Character* player) const
{
    if (player == nullptr) return;

    cout << "\n=============================== 몬스터 처치 수 =======================================" << endl;
    for (pair<const string, int> count : killCount)
    {
        cout << "  " << count.first << " 처치 횟수 [" << count.second << "]" << endl;
    }
    cout << "======================================================================================" << endl;
}

bool GameManager::getIsGameOver()
{
    return isGameOver;
}