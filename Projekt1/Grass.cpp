#include "Grass.h"

#define STRENGTH 0
#define SYMBOL 'T'
#define NAME "trawa"

Grass::Grass(World* world, int positionX, int positionY) : 
	Plant(world, STRENGTH, positionX, positionY, SYMBOL, NAME) {

}

void Grass::spread(Field* field) {
	Vector2D* position = field->getPosition();
	Grass* grass = new Grass(world, position->getX(), position->getY());
	field->setOrganism(grass);
}
