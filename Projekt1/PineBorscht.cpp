#include "PineBorscht.h"
#include "Animal.h"

#define STRENGTH 10
#define SYMBOL 'B'
#define NAME "barszcz sosnowskiego"

PineBorscht::PineBorscht(World* world, int positionX, int positionY) : 
	Plant(world, STRENGTH, positionX, positionY, SYMBOL, NAME) {

}

void PineBorscht::spread(Field* field) {
	Vector2D* position = field->getPosition();
	PineBorscht* pineBorscht = new PineBorscht(world, position->getX(), position->getY());
	field->setOrganism(pineBorscht);
}

void PineBorscht::action() {
	Field* field = world->getField(position);
	std::vector<Field*> fields = world->getFieldsAround(field);
	for (int i = 0; i < fields.size(); i++) {
		Organism* organism = fields[i]->getOrganism();
		if (dynamic_cast<Animal*>(organism) != nullptr) {
			world->appendBattleResultMessage(this, organism);
			fields[i]->removeOrganism();
			world->kill(organism);
		}
	}
}

void PineBorscht::collision(Organism* attacker) {
	Field* attackerField = world->getField(attacker->getPosition());
	attackerField->removeOrganism();
	world->kill(attacker);
	world->appendBattleResultMessage(this, attacker);
}