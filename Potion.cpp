#include "Potion.h"
#include <vector>

// 인벤토리 내의 모든 종류의 포션 개수를 반환하는 함수
int Potion::countTotalPotions(const std::vector<Item*>& inventory) {
    int count = 0;
    for (Item* item : inventory) {
        // 2. inventory가 const이므로 포인터도 const Potion*으로 캐스팅하는 것이 안전합니다.
        if (dynamic_cast<const Potion*>(item) != nullptr) {
            count++;
        }
    }
    return count;
}

void Potion::consumeOnePotion(std::vector<Item*>& inventory) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (dynamic_cast<Potion*>(*it) != nullptr) {
            delete* it;
            inventory.erase(it);
            return;
        }
    }
}