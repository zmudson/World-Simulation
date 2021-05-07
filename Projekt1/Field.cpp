#include "Field.h"
#include <iostream>
#include "Human.h"
#include "Animal.h"
#include "Plant.h"

Field::Field(Organism* organism, int x, int y){
	this->organism = organism;
	this->isEmpty = organism == nullptr;
	this->position = new Vector2D(x, y);
}

Field::~Field(){
	delete position;
	if (organism != nullptr) {
		delete organism;
	}
}

Organism* Field::getOrganism(){
	return organism;
}

void Field::setOrganism(Organism* organism){
	if (organism != nullptr) {
		isEmpty = false;
		organism->setPosition(position->getX(), position->getY());
	}
	else
		isEmpty = true;
	this->organism = organism;
}

void Field::removeOrganism() {
	organism = nullptr;
	isEmpty = true;
}

Vector2D* Field::getPosition(){
	return position;
}

void Field::draw() {
	if (isEmpty)
		std::cout << symbol;
	else 
		organism->draw();
}

bool Field::empty() {
	return isEmpty;
}