#include "Cemetery.h"


void Cemetery::bury(){
	for (int i = 0; i < organisms.size(); i++) {
		delete organisms[i];
		organisms[i] = nullptr;
	}
	organisms.clear();
}

void Cemetery::kill(Organism* organism){
	organisms.push_back(organism);
}
