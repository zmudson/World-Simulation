#pragma once

#include "Plant.h"

class Guarana : public Plant {
public:
	Guarana(World* world, int positionX, int positionY);
	void spread(Field* field);
	void collision(Organism* attacker) override;
};

