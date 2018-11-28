#include "backstage.h"

float indx2Grid(int index, float cellSize, int offsetIndex = 0) {
	return index * cellSize + offsetIndex * cellSize;
}

Backstage::Backstage(float relativeCellSizeX, float relativeCellSizeY) {

	constructLabyrinth();
	constructWalls();
	for (int a = 0; a < 22; ++a) {
		walls.push_back(new Wall(indx2Grid(a, relativeCellSizeX, -10), 11 * relativeCellSizeY, relativeCellSizeX, relativeCellSizeY)); // ------
		walls.push_back(new Wall(-11 * relativeCellSizeX, indx2Grid(a, relativeCellSizeY, -10), relativeCellSizeX, relativeCellSizeY)); // |
		walls.push_back(new Wall(10 * relativeCellSizeX, indx2Grid(a, relativeCellSizeY, -10), relativeCellSizeX, relativeCellSizeY)); //       |
		walls.push_back(new Wall(indx2Grid(a, relativeCellSizeX, -10), -10 * relativeCellSizeY, relativeCellSizeX, relativeCellSizeY)); // _____ 
	}

	for (int a = 0; a < 20; ++a) {
		for (int b = 0; b < 20; ++b) {
			if (!map[a][b]) {
				walls.push_back(new Wall(indx2Grid(b, relativeCellSizeX, -10), indx2Grid(19 - a, relativeCellSizeY, -9), relativeCellSizeX, relativeCellSizeY));
			}
		}
	}
	constructCarcass();
}

bool Backstage::collisionOccured(Figure* activeObj)
{
	//for (Wall* wall : walls) {
	//	if (activeObj->intersects(wall->rectangle)) {
	//		return true;
	//	}
	//}
	return false;
}

void Backstage::constructCarcass() {

	std::vector<Primitive*> carcass;
	//for (int a = 0; a < borders.size(); ++a)
	//	carcass.push_back(borders[a]->getRectangle());
	for (int a = 0; a < walls.size(); ++a)
		carcass.push_back(walls[a]->rectangle);
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

void Backstage::constructWalls()
{

	for (int b = 0; b < 7; ++b) {
		int index = rand() % 20;
		for (int a = 0; a < 20; ++a) {
			map[a][index] = false;
			map[a][index] = false;
			map[index][a] = false;
			map[index][a] = false;
		}
	}

}



 