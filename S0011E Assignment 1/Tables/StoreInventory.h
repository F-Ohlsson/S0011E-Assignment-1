#pragma once
#include <vector>
#include <string>
#include "../Code/GameEntity/GameEntitySubClasses/Consumable.h"
#include "DrinkTypes.h"
#include "FoodTypes.h"
#include "ToolTypes.h"

struct Item {
	ConsType itemType;
	int itemVariant;
	int cost;
};

class StoreInventory {
private:
	StoreInventory();
	std::vector<Item> inventory;
public:
	static StoreInventory* Instance();
	int GetInventorySize();
	Item GetInventoryAtIndex(int index);
	Item GetItemFromInventory(ConsType, int itemVariant);
};