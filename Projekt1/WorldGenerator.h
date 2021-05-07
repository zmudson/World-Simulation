#pragma once

#include "World.h"
#include <string>

class WorldGenerator {
public:
	World* generate();
private:
	int loadDimension(std::string message);
	std::string loadFilename(std::string message);
	void printMenu();
};

