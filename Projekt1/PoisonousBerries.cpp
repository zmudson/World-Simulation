#include "PoisonousBerries.h"

#define STRENGTH 99
#define SYMBOL 'J'
#define NAME "wilcze jagody"

PoisonousBerries::PoisonousBerries(World* world, int positionX, int positionY) : 
	Plant(world, STRENGTH, positionX, positionY, SYMBOL, NAME) {

}

void PoisonousBerries::spread(Field* field) {
	Vector2D* position = field->getPosition();
	PoisonousBerries* poisonousBerries = new PoisonousBerries(world, position->getX(), position->getY());
	field->setOrganism(poisonousBerries);
}

void PoisonousBerries::collision(Organism* attacker) {
	Field* attackerField = world->getField(attacker->getPosition());
	attackerField->removeOrganism();
	world->kill(attacker);
	world->appendBattleResultMessage(this, attacker);
}
