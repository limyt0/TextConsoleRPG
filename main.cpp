#include <iostream>
#include "Character.h"
#include "GameManager.h"

using namespace std;

int main() {
	string name;
	cout << "캐릭터 이름을 설정하세요: " << endl;
	cin >> name;
	Character character(name);
	cout << "캐릭터 " << character.getName() << "생성 완료! 레벨: " << character.getLevel() << ", 체력: " << character.getHealth() << ", 공격력: " << character.getAttack() << endl;
	GameManager gameManager = GameManager();
	/*while (!gameManager.getIsGameOver()) {
	}*/
		gameManager.generateMonster(character.getLevel());
		gameManager.battle(&character);
	return 0; 
}