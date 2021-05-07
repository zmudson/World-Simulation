#pragma once

#include "Animal.h"

class Turtle : public Animal {
public:
	Turtle(World* world, int positionX, int positionY);
	void reproduce(Field* field) override;
	void action() override;
	void collision(Organism* attacker) override;
};