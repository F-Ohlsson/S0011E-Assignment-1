#include "FoodTypes.h"

FoodTypes::FoodTypes() {
	//Set up food database on first instantiation

	//Bread
	FoodVariant bread = food_bread;
	FoodVariables breadVariables;
	breadVariables.name = "bread";
	breadVariables.fullnessValue = 30;
	breadVariables.uses = 2;
	this->foodDB.insert({ bread, breadVariables });

	//Vegetables
	FoodVariant vegetables = food_vegetables;
	FoodVariables vegetableVariables;
	vegetableVariables.name = "vegetables";
	vegetableVariables.fullnessValue = 10;
	vegetableVariables.uses = 4;
	this->foodDB.insert({ vegetables, vegetableVariables });

}

FoodVariables FoodTypes::FetchFood(FoodVariant food) {
	return this->foodDB.at(food);
}

FoodTypes* FoodTypes::Instance() {
	static FoodTypes instance;

	return &instance;
}