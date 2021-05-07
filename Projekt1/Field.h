#pragma once

#include "Organism.h"
#include "Vector2D.h"

class Organism;

class Field {
public:
	Field(Organism* organism, int x, int y);
	~Field();
	Organism* getOrganism();
	void setOrganism(Organism* organism);
	void removeOrganism();
	Vector2D* getPosition();
	void draw();
	bool empty();
private:
	Organism* organism;
	bool isEmpty;
	Vector2D* position;
	char symbol = ' ';
};

