#pragma once

#include <string>
#include "World.h"
#include "Vector2D.h"

class World;
class Field;
class Cemetery;

class Organism {
public:
	Organism(World* world, int strength, int initiative, int positionX, int positionY, char symbol, std::string name);
	~Organism();
	int getStrength() const;
	void setStrength(int strength);
	int getInitiative() const;
	void setInitiative(int initiative);
	Vector2D* getPosition() const;
	void setPosition(int x, int y);
	int getAge();
	void setAge(int age);
	void incrementAge();
	std::string getName();
	Field* findEmptyField(Organism* organism);
	Field* findEmptyFieldAround();

	virtual void action() = 0;
	virtual void collision(Organism* attacker);
	virtual void draw();
protected:
	World* world;
	Vector2D* position;
	std::string name;
	int strength;
private:
	int initiative;
	char symbol;
	int age = 0;
};

