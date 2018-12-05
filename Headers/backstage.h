#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include "figure.h"
#include "primitive.h"
#include <vector>
#include "subordinate.h"
#include <algorithm>
#include <graph.h>
#include "block.h"
#include "dynamic_block.h"


class Backstage : public Subordinate, public Supervisor {
	bool map[20][20];
	Block* wall;
	Block* corridor;
	DynamicBlock* bombs;
	Graph* g;
	float relativeCellWidth;
	float relativeCellHeight;
	Point2D* mapDisplacements;


public:
	Backstage(float relativeCellSizeX, float relativeCellSizeY);
	Block* getWall();
	Block* getCorridor();
	DynamicBlock* getBombs();
	void displaceMap(Point2D* pos);

private:
	void constructLabyrinth();
	void constructWalls();
	void createRemarks();
};




#endif