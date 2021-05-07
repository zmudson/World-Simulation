#include "Organism.h"
#include "Plant.h"
#include <iostream>

Organism::Organism(World* world, int strength, int initiative, int positionX, int positionY, char symbol, std::string name) {
	this->world = world;
	this->strength = strength;
	this->initiative = initiative;
	this->position = new Vector2D(positionX, positionY);
	this->symbol = symbol;
	this->name = name;
}

Organism::~Organism() {
	delete position;
}

int Organism::getStrength() const{
	return strength;
}

void Organism::setStrength(int strength){
	this->strength = strength;
}

int Organism::getInitiative() const{
	return initiative;
}

void Organism::setInitiative(int initiative){
	this->initiative = initiative;
}

Vector2D* Organism::getPosition() const{
	return position;
}

void Organism::setPosition(int x, int y){
	delete position;
	position = new Vector2D(x, y);
}

void Organism::draw() {
	std::cout << symbol;
}

int Organism::getAge(){
	return age;
}

void Organism::setAge(int age){
	this->age = age;
}

void Organism::incrementAge(){
	age++;
}

std::string Organism::getName() {
	return name;
}

Field* Organism::findEmptyField(Organism* organism) {
	std::vector<Field*> organismFieldsAround = world->getFieldsAround(position->getX(), position->getY());
	Vector2D* otherOrganismPosition = organism->getPosition();
	std::vector<Field*> otherOrganismFieldsAround = world->getFieldsAround(otherOrganismPosition->getX(), otherOrganismPosition->getY());
	std::vector<Field*> emptyFields(0);
	Field* currentField;
	for (int i = 0; i < organismFieldsAround.size(); i++) {
		currentField = organismFieldsAround[i];
		if (currentField->empty()) {
			emptyFields.push_back(currentField);
		}
	}
	for (int i = 0; i < otherOrganismFieldsAround.size(); i++) {
		currentField = otherOrganismFieldsAround[i];
		if (currentField->empty()) {
			emptyFields.push_back(currentField);
		}
	}
	if (emptyFields.size() > 0) {
		return emptyFields[rand() % emptyFields.size()];
	}
	else {
		return nullptr;
	}
}

Field* Organism::findEmptyFieldAround() {
	std::vector<Field*> fieldsAround = world->getFieldsAround(position->getX(), position->getY());
	std::vector<Field*> emptyFields(0);
	Field* currentField;
	for (int i = 0; i < fieldsAround.size(); i++) {
		currentField = fieldsAround[i];
		if (currentField->empty()) {
			emptyFields.push_back(currentField);
		}
	}
	if (emptyFields.size() > 0) {
		return emptyFields[rand() % emptyFields.size()];
	}
	else {
		return nullptr;
	}
}


void Organism::collision(Organism* attacker) {
	Organism* winner;
	Organism* loser;
	if (attacker->getStrength() >= strength) {
		winner = attacker;
		loser = this;
	}
	else {
		winner = this;
		loser = attacker;
	}
	Vector2D* winnerPosition = winner->getPosition();
	Vector2D* loserPosition = loser->getPosition();
	Field* winnerField = world->getField(winnerPosition);
	Field* loserField = world->getField(loserPosition);
	loserField->removeOrganism();
	winnerField->removeOrganism();
	world->getField(position)->setOrganism(winner);
	world->kill(loser);
	world->appendBattleResultMessage(winner, loser);
}