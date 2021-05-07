#pragma once

#include "Organism.h"
#include <vector>

class World;
class Organism;

class Cemetery {
public:
	void bury();
	void kill(Organism* organism);
private:
	std::vector<Organism*> organisms = std::vector<Organism*>(0);
};

