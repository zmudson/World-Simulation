#include "Guarana.h"
#include <string>

#define STRENGTH 0
#define SYMBOL 'G'
#define NAME "guarana"
#define STRENGTH_BONUS 3

Guarana::Guarana(World* world, int positionX, int positionY) : 
	Plant(world, STRENGTH, positionX, positionY, SYMBOL, NAME) {

}

void Guarana::spread(Field* field) {
	Vector2D* position = field->getPosition();
	Guarana* guarana = new Guarana(world, position->getX(), position->getY());
	field->setOrganism(guarana);
}

void Guarana::collision(Organism* attacker) {
	Field* field = world->getField(position);
	Field* attackerField = world->getField(attacker->getPosition());
	attackerField->removeOrganism();
	field->removeOrganism();
	field->setOrganism(attacker);
	world->kill(this);
	attacker->setStrength(attacker->getStrength() + STRENGTH_BONUS);
	std::string message = attacker->getName() + " zjada " + name + ", sila wzrasta do " + std::to_string(attacker->getStrength());
	world->appendMessage(message);
}
