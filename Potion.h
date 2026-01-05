#pragma once
#include <vector>
#include "Item.h"

class Potion : public Item
{
public:

	virtual ~Potion() {}

    static int countTotalPotions(const std::vector<Item*>& inventory);

    static void consumeOnePotion(std::vector<Item*>& inventory);
};

