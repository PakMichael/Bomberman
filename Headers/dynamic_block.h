#ifndef DYNAMIC_BLOCK_H
#define DYNAMIC_BLOCK_H


#include "subordinate.h"
#include "block.h"
#include "primitive.h"
 


class DynamicBlock : public Block  {


public:
	DynamicBlock(Point2D* displacements, char* texturePath);


	void placeBombAt(Point2D * pos, Point2D* dimensions);


};


#endif