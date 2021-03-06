#ifndef BLOCK_H
#define BLOCK_H


#include "subordinate.h"
#include "entity.h"
#include "primitive.h"
#include <vector>


class Block :public Subordinate, public Entity {

	Point2D* displacements;

public:
	std::vector<Primitive*> bricks;

public:
	Block(Point2D* displacements, char* texPath = "Textures/SolidBlock.png");
	bool intersects(Rectangle* rec);
	void  addBrick(float x, float y, float width, float height);
	void  addBrick(Rectangle* rec);
	void removeBrick(Rectangle* rec);
	void constructCarcass();
protected:
	~Block();



	void moveTo(int key) {}
	void nudge();



};


#endif