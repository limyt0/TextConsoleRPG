#include "Troll.h"


Troll::Troll(int playerLevel) : Monster("트롤", playerLevel) {
	Health += playerLevel * 3; // 트롤 추가 체력 보너스
	Attack += playerLevel * 2; // 트롤 추가 공격력 보너스
}


