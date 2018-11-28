#ifndef BLOCK_H
#define BLOCK_H


#include "subordinate.h"
#include "entity.h"
#include "primitive.h"
#include <vector>


class Block :public Subordinate, public Entity {



public:
	std::vector<Primitive*> bricks;

public:
	Block(char* texPath = "Textures/SolidBlock.png");
	bool intersects(Rectangle* rec);
	void  addBrick(float x, float y, float width, float height);
	void constructCarcass();
private:
	~Block() { for (Primitive* ptr : bricks) { delete ptr; } };



	void moveTo(int key) {}
	void nudge() {}



};


#endif