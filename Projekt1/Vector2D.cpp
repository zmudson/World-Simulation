#include "Vector2D.h"

Vector2D::Vector2D(int x, int y) {
	this->x = x;
	this->y = y;
}

int Vector2D::getX() const{
	return x;
}

void Vector2D::setX(int x) {
	this->x = x;
}

int Vector2D::getY() const{
	return y;
}

void Vector2D::setY(int y){
	this->y = y;
}

std::string Vector2D::toString() {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}