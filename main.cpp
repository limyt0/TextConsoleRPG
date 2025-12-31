#include <iostream>
#include "Character.h"
#include "GameManager.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

int main() {
	string name;
	cout << "| 캐릭터 이름을 설정하세요 |" << endl;
	//cin.ignore();
	bool isNameEmpty = false;
	while (!isNameEmpty) {
		getline(cin, name);
		if (name.empty()) {
			cout << "\033[1;31m" << "[Error] 캐릭터 이름을 다시 입력해주세요." << "\033[0m" << endl;
		}
		else {
			isNameEmpty = true;
		}
	}
	cout << endl;
	Character character(name);
	cout << "============================= 캐릭터 생성 완료 =======================================" << endl;
	cout << "  이름: " << character.getName() << ", 레벨:" << character.getLevel() << ", 체력 : " << character.getHealth() << ", 공격력 : " << character.getAttack() << endl;
	GameManager gameManager = GameManager();
	gameManager.generateMonster(character.getLevel());
	gameManager.battle(&character);
	bool isContinue = true;
	while (!gameManager.getIsGameOver() && isContinue) {
		cout << "\n================================= 행동선택 ===========================================" << endl;
		cout << "  1. [배틀] \n  2. [스탯보기] \n  3. [인벤토리 확인하기] \n  4. [몬스터 처치 로그 확인하기] \n  5. [상점] \n  0. [게임종료]" << endl;
		cout << "======================================================================================" << endl;
		string select;
		cin >> select;
		int a = -1;
		try {
			a = stoi(select);
		}
		catch (const std::invalid_argument& e) {
			cout << "\033[1;31m" << "[Error]잘못된 입력입니다." << "\033[0m" << endl;
			continue;
		}
		cout << endl;
		switch (a) {
		case  1:
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
		case 5:
			
			gameManager.useShop( &character);
			break;
		case 0:
			isContinue = false;
			break;
		default:
			cout << "\033[1;31m" << "[Error]숫자 범위가 안 맞습니다. 다시 입력해주세요." << "\033[0m" << endl;
			break;

		}

		//cin.get();
	}
	return 0;
}