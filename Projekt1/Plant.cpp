#include "Plant.h"
#include <string>

#define INITIATIVE 0
#define SPREAD_CHANCE_PERCENTAGE 20
#define LIGHT_GREEN_COLOR_CODE 10

Plant::Plant(World* world, int strength, int positionX, int positionY, char symbol, std::string name)
	: Organism(world, strength, INITIATIVE, positionX, positionY, symbol, name) {}

void Plant::action() {
	if (rand() % 100 < SPREAD_CHANCE_PERCENTAGE) {
		std::string message;
		Field* field = this->findEmptyFieldAround();
		if (field != nullptr) {
			spread(field);
			message = name + " rozprzestrzenia sie na polu " + field->getPosition()->toString();
		}
		else {
			message = name + " nie udalo sie rozprzestrzenic przez brak miejsca";
		}
		world->appendMessage(message);
	}
}

void Plant::collision(Organism* attacker) {
	Organism::collision(attacker);
}

void Plant::draw() {
	world->setOutputColor(LIGHT_GREEN_COLOR_CODE);
	Organism::draw();
}
