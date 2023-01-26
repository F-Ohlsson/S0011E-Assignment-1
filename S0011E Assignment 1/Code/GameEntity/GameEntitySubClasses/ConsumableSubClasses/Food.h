#pragma once
#include "../Consumable.h"
#include "../../../../Tables/FoodTypes.h"

class Food : public Consumable{
private:
	int fullnessValue;
public:
	Food(FoodVariant);
	int Use();
	int GetFullnessValue();
	void Update();
	void HandleMessage(Message);

};

