#pragma once

#include "Animal.h"

class Wolf : public Animal{
public:
	Wolf(World* world, int positionX, int positionY);
	void reproduce(Field* field) override;
};

