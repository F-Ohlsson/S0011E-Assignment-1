#include "EntityManager.h"

#include <iostream>

EntityManager::EntityManager() {

}

EntityManager* EntityManager::Instance() {
	static EntityManager instance;

	return &instance;
}

void EntityManager::AddEntity(GameEntity* entity) {
	this->entities.insert(std::pair<int, GameEntity*> (entity->ID, entity));
}

void EntityManager::RemoveEntity(int ID) {
	this->entities.erase(ID);
}

GameEntity* EntityManager::FetchEntityByID(int ID) {
	return this->entities.at(ID);
}

void EntityManager::PrintListOfEntities() {
	for (auto i = this->entities.begin(); i != this->entities.end(); i++) {
		std::cout << "Key: " << (*i).first << ", Value: " << (*i).second << "\n";
	}
}