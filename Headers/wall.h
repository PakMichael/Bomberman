#ifndef WALL_H
#define WALL_H


#include "subordinate.h"
#include "entity.h"
#include "primitive.h"

class Wall :public Subordinate, public Entity {



public:
	Rectangle* rectangle;

public:
	Wall(float x, float y, float width, float height);
	bool intersects(Rectangle* rec);

private:
	~Wall() { delete rectangle; };

	void constructCarcass();

	void moveTo(int key) {}
	void nudge() {}



};


#endif