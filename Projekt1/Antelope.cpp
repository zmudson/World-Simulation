#include "Antelope.h"

#define STRENGTH 4
#define INITIATIVE 4
#define SYMBOL 'A'
#define NAME "antylopa"
#define ESCAPE_CHANCE_PERCENTAGE 50

Antelope::Antelope(World* world, int positionX, int positionY) 
	: Animal(world, STRENGTH, INITIATIVE, positionX, positionY, SYMBOL, NAME) {

}

void Antelope::reproduce(Field* field) {
	Vector2D* position = field->getPosition();
	Antelope* antelope = new Antelope(world, position->getX(), position->getY());
	field->setOrganism(antelope);
}

void Antelope::action() {
	Field* currentField = world->getField(position);
	std::vector<Field*> fields = world->getFieldsAround(currentField);
	Field* drawnField = fields[rand() % fields.size()];
	fields = world->getFieldsAround(drawnField);
	std::vector<Field*> possibleFields(0);
	for (int i = 0; i < fields.size(); i++) {
		if (fields[i] != currentField)
			possibleFields.push_back(fields[i]);
	}
	drawnField = possibleFields[rand() % possibleFields.size()];
	if (drawnField->empty()) {
		currentField->removeOrganism();
		drawnField->setOrganism(this);
	}
	else {
		drawnField->getOrganism()->collision(this);
	}
}

void Antelope::collision(Organism* attacker) {
	if (attacker->getName() == name || rand() % 100 >= ESCAPE_CHANCE_PERCENTAGE) {
		Animal::collision(attacker);
	}
	else {
		Field* attackerField = world->getField(attacker->getPosition());
		attackerField->removeOrganism();
		Field* emptyField = findEmptyFieldAround();
		Field* currentField = world->getField(position);
		emptyField->setOrganism(this);
		currentField->setOrganism(attacker);
		std::string message = name + " ucieka przed " + attacker->getName();
		world->appendMessage(message);
	}
}