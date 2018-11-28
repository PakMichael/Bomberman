#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include "figure.h"
#include "primitive.h"
#include <vector>
#include "subordinate.h"
#include <algorithm>
#include <graph.h>
#include "block.h"


class Backstage : public Subordinate {
	bool map[20][20];
	Block* wall;
	Block* corridor;
	Graph* g;
	float relativeCellWidth;
	float relativeCellHeight;

public:
	Backstage(float relativeCellSizeX, float relativeCellSizeY);
	Block* getWall();
	Block* getCorridor();


private:
	void constructLabyrinth();
	void constructWalls();
};




#endif