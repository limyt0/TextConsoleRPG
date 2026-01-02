#include "Troll.h"
#include "Character.h"


Troll::Troll(Character* player) : Monster("트롤", player) {
	Health += player->getLevel() * 3; // 트롤 추가 체력 보너스
	Attack += player->getLevel() * 2; // 트롤 추가 공격력 보너스
}


