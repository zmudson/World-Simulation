#pragma once

#include "Organism.h"

class Animal : public Organism{
public:
	Animal(World* world, int strength, int initiative, int positionX, int positionY, char symbol, std::string name);
	virtual void action() override;
	virtual void collision(Organism* attacker) override;
	virtual void draw() override;
	virtual void reproduce(Field* field) = 0;
};

