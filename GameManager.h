#pragma once
#include <string>
#include <vector>
#include <map>
#include <random>
#include "Character.h"
#include "Monster.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
//#include "Boss.h"
#include "Item.h"
#include "Shop.h"

class GameManager
{
private:
    Monster* monster;
    bool isGameOver;
    map<string, int> killCount;
public:
    GameManager();

    // 몬스터 생성
    Monster* generateMonster(int level);
    // 보스 몬스터 생성
    //Monster* generateBossMonster(int level);
    // 배틀
    void battle(Character* player);
    // 보스 배틀
    void bossBattle(Character* player);
    // 상점 이용
    void useShop(Character* player);
    // 아이템 구매
    void buyItem(Shop* shop, Character* player);
    // 아이템 판매
    void sellItem(Shop* shop, Character* player);
    // 인벤토리 출력
    void displayInventory(Character* player);
    // 처치 로그 출력
    void displayKillCount(Character* player);
    // 게임오버 여부 반환
    bool getIsGameOver();
};