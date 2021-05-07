#pragma once

#include "Animal.h"

class Human : public Animal {
public:
	Human(World* world, int positionX, int positionY);
	void reproduce(Field* field) override;
	void action(World::directions direction);
	void draw() override;
	bool validateMove(World::directions direction);
	void activateSkill();
	bool getSkillActive();
	std::string describeCollisionWithPlant(Organism* plant);
	void initSkillsFlags(int skillActivationTime);
	int getSkillActivationTime();
private:
	bool isSkillActive = false;
	bool isSkillReady = true;
	int skillActivationTime = 0;
};