#include "Drink.h"

//Create Food object of drinkVariant type
Drink::Drink(DrinkVariant drinkVariant) {
	this->type = cons_drink;
	DrinkVariables drinkVariables = DrinkTypes::Instance()->FetchDrink(drinkVariant);
	this->name = drinkVariables.name;
	this->hydrationValue = drinkVariables.hydrationValue;
	this->durability = drinkVariables.uses;
	this->active = true;
}

//Returns the value of thirst quenched for one use of specified drink consumable
int Drink::Use() {
	if (this->durability > 0) {
		this->durability -= 1;
		if (this->durability <= 0)
			this->active = false;
		return this->hydrationValue;
	}
	else {
		if (this->active)
			this->active = false;
		return 0;
	}
}

int Drink::GetHydrationValue() {
	return this->hydrationValue;
}

void Drink::Update() {

}

void Drink::HandleMessage(Message) {

}