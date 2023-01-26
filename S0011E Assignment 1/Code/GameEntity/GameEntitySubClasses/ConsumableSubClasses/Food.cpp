#include "Food.h"

//Create Food object of foodVariant type
Food::Food(FoodVariant foodVariant) {
	this->type = cons_food;
	FoodVariables temp = FoodTypes::Instance()->FetchFood(foodVariant);
	this->fullnessValue = temp.fullnessValue;
	this->durability = temp.uses;
	this->name = temp.name;
	this->active = true;
}

//Returns the value of hunger satisfied for one use of specified food consumable
int Food::Use() {
	if (this->durability > 0) {
		this->durability -= 1;
		if (this->durability <= 0)
			this->active = false;
		return this->fullnessValue;
	}
	else {
		if (this->active)
			this->active = false;
		return 0;
	}
}

int Food::GetFullnessValue() {
	return this->fullnessValue;
}

void Food::Update() {

}
void Food::HandleMessage(Message) {

}