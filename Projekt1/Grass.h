#pragma once

#include "Plant.h"

class Grass : public Plant{
public:
	Grass(World* world, int positionX, int positionY);
	void spread(Field* field);
};

