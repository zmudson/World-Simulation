#pragma once

#include "Animal.h"
#include "Field.h"

class Fox : public Animal {
public:
	Fox(World* world, int positionX, int positionY);
	void reproduce(Field* field) override;
	void action() override;
	Field* findSafeField();
};