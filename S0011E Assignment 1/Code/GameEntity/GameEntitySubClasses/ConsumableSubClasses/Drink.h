#pragma once
#include "../Consumable.h"
#include "../../../../Tables/DrinkTypes.h"

class Drink : public Consumable {
private:
	int hydrationValue;
public:
	Drink(DrinkVariant drink);
	int Use();
	int GetHydrationValue();
	void Update();
	void HandleMessage(Message);

};