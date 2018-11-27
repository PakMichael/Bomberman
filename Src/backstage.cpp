#include "backstage.h"

float indx2Grid(int index, float cellSize, int offsetIndex = 0) {
	return index * cellSize + offsetIndex * cellSize;
}

Backstage::Backstage(float relativeCellSizeX, float relativeCellSizeY) {

	for (int a = 0; a < 22; ++a) {
		borders.push_back(new Figure(indx2Grid(a, relativeCellSizeX, -10), 11 * relativeCellSizeY, relativeCellSizeX, relativeCellSizeY)); // ------
		borders.push_back(new Figure(-11 * relativeCellSizeX, indx2Grid(a, relativeCellSizeY, -10), relativeCellSizeX, relativeCellSizeY)); // |
		borders.push_back(new Figure(10 * relativeCellSizeX, indx2Grid(a, relativeCellSizeY, -10), relativeCellSizeX, relativeCellSizeY)); //       |
		borders.push_back(new Figure(indx2Grid(a, relativeCellSizeX, -10), -10 * relativeCellSizeY, relativeCellSizeX, relativeCellSizeY)); // _____ 
	}

	constructLabyrinth();

	for (int a = 0; a < 20; ++a) {
		for (int b = 0; b < 20; ++b) {
			if (map[a][b]) {
				borders.push_back(new Figure(indx2Grid(b, relativeCellSizeX, -10), indx2Grid(19-a, relativeCellSizeY, -9), relativeCellSizeX, relativeCellSizeY));
			}
		}
	}
	constructCarcass();
}

bool Backstage::collisionOccured(Figure* activeObj)
{
	for (Figure* stationaryObj : borders) {
		if (activeObj->intersects(stationaryObj->getRectangle())) {
			return true;
		}
	}
	return false;
}

void Backstage::constructCarcass() {

	std::vector<Primitive*> carcass;
	for (int a = 0; a < borders.size(); ++a)
		carcass.push_back(borders[a]->getRectangle());

	assemble(carcass, 4);
}

void Backstage::constructLabyrinth()
{

	for (int a = 0; a < 20; ++a) {
		for (int b = 0; b < 20; ++b) {
			map[a][b] = false;
		}

	}
	g = new Graph();

	for (int a = 0; a < 20; ++a)
		for (int b = 0; b < 20; ++b) {
			g->createNode(a * 20 + b);
		}

	for (int a = 1; a < 20; ++a)
		for (int b = 1; b < 20; ++b) {
			g->connectTwo(a * 20 + b, a * 20 + b - 1);
			g->connectTwo(a * 20 + b, (a - 1) * 20 + b);
		}
	for (int a = 1; a < 20; ++a) {
		g->connectTwo(a * 20, (a - 1) * 20);
		g->connectTwo(a, a - 1);
	}
	DFS* dfs = new DFS();
	dfs->traverse(g, 105, 100);
	for (Node* nd : dfs->visited) {
		int indx = nd->getIndex();
		map[indx / 20][indx - (indx / 20) * 20] = true;
	}

	for (int a = 0; a < 20; ++a) {
		for (int b = 0; b < 20; ++b) {
			std::cout << map[a][b] << ", ";
		}
		std::cout << "\n";
	}



}
