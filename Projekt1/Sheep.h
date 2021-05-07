#pragma once

#include "Animal.h"

class Sheep : public Animal {
public:
	Sheep(World* world, int positionX, int positionY);
	void reproduce(Field* field) override;
};



