#include "Human.h"
#include "Grass.h"
#include "Guarana.h"
#include "Dandelion.h"
#include <iostream>

#define STRENGTH 5
#define INITIATIVE 4
#define SYMBOL 'C'
#define NAME "czlowiek"
#define SKILL_STRENGTH 10
#define SKILL_DURATION_TIME 5
#define SKILL_RENEWING_TIME 5
#define YELLOW_COLOR_CODE 14

Human::Human(World* world, int positionX, int positionY) : 
	Animal(world, STRENGTH, INITIATIVE, positionX, positionY, SYMBOL, NAME) {

}

void Human::reproduce(Field* field) {
	// human can't have children
}

void Human::action(World::directions direction) {
	int x = position->getX();
	int y = position->getY();
	Field* currentField = world->getField(x, y);
	if (direction == World::directions::LEFT)
		x--;
	else if (direction == World::directions::RIGHT)
		x++;
	else if (direction == World::directions::UP)
		y--;
	else if (direction == World::directions::DOWN)
		y++;
	Field* newField = world->getField(x, y);
	if (newField->empty()) {
		currentField->removeOrganism();
		newField->setOrganism(this);
	}
	else {
		newField->getOrganism()->collision(this);
	}
	if (skillActivationTime == SKILL_DURATION_TIME) {
		std::string message = name + " traci moc magicznego eliksiru";
		world->appendMessage(message);
		isSkillActive = false;
		skillActivationTime++;
	}
	else if (skillActivationTime == SKILL_DURATION_TIME + SKILL_RENEWING_TIME) {
		isSkillReady = true;
		skillActivationTime = 0;
	}
	else if (isSkillActive) {
		strength--;
		skillActivationTime++;
	}
	else if (skillActivationTime > SKILL_DURATION_TIME) {
		skillActivationTime++;
	}

}

void Human::draw() {
	world->setOutputColor(YELLOW_COLOR_CODE);
	Organism::draw();
}

bool Human::validateMove(World::directions direction) {
	bool isValid = true;
	if (position->getX() == 0 && direction == World::directions::LEFT)
		isValid = false;
	else if (position->getX() == world->getWidth() - 1 && direction == World::directions::RIGHT)
		isValid = false;
	else if (position->getY() == 0 && direction == World::directions::UP)
		isValid = false;
	else if (position->getY() == world->getHeight() - 1 && direction == World::directions::DOWN)
		isValid = false;
	return isValid;
}

void Human::activateSkill() {
	if (isSkillReady) {
		isSkillActive = true;
		isSkillReady = false;
		strength = SKILL_STRENGTH;
		std::string message = name + " wypija magiczny eliksir";
		std::cout << message << std::endl;
	}
}

bool Human::getSkillActive() {
	return isSkillActive;
}

std::string Human::describeCollisionWithPlant(Organism* plant) {
	std::string message;
	if (dynamic_cast<Dandelion*>(plant) != nullptr) {
		message = name + " zdeptuje mlecz";
	}
	else if (dynamic_cast<Grass*>(plant) != nullptr) {
		message = name + " kosi trawe";
	}
	else if (dynamic_cast<Guarana*>(plant) != nullptr) {
		message = name + " je guarane, jego sila wzrasta do " + std::to_string(strength);
	}
	return message;
}

void Human::initSkillsFlags(int) {
	if (skillActivationTime == 0) {
		isSkillActive = false;
		isSkillReady = true;
	}
	else if (skillActivationTime < SKILL_DURATION_TIME) {
		isSkillActive = true;
		isSkillReady = false;
	}
	else {
		isSkillActive = false;
		isSkillReady = false;
	}
}

int Human::getSkillActivationTime() {
	return skillActivationTime;
}
