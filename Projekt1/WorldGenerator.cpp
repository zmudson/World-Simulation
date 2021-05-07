#include "WorldGenerator.h"
#include <iostream>
#include <conio.h>
#include <cctype>
#include <time.h>
#include <fstream>

#define NEW 110 // n - ASCII code
#define LOAD 108 // l - ASCII code
#define QUIT 113 // q - ASCII code
#define BACK_MESSAGE "back"
#define FILE_EXTENSION "txt"
#define MAX_STREAM_LENGTH 10000

World* WorldGenerator::generate() {
	char choice;
	bool isChosen = false;
	World* world = nullptr;
	srand(time(NULL));

	printMenu();

	while (!isChosen) {
		choice = tolower(_getch());
		switch (choice) {
			case NEW: 
				int n, m;
				n = loadDimension("Podaj szerokosc planszy: ");
				m = loadDimension("Podaj wysokosc planszy: ");
				world = new World(n, m);
				isChosen = true;
				break;
			case LOAD: {
				std::string filename;
				filename = loadFilename("Podaj nazwe pliku (bez rozszerzenia): ");
				if (filename != BACK_MESSAGE) {
					world = new World(filename);
					isChosen = true;
				}
				else {
					system("cls");
					printMenu();
				}
				}
				break;
			case QUIT:
				isChosen = true; // leave world as nullptr
				break;
		}
	}
	return world;
}

int WorldGenerator::loadDimension(std::string message) {
	int dimension;
	while (true) {
		std::cout << message;
		std::cin >> dimension;
		if (dimension > 0)
			break;
		std::cin.clear();
		std::cin.ignore(MAX_STREAM_LENGTH, '\n');
		std::cout << "Wymiar musi byc liczba dodatnia!" << std::endl;
	}
	return dimension;
}

std::string WorldGenerator::loadFilename(std::string message) {
	std::string filename;
	bool isCorrect = false;
	while (!isCorrect) {
		std::cout << message;
		std::cin >> filename;
		filename = filename + "." + FILE_EXTENSION;
		std::ifstream file(filename);
		if (file.good()) {
			isCorrect = true;
		}
		else {
			std::cout << "Plik o podanej nazwie nie istnieje!" << std::endl;
			char choice;
			bool isChosen = false;
			while (!isChosen) {
				std::cout << "Czy chcesz powrocic do menu? (t/n)" << std::endl;
				choice = tolower(_getch());
				switch (choice) {
					case 't':
						file.close();
						return BACK_MESSAGE;
					break;
					case 'n':
						isChosen = true;
					break;
				}
			}
		}
		file.close();
	}
	return filename;
}

void WorldGenerator::printMenu() {
	std::cout << "World simulation powered by Dominik Zmuda-Trzebiatowski (184926)" << std::endl;
	std::cout << "Menu:" << std::endl;
	std::cout << "l - wczytaj symulacje" << std::endl;
	std::cout << "n - nowa symulacja" << std::endl;
	std::cout << "q - zakoncz symulacje" << std::endl;
}