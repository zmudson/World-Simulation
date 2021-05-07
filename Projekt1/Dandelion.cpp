#include "Dandelion.h"

#define STRENGTH 0
#define SYMBOL 'M'
#define NAME "mlecz"
#define SPREAD_ATTEMPTS_NUMBER 3

Dandelion::Dandelion(World* world, int positionX, int positionY) : 
	Plant(world, STRENGTH, positionX, positionY, SYMBOL, NAME) {

}

void Dandelion::spread(Field* field) {
	Vector2D* position = field->getPosition();
	Dandelion* dandelion = new Dandelion(world, position->getX(), position->getY());
	field->setOrganism(dandelion);
}

void Dandelion::action() {
	for (int i = 0; i < SPREAD_ATTEMPTS_NUMBER; i++) {
		Plant::action();
	}
}