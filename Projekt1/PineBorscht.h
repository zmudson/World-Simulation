#pragma once

#include "Plant.h"

class PineBorscht : public Plant {
public:
	PineBorscht(World* world, int positionX, int positionY);
	void spread(Field* field);
	void action() override;
	void collision(Organism* attacker);
};
