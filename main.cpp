#include <iostream>
#include "Character.h"
#include "GameManager.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <Windows.h>

using namespace std;

// 커서 옮기기
void gotoXY(int x, int y);
// 타이틀
void title();

int main() {
	system("mode con cols=87 lines=30 | title TextConsoleRPG"); // 콘솔 창 크기 및 제목 설정
	title();
	gotoXY(27, 25);
	string name;
	cout << "  | 캐릭터 이름을 설정하세요 |" << endl;
	gotoXY(39, 27);
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
	system("cls");
	cout << endl;
	Character character(name);
	cout << "================================== 캐릭터 생성 완료 ==================================" << endl;
	cout << "  이름: " << character.getName() << ", 레벨:" << character.getLevel() << ", 체력 : " << character.getHealth() << ", 공격력 : " << character.getAttack() << endl;
	GameManager gameManager = GameManager();
	gameManager.generateMonster(&character);
	gameManager.battle(&character);
	bool isContinue = true;
	while (!gameManager.getIsGameOver() && isContinue) {
		cout << "\n====================================== 행동선택 ======================================" << endl;
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
		system("cls");
		switch (a) {
		case  1:
			if (character.getLevel() >= 10) {
				gameManager.generateBossMonster(&character);
				gameManager.bossBattle(&character);
			}
			else {
				gameManager.generateMonster(&character);
				gameManager.battle(&character);
			}
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

void gotoXY(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title() {
	cout << "\n  d888888b d88888b db    db d888888b\n";
	cout << "  `~~88~~' 88'     `8b  d8' `~~88~~'\n";
	cout << "     88    88ooooo  `8bd8'     88   \n";
	cout << "     88    88~~~~~  .dPYb.     88   \n";
	cout << "     88    88.     .8P  Y8.    88   \n";
	cout << "     YP    Y88888P YP    YP    YP   \n";
	cout << "   .o88b.  .d88b.  d8b   db .d8888.  .d88b.  db      d88888b\n";
	cout << "  d8P  Y8 .8P  Y8. 888o  88 88'  YP .8P  Y8. 88      88'    \n";
	cout << "  8P      88    88 88V8o 88 `8bo.   88    88 88      88ooooo\n";
	cout << "  8b      88    88 88 V8o88   `Y8b. 88    88 88      88~~~~~\n";
	cout << "  Y8b  d8 `8b  d8' 88  V888 db   8D `8b  d8' 88booo. 88.     \n";
	cout << "   `Y88P'  `Y88P'  VP   V8P `8888Y'  `Y88P'  Y88888P Y88888P\n";
	cout << "  d8888b. d8888b.  d888b \n";
	cout << "  88  `8D 88  `8D 88' Y8b\n";
	cout << "  88oobY' 88oodD' 88     \n";
	cout << "  88`8b   88~~~   88  ooo\n";
	cout << "  88 `88. 88      88. ~8~\n";
	cout << "  88   YD 88       Y888P \n";
}