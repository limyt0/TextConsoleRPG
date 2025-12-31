#include <iostream>
#include "Character.h"
#include "GameManager.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

int main() {
	string name;
	cout << "캐릭터 이름을 설정하세요: " << endl;
	cin >> name;
	Character character(name);
	cout << "캐릭터 " << character.getName() << "생성 완료! 레벨: " << character.getLevel() << ", 체력: " << character.getHealth() << ", 공격력: " << character.getAttack() << endl;
	GameManager gameManager = GameManager();
    gameManager.generateMonster(character.getLevel());
    gameManager.battle(&character);
	bool isContinue = true;
	while (!gameManager.getIsGameOver() && isContinue) {
		cout << "=======================================================" << endl;
		cout << "1: 배틀 2: 스탯보기 3: 인벤토리 확인하기" << endl;
		cout << "4: 몬스터 처치 로그 확인하기 0: 게임종료." << endl;
		cout << "=======================================================" << endl;
		int select;
		cin >> select;
		switch (select) {
		case 1:
			gameManager.generateMonster(character.getLevel());
			gameManager.battle(&character);
			break;
		case 2:
			//
			character.showStatus();
			break;
		case 3: 
			//인벤토리 확인
			gameManager.displayInventory(&character);
			break;
		case 4:
			gameManager.displayKillCount(&character);
			break;
		case 0:
			isContinue = false;
			break;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
			break;

		}

		//cin.get();
	}
	return 0; 
}