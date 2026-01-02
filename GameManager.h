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
#include "Boss.h"
#include "Item.h"
#include "Shop.h"

class GameManager
{
private:
    // 몬스터 클래스 포인터 변수
    Monster* monster;
    // 게임 오버 여부 체크 변수
    bool isGameOver;
    // 몬스터 처치 로그
    map<string, int> killCount;
public:
    // 게임매니저 생성자
    GameManager();
    // 몬스터 생성
    Monster* generateMonster(int level);
    // 보스 몬스터 생성
    Monster* generateBossMonster(int level);
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
    void displayInventory(Character* player) const;
    // 처치 로그 출력
    void displayKillCount(Character* player) const;
    // 게임오버 여부 반환
    bool getIsGameOver();
};