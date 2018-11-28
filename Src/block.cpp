#include "block.h"
 



void Block::constructCarcass()
{
	assemble(bricks, 4);
}

Block::Block(char* texPath)
{
	texturePath = texPath ;
}

bool Block::intersects(Rectangle* rec) {
	for (Primitive* r : bricks) {
		if (*static_cast<Rectangle*>(r) == *rec)return true;
	}
	return  false;
}

void Block::addBrick(float posX, float posY, float width, float height)
{
	bricks.push_back(new Rectangle(posX, posY, width, height));
}
