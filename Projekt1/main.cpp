#include <iostream>
#include <conio.h>
#include <string>

#include "World.h"
#include "WorldGenerator.h"

#define KEY_UP 104
#define KEY_DOWN 112
#define KEY_LEFT 107
#define KEY_RIGHT 109
#define QUIT 113 // q - ASCII code
#define SKILL_ACTIVATION 101 // e - ASCII code
#define SAVE 115 // s - ASCII code
#define NEW_TURN 110 // n - ASCII code

int main() {
	WorldGenerator* generator = new WorldGenerator();
	World* world = generator->generate();
    if (world != nullptr) {
        world->draw();
        char choice;
        bool isValid, turnCompleted;
        while (world->running()) {
            isValid = false;
            enum class World::directions direction;
            choice = tolower(_getch());
            switch (choice) {
                case KEY_UP:
                    direction = World::directions::UP;
                    isValid = true;
                    break;
                case KEY_DOWN:
                    direction = World::directions::DOWN;
                    isValid = true;
                    break;
                case KEY_LEFT:
                    direction = World::directions::LEFT;
                    isValid = true;
                    break;
                case KEY_RIGHT:
                    direction = World::directions::RIGHT;
                    isValid = true;
                    break;
                case QUIT:
                    world->end();
                    break;
                case SKILL_ACTIVATION:
                    world->activateSkill();
                    break;
                case SAVE:
                    world->save();
                    break;
                case NEW_TURN:
                    if (!world->isHumanAlive()) {
                        world->handleTurn();
                        world->draw();
                    }
                    break;
                }
            if (world->isHumanAlive() && isValid) {
                turnCompleted = world->handleTurn(direction);
                if(turnCompleted)
                    world->draw();
            }
        }
    }
	delete generator;
	if(world != nullptr)
		delete world;
	return 0;
}