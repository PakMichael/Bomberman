#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include "figure.h"
#include "primitive.h"
#include <vector>
#include "subordinate.h"
#include <algorithm>
#include <graph.h>
#include "wall.h"


class Backstage : public Entity, public Subordinate {
	bool map[20][20];
	std::vector<Wall*> walls;
	Graph* g;

public:
	Backstage(float relativeCellSizeX, float relativeCellSizeY);
	void moveTo(int key) {}
	void nudge() {}
	bool collisionOccured(Figure* fig);
private:
	void constructCarcass();
	void constructLabyrinth();
	void constructWalls();
};




#endif