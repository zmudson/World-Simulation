#include "Wolf.h"

#define STRENGTH 9
#define INITIATIVE 5
#define SYMBOL 'W'
#define NAME "wilk"

Wolf::Wolf(World* world, int positionX, int positionY) : 
	Animal(world, STRENGTH, INITIATIVE, positionX, positionY, SYMBOL, NAME){

}

void Wolf::reproduce(Field* field) {
	Vector2D* position = field->getPosition();
	Wolf* wolf = new Wolf(world, position->getX(), position->getY());
	field->setOrganism(wolf);
}