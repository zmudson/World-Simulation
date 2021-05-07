#include "Sheep.h"

#define STRENGTH 4
#define INITIATIVE 4
#define SYMBOL 'O'
#define NAME "owca"

Sheep::Sheep(World* world, int positionX, int positionY) : 
	Animal(world, STRENGTH, INITIATIVE, positionX, positionY, SYMBOL, NAME) {

}

void Sheep::reproduce(Field* field) {
	Vector2D* position = field->getPosition();
	Sheep* sheep = new Sheep(world, position->getX(), position->getY());
	field->setOrganism(sheep);
}