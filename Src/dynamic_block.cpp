#include "dynamic_block.h"

 

 

DynamicBlock::DynamicBlock(Point2D * displacements, char * texturePath) :Block(displacements, texturePath) {



}

 

void DynamicBlock::placeBombAt(Point2D * pos, Point2D* dimensions)
{
	addBrick(pos->getX(), pos->getY(), dimensions->getX(), dimensions->getY());
	constructCarcass();
}
