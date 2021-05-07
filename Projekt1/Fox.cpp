#include "Fox.h"

#define STRENGTH 3
#define INITIATIVE 7
#define SYMBOL 'L'
#define NAME "lis"

Fox::Fox(World* world, int positionX, int positionY) : 
	Animal(world, STRENGTH, INITIATIVE, positionX, positionY, SYMBOL, NAME) {

}

void Fox::reproduce(Field* field) {
	Vector2D* position = field->getPosition();
	Fox* fox = new Fox(world, position->getX(), position->getY());
	field->setOrganism(fox);
}

void Fox::action() {
	Field* safeField = findSafeField();
	Field* currentField = world->getField(position);
	if (safeField != nullptr) {
		if (safeField->empty()) {
			currentField->removeOrganism();
			safeField->setOrganism(this);
		}
		else {
			safeField->getOrganism()->collision(this);
		}
	}
	else {
		std::string message = name + " nie wywachal wolnego miejsca, pozostaje na swoim polu";
		world->appendMessage(message);
	}
}

Field* Fox::findSafeField() {
	Field* currentField = world->getField(position);
	std::vector<Field*> fields = world->getFieldsAround(currentField);
	std::vector<Field*> safeFields(0);
	for (int i = 0; i < fields.size(); i++) {
		if (fields[i]->empty() || fields[i]->getOrganism()->getStrength() <= strength) {
			safeFields.push_back(fields[i]);
		}
	}
	if (safeFields.size() > 0) {
		return fields[rand() % fields.size()];
	}
	else {
		return nullptr;
	}
}