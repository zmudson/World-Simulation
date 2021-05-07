#pragma once

#include "Plant.h"

class PoisonousBerries : public Plant {
public:
	PoisonousBerries(World* world, int positionX, int positionY);
	void spread(Field* field);
	void collision(Organism* attacker);
};

