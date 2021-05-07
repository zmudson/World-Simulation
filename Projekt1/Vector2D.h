#pragma once

#include <string>

class Vector2D {
public:
	Vector2D(int x, int y);
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	std::string toString();
private:
	int x;
	int y;
};

