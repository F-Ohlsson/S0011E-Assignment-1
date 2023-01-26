#pragma once
#include <map>
#include <string>

//Used to identify what FoodVariables to fetch from foodDB
//Allows for easy creation of item using only an enum as argument
enum FoodVariant {
	food_bread,
	food_vegetables,
};

struct FoodVariables {
	int fullnessValue;
	int uses;
	std::string name;
};

class FoodTypes {
private:
	FoodTypes();
	std::map<FoodVariant, FoodVariables> foodDB;

public:
	static FoodTypes* Instance();
	FoodVariables FetchFood(FoodVariant);

};