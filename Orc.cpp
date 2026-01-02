#include "Orc.h"
#include "Character.h"


Orc::Orc(Character* player) : Monster("오크", player) {
   Attack += player->getLevel() * 3; // 오크 추가 공격력 보너스
}