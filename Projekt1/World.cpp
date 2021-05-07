#define _CRT_SECURE_NO_WARNINGS

#include "World.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Animal.h"
#include "Antelope.h"
#include "Dandelion.h"
#include "Fox.h"
#include "Grass.h"
#include "Guarana.h"
#include "Human.h"
#include "PineBorscht.h"
#include "PoisonousBerries.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"


#define SPECIES_NUMBER 10
#define BOARD_FILLING_PERCENTAGE 20
#define WHITE_COLOR_CODE 7
#define FILE_EXTENSION "txt"
#define FILE_ERROR_MESSAGE "Zaladowano niepoprawny plik!"
#define ANTELOPE_NAME "antylopa"
#define DANDELION_NAME "mlecz"
#define FOX_NAME "lis"
#define GRASS_NAME "trawa"
#define GUARANA_NAME "guarana"
#define HUMAN_NAME "czlowiek"
#define PINE_BORSCHT_NAME "barszcz sosnowskiego"
#define POISONOUS_BERRIES_NAME "wilcze jagody"
#define SHEEP_NAME "owca"
#define TURTLE_NAME "zolw"
#define WOLF_NAME "wilk"

World::World(std::string filename){
	cemetery = new Cemetery();
	load(filename);
	setOutputColor(WHITE_COLOR_CODE);
}

World::World(int n, int m){
	dimensions = new Vector2D(n, m);
	cemetery = new Cemetery();
	init();
	setOutputColor(WHITE_COLOR_CODE);
}

World::~World(){
	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			delete fields[y][x];
		}
	}
	delete dimensions;
	delete cemetery;
}



bool World::handleTurn(enum class World::directions direction){
	if (human != nullptr && !((Human*)human)->validateMove(direction))
		return false;
	message = "";
	const int initatives[] = { 7, 5, 4, 1 , 0};
	int length = sizeof(initatives) / sizeof(initatives[0]);
	std::vector<Field*> fieldsWithOrganisms(0);
	Field* currentField;
	for (int i = 0; i < length; i++) {
		for (int y = 0; y < getHeight(); y++) {
			for (int x = 0; x < getWidth(); x++) {
				currentField = fields[y][x];
				if (!currentField->empty() && currentField->getOrganism()->getInitiative() == initatives[i]){
					fieldsWithOrganisms.push_back(currentField);
					currentField->getOrganism()->incrementAge();
				}
			}
		}
		if (fieldsWithOrganisms.size() > 0) {
			sortOrganismsByAge(fieldsWithOrganisms, 0, fieldsWithOrganisms.size() - 1);
			for (int j = 0; j < fieldsWithOrganisms.size(); j++) {
				currentField = fieldsWithOrganisms[j];
				if (!currentField->empty()) {
					if (currentField->getOrganism() == human) {
						((Human*)human)->action(direction);
					}
					else {
						currentField->getOrganism()->action();
					}
				}
			}
			fieldsWithOrganisms.clear();
		}
	}
	cemetery->bury();
	return true;
}

void World::handleTurn() {
	handleTurn(directions::UP);
}

void World::sortOrganismsByAge(std::vector<Field*>& fields, int left, int right) {
	int i, j;
	Field* pivot;
	i = (left + right) / 2;
	pivot = fields[i];
	fields[i] = fields[right];
	fields[right] = pivot;
	i = left;
	j = left;
	while (i < right) {
		if (fields[i]->getOrganism()->getAge() < pivot->getOrganism()->getAge()) {
			Field* tmp = fields[i];
			fields[i] = fields[j];
			fields[j] = tmp;
			j++;
		}
		i++;
	}
	fields[right] = fields[j];
	fields[j] = pivot;
	if (left < j - 1) sortOrganismsByAge(fields, left, j - 1);
	if (right > j + 1) sortOrganismsByAge(fields, j + 1, right);
}

void World::draw(){
	system("cls");
	std::cout << "World simulation powered by Dominik Zmuda-Trzebiatowski (184926)" << std::endl << std::endl;
	drawLine();
	for (int y = 0; y < getHeight(); y++) {
		setOutputColor(WHITE_COLOR_CODE);
		std::cout << "*";
		for (int x = 0; x < getWidth(); x++) {
			fields[y][x]->draw();
			if(x != getWidth() - 1)
				std::cout << " ";
		}
		setOutputColor(WHITE_COLOR_CODE);
		std::cout << "*";
		std::cout << std::endl;
	}
	drawLine();
	setOutputColor(WHITE_COLOR_CODE);
	if (!message.empty()) {
		std::cout << "Wydarzenia:" << std::endl;
		drawLine();
		showResult();
		drawLine();
	}
}

void World::drawLine() {
	setOutputColor(WHITE_COLOR_CODE);
	for (int i = 0; i < getWidth() * 2 + 1; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;
}

int World::getWidth(){
	return dimensions->getX();
}

int World::getHeight(){
	return dimensions->getY();
}

int World::getSize(){
	return getWidth() * getHeight();
}


void World::init() {
	fields = new Field ** [getHeight()];
	std::vector<Field*> emptyFields(getSize());
	for (int y = 0, i = 0; y < getHeight(); y++) {
		fields[y] = new Field * [getWidth()];
		for (int x = 0; x < getWidth(); x++, i++) {
			Field* newField = new Field(nullptr, x, y);
			fields[y][x] = newField;
			emptyFields[i] = newField;
		}
	}

	Organism* human = new Human(this, -1, -1);
	handleOrganismInit(emptyFields, human);
	this->human = human;

	int organismsPerSpecies = getSize() * BOARD_FILLING_PERCENTAGE / SPECIES_NUMBER  / 100;
	for (int i = 0; i < organismsPerSpecies; i++) {
		Organism* antelope = new Antelope(this, -1, -1);
		handleOrganismInit(emptyFields, antelope);
		Organism* dandelion = new Dandelion(this, -1, -1);
		handleOrganismInit(emptyFields, dandelion);
		Organism* fox = new Fox(this, -1, -1);
		handleOrganismInit(emptyFields, fox);
		Organism* grass = new Grass(this, -1, -1);
		handleOrganismInit(emptyFields, grass);
		Organism* guarana = new Guarana(this, -1, -1);
		handleOrganismInit(emptyFields, guarana);
		Organism* pineBorscht = new PineBorscht(this, -1, -1);
		handleOrganismInit(emptyFields, pineBorscht);
		Organism* poisonousBerries = new PoisonousBerries(this, -1, -1);
		handleOrganismInit(emptyFields, poisonousBerries);
		Organism* sheep = new Sheep(this, -1, -1);
		handleOrganismInit(emptyFields, sheep);
		Organism* turtle = new Turtle(this, -1, -1);
		handleOrganismInit(emptyFields, turtle);
		Organism* wolf = new Wolf(this, -1, -1);
		handleOrganismInit(emptyFields, wolf);
	}
	isRunning = true;
}

void World::load(std::string filename) {
	std::ifstream file(filename);
	int n, m;
	std::string line = "";
	std::getline(file, line);
	std::istringstream iss(line);
	if (!(iss >> n >> m)) {
		isRunning = false;
		file.close();
		std::cout << FILE_ERROR_MESSAGE << std::endl;
		return;
	}
	dimensions = new Vector2D(n, m);
	fields = new Field **[getHeight()];
	for (int y = 0; y < getHeight(); y++) {
		fields[y] = new Field * [getWidth()];
		for (int x = 0; x < getWidth(); x++) {
			Field* newField = new Field(nullptr, x, y);
			fields[y][x] = newField;
		}
	}
	int x, y, age, strength;
	std::string name;

	while (std::getline(file, line)) {
		int index = line.find(':');
		name = line.substr(0, index);
		line = line.substr(index + 2);
		std::istringstream iss(line);
		if (name == HUMAN_NAME) {
			int skillActivationTime;
			if (!(iss >> x >> y >> age >> strength >> skillActivationTime)) {
				isRunning = false;
				file.close();
				std::cout << FILE_ERROR_MESSAGE << std::endl;
				return;
			}
			Organism* human = new Human(this, x, y);
			handleOrganismInit(human, x, y, age, strength);
			this->human = human;
			((Human*)human)->initSkillsFlags(skillActivationTime);
		}
		else {
			if (!(iss >> x >> y >> age >> strength)) {
				isRunning = false;
				file.close();
				std::cout << FILE_ERROR_MESSAGE << std::endl;
				return;
			}
			Organism* organism = createOrganism(name, x, y);
			handleOrganismInit(organism, x, y, age, strength);
		}
	}
	file.close();
	isRunning = true;
}

void World::save() {
	std::string filename = loadFilename();
	std::ofstream file(filename);
	std::string line;
	line = std::to_string(getWidth()) + " " + std::to_string(getHeight());
	file << line << std::endl;
	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			if (!fields[y][x]->empty()) {
				Organism* organism = fields[y][x]->getOrganism();
				Vector2D* position = organism->getPosition();
				line = organism->getName() + ": " + std::to_string(position->getX()) 
					+ " " + std::to_string(position->getY()) + " " + std::to_string(organism->getAge()) 
					+ " " + std::to_string(organism->getStrength());
				if (human != nullptr && dynamic_cast<Human*>(organism) != nullptr) {
					line += " " + std::to_string(((Human*)organism)->getSkillActivationTime());
				}
				file << line << std::endl;
			}
		}
	}
	file.close();
	draw();
	std::cout << "Symulacja zostala zapisana pomyslnie!" << std::endl;
}

std::string World::loadFilename() {
	std::string filename = "";
	while (true) {
		std::cout << "Podaj nazwe pliku (bez rozszerzenia): ";
		std::cin >> filename;
		if (filename.empty())
			std::cout << "Nazwa pliku nie moze byc pustym ciagiem znakow!" << std::endl;
		else
			return filename + "." + FILE_EXTENSION;
	}
}


Organism* World::createOrganism(std::string name, int x, int y) {
	Organism* organism = nullptr;
	if (name == ANTELOPE_NAME) 
		organism = new Antelope(this, x, y);
	else if(name == DANDELION_NAME)
		organism = new Dandelion(this, x, y);
	else if(name == FOX_NAME)
		organism = new Fox(this, x, y);
	else if(name == GRASS_NAME)
		organism = new Grass(this, x, y);
	else if(name == GUARANA_NAME)
		organism = new Guarana(this, x, y);
	else if (name == PINE_BORSCHT_NAME)
		organism = new PineBorscht(this, x, y);
	else if (name == POISONOUS_BERRIES_NAME)
		organism = new PoisonousBerries(this, x, y);
	else if (name == SHEEP_NAME)
		organism = new Sheep(this, x, y);
	else if (name == TURTLE_NAME)
		organism = new Turtle(this, x, y);
	else if (name == WOLF_NAME)
		organism = new Wolf(this, x, y);
	return organism;
}

void World::addOrganism(Organism* organism, Field* field) {
	field->setOrganism(organism);
}

int World::drawFieldIndex(std::vector<Field*> &fields) {
	return rand() % fields.size();
}

void World::handleOrganismInit(std::vector<Field*>& fields, Organism* organism) {
	int index = drawFieldIndex(fields);
	Field* drawnField = fields[index];
	int lastIndex = fields.size() - 1;
	fields[index] = fields.back();
	fields[lastIndex] = drawnField;
	fields.pop_back();
	addOrganism(organism, drawnField);
	Vector2D* position = drawnField->getPosition();
	organism->setPosition(position->getX(), position->getY());
}

void World::handleOrganismInit(Organism* organism, int x, int y, int age, int strength) {
	organism->setAge(age);
	organism->setStrength(strength);
	Field* field = getField(x, y);
	field->setOrganism(organism);
}


bool World::running(){
	return isRunning;
}

void World::end(){
	isRunning = false;
}

std::vector<Field*> World::getFieldsAround(int x, int y) {
	std::vector<Field*> fieldsAround;
	if (x != 0)
		fieldsAround.push_back(fields[y][x - 1]);
	if(x != getWidth() - 1)
		fieldsAround.push_back(fields[y][x + 1]);
	if (y != 0)
		fieldsAround.push_back(fields[y - 1][x]);
	if (y != getHeight() - 1)
		fieldsAround.push_back(fields[y + 1][x]);

	return fieldsAround;
}

std::vector<Field*> World::getFieldsAround(Field* field) {
	Vector2D* position = field->getPosition();
	return getFieldsAround(position->getX(), position->getY());
}

Field* World::getField(int x, int y) {
	return fields[y][x];
}

Field* World::getField(Vector2D* position) {
	return getField(position->getX(), position->getY());
}

void World::kill(Organism* organism) {
	if (organism == human) {
		human = nullptr;
	}
	cemetery->kill(organism);
}

void World::activateSkill() {
	if (human != nullptr) {
		((Human*)human)->activateSkill();
	}
}

void World::appendMessage(std::string message) {
	this->message += message + "\n";
}

void World::appendBattleResultMessage(Organism* winner, Organism* loser) {
	std::string message;
	if (dynamic_cast<Plant*>(loser) != nullptr) {
		if (dynamic_cast<Human*>(winner) != nullptr) {
			message = ((Human*)winner)->describeCollisionWithPlant(loser);
		}
		else {
			message = winner->getName() + " zjada " + loser->getName();
		}
	}
	else {
		message = winner->getName() + " zabija " + loser->getName();
	}
	appendMessage(message);
}

void World::showResult() {
	std::cout << message;
}

void World::setOutputColor(int color) {
	SetConsoleTextAttribute(hConsole, color);
}

bool World::isHumanAlive() {
	return human != nullptr;
}
