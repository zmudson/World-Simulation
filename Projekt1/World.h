#pragma once

#include "Organism.h"
#include "Vector2D.h"
#include "Field.h"
#include "Cemetery.h"
#include <string>
#include <vector>
#include <string>
#include <windows.h>

class Organism;
class Field;
class Cemetery;

class World {
public:
	enum class directions {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
	World(std::string filename);
	World(int n, int m);
	~World();
	bool handleTurn(enum class World::directions direction);
	void handleTurn();
	void draw();
	int getWidth();
	int getHeight();
	int getSize();
	bool running();

	void load(std::string filename);
	void save();
	std::string loadFilename();
	void addOrganism(Organism* organism, Field* field);
	void end();
	std::vector<Field*> getFieldsAround(int x, int y);
	std::vector<Field*> getFieldsAround(Field* field);
	Field* getField(int x, int y);
	Field* getField(Vector2D* position);
	void kill(Organism* organism);
	void activateSkill();
	void appendMessage(std::string message);
	void appendBattleResultMessage(Organism* winner, Organism* loser);
	void setOutputColor(int color);
	bool isHumanAlive();

private:
	Vector2D* dimensions;
	Field*** fields;
	Organism* human;
	Cemetery* cemetery;
	bool isRunning = false;
	std::string message = "";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;

	void init();
	int drawFieldIndex(std::vector<Field*> &fields);
	void handleOrganismInit(std::vector<Field*> &fields, Organism* organism);
	void handleOrganismInit(Organism* organism, int x, int y, int age, int strength);
	void drawLine();
	void sortOrganismsByAge(std::vector<Field*>& fields, int left, int right);
	void showResult();
	Organism* createOrganism(std::string name, int x, int y);
};

