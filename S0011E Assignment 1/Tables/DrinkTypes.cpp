#include "DrinkTypes.h"

DrinkTypes::DrinkTypes() {
	//Set up drink database on first instantiation
	
	//Fancy Water
	DrinkVariant fWater = drink_fancyWater;
	DrinkVariables fwaterVariables;
	fwaterVariables.name = "fancy water";
	fwaterVariables.hydrationValue = 40;
	fwaterVariables.uses = 2;
	this->drinkDB.insert({ fWater, fwaterVariables });

	//regular water
	DrinkVariant water = drink_water;
	DrinkVariables waterVariables;
	waterVariables.name = "water";
	waterVariables.hydrationValue = 15;
	waterVariables.uses = 2;
	this->drinkDB.insert({ water, waterVariables });

}

DrinkVariables DrinkTypes::FetchDrink(DrinkVariant type) {
	return this->drinkDB.at(type);
}

DrinkTypes* DrinkTypes::Instance() {
	static DrinkTypes instance;

	return &instance;
}