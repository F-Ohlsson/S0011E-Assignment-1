#pragma once
#include "../GameEntity.h"
#include <string>

//Used for indentification of consumable subclass to allow for safe casting to said subclass
enum ConsType {
	cons_food,
	cons_drink,
	cons_tool,
	cons_null = -1,
};

class Consumable : public GameEntity
{
protected:
	int durability;
public:
	std::string name;
	ConsType type;
	virtual int Use() = 0;
};

