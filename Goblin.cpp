#include "Goblin.h"


Goblin::Goblin(int playerLevel) : Monster("고블린", playerLevel) {
	Attack += playerLevel; // 고블린 추가 공격력 보너스
}
