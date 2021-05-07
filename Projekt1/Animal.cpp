#include "Animal.h"
#include <iostream>

#define RED_COLOR_CODE 12

Animal::Animal(World* world, int strength, int initiative, int positionX, int positionY, char symbol, std::string name)
	: Organism(world, strength, initiative, positionX, positionY, symbol, name){}

void Animal::action(){
	Field* currentField = world->getField(position->getX(), position->getY());
	std::vector<Field*> fieldsAround = world->getFieldsAround(currentField);
	Field* drawnField = fieldsAround[rand() % fieldsAround.size()];
	if (drawnField->empty()) {
		currentField->removeOrganism();
		drawnField->setOrganism(this);
	}
	else {
		drawnField->getOrganism()->collision(this);
	}
}

void Animal::collision(Organism* attacker){
	if (name == attacker->getName()) {
		std::string message;
		Field* field = this->findEmptyField(attacker);
		if (field != nullptr) {
			this->reproduce(field);
			message = name + " wydaje na swiat potomka na polu " + field->getPosition()->toString();
		}
		else {
			message = name + " nie udalo sie rozmnozyc przez brak miejsca";
		}
		world->appendMessage(message);
	}
	else {
		Organism::collision(attacker);
	}
}

void Animal::draw() {
	world->setOutputColor(RED_COLOR_CODE);
	Organism::draw();
}
