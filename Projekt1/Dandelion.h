#pragma once

#include "Plant.h"

class Dandelion : public Plant {
public:
	Dandelion(World* world, int positionX, int positionY);
	void spread(Field* field);
	void action() override;
};