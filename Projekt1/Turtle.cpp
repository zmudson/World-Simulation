#include "Turtle.h"

#define STRENGTH 2
#define INITIATIVE 1
#define SYMBOL 'Z'
#define NAME "zolw"
#define MOVE_CHANCE_PERCENTAGE 75
#define MAX_STRENGTH_DEFENCE 4


Turtle::Turtle(World* world, int positionX, int positionY) : 
	Animal(world, STRENGTH, INITIATIVE, positionX, positionY, SYMBOL, NAME) {

}

void Turtle::reproduce(Field* field) {
	Vector2D* position = field->getPosition();
	Turtle* turtle = new Turtle(world, position->getX(), position->getY());
	field->setOrganism(turtle);
}

void Turtle::action() {
	if (rand() % 100 < MOVE_CHANCE_PERCENTAGE) {
		Animal::action();
	}
	else {
		std::string message = name + " zostaje na swoim polu";
		world->appendMessage(message);
	}
}

void Turtle::collision(Organism* attacker) {
	if (name == attacker->getName() || attacker->getStrength() > MAX_STRENGTH_DEFENCE) {
		Animal::collision(attacker);
	}
	else {
		std::string message = name + " odparl atak " + attacker->getName();
		world->appendMessage(message);
	}
}