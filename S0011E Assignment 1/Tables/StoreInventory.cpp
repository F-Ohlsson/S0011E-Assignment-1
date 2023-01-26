#include "StoreInventory.h"


StoreInventory::StoreInventory() {
	//Fill store inventory on first instantiation

	Item bread;
	bread.itemType = cons_food;
	bread.itemVariant = food_bread;
	bread.cost = 6;
	this->inventory.push_back(bread);

	Item vegetables;
	vegetables.itemType = cons_food;
	vegetables.itemVariant = food_vegetables;
	vegetables.cost = 3;
	this->inventory.push_back(vegetables);

	Item fancyWater;
	fancyWater.itemType = cons_drink;
	fancyWater.itemVariant = drink_fancyWater;
	fancyWater.cost = 6;
	this->inventory.push_back(fancyWater);

	Item water;
	water.itemType = cons_drink;
	water.itemVariant = drink_water;
	water.cost = 3;
	this->inventory.push_back(water);

	Item pickaxe;
	pickaxe.itemType = cons_tool;
	pickaxe.itemVariant = tool_pickaxe;
	pickaxe.cost = 9;
	this->inventory.push_back(pickaxe);

}

StoreInventory* StoreInventory::Instance() {
	static StoreInventory instance;

	return &instance;
}

int StoreInventory::GetInventorySize() {
	return (int)this->inventory.size();
}

Item StoreInventory::GetInventoryAtIndex(int index) {
	return this->inventory[index];
}

Item StoreInventory::GetItemFromInventory(ConsType itemType, int itemVariant) {
	for (int i = 0; i < this->inventory.size(); i++) {
		if ((this->inventory[i].itemType == itemType) && (this->inventory[i].itemVariant == itemVariant)) {
			return this->inventory[i];
		}
	}
	Item nullItem;
	nullItem.cost = 0;
	nullItem.itemType = cons_null;
	nullItem.itemVariant = -1;
	return nullItem;
}