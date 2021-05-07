#pragma once

#include "Animal.h"

class Antelope : public Animal {
public:
	Antelope(World* world, int positionX, int positionY);
	void reproduce(Field* field) override;
	void action() override;
	void collision(Organism* attacker) override;
};