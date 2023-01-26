#pragma once
#include <map>
#include "../GameEntity/GameEntity.h" //gameentity
class GameEntity;

class EntityManager
{
private:
	EntityManager();
	std::map<int, GameEntity*> entities;
public:
	static EntityManager* Instance();
	void AddEntity(GameEntity*);
	void RemoveEntity(int);
	GameEntity* FetchEntityByID(int);
	void PrintListOfEntities();
};

