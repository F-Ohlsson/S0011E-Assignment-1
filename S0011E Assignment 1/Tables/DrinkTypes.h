#pragma once
#include <map>
#include <string>

//Used to identify what DrinkVariables to fetch from drinkDB
//Allows for easy creation of item using only an enum as argument
enum DrinkVariant {
	drink_fancyWater,
	drink_water,
};

struct DrinkVariables {
	int hydrationValue;
	int uses;
	std::string name;
};

class DrinkTypes {
private:
	DrinkTypes();
	std::map<DrinkVariant, DrinkVariables> drinkDB;

public:
	static DrinkTypes* Instance();
	DrinkVariables FetchDrink(DrinkVariant);

};