#pragma once
#include "Monster.h"
#include "Potion.h"

struct GuardSummary {
    bool allSuccess;
    int failCount;
    int successCount;
};

class Boss : public Monster {
private:
    static bool isFirstPattern;
	int MaxHealth = Health;

public:
    Boss(Character* player);

    EntityState attackPlayer() override;

    void takeDamage(int damage) override;

    void onDeath() override;

    GuardSummary BossAttackGuard(int& potionCount);

    void showPatternGuide(); // 도움말 출력 함수

    int getMaxHealth() { return MaxHealth; }
};