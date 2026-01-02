#include "Boss.h"
#include <thread>
#include <chrono>

Boss::Boss(int playerLevel) : Monster("보스 몬스터", playerLevel)
{
	Health += playerLevel * 70; // 보스 추가 체력 보너스
	Attack += playerLevel * 20;  // 보스 추가 공격력 보너스
}

//int Boss::attackPlayer(class Character* player) {
//
//}

void Boss::onDeath() {

	std::cout << "\n\n\033[1;33m BOSS : " << Name << "를 물리쳤다! ]\033[0m" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "\n  세상에 평화가 찾아왔습니다..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));

	// 엔딩 크레딧 연출
	std::string credits[] = {
		"          --- ENDING CREDITS ---",
		"          TextConsole RPG by 5조",
		"  ",
		"조장 및 메인 구현 및 팀원 보조 : 임 영택  ",
		"캐릭터 및 상점 클래스구현      : 정 야후  ",
		"게임 매니저 클래스 구현        : 이 병헌  ",
		"아이템 클래스 구현             : 강 민승  ",
		"몬스터 클래스 구현             : 이 현진  ",
		"------------------------------------------",
		"           THANKS FOR PLAYING!  "
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
	};

	for (const std::string& line : credits) {
		std::cout << "      " << line << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(800)); // 0.8초 간격 출력
	}
}