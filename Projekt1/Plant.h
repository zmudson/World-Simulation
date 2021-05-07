#pragma once

#include "Organism.h"

class Plant : public Organism{
public:
	Plant(World* world, int strength, int positionX, int positionY, char symbol, std::string name);
	virtual void action() override;
	virtual void collision(Organism* attacker) override;
	virtual void draw() override;
	virtual void spread(Field* field) = 0;
};

