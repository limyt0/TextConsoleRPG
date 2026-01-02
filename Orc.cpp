#include "Orc.h"



Orc::Orc(int playerLevel) : Monster("오크", playerLevel) {
   Attack += playerLevel * 3; // 오크 추가 공격력 보너스
}